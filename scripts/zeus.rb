#!/usr/bin/env ruby
require "tempfile"
require "getoptlong"

class Array
  def to_h
    ret = Hash.new;
    each { |k,v| ret[k] = v; }
    return ret;
  end
end

class String
  def String.rand_alpha_chr
    c = (rand(26)+65).chr;
    if (rand(2)) != 0 then c else c.downcase end;
  end
  
  def String.rand_chr
    x = (rand(10+26+26+1))
    case x
      when (0...10) then (48+x).chr
      when (10...62) then rand_alpha_chr
      when 62 then '_'
    end
  end

  def String.random(len = (rand(5)+5))
    rand_alpha_chr.to_s + 
      ((1...len).map { |i| rand_chr }.join(""))
  end
end


class RelationField
  attr_reader :type, :name;
  
  def initialize(name, type = :int)
    @name = name;
    @type = type;
  end
  
  def shuffle
    RelationField.new(@name,
      case @type
        when :int then 
          case rand(10)
            when 0,1,2,3,4,5,6,7 then :int
            when 8 then :float
            when 9 then :string
          end
        when :float then
          case rand(5)
            when 0,1,2,3 then :float
            when 4 then :string
          end
        else @type
      end
    )  
  end
  
  def to_s
    "#{@name} #{@type}"
  end
end

class Field
  attr_reader :source, :name
  
  def initialize(name, source = nil)
    @name = name;
    @source = source;
  end
  
  def to_s
    if source.nil? then name else "#{source}.#{name}" end
  end
end

class Relation
  attr_reader :name, :source, :base_name, :is_stream;
  
  def initialize(name, fields, source, is_stream, base_name = nil);
    @name = name;
    @base_name = base_name || name;
    @fields = fields;
    @source = source;
    @is_stream = is_stream;
  end
  
  def shuffle
    Relation.new(
      String.random,
      fields.map { |f| f.shuffle },
      source,
      (random(5) == 0)
    )
  end
  
  def rename(new_name)
    Relation.new(new_name, @fields, @source, @is_stream, @base_name);
  end
  
  def fields
    @fields.map { |f| Field.new(f.name, @name) }
  end
  
  def field_names
    @fields.map { |f| f.name }
  end
  
  def to_defn
    "CREATE #{@is_stream ? "STREAM" : "TABLE"} #{@name}(#{@fields.join(", ")})"+
    " FROM FILE '#{@source}'"+
    " LINE DELIMITED"+
    " CSV();"
  end
  
  def to_from
    if (name == base_name) then name else "#{base_name} #{name}" end
  end
end

class Expression
  def initialize(op, *rest) 
    @op = op;
    @params = rest;
  end
  
  def is_agg?
    case @op
      when :plus     then not (@params.index {|i| i.is_agg?}).nil?
      when :minus    then not (@params.index {|i| i.is_agg?}).nil?
      when :div      then not (@params.index {|i| i.is_agg?}).nil?
      when :prod     then not (@params.index {|i| i.is_agg?}).nil?
      when :sumagg   then true
      when :countagg then true
      when :avgagg   then true
      when :var      then false
      when :const    then false
      else raise "Unknown op type #{@op}"
    end
  end
  
  def to_s
    case @op
      when :plus     then "(#{@params.join("+")})";
      when :minus    then "(#{@params.join("-")})";
      when :div      then "(#{@params.join("/")})";
      when :prod     then "(#{@params.join("*")})";
      when :sumagg   then "SUM(#{@params[0]})";
      when :countagg then "COUNT(*)";
      when :avgagg   then "AVG(#{@params[0]})";
      when :var      then @params[0].to_s;
      when :const    then @params[0].to_s;
      else raise "Unknown op type #{@op}"
    end
  end
  
  def Expression.random(vars)
    case rand(20)
      when (0...4)   then Expression.new(:const, rand(10))
      when (4...6)   then Expression.new(:const, (rand * 10000).round/100.0)
      when (6...16)  then 
        if vars.length == 0 then Expression.random(vars)
        else vars[rand(vars.length)] 
        end
      when 16        then Expression.new(:plus,
                                *((0..(rand(2)+1)).map do |i|
                                    Expression.random(vars)
                                end))
      when (17..18) then Expression.new(:prod,
                                *((0..(rand(2)+1)).map do |i|
                                    Expression.random(vars)
                                end))
      when 19        then Expression.new(if rand(5) != 0 then :minus else :div end,
                                Expression.random(vars),
                                Expression.random(vars)
                              )
    end
  end
  
  def Expression.random_agg(gb_vars, vars)
    agg = 
      case rand(10)
        when (0...7) then Expression.new(:sumagg, Expression.random(vars))
        when (7...9) then Expression.new(:countagg)
        when 9       then Expression.new(:avgagg, Expression.random(vars))
      end
    if (rand(3)) != 0 then agg else 
      agg_vars = gb_vars + ([agg]*(gb_vars.length+1))
      ret_agg = Expression.new(:const, 0);
      while not ret_agg.is_agg? do
        ret_agg = Expression.random(agg_vars)
      end
      ret_agg
    end
  end
  
  def Expression.mk_var(v)
    Expression.new(:var, v)
  end
end

