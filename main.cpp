#include <cmath>

#include <iomanip>

#include <iostream>

class Prefixes {
 public:
  int size;
  double RequestProcessing();
  double* prefix_array;
  void ArrayConstructing(int index, double t);
  ~Prefixes() { delete[] prefix_array; }
};

double Prefixes::RequestProcessing() {
  int l, r;
  std::cin >> l >> r;
  double product;
  if (l == 0) {
    product = prefix_array[r];
  } else {
    product = prefix_array[r] / prefix_array[l - 1];
  }
  double t = pow(product, static_cast<double>(size) / (double)(r - l + 1));
  return t;
}

void Prefixes::ArrayConstructing(int index, double t) {
  if (index == 0) {
    prefix_array[0] = pow(t, (double)1 / static_cast<double>(size));
    return;
  }
  prefix_array[index] =
          pow(t, (double)1 / static_cast<double>(size)) * prefix_array[index - 1];
}

int main() {
  Prefixes prefix_products;
  std::cin >> prefix_products.size;
  prefix_products.prefix_array = new double[prefix_products.size];
  for (int i = 0; i < prefix_products.size; ++i) {
    double t;
    std::cin >> t;
    prefix_products.ArrayConstructing(i, t);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    double ans = prefix_products.RequestProcessing();
    std::cout << std::fixed << std::setprecision(10) << ans << '\n';
  }
}