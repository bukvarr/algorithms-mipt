#include <cmath>

#include <iomanip>

#include <iostream>

class Prefixes {
public:
    int size;
    void ArrayConstructing();
    void RequestProcessing();
    double* prefix_array;
};

void Prefixes::ArrayConstructing() {
  double t;
  std::cin >> t;
  prefix_array[0] = pow(t, (double)1 / static_cast<double>(size));
  for (int i = 1; i < size; ++i) {
    std::cin >> t;
    prefix_array[i] =
            pow(t, (double)1 / static_cast<double>(size)) * prefix_array[i - 1];
  }
}

void Prefixes::RequestProcessing() {
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
    double t = pow(product, static_cast<double>(size) / (double)(r - l + 1));
    std::cout << std::fixed << std::setprecision(10) << t << std::endl;
  }
}

int main() {
  Prefixes prefix_products;
  std::cin >> prefix_products.size;
  prefix_products.prefix_array = new double[prefix_products.size];
  prefix_products.ArrayConstructing();
  prefix_products.RequestProcessing();
  delete[] prefix_products.prefix_array;
}