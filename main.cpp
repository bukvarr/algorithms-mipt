/* Дан массив неотрицательных целых 64-битных чисел.
  Количество чисел не больше 106.
  Отсортировать массив методом поразрядной сортировки LSD по байтам. */

#include <iostream>

class BigNumbersArray {
 private:
  int size_;
  unsigned long long *numbers_;
  unsigned long long *sorted_numbers_;
  unsigned long long *bytes_array_;

  void ByteSorting(const int& byte) {
    int counting_array[256] = {};
    for (int i = 0; i < size_; ++i) {
      bytes_array_[i] = FindByte(numbers_[i], byte);
      ++counting_array[bytes_array_[i]];
    }
    for (int i = 1; i < 256; ++i) {
      counting_array[i] += counting_array[i - 1];
    }
    for (int i = size_ - 1; i >= 0; --i) {
      sorted_numbers_[--counting_array[bytes_array_[i]]] = numbers_[i];
    }
    for (int i = 0; i < size_; ++i) {
      numbers_[i] = sorted_numbers_[i];
    }
  }

  unsigned long long FindByte(unsigned long long num,
                                               const int& byte) {
    num = num >> (byte << 3);
    return num % 256;
  }

 public:
  BigNumbersArray(int size) : size_(size), numbers_(new unsigned long long[size_]),
                              sorted_numbers_(new unsigned long long[size_]),
                              bytes_array_(new unsigned long long[size_]){};

  void Sort() {
    for (int i = 0; i < 8; ++i) {
      ByteSorting(i);
    }
  }

  void ArrayConstricting(unsigned long long t, int index) {
    numbers_[index] = t;
  }

  unsigned long long GiveNumber(int index) {
    return sorted_numbers_[index];
  }

  ~BigNumbersArray() {
    delete[] numbers_;
    delete[] sorted_numbers_;
    delete[] bytes_array_;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false); //speeding up cin
  std::basic_ostream<char, std::char_traits<char> >* aboba = 0; //speeding up cin
  std::cin.tie(aboba); //speeding up cin
  int size;
  std::cin >> size;
  BigNumbersArray array(size);
  for (int i = 0; i < size; ++i) {
    unsigned long long t;
    std::cin >> t;
    array.ArrayConstricting(t, i);
  }
  array.Sort();
  for (int i = 0; i < size; ++i) {
    std::cout << array.GiveNumber(i) << '\n';
  }
}