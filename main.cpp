#include <iostream>

int Partition(int* a, int left_border, int right_border) {
  int left_index = left_border;
  int right_index = right_border - 1;
  int pivot = a[right_index];
  while (left_index != right_index) {
    if (a[left_index] > pivot && a[right_index] <= pivot) {
      a[left_index] += a[right_index];
      a[right_index] = a[left_index] - a[right_index];
      a[left_index] -= a[right_index];
    }
    if (a[left_index] <= pivot) {
      ++left_index;
    } else if (a[right_index] >= pivot) {
      --right_index;
    }
  }
  return left_index;
}

void QuickSort(int*a, int left_border, int right_border) {
  int p = Partition(a, left_border, right_border);
  if (right_border - left_border <= 2) {
    return;
  }
  QuickSort(a, left_border, p);
  QuickSort(a, p, right_border);
}

int main() {
  int n;
  std::cin >> n;
  int a[100];
  for (int i = 0; i < n; ++i) {
    int t;
    std::cin >> t;
    a[i] = t;
  }
  QuickSort(a, 0, n);
  for (int i = 0; i < n; ++i) {
    std::cout << a[i] << " ";
  }
}

