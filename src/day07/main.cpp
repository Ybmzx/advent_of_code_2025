#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <cstring>
#include <set>
#include <numeric>

using Point = std::pair<int, int>;
using Grid = std::vector<std::string>;

std::vector<std::string> readAllLinesFromFile(const std::string& filename) {
  std::vector<std::string> lines;
  std::ifstream file;
  file.open(filename);
  assert(file.is_open());

  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  return lines;
}

/// @brief 找到起点 S 所在位置, 若未找到则为 { -1, -1 }.
/// @param grid 网格
/// @return S 所在位置, 若未找到则为 { -1, -1 }.
Point findStartingPoint(const Grid& grid) {
  for (int i = 0; i < grid.size(); i ++) {
    auto&& row = grid[i];
    std::size_t pos = row.find('S');
    if (pos != std::string::npos) {
      return Point { i, pos };
    }
  }

  return Point { -1, -1 };
}

bool isInvalidPosition(const Point& pos, const Grid& grid) {
  return pos.first < 0 || pos.first >= grid.size() || pos.second < 0 || pos.second >= grid[pos.first].size();
}

int part01(const Grid& grid) {
  Point start = findStartingPoint(grid);
  if (start == Point { -1, -1 }) {
    throw std::runtime_error("Error: Cannot find starting point.");
  }

  std::set<Point> splitPositions;

  auto beamDownward = [](Point start, const Grid& grid, std::set<Point>& splitPositions, auto&& self) -> void {
    if (isInvalidPosition(start, grid)) {
      return;
    }

    for (int i = start.first; i < grid.size(); i ++) {
      if (grid[i][start.second] == '^') {
        // 如果该处被一个快子束撞击过了, 跳过该处
        if (splitPositions.count({ i, start.second })) {
          break;
        }
        splitPositions.insert({ i, start.second });
        self({ i, start.second - 1 }, grid, splitPositions, self);
        self({ i, start.second + 1 }, grid, splitPositions, self);
        break;
      }
    }
  };

  beamDownward(start, grid, splitPositions, beamDownward);

  return splitPositions.size();
}

long long part02(const Grid& grid) {
  Point start = findStartingPoint(grid);
  if (start == Point { -1, -1 }) {
    throw std::runtime_error("Error: Cannot find starting point.");
  }

  // f[i][j] 经过 i,j 的路径数量
  std::vector<std::vector<long long>> f(grid.size(), std::vector<long long>(grid[0].size(), 0));

  for (int i = 0; i < grid.size(); i ++) {
    for (int j = 0; j < grid[i].size(); j ++) {
      if (Point { i, j } == start) {
        f[i][j] = 1;
        continue;
      }
      if (i - 1 < 0) {
        continue;
      }
      if (grid[i - 1][j] != '^') {
        f[i][j] = f[i - 1][j];
      }
      // 左侧和右侧
      for (int k = -1; k <= 1; k += 2) {
        // 若一侧是 ^, 则继承他上方的路径数
        if (!isInvalidPosition({ i, j + k }, grid) &&
            !isInvalidPosition({ i - 1, j + k }, grid) &&
            grid[i][j + k] == '^') {
          f[i][j] += f[i - 1][j + k];
        }
      }
    }
  }

  return std::accumulate(f.back().begin(), f.back().end(), 0ll);
}

int main(int argc, char* argv[]) {
  // Grid = std::vector<std::string>
  Grid grid = readAllLinesFromFile("input.in");
  // 去除最后空行
  while (!grid.empty() && grid.back().empty()) {
    grid.pop_back();
  }

  if (argc == 1 || strcmp(argv[1], "part01") == 0) {
    std::cout << part01(grid) << '\n';
  }
  else if (strcmp(argv[1], "part02") == 0) {
    std::cout << part02(grid) << '\n';
  }
  else {
    fprintf(stderr, "Error: Invalid argument.\n");
    return 1;
  }
}