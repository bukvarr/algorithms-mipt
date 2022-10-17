/*

 Реализуйте структуру данных, способную выполнять операции ниже.
Напишите программу, реализовав все указанные здесь методы. Возможные команды для программы:

    insert n — добавить в структуру число n (1 ≤ n ≤ 109) (значение n задается после команды).
    Программа должна вывести ok.

    extract_min — удалить из структуры минимальный элемент. Программа должна вывести его значение.

    get_min — программа должна вывести значение минимального элемента, не удаляя его из структуры.

    extract_max — удалить из структуры максимальный элемент. Программа должна вывести его значение.

    get_max — программа должна вывести значение миаксимального элемента, не удаляя его из структуры.

    size — программа должна вывести количество элементов в структуре.

    clear — Программа должна очистить структуру и вывести ok.

Перед исполнением операций extract_min, extract_max, get_min и get_max программа должна проверять,
 содержится ли в структуре хотя бы один элемент.

Если во входных данных встречается операция extract_min, extract_max, get_min или get_max,
 и при этом в структуре нет ни одного элемента, то программа должна вместо числового значения вывести строку error.
*/

#include <iostream>

class HeapTools {
public:
		std::pair<int, int> max_heap[200'000];
		std::pair<int, int> min_heap[200'000];
		int requests_order_min[200'000];
		int requests_order_max[200'000];
		int size;
		void SiftDownMin(int index);
		void SiftDownMax(int index);
		void SiftUpMin(int index);
		void SiftUpMax(int index);
		void Insert(int request_number);
		void ExtractMin();
		void ExtractMax();
		void RequestProcessing();
		void GetMin();
		void GetMax();
		void Clear();
};

void HeapTools::SiftDownMin(int index) {
	while (2 * index + 1 < size) {
		int u = 2 * index + 1;
		if (u + 1 < size && min_heap[u + 1].first < min_heap[u].first) {
			++u;
		}
		if (min_heap[u].first < min_heap[index].first) {
			std::swap(min_heap[index], min_heap[u]);
			std::swap(requests_order_min[min_heap[index].second],
			          requests_order_min[min_heap[u].second]);
			index = u;
		} else {
			break;
		}
	}
}

void HeapTools::SiftDownMax(int index) {
	while (2 * index + 1 < size) {
		int u = 2 * index + 1;
		if (u + 1 < size && max_heap[u + 1].first > max_heap[u].first) {
			++u;
		}
		if (max_heap[u].first > max_heap[index].first) {
			std::swap(max_heap[index], max_heap[u]);
			std::swap(requests_order_max[max_heap[index].second],
			          requests_order_max[max_heap[u].second]);
			index = u;
		} else {
			break;
		}
	}
}

void HeapTools::SiftUpMin(int index) {
	while (index > 0) {
		if (min_heap[index].first < min_heap[(index - 1) / 2].first) {
			std::swap(min_heap[index], min_heap[(index - 1) / 2]);
			std::swap(requests_order_min[min_heap[index].second],
			          requests_order_min[min_heap[(index - 1) / 2].second]);
			index = (index - 1) / 2;
		} else {
			break;
		}
	}
}

void HeapTools::SiftUpMax(int index) {
	while (index > 0) {
		if (max_heap[index].first > max_heap[(index - 1) / 2].first) {
			std::swap(max_heap[index], max_heap[(index - 1) / 2]);
			std::swap(requests_order_max[max_heap[index].second],
			          requests_order_max[max_heap[(index - 1) / 2].second]);
			index = (index - 1) / 2;
		} else {
			break;
		}
	}
}

void HeapTools::Insert(int request_number) {
	int x;
	std::cin >> x;
	int index = size;
	++size;
	requests_order_min[request_number] = index;
	requests_order_max[request_number] = index;
	min_heap[index].first = x;
	min_heap[index].second = request_number;
	max_heap[index].first = x;
	max_heap[index].second = request_number;
	SiftUpMin(index);
	SiftUpMax(index);
	std::cout << "ok" << std::endl;
}

void HeapTools::ExtractMin() {
	if (size == 0) {
		std::cout << "error" << std::endl;
		return;
	}
	std::cout << min_heap[0].first << std::endl;
	int index = requests_order_max[min_heap[0].second];
	--size;
	if (index != size) {
		std::swap(max_heap[index], max_heap[size]);
		std::swap(requests_order_max[max_heap[index].second],
		          requests_order_max[max_heap[size].second]);
		SiftDownMax(index);
		SiftUpMax(index);
	}
	std::swap(min_heap[0], min_heap[size]);
	std::swap(requests_order_min[min_heap[0].second],
	          requests_order_min[min_heap[size].second]);
	SiftDownMin(0);
}

void HeapTools::ExtractMax() {
	if (size == 0) {
		std::cout << "error" << std::endl;
		return;
	}
	std::cout << max_heap[0].first << std::endl;
	int index = requests_order_min[max_heap[0].second];
	--size;
	if (index != size) {
		std::swap(min_heap[index], min_heap[size]);
		std::swap(requests_order_min[min_heap[index].second],
		          requests_order_min[min_heap[size].second]);
		SiftDownMin(index);
		SiftUpMin(index);
	}
	std::swap(max_heap[0], max_heap[size]);
	std::swap(requests_order_max[max_heap[0].second],
	          requests_order_max[max_heap[size].second]);
	SiftDownMax(0);
}

void HeapTools::GetMin() {
	if (size == 0) {
		std::cout << "error" << std::endl;
		return;
	}
	std::cout << min_heap[0].first << std::endl;
}

void HeapTools::GetMax() {
	if (size == 0) {
		std::cout << "error" << std::endl;
		return;
	}
	std::cout << max_heap[0].first << std::endl;
}

void HeapTools::Clear() {
	size = 0;
	std::cout << "ok" << std::endl;
}

void HeapTools::RequestProcessing() {
	int q;
	std::cin >> q;
	for (int i = 1; i <= q; ++i) {
		std::string s;
		std::cin >> s;
		if (s == "insert") {
			Insert(i);
		}
		if (s == "get_min") {
			GetMin();
		}
		if (s == "get_max") {
			GetMax();
		}
		if (s == "extract_min") {
			ExtractMin();
		}
		if (s == "extract_max") {
			ExtractMax();
		}
		if (s == "size") {
			std::cout << size << std::endl;
		}
		if (s == "clear") {
			Clear();
		}
	}
}

int main() {
	HeapTools heap;
	heap.size = 0;
	std::ios_base::sync_with_stdio(false); //speeding up cin
	std::basic_ostream<char, std::char_traits<char> >* aboba = 0; //speeding up cin
	std::cin.tie(aboba); //speeding up cin
	heap.RequestProcessing();
}