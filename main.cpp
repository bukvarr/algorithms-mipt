#include <iostream>

#include <vector>

void DynamicConstruction(const std::vector<long long>& a, std::vector<int>& dp,
                         std::vector<int>& max_pos) {
  size_t n = a.size();
  for (size_t i = 1; i < n; ++i) {
    size_t l = 0;
    size_t r = n;
    while (r - l > 1) {
      size_t m = (l + r) / 2;
      if (dp[m] == -1 || a[dp[m]] < a[i]) {
        r = m;
      } else {
        l = m;
      }
    }
    if (a[dp[l]] >= a[i]) {
      dp[l + 1] = i;
      max_pos[i] = l + 1;
    } else {
      if (l + 1 == n || dp[l + 1] == -1) {
      }
      dp[l] = i;
      max_pos[i] = l;
    }
  }
}

std::vector<int> IndexesGathering(const std::vector<int>& dp,
                                  const std::vector<int>& max_pos) {
  int n = static_cast<int>(dp.size());
  int length = 0;
  for (int i = n - 1; i > 0; --i) {
    if (dp[i] != -1) {
      length = i;
      break;
    }
  }
  int index = dp[length];
  std::vector<int> vect;
  while (length >= 0) {
    if (max_pos[index] == length) {
      vect.push_back(index + 1);
      --length;
    }
    --index;
  }
  return vect;
}

int main() {
  size_t n;
  std::cin >> n;
  std::vector<long long> a(n);
  std::vector<int> dp(n, -1); //on each iteration max sequence on first i elements with length = 1, ... , n
  std::vector<int> max_pos(n, -1); //max position of element 0 <= i < n
  for (size_t i = 0; i < n; ++i) {
    std::cin >> a[i];
  }
  dp[0] = 0;
  max_pos[0] = 0;
  DynamicConstruction(a, dp, max_pos);
  std::vector<int> indexes = IndexesGathering(dp, max_pos);
  std::cout << indexes.size() << '\n';
  for (int i = indexes.size() - 1; i >= 0; --i) {
    std::cout << indexes[i] << " ";
  }
}