class Condition
  attr_reader :op, :params;
  
  def initialize(op, *rest)
    @op = op;
    @params = rest;
  end
  
  def to_s
    case @op
      when :and then "(#{@params.join(" AND ")})"
      when :or  then "(#{@params.join(" OR ")})"
      when :cmp then "#{@params[1]} #{@params[0]} #{@params[2]}"
      when :not then "(NOT #{@params[0]})"
    end
  end
  
  def Condition.random_cmp(vars)
    Condition.new(:cmp,
      case rand(10)
        when (0...5) then "="
        when 5       then "<"
        when 6       then "<="
        when 7       then ">"
        when 8       then ">="
        when 9       then "<>"
        else raise "Unhandled comparison case"
      end,
      Expression.random(vars),
      Expression.random(vars)
    )
  end
  
  def Condition.random(vars)
    case rand(10)
      when (0...6) then Condition.random_cmp(vars)
      when 6,7     then Condition.new(:and,
                                *((0..(rand(2)+1)).map do |i|
                                    Condition.random(vars)
                                end))
      when 8       then Condition.new(:or,
                                *((0..(rand(2)+1)).map do |i|
                                    Condition.random(vars)
                                end))
      when 9       then Condition.new(:not, Condition.random(vars))
    end
  end
end

class Target
  attr_reader :expr, :name;
  
  def initialize(expr, name = String.random)
    @expr = expr
    @name = Field.new(name)
  end
  
  def source=(s)
    @name = Field.new(@name.name, s)
  end
  
  def fields
    [@name]
  end
  
  def to_s
    "#{expr} AS #{name.name}"
  end
  
  def Target.random(vars)
    Target.new(Expression.random(vars), String.random);
  end
  
  def Target.randlist(vars, explength = 4)
    [Target.random(vars)] + (
      if rand(explength) == 0 then [] else Target.randlist(vars) end
    )
  end
end

class WildcardTarget
  attr_reader :source, :fields;
  def initialize(fields, source = nil)
    @source = source
  end
  
  def source=(s)
    @fields = @fields.map do |f|
      Field.new(f.name, s)
    end
  end
  
  def to_s
    if @source.nil? then "*" else "#{source}.*" end
  end
end

class Query
  attr_reader :name, :targets, :sources, :condition, :group_by;
  attr_writer :name;
  
  def initialize(targets, sources, condition, group_by)
    @targets = targets;
    @sources = sources;
    @condition = condition;
    @group_by = group_by;
  end
  
  def fields
    @targets.map { |t| t.fields }.flatten(1);
  end
  
  def fields
    field_names.map { |f| f.name }
  end
  
  def Query.random_source(relations, used_names = Hash.new(false))
    rel = relations[rand(relations.length)];
    chosen_name = if rand(2) == 0 then rel.base_name else String.random end
    while used_names[chosen_name] do
      chosen_name = String.random
    end
    used_names[chosen_name] = true;
    rel.rename(chosen_name)
  end
  
  def Query.random_sources(relations, used_names = Hash.new(false))
    return [] if relations.length == 0;
    (0..rand(3)).map { |i| Query.random_source(relations, used_names) }
  end
  
  def Query.source_targets(sources, qname = nil)
    tgts = 
      if rand(4) == 0 then
        [WildcardTarget.new(sources.map {|s|s.fields}.flatten(1))]
      else
        sources.map do |s|
          if rand(4) == 0 then
            [WildcardTarget.new(s.fields, s.name)]
          else
            s.fields.
              map { |t| if rand(3) == 0 then nil else t end }.
              compact
          end
        end.flatten
      end
    tgts.each { |t| t.source = qname } if qname
    tgts
  end
  
  def Query.random_nonagg(relations, scope = [])
    scope_rels = scope.map {|s| [s.name, true]}.to_h;
    sources = Query.random_sources(relations, scope_rels);
    source_vars = sources.map {|s| s.fields }.flatten(1);
    scope_vars = scope.map {|s| s.fields }.flatten(1);
    
    q_vars = source_vars+scope_vars
    
    targets = case rand(5)
      when 0 then Query.source_targets(sources); #simple targets
      when 1 then Query.source_targets(sources) + Target.randlist(q_vars,2); #mixed
      else        Target.randlist(q_vars); #target expressions
    end
    
    if rand(4) == 0 then
      condition = nil
    else
      condition = Condition.random(q_vars);
    end
  
    Query.new(targets, sources, condition, nil);
  end
  
  def Query.random(relations, scope = [])
    Query.random_nonagg(relations, scope);
  end
  
  def to_s
    (if @targets.length > 0 then "SELECT #{targets.join(", ")}" else "SELECT 1" end)+
    (if @sources.length > 0 then " FROM #{sources.map{|s|s.to_from}.join(", ")}" else "" end)+
    (if @condition.nil? then "" else " WHERE #{condition}" end)+
    (if @group_by.nil? then "" else " GROUP BY #{group_by.join(", ")}" end)+
    ";"
  end
end

$global_rels = [
  Relation.new("R", [
    RelationField.new("A", :int),
    RelationField.new("B", :int)
  ], "@@DATA@@/r.dat", true),
  Relation.new("S", [
    RelationField.new("B", :int),
    RelationField.new("C", :int)
  ], "@@DATA@@/s.dat", true),
  Relation.new("T", [
    RelationField.new("C", :int),
    RelationField.new("D", :int)
  ], "@@DATA@@/t.dat", true)
];


class Test
  def Test.run(params)
    prng_seed  = params.fetch(:seed,       rand(100000000));
    puts "-- seed = #{prng_seed}"
    srand(prng_seed);
    q = Query.random($global_rels)
    # puts q.to_s;
    query_string = "#{$global_rels.map { |rel| rel.to_defn }.join("\n")}\n#{q}\n"
    puts query_string
  end 
end

$params = Hash.new;

GetoptLong.new(['-s', GetoptLong::REQUIRED_ARGUMENT]).each do |opt,arg|
  case opt when '-s' then $params[:seed] = arg.to_i; end
end

Test.run($params);
