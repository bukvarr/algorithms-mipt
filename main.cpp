/* Дан массив неотрицательных целых 64-битных чисел.
  Количество чисел не больше 106.
  Отсортировать массив методом поразрядной сортировки LSD по байтам. */

#include <iostream>

unsigned long long FindByte(unsigned long long num, const int& byte) {
  num = num >> (byte << 3);
  return num % 256;
}

void ByteSorting(const int& byte, int size, unsigned long long* numbers,
                 unsigned long long* sorted_numbers,
                 unsigned long long* bytes_array) {
  int counting_array[256] = {};
  for (int i = 0; i < size; ++i) {
    bytes_array[i] = FindByte(numbers[i], byte);
    ++counting_array[bytes_array[i]];
  }
  for (int i = 1; i < 256; ++i) {
    counting_array[i] += counting_array[i - 1];
  }
  for (int i = size - 1; i >= 0; --i) {
    sorted_numbers[--counting_array[bytes_array[i]]] = numbers[i];
  }
  for (int i = 0; i < size; ++i) {
    numbers[i] = sorted_numbers[i];
  }
}

void Sort(int size, unsigned long long* numbers) {
  unsigned long long* sorted_numbers = new unsigned long long[size];
  unsigned long long* bytes_array = new unsigned long long[size];
  for (int i = 0; i < 8; ++i) {
    ByteSorting(i, size, numbers, sorted_numbers, bytes_array);
  }
  delete[] sorted_numbers;
  delete[] bytes_array;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::basic_ostream<char, std::char_traits<char> >* aboba = 0;
  std::cin.tie(aboba);
  int size;
  std::cin >> size;
  unsigned long long* numbers = new unsigned long long[size];
  for (int i = 0; i < size; ++i) {
    unsigned long long t;
    std::cin >> t;
    numbers[i] = t;
  }
  Sort(size, numbers);
  for (int i = 0; i < size; ++i) {
    std::cout << numbers[i] << '\n';
  }
  delete[] numbers;
}