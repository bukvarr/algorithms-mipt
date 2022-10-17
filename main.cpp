/* Дан массив неотрицательных целых 64-битных чисел.
  Количество чисел не больше 106.
  Отсортировать массив методом поразрядной сортировки LSD по байтам. */

#include <iostream>

class SortingTools {
public:
		int size;
		unsigned long long* numbers = new unsigned long long[1'000'000];
		unsigned long long* sorted_numbers = new unsigned long long[1'000'000];
		unsigned long long* bytes_array = new unsigned long long[1'000'000];
		void Input();
		void ByteSorting(const int& byte);
		void LsdSorting();
		void Output();
		unsigned long long FindByte(unsigned long long num, const int& byte);
};

void SortingTools::Input() {
	for (int i = 0; i < size; ++i) {
		std::cin >> numbers[i];
	}
}

unsigned long long SortingTools::FindByte(unsigned long long num,
                                          const int& byte) {
	num = num >> (byte << 3);
	return num % 256;
}

void SortingTools::ByteSorting(const int& byte) {
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

void SortingTools::LsdSorting() {
	for (int i = 0; i < 8; ++i) {
		ByteSorting(i);
	}
}

void SortingTools::Output() {
	for (int i = 0; i < size; ++i) {
		std::cout << numbers[i] << " ";
	}
}

int main() {
	std::ios_base::sync_with_stdio(false); //speeding up cin
	std::basic_ostream<char, std::char_traits<char> >* aboba = 0; //speeding up cin
	std::cin.tie(aboba); //speeding up cin
	SortingTools sort;
	std::cin >> sort.size;
	sort.Input();
	sort.LsdSorting();
	sort.Output();
	delete[] sort.numbers;
	delete[] sort.sorted_numbers;
	delete[] sort.bytes_array;
}