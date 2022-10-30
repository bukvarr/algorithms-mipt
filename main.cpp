#include <cmath>

#include <iomanip>

#include <iostream>

class PrefixArray {
 public:
  int size;
  double* prefix_array;
  void InsertGM(int index, double t);
  double GetGM(int left_index, int right_index);
  PrefixArray(int size) : size(size), prefix_array(new double[size]){};
  ~PrefixArray() { delete[] prefix_array; }
};

double PrefixArray::GetGM(int left_index, int right_index) {
  double product;
  if (left_index == 0) {
    product = prefix_array[right_index];
  } else {
    product = prefix_array[right_index] / prefix_array[left_index - 1];
  }
  double t = pow(product, static_cast<double>(size) /
                          (double)(right_index - left_index + 1));
  return t;
}

void PrefixArray::InsertGM(int index, double t) {
  if (index == 0) {
    prefix_array[0] = pow(t, (double)1 / static_cast<double>(size));
    return;
  }
  prefix_array[index] =
          pow(t, (double)1 / static_cast<double>(size)) * prefix_array[index - 1];
}

int main() {
  int size;
  std::cin >> size;
  PrefixArray prefix_products(size);
  for (int i = 0; i < prefix_products.size; ++i) {
    double t;
    std::cin >> t;
    prefix_products.InsertGM(i, t);
  }
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    int left_index, right_index;
    std::cin >> left_index >> right_index;
    double ans = prefix_products.GetGM(left_index, right_index);
    std::cout << std::fixed << std::setprecision(10) << ans << '\n';
  }
}