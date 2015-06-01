require "./#{File.dirname($0)}/util.rb"

class String
  def mirror_chomp
    if length <= 0 then self
    elsif /^[\s]+(.*)$/ =~ self then $1.mirror_chomp
    elsif /^(.*)[\s]+$/ =~ self then $1.mirror_chomp
    else self
    end
  end

  def extract_dbt_value
    case self
      when /^([0-9]+)\-([0-9]+)\-([0-9]+)$/,
           /^DATE\('([0-9]+)\-([0-9]+)\-([0-9]+)'\)$/ 
                  then ($1.to_i*10000+$2.to_i*100+$3.to_i).to_f;
      when /^([\-\+]?[0-9]+\.[0-9]*e?[\-\+]?[0-9]*)$/ then $1.to_f;
      when /^([\-\+]?[0-9]+)$/ then $1.to_f;
      when /^'([a-zA-Z0-9_#\-,.:;!? ]*)'$/ then $1
      when /^([a-zA-Z0-9_#\-,.:;!? ]*)$/ then $1
      else self
    end
  end
end

class OcamlDB < Hash
  def initialize(db_string, reverse_key = true)
    tok = Tokenizer.new(
      db_string,
        /\[|\]|->|DATE\('[0-9]+\-[0-9]+\-[0-9]+'\)|[\-\+]?[0-9]+\.?[0-9]*e[\-\+]?[0-9]*|[\-\+]?[0-9]+\.?[0-9]*|'[a-zA-Z0-9_#\-\s,.:;!?]*'|<pat=[^>]*>|SingleMap|DoubleMap|TupleList|\(|\)|;/
    )
    tok.next while (tok.peek == "SingleMap") || tok.peek == "DoubleMap" || tok.peek == "TupleList" || (tok.peek == "(");
    raise "Not A Database (Got '#{tok.peek}')" unless tok.peek == "[";
    tree = TreeBuilder.new(tok) do |tree, t|
      case t
        when "[" then tree.push
        when "]" then tree.pop
        when "->" then 
          lhs = tree.backtrack;
          rhs = tree.next_leaf;
          tree.insert [lhs, rhs]
        when "." then 
          lhs = tree.backtrack;
          if /[0-9]+/ =~ tree.peek 
            then tree.insert "#{lhs}.#{tree.next_leaf}"
            else tree.insert lhs
          end
          
        when /<pat=.*/, ";" then #ignore
        else tree.insert t 
      end
    end
    OcamlDB.parse_named_forest(tree.pop.pop, reverse_key, self);
  end
  
  def OcamlDB.parse_named_forest(elements, reverse, into = Hash.new)
    elements.each do |k, contents|
      val = 
        case contents
          when Array then
            v = parse_named_forest(contents);
            v unless v.length == 0;
          when /nan/ then
            v = 0;
          when /[\-\+]?[0-9]+\.[0-9]*e?[\-\+]?[0-9]*/ then 
            v = contents.to_f;
            v unless v == 0.0;
          when /[\-\+]?[0-9]+/ then
            v = contents.to_f;
            v unless v == 0;
          else raise "Unknown value type: '#{contents}'"
        end
      k = k.map { |k_elem| k_elem.mirror_chomp.extract_dbt_value }
      k = k.reverse if reverse;
      into[k] = val unless val.nil?;
    end
    into;
  end
end

class CppDB < Hash
  def initialize(db_string)
    tok = Tokenizer.new(db_string, /<\/?[^>]+>|[^<]+/);
    loop do 
      tok.tokens_up_to(/<item[^>]*>/);
      break unless /<item[^>]*>/ =~ tok.last;
      fields = Array.new;
      curr_field = -1;
      active = false;
      tok.tokens_up_to("</item>").each do |t|
        case t
          when /<\/.*>/ then active = false;
          when /<(.*)>/ then curr_field = curr_field+1; fields[curr_field] = ""; active = true;
          else
            fields[curr_field] = fields[curr_field] + t if active;
        end
      end
      self[
        fields[0..-2].map { |k| k.extract_dbt_value }
      ] = fields[-1].to_f unless fields[-1].to_f == 0.0
    end
  end
end