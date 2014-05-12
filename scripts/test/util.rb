class Tokenizer
  def initialize(string, token, input_source = nil)
    @tokens = string.scan(token);
    @last = nil;
    @input_source = input_source;
    @string = string;
  end
  
  def scan
    while @tokens.size > 0
      if !(yield @tokens.shift) then break; end
    end
  end
  
  def peek
    if @tokens.size > 0 then @tokens[0]
    else nil; end
  end
  
  def next
    @last = 
      if @tokens.size > 0 then @tokens.shift
      else nil; end
  end
  
  def clear_whitespace
    @tokens.delete_if { |t| t.chomp == "" };
  end
  
  def last
    @last;
  end
  
  def more?
    @tokens.size > 0;
  end
  
  def flatten
    @tokens = @tokens.flatten;
  end
  
  def assert_next(token, errstr = nil)
    case token
      when String then raise_error(errstr || "Expected '#{token}' but found '#{last}'") unless self.next == token
      when Array  then raise_error(errstr || "Expected '#{token.join("','")}' but found '#{last}'") unless token.include? self.next;
    end
    self.last;
  end
  
  def raise_error(errstr);
    errstr = "#{errstr} (line #{@input_source.lineno})" if @input_source;
    errstr = "#{errstr} (#{@string})" unless @input_source;
    raise "Parse Error: #{errstr}";
  end
  
  def tokens_up_to(token)
    ret = Array.new;
    match = if token.is_a? String 
              then proc { |t| token == t } 
              else proc { |t| token =~ t } 
            end
    while (more? && (not match.call(self.next)))
      ret.push(last)
    end
    ret;
  end
end

class TreeBuilder
  def initialize(tokenizer = nil, &parser)
    @stack = [[]]
    @tok = tokenizer;
    @parser = parser;
    if(@parser and @tok) then
      next_leaf(false);
    end
  end
  
  def next_leaf(should_backtrack = true)
    start_depth = depth;
    while @tok.more?
      @parser.call(self, @tok.next);
      break if depth == start_depth;
    end
    backtrack if should_backtrack;
  end
  
  def depth
    @stack.length-1;
  end
  
  def insert(v)
    @stack[-1].push(v); v;
  end
  
  def append(v)
    @stack[-1][-1] += v;
  end
  
  def push
    v = Array.new;
    insert(v)
    @stack.push(v);
  end
  
  def pop
    @stack.pop;
  end
  
  def peek
    @tok.peek
  end
  
  def backtrack
    @stack[-1].pop;
  end
  
  def to_a
    @stack[0].clone;
  end
end

class String
  def pad(padlen,str=" ")
    if self.length >= padlen then self
    else
      self + (str * ((padlen - self.length) / str.length).to_i)
    end
  end
end

class Array
  def to_h
    ret = Hash.new;
    each { |k,v| ret[k] = v; }
    return ret;
  end

  def unzip
    ret = Array.new;
    each_index do |i|
      ret.push Array.new(i) while ret.length < self[i].length
      ret.each_index do |j|
        ret[j][i] = self[i][j]
      end
    end
    return ret;
  end

  def fold(i)
    each { |x| i = yield(i,x); }
    i;
  end
  
  def sum
    fold(0) { |i,x| i+x }
  end
  
  def max(&cmp)
    fold(nil) { |i,x| (i.nil? || (cmp.nil? ? (i < x) : cmp(i,x))) ? x : i; }
  end

  def avg
    sum.to_f / length.to_f
  end

  def stddev
    Math.sqrt((avg ** 2 - (map{|i| i.to_f ** 2}.avg)).abs)
  end
  
  def reduce(&reducer)
    ret = Hash.new;
    each do |k,v|
      ret[k] = Array.new unless ret.has_key? k;
      ret[k].push(v);
    end
    if reducer.nil? then ret
    else
      ret.to_a.collect do |k,vs|
        reducer.call(y, vs)
      end.to_h
    end
  end
  
  def tabulate
    widths = 
      unzip.map { |col| col.map { |v| v.to_s.length }.max }
    head_foot = "+" + ("-" * (2 + widths.sum + (widths.length-1) * 3)) + "+";
    head_foot + "\n" +
      map do |row| 
        "| " + (widths.zip(row).map { |w, v| v.to_s.pad(w) }.join(" | ")) + " |"
      end.join("\n") +
      "\n" + head_foot;
  end
  
  def s?
    if self.length > 1 then "s" else "" end;
  end
  
  def intersect(other)
    self.clone.delete_if { |e| not other.include? e };
  end
  
  def power_set
    if empty? then [[]]
    elsif self.length == 1 then
      [[], [self[0]]];
    else
      child = self[1..-1].power_set;
      child + child.map { |c| [self[0]] + c };
    end
  end

  def grep(pattern, &block)
    ret = [];
    if block.nil? 
    then each { |l| ret.push(l) if pattern =~ l; }
    else each { |l| match = pattern.match(l);
                    ret.push(block.call(match)) if match; }
    end
    ret
  end
end

class Hash
  def intersect(other)
    keys.find_all { |k| other.has_key?(k) }
  end
  
  def bar_graph_dataset(bar = 0.5, set_sep = 1.0, bar_sep = 0.2)
    curr_width = 0;
    tics = collect do |human,data|
      next_delta = data.length * bar + (data.length - 1) * bar_sep;
      curr_width += next_delta + set_sep;
      "\"#{human}\" #{curr_width - next_delta / 2}"
    end

    curr_width = 0;
    points = values.collect do |data|
      curr_width += set_sep - bar_sep
      data.collect do |point|
        curr_width += bar_sep + bar;
        [curr_width - bar / 2, point]
      end
    end.unzip;

    return ["(#{tics.join(', ')})" , points, "[0:#{curr_width+set_sep}]"];
  end
end

