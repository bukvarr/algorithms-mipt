#include <iostream>

class Heap {
 private:
  std::pair<long long, int> heap_array_[100'000];
  int* requests_order_;
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
  Heap(int rq) : requests_order_(new int[rq]) {}

  void Insert(long long x, int request_number) {
    requests_order_[request_number] = size_;
    heap_array_[size_].first = x;
    heap_array_[size_].second = request_number;
    SiftUp(size_++);
  }

  long long GetMin() const { return heap_array_[0].first; }

  void DecreaseKey(int request_number, long long delta) {
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

  ~Heap() { delete[] requests_order_; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::basic_ostream<char, std::char_traits<char> >* aboba = 0;
  std::cin.tie(aboba);
  int q;
  std::cin >> q;
  Heap heap(q + 1);
  for (int i = 1; i <= q; ++i) {
    std::string s;
    std::cin >> s;
    if (s == "insert") {
      long long x;
      std::cin >> x;
      heap.Insert(x, i);
    }
    if (s == "decreaseKey") {
      int request_number;
      long long delta;
      std::cin >> request_number >> delta;
      heap.DecreaseKey(request_number, delta);
    }
    if (s == "extractMin") {
      heap.ExtractMin();
    }
    if (s == "getMin") {
      std::cout << heap.GetMin() << '\n';
    }
  }
}