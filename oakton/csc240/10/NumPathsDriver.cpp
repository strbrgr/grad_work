#include "iostream"

int NumPaths(int row, int col, int n) {
  // Base case
  if (row == n && col == n) {
    return 1;
  }

  // Base case
  if (row > n || col > n) {
    return 0;
  }

  return NumPaths(row + 1, col, n) + NumPaths(row, col + 1, n);
}

int NumPathsMemoized(int row, int col, int n, int memo[4][4]) {
  // Base case
  if (row == n && col == n) {
    return 1;
  }

  // Base case
  if (row > n || col > n) {
    return 0;
  }

  if (memo[row][col] != -1) {
    return memo[row][col];
  }
  memo[row][col] = NumPathsMemoized(row + 1, col, n, memo) +
                   NumPathsMemoized(row, col + 1, n, memo);
  return memo[row][col];
}

int main() {
  int memo[4][4];
  for (int i = 0; i <= 4; ++i) {
    for (int j = 0; j <= 4; ++j) {
      memo[i][j] = -1;
    }
  }

  auto start_num_paths_timer = std::chrono::steady_clock::now();
  int number_of_paths = NumPaths(1, 1, 4);
  auto end_num_paths_timer = std::chrono::steady_clock::now();
  auto diff_num_paths_timer = end_num_paths_timer - start_num_paths_timer;

  auto start_num_paths_memo_timer = std::chrono::steady_clock::now();
  int number_of_paths_memo = NumPathsMemoized(1, 1, 4, memo);
  auto end_num_paths_memo_timer = std::chrono::steady_clock::now();
  auto diff_num_paths_memo_timer =
      end_num_paths_memo_timer - start_num_paths_memo_timer;

  std::cout << number_of_paths << std::endl;
  std::cout << number_of_paths_memo << std::endl;

  std::cout << "Time in ms to compute without memo: " << std::endl;
  std::cout
      << std::chrono::duration<double, std::milli>(diff_num_paths_timer).count()
      << " ms" << std::endl;

  std::cout << "Time in ms to compute with memo: " << std::endl;
  std::cout << std::chrono::duration<double, std::milli>(
                   diff_num_paths_memo_timer)
                   .count()
            << " ms" << std::endl;
  return 0;
}
