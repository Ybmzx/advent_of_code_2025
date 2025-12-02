from collections.abc import Callable
import sys

def sum_invaild_ids(content: str, check_id: Callable[[str], bool]) -> int:
  ranges = content.split(',')
  invalid_ids_sum = 0
  for rng in ranges:
    left, right = rng.split('-')
    for cur_id in range(int(left), int(right) + 1):
      if not check_id(str(cur_id)):
        invalid_ids_sum += cur_id

  return invalid_ids_sum

def part01(content: str) -> int:
  def check_id(id_str: str) -> bool:
    if len(id_str) % 2 == 1:
      return True
    half = len(id_str) // 2
    left = id_str[:half]
    right = id_str[half:]
    return left != right

  return sum_invaild_ids(content, check_id)

def part02(content: str) -> int:
  def is_repeated_pattern(id_str: str, id_len: int):
    if len(id_str) % id_len != 0:
      return False
    for i in range(0, (len(id_str) // id_len) - 1):
      if id_str[i * id_len:(i + 1) * id_len] != id_str[(i + 1) * id_len:(i + 2) * id_len]:
        return False
    return True
  def check_id(id_str: str) -> bool:
    for id_len in range(1, len(id_str) // 2 + 1):
      if len(id_str) % id_len != 0:
        continue
      if is_repeated_pattern(id_str, id_len):
        return False
    return True

  return sum_invaild_ids(content, check_id)

if __name__ == "__main__":
  with open("input.in", "r") as f:
    content = f.read()
  if "part01" in sys.argv or len(sys.argv) == 1:
    print(part01(content))
  elif "part02" in sys.argv:
    print(part02(content))
  else:
    print("Invalid argument")