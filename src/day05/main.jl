function parse_string(content::String)::Tuple{Vector{Tuple{Int, Int}}, Vector{Int}}
  id_ranges, queries = split(content, "\n\n")
  id_ranges = [split(id_range, "-") for id_range in split(id_ranges, "\n") if length(id_range) > 0]
  id_ranges = [(parse(Int, id_range[1]), parse(Int, id_range[2])) for id_range in id_ranges]
  queries = [parse(Int, query) for query in split(queries, '\n') if length(query) > 0]

  (id_ranges, queries)
end

function part01(id_ranges::Vector{Tuple{Int, Int}}, queries::Vector{Int})
  count(x -> (any(range -> range[1] <= x <= range[2], id_ranges)), queries)
end

function part02(id_ranges::Vector{Tuple{Int, Int}})
  sort!(id_ranges, by=x -> x[1])
  len = 0
  cur_rng = id_ranges[1]
  for rng in id_ranges
    # 如果当前区间和遍历到的区间不相交, 就计算区间大小并把当前区间设为遍历到的区间
    if cur_rng[2] < rng[1]
      len += cur_rng[2] - cur_rng[1] + 1
      cur_rng = rng
      continue
    # 相交就合并区间(把当前区间扩大), 若是包含关系则不做任何处理
    elseif cur_rng[2] < rng[2]
      cur_rng = (cur_rng[1], rng[2])
    end
  end
  len += cur_rng[2] - cur_rng[1] + 1
  len
end

function main()
  id_ranges, queries = parse_string(read("input.in", String))
  if length(ARGS) == 0 || ARGS[1] == "part01"
    println(part01(id_ranges, queries))
  elseif ARGS[1] == "part02"
    println(part02(id_ranges))
  else
    println("Invailid argument")
  end
end

main()