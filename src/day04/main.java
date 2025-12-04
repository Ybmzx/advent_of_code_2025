import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

public class main {
  private static List<String> grid;
  private static int[][] directions = new int[][] {
    {0, 1},
    {1, 0},
    {0, -1},
    {-1, 0},
    {-1, -1},
    {1, 1},
    {1, -1},
    {-1, 1}
  };

  private static boolean canAccess(int x, int y) {
    if (grid.get(x).charAt(y) != '@') {
      return false;
    }

    int count = 0;
    for (int i = 0; i < directions.length; i++) {
      int x1 = x + directions[i][0];
      int y1 = y + directions[i][1];
      if (x1 < 0 || x1 >= grid.size() || y1 < 0 || y1 >= grid.get(x1).length()) {
        continue;
      }
      if (grid.get(x1).charAt(y1) == '@') {
        count += 1;
      }
    }
    return count < 4;
  }

  private static int solve() {
    int count = 0;
    ArrayList<int[]> canAccesses = new ArrayList<>();
    for (int i = 0; i < grid.size(); i++) {
      for (int j = 0; j < grid.get(i).length(); j++) {
        if (canAccess(i, j)) {
          canAccesses.add(new int[] {i, j});
          count += 1;
        }
      }
    }
    for (int[] pos : canAccesses) {
      grid.set(pos[0], grid.get(pos[0]).substring(0, pos[1]) + '.' + grid.get(pos[0]).substring(pos[1] + 1));
    }
    return count;
  }

  private static int part01() {
    return solve();
  }

  // 其实可以用 queue 优化, 但我懒
  private static int part02() {
    int count = 0;
    while (true) {
      int c = solve();
      if (c == 0) {
        break;
      }
      count += c;
    }
    return count;
  }

  public static void main(String[] args) throws IOException {
    grid = Files.readAllLines(Paths.get("input.in"));
    if (args.length == 0 || args[0].equals("part01")) {
      System.out.println(part01());
    }
    else if (args[0].equals("part02")) {
      System.out.println(part02());
    }
    else {
      System.out.println("Invalid argument");
    }
  }
}