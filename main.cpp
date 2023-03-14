#include <iostream>

#include <vector>

int DynamicConstruction(int n, std::vector<int>& max_floor) {
  int k = static_cast<int>(max_floor.size()) - 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = k; j >= 1; --j) {
      max_floor[j] += max_floor[j - 1];
      if (max_floor[j] >= n) {
        return i;
      }
    }
  }
  return -1;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  if (k == 0 && n > 1) {
    std::cout << -1;
    return 0;
  }
  if (n == 1) {
    std::cout << 0;
    return 0;
  }
  std::vector<int> max_floor(k + 1, 1);
  int ans = DynamicConstruction(n, max_floor);
  std::cout << ans;
}