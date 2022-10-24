
/*В этой задаче вам необходимо найти k-ую порядковую статистику (k-ое по неубыванию) числовой последовательности A,
элементы которой задаются следующим образом: A[i] = (A[i-1] * 123 + A[i-2] * 45) % (10^7 + 4321) */


#include <iostream>

class OrderStatistic {
public:
    int* array;
    int QuickSelect(int left_border, int right_border, int k);
    int Partition(int pivot, int left_border, int right_border);
};

int OrderStatistic::Partition(int pivot, int left_border, int right_border) {
  int left_index = left_border;
  int right_index = right_border - 1;
  while (right_index != left_index) {
    if (array[left_index] > pivot && array[right_index] <= pivot) {
      std::swap(array[left_index], array[right_index]);
    }
    if (array[left_index] <= pivot) {
      ++left_index;
    }
    if (pivot <= array[right_index] && right_index != left_index) {
      --right_index;
    }
  }
  if (array[left_index] < pivot) {
    return left_index + 1;
  }
  return left_index;
}

int OrderStatistic::QuickSelect(int left_border, int right_border, int k) {
  if (right_border - left_border == 1) {
    return array[left_border];
  }
  if (right_border - left_border == 2) {
    if (k == 2) {
      return (std::max(array[left_border], array[right_border - 1]));
    }
    if (array[left_border] <= array[right_border - 1]) {
      return array[left_border];
    }
    return array[right_border - 1];
  }
  int random = 0;
  if (right_border != left_border) {
    random = std::rand() % (right_border - left_border);
  }
  int p = Partition(array[left_border + random], left_border, right_border);
  if (p - left_border >= k) {
    return (QuickSelect(left_border, p, k));
  }
  return (QuickSelect(p, right_border, k - p + left_border));
}

int main() {
  OrderStatistic find_statistic;
  int size, k;
  std::cin >> size >> k;
  int a0, a1;
  std::cin >> a0 >> a1;
  find_statistic.array = new int[size];
  find_statistic.array[0] = a0;
  find_statistic.array[1] = a1;
  for (int i = 2; i < size; ++i) {
    find_statistic.array[i] =
            (find_statistic.array[i - 1] * 123 + find_statistic.array[i - 2] * 45) %
            (10'004'321);
  }
  int k_statistic = find_statistic.QuickSelect(0, size, k);
  std::cout << k_statistic;
  delete[] find_statistic.array;
}