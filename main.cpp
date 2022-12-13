#include <iostream>

struct Node {
 public:
  int value;
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
          : heap_array_(new Node[std::min(rq, 200'000)]),
            requests_order_(new int[rq]) {}

  void Insert(long long x, int request_number);

  long long GetMin() const { return heap_array_[0].value; }

  void DecreaseKey(int request_number, long long delta);

  void ExtractKey(int request_number);

  void ExtractMin();

  int GetRequestNumOfMin() { return heap_array_[0].request_number; }

  int Size() { return size_; }

  void Clear() { size_ = 0; }

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

void Heap::ExtractKey(int request_number) {
  int index = requests_order_[request_number];
  heap_array_[index].value = heap_array_[0].value - 1;
  SiftUp(index);
  ExtractMin();
}

void Heap::ExtractMin() {
  std::swap(heap_array_[0], heap_array_[--size_]);
  std::swap(requests_order_[heap_array_[0].request_number],
            requests_order_[heap_array_[size_].request_number]);
  SiftDown(0);
}

void Insert(int request_number, int value, Heap& max_heap, Heap& min_heap) {
  max_heap.Insert(-value, request_number);
  min_heap.Insert(value, request_number);
}

int ExtractMin(Heap& max_heap, Heap& min_heap) {
  int min = min_heap.GetMin();
  int request_number = min_heap.GetRequestNumOfMin();
  max_heap.ExtractKey(request_number);
  min_heap.ExtractMin();
  return min;
}

int ExtractMax(Heap& max_heap, Heap& min_heap) {
  int max = -max_heap.GetMin();
  int request_number = max_heap.GetRequestNumOfMin();
  min_heap.ExtractKey(request_number);
  max_heap.ExtractMin();
  return max;
}

int GetMin(const Heap& min_heap) { return min_heap.GetMin(); }

int GetMax(const Heap& max_heap) { return -max_heap.GetMin(); }

void Clear(Heap& max_heap, Heap& min_heap) {
  min_heap.Clear();
  max_heap.Clear();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::basic_ostream<char, std::char_traits<char> >* aboba = 0;
  std::cin.tie(aboba);
  int q;
  std::cin >> q;
  Heap min_heap(q);
  Heap max_heap(q);
  for (int i = 0; i < q; ++i) {
    std::string s;
    std::cin >> s;
    if (s == "insert") {
      int value;
      std::cin >> value;
      Insert(i, value, max_heap, min_heap);
      std::cout << "ok" << '\n';
      continue;
    }
    if (s == "size") {
      std::cout << min_heap.Size() << '\n';
      continue;
    }
    if (s == "clear") {
      Clear(min_heap, max_heap);
      std::cout << "ok" << '\n';
      continue;
    }
    if (min_heap.Size() == 0) {
      std::cout << "error" << '\n';
      continue;
    }
    if (s == "get_min") {
      std::cout << GetMin(min_heap) << '\n';
      continue;
    }
    if (s == "get_max") {
      std::cout << GetMax(max_heap) << '\n';
      continue;
    }
    if (s == "extract_min") {
      std::cout << ExtractMin(max_heap, min_heap) << '\n';
      continue;
    }
    if (s == "extract_max") {
      std::cout << ExtractMax(max_heap, min_heap) << '\n';
      continue;
    }
  }
}