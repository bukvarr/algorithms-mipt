/* Реализуйте двоичную кучу.

Обработайте запросы следующих видов:

    insert x — вставить целое число x в кучу;

    getMin — вывести значение минимального элемента в куче (гарантируется, что к этому моменту куча не пуста);

    extractMin — удалить минимальный элемент из кучи, выводить его не нужно (гарантируется, что к этому моменту куча не пуста);

    decreaseKey i Δ — уменьшить число, вставленное на i-м запросе, на целое число Δ≥0
    (гарантируется, что i-й запрос был осуществлён ранее, являлся запросом добавления, а добавленное на этом шаге число всё ещё лежит в куче).
    Обратите внимание, число i равно номеру запроса среди всех запросов, а не только среди запросов добавления!

Можете считать, что в любой момент времени все числа, хранящиеся в куче, попарно различны, а их количество не превышает 100'000.
*/

#include <iostream>

class HeapTools {
public:
		std::pair<long long int, int> heap_array[100'000];
		int requests_order[1'000'000];
		int size;
		void SiftDown(int index);
		void SiftUp(int index);
		void RequestProcessing();
		void Insert(long long int x, int request_number);
		void DecreaseKey();
		void ExtractMin();
};

void HeapTools::SiftDown(int index) {
	while (2 * index + 1 < size) {
		int u = 2 * index + 1;
		if (u + 1 < size && heap_array[u + 1].first < heap_array[u].first) {
			++u;
		}
		if (heap_array[u].first < heap_array[index].first) {
			std::swap(heap_array[index], heap_array[u]);
			std::swap(requests_order[heap_array[index].second],
			          requests_order[heap_array[u].second]);
			index = u;
		} else {
			break;
		}
	}
}

void HeapTools::SiftUp(int index) {
	while (index > 0) {
		if (heap_array[index] < heap_array[(index - 1) / 2]) {
			std::swap(heap_array[index], heap_array[(index - 1) / 2]);
			std::swap(requests_order[heap_array[index].second],
			          requests_order[heap_array[(index - 1) / 2].second]);
			index = (index - 1) / 2;
		} else {
			break;
		}
	}
}

void HeapTools::Insert(long long int x, int request_number) {
	requests_order[request_number] = size;
	heap_array[size].first = x;
	heap_array[size].second = request_number;
	SiftUp(size++);
}

void HeapTools::DecreaseKey() {
	int request_number;
	long long int delta;
	std::cin >> request_number >> delta;
	int index = requests_order[request_number];
	heap_array[index].first -= delta;
	SiftUp(index);
}

void HeapTools::ExtractMin() {
	std::swap(heap_array[0], heap_array[--size]);
	std::swap(requests_order[heap_array[0].second],
	          requests_order[heap_array[size].second]);
	SiftDown(0);
}

void HeapTools::RequestProcessing() {
	int q;
	std::cin >> q;
	for (int i = 1; i <= q; ++i) {
		std::string s;
		std::cin >> s;
		if (s == "insert") {
			long long int x;
			std::cin >> x;
			Insert(x, i);
		}
		if (s == "getMin") {
			std::cout << heap_array[0].first << std::endl;
		}
		if (s == "decreaseKey") {
			DecreaseKey();
		}
		if (s == "extractMin") {
			ExtractMin();
		}
	}
}

int main() {
	HeapTools heap;
	heap.size = 0;
	std::ios_base::sync_with_stdio(false);
	std::basic_ostream<char, std::char_traits<char> >* aboba = 0;
	std::cin.tie(aboba);
	heap.RequestProcessing();
}