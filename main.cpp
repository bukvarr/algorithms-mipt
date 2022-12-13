#include <iostream>

struct Node {
    long long value;
    int request_number;
};

class Heap {
 private:
  Node* heap_array_;
  int* requests_order_;
  int size_ = 0;

  void SiftDown(int index);

  void SiftUp(int index);

 public:
  Heap(int rq)
          : heap_array_(new Node[std::min(rq, 100'000)]),
            requests_order_(new int[rq]) {}

  void Insert(long long x, int request_number);

  long long GetMin() const { return heap_array_[0].value; }

  void DecreaseKey(int request_number, long long delta);

  void ExtractMin();

  ~Heap() {
    delete[] heap_array_;
    delete[] requests_order_;
  }
};

void Heap::SiftDown(int index) {
  while (2 * index + 1 < size_) {
    int u = 2 * index + 1;
    if (u + 1 < size_ && heap_array_[u + 1].value < heap_array_[u].value) {
      ++u;
    }
    if (heap_array_[u].value < heap_array_[index].value) {
      std::swap(heap_array_[index], heap_array_[u]);
      std::swap(requests_order_[heap_array_[index].request_number],
                requests_order_[heap_array_[u].request_number]);
      index = u;
    } else {
      break;
    }
  }
}

void Heap::SiftUp(int index) {
  while (index > 0) {
    if (heap_array_[index].value < heap_array_[(index - 1) / 2].value) {
      std::swap(heap_array_[index], heap_array_[(index - 1) / 2]);
      std::swap(requests_order_[heap_array_[index].request_number],
                requests_order_[heap_array_[(index - 1) / 2].request_number]);
      index = (index - 1) / 2;
    } else {
      break;
    }
  }
}

void Heap::Insert(long long x, int request_number) {
  requests_order_[request_number] = size_;
  heap_array_[size_].value = x;
  heap_array_[size_].request_number = request_number;
  SiftUp(size_++);
}

void Heap::DecreaseKey(int request_number, long long delta) {
  int index = requests_order_[request_number];
  heap_array_[index].value -= delta;
  SiftUp(index);
}

void Heap::ExtractMin() {
  std::swap(heap_array_[0], heap_array_[--size_]);
  std::swap(requests_order_[heap_array_[0].request_number],
            requests_order_[heap_array_[size_].request_number]);
  SiftDown(0);
}

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