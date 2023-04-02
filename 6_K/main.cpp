#include <iostream>

#include <vector>

void ConstructingDP(std::vector<std::vector<int>>& dp,
                         const std::vector<int>& weight,
                         const std::vector<int>& cost) {
  size_t n = static_cast<int>(dp.size());
  size_t m = static_cast<int>(dp[0].size()) - 1;
  for (size_t j = 0; j < weight[0]; ++j) {
    dp[0][j] = 0;
  }
  for (size_t j = weight[0]; j <= m; ++j) {
    dp[0][j] = cost[0];
  }
  for (size_t i = 1; i < n; ++i) {
    for (size_t j = 0; j <= m; ++j) {
      dp[i][j] = (j >= weight[i] ? std::max(dp[i - 1][j - weight[i]] + cost[i], //updating max cost
                                            dp[i - 1][j])
                                 : dp[i - 1][j]);
    }
  }
}

std::vector<int> IndexesGathering(const std::vector<std::vector<int>>& dp,
                                  const std::vector<int>& weight) {
  size_t n = static_cast<int>(dp.size());
  size_t m = static_cast<int>(dp[0].size()) - 1;
  size_t max_w = 0;
  for (size_t j = 1; j <= m; ++j) {
    if (dp[n - 1][j] > dp[n - 1][max_w]) {
      max_w = j;
    }
  }
  std::vector<int> indexes;
  for (size_t i = n - 1; i >= 0; --i) {
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
  size_t n, m;
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
  ConstructingDP(dp, weight, cost);
  std::vector<int> indexes = IndexesGathering(dp, weight);
  for (size_t i = indexes.size(); i >= 1; --i) {
    std::cout << indexes[i - 1] << '\n';
  }
}