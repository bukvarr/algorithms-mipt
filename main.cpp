//Нужно с помощью быстрой сортировки отсортировать массив.

//Запрещено инклудить algorithm!

#include <iostream>

int Partition(int* array, int pivot, int left_border, int right_border) {
  int left_index = left_border;
  int right_index = right_border - 1;
  while (right_index != left_index) {
    if (array[left_index] >= pivot && array[right_index] <= pivot) {
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

void QuickSort(int* array, int left_border, int right_border) {
  if (right_border == left_border) {
    return;
  }
  int pivot;
  int random = 0;
  if (right_border > left_border) {
    random = std::rand() % (right_border - left_border);
  }
  pivot = array[left_border + random];
  int p = Partition(array, pivot, left_border, right_border);
  if (right_border - left_border <= 2) {
    return;
  }
  QuickSort(array, left_border, p);
  QuickSort(array, p, right_border);
}

int main() {
  int size;
  std::cin >> size;
  int* array = new int[size];
  for (int i = 0; i < size; ++i) {
    int t;
    std::cin >> t;
    array[i] = t;
  }
  QuickSort(array, 0, size);
  for (int i = 0; i < size; ++i) {
    std::cout << array[i] << std::endl;
  }
  delete[] array;
}