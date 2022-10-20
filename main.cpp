#include <cmath>

#include <iomanip>

#include <iostream>

double prefix_array[3 * 100'000];

void ArrayConstructing(const int& n) {
  double t;
  std::cin >> t;
  prefix_array[0] = pow(t, (double)1 / (double)n);
  for (int i = 1; i < n; ++i) {
    std::cin >> t;
    prefix_array[i] = pow(t, (double)1 / (double)n) * prefix_array[i - 1];
  }
}

void RequestProcessing(const int& n) {
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int l, r;
    std::cin >> l >> r;
    double product;
    if (l == 0) {
      product = prefix_array[r];
    } else {
      product = prefix_array[r] / prefix_array[l - 1];
    }
    double t = pow(product, (double)n / (double)(r - l + 1));
    std::cout << std::fixed << std::setprecision(10) << t << std::endl;
  }
}

int main() {
  int n;
  std::cin >> n;
  ArrayConstructing(n);
  RequestProcessing(n);
}