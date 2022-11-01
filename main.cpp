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

class Heap {
 private:
  std::pair<long long, int> heap_array_[100'000];
  int requests_order_[1'000'000];
  int size_ = 0;

  void SiftDown(int index) {
    while (2 * index + 1 < size_) {
      int u = 2 * index + 1;
      if (u + 1 < size_ && heap_array_[u + 1].first < heap_array_[u].first) {
        ++u;
      }
      if (heap_array_[u].first < heap_array_[index].first) {
        std::swap(heap_array_[index], heap_array_[u]);
        std::swap(requests_order_[heap_array_[index].second],
                  requests_order_[heap_array_[u].second]);
        index = u;
      } else {
        break;
      }
    }
  }

  void SiftUp(int index) {
    while (index > 0) {
      if (heap_array_[index] < heap_array_[(index - 1) / 2]) {
        std::swap(heap_array_[index], heap_array_[(index - 1) / 2]);
        std::swap(requests_order_[heap_array_[index].second],
                  requests_order_[heap_array_[(index - 1) / 2].second]);
        index = (index - 1) / 2;
      } else {
        break;
      }
    }
  }

 public:
  void Insert(long long x, int request_number) {
    requests_order_[request_number] = size_;
    heap_array_[size_].first = x;
    heap_array_[size_].second = request_number;
    SiftUp(size_++);
  }

  long long GetMin() const { return heap_array_[0].first; }

  void DecreaseKey() {
    int request_number;
    long long delta;
    std::cin >> request_number >> delta;
    int index = requests_order_[request_number];
    heap_array_[index].first -= delta;
    SiftUp(index);
  }

  void ExtractMin() {
    std::swap(heap_array_[0], heap_array_[--size_]);
    std::swap(requests_order_[heap_array_[0].second],
              requests_order_[heap_array_[size_].second]);
    SiftDown(0);
  }
};

void RequestProcessing(std::string s, int request_number, Heap& heap) {
  if (s == "insert") {
    long long x;
    std::cin >> x;
    heap.Insert(x, request_number);
  }
  if (s == "decreaseKey") {
    heap.DecreaseKey();
  }
  if (s == "extractMin") {
    heap.ExtractMin();
  }
}

int main() {
  Heap heap;
  std::ios_base::sync_with_stdio(false);
  std::basic_ostream<char, std::char_traits<char> >* aboba = 0;
  std::cin.tie(aboba);
  int q;
  std::cin >> q;
  for (int i = 1; i <= q; ++i) {
    std::string s;
    std::cin >> s;
    if (s != "getMin") {
      RequestProcessing(s, i, heap);
    } else {
      std::cout << heap.GetMin() << '\n';
    }
  }
}