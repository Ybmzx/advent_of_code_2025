# lines :: Array[String]
def parse_data_part01 ( lines )
  lines = lines.select { |line| line.strip.length > 0 }
  matrix = lines[...-1].map { |line|
    line.split(' ').map{ |x| x.to_i }
  }.transpose
  operators = lines[-1].split(' ')
  return matrix, operators
end

def parse_data_part02 ( lines )
  lines = lines.select { |line| line.strip.length > 0 }.map { |line| line[...-1] }
  operators = lines[-1].split(' ')

  # like -> ["  4", "431", "   ", "175", "581"]
  numbers_as_string = lines[...-1]
    .map(&:chars)
    .transpose
    .map(&:join)

  matrix = [[]]

  # 以空白段为分隔符分割 numbers_as_string 到 matrix
  # 可以看作 matrix = numbers_as_string.split { |x| x.strip.length <= 0 }
  # 但是 Array 没有 split 函数, 所以写成这样了
  numbers_as_string.each { |x|
    if x.strip.length <= 0
      matrix.push []
      next
    end
    matrix[-1].push x.to_i
  }

  if matrix.length > 0 && matrix[-1].length <= 0
    matrix.pop
  end

  return matrix, operators
end

def solve ( matrix, operators )
  result_sum = 0
  matrix.each_with_index { |numbers, index|
    op = operators[index]
    result_sum += op == '+' ? numbers.sum : numbers.reduce(:*)
  }
  result_sum
end

def main
  if ARGV.length == 0 || (ARGV.length >= 1 && (ARGV[0] == "part01" || ARGV[0] == "part02"))
    lines = IO.readlines("input.in")
    if ARGV.length == 0 || ARGV[0] == "part01"
      matrix, operators = parse_data_part01(lines)
    else
      matrix, operators = parse_data_part02(lines)
    end
    puts solve(matrix, operators)
  else
    puts "Invalid Arguments."
  end
end

main
