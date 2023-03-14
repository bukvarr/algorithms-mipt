#include <iostream>

#include <vector>

void DynamicConstructing(std::vector<std::vector<int>>& dp,
                         const std::vector<int>& weight,
                         const std::vector<int>& cost) {
  int n = static_cast<int>(dp.size());
  int m = static_cast<int>(dp[0].size()) - 1;
  for (int j = 0; j < weight[0]; ++j) {
    dp[0][j] = 0;
  }
  for (int j = weight[0]; j <= m; ++j) {
    dp[0][j] = cost[0];
  }
  for (int i = 1; i < n; ++i) {
    for (int j = 0; j <= m; ++j) {
      dp[i][j] = (j >= weight[i] ? std::max(dp[i - 1][j - weight[i]] + cost[i],
                                            dp[i - 1][j])
                                 : dp[i - 1][j]);
    }
  }
}

std::vector<int> IndexesGathering(const std::vector<std::vector<int>>& dp,
                                  const std::vector<int>& weight) {
  int n = static_cast<int>(dp.size());
  int m = static_cast<int>(dp[0].size()) - 1;
  int max_w = 0;
  for (int j = 1; j <= m; ++j) {
    if (dp[n - 1][j] > dp[n - 1][max_w]) {
      max_w = j;
    }
  }
  std::vector<int> indexes;
  for (int i = n - 1; i >= 0; --i) {
    if (i == 0) {
      if (dp[0][max_w] != 0) {
        indexes.push_back(1);
      }
      break;
    }
    if (dp[i][max_w] != dp[i - 1][max_w]) {
      indexes.push_back(i + 1);
      max_w -= weight[i];
    }
  }
  return indexes;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> weight(n);
  std::vector<int> cost(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> weight[i];
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> cost[i];
  }
  std::vector<std::vector<int>> dp(n, std::vector<int>(m + 1, 0));
  DynamicConstructing(dp, weight, cost);
  std::vector<int> indexes = IndexesGathering(dp, weight);
  for (size_t i = indexes.size(); i >= 1; --i) {
    std::cout << indexes[i - 1] << '\n';
  }
}