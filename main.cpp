
/*В этой задаче вам необходимо найти k-ую порядковую статистику (k-ое по неубыванию) числовой последовательности A,
элементы которой задаются следующим образом: A[i] = (A[i-1] * 123 + A[i-2] * 45) % (10^7 + 4321) */


#include <iostream>

class Array {
 private:
  int* array_;

  int Partition(int pivot, int left_border, int right_border) {
    int left_index = left_border;
    int right_index = right_border - 1;
    while (right_index != left_index) {
      if (array_[left_index] > pivot && array_[right_index] <= pivot) {
        std::swap(array_[left_index], array_[right_index]);
      }
      if (array_[left_index] <= pivot) {
        ++left_index;
      }
      if (pivot <= array_[right_index] && right_index != left_index) {
        --right_index;
      }
    }
    if (array_[left_index] < pivot) {
      return left_index + 1;
    }
    return left_index;
  }

 public:
  Array(int size, int a0, int a1) : array_(new int[size]) {
    array_[0] = a0;
    array_[1] = a1;
    for (int i = 2; i < size; ++i) {
      array_[i] = (array_[i - 1] * 123 + array_[i - 2] * 45) % (10'004'321);
    }
  }

  int GetStatistic(int left_border, int right_border, int k) {
    if (right_border - left_border == 1) {
      return array_[left_border];
    }
    if (right_border - left_border == 2) {
      if (k == 2) {
        return (std::max(array_[left_border], array_[right_border - 1]));
      }
      if (array_[left_border] <= array_[right_border - 1]) {
        return array_[left_border];
      }
      return array_[right_border - 1];
    }
    int random = 0;
    if (right_border != left_border) {
      random = std::rand() % (right_border - left_border);
    }
    int p = Partition(array_[left_border + random], left_border, right_border);
    if (p - left_border >= k) {
      return (GetStatistic(left_border, p, k));
    }
    return (GetStatistic(p, right_border, k - p + left_border));
  }

  ~Array() { delete[] array_; }
};

int main() {
  int size, k;
  std::cin >> size >> k;
  int a0, a1;
  std::cin >> a0 >> a1;
  Array array(size, a0, a1);
  int k_statistic = array.GetStatistic(0, size, k);
  std::cout << k_statistic;
}