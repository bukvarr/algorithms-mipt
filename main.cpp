/*

 Реализуйте структуру данных, способную выполнять операции ниже.
Напишите программу, реализовав все указанные здесь методы. Возможные команды для программы:

    insert n — добавить в структуру число n (1 ≤ n ≤ 109) (значение n задается после команды).
    Программа должна вывести ok.

    extract_min — удалить из структуры минимальный элемент. Программа должна вывести его значение.

    get_min — программа должна вывести значение минимального элемента, не удаляя его из структуры.

    extract_max — удалить из структуры максимальный элемент. Программа должна вывести его значение.

    get_max — программа должна вывести значение миаксимального элемента, не удаляя его из структуры.

    size_ — программа должна вывести количество элементов в структуре.

    clear — Программа должна очистить структуру и вывести ok.

Перед исполнением операций extract_min, extract_max, get_min и get_max программа должна проверять,
 содержится ли в структуре хотя бы один элемент.

Если во входных данных встречается операция extract_min, extract_max, get_min или get_max,
 и при этом в структуре нет ни одного элемента, то программа должна вместо числового значения вывести строку error.
*/

#include <iostream>

struct Node {
 public:
  int value;
  int request_number;
};

class Heap {
  friend void Insert(int request_number, int value, Heap& max_heap,
                     Heap& min_heap);
  friend int ExtractMin(Heap& max_heap, Heap& min_heap);
  friend int ExtractMax(Heap& max_heap, Heap& min_heap);
  friend void Clear(Heap& max_heap, Heap& min_heap);

 private:
  Node heap_array_[200'000];
  int* requests_order_;
  int size_ = 0;

  void SiftDown(int index) {
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

  void SiftUp(int index) {
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

 public:
  Heap(int rq) : requests_order_(new int[rq]) {}

  void Insert(long long x, int request_number) {
    requests_order_[request_number] = size_;
    heap_array_[size_].value = x;
    heap_array_[size_].request_number = request_number;
    SiftUp(size_++);
  }

  long long GetMin() const { return heap_array_[0].value; }

  void DecreaseKey(int request_number, long long delta) {
    int index = requests_order_[request_number];
    heap_array_[index].value -= delta;
    SiftUp(index);
  }

  void ExtractMin() {
    std::swap(heap_array_[0], heap_array_[--size_]);
    std::swap(requests_order_[heap_array_[0].request_number],
              requests_order_[heap_array_[size_].request_number]);
    SiftDown(0);
  }

  int Size() { return size_; }

  ~Heap() { delete[] requests_order_; }
};

void Insert(int request_number, int value, Heap& max_heap, Heap& min_heap) {
  int index = min_heap.size_;
  ++min_heap.size_;
  ++max_heap.size_;
  min_heap.requests_order_[request_number] = index;
  max_heap.requests_order_[request_number] = index;
  min_heap.heap_array_[index].value = value;
  min_heap.heap_array_[index].request_number = request_number;
  max_heap.heap_array_[index].value = -value;
  max_heap.heap_array_[index].request_number = request_number;
  min_heap.SiftUp(index);
  max_heap.SiftUp(index);
}

int ExtractMin(Heap& max_heap, Heap& min_heap) {
  int min = min_heap.heap_array_[0].value;
  int index = max_heap.requests_order_[min_heap.heap_array_[0].request_number];
  --min_heap.size_;
  --max_heap.size_;
  int size = max_heap.size_;
  if (index != size) {
    std::swap(max_heap.heap_array_[index], max_heap.heap_array_[size]);
    std::swap(
            max_heap.requests_order_[max_heap.heap_array_[index].request_number],
            max_heap.requests_order_[max_heap.heap_array_[size].request_number]);
    max_heap.SiftDown(index);
    max_heap.SiftUp(index);
  }
  std::swap(min_heap.heap_array_[0], min_heap.heap_array_[size]);
  std::swap(
          min_heap.requests_order_[min_heap.heap_array_[0].request_number],
          min_heap.requests_order_[min_heap.heap_array_[size].request_number]);
  min_heap.SiftDown(0);
  return min;
}

int ExtractMax(Heap& max_heap, Heap& min_heap) {
  int max = max_heap.heap_array_[0].value;
  int index = min_heap.requests_order_[max_heap.heap_array_[0].request_number];
  --min_heap.size_;
  --max_heap.size_;
  int size = max_heap.size_;
  if (index != size) {
    std::swap(min_heap.heap_array_[index], min_heap.heap_array_[size]);
    std::swap(
            min_heap.requests_order_[min_heap.heap_array_[index].request_number],
            min_heap.requests_order_[min_heap.heap_array_[size].request_number]);
    min_heap.SiftDown(index);
    min_heap.SiftUp(index);
  }
  std::swap(max_heap.heap_array_[0], max_heap.heap_array_[size]);
  std::swap(
          max_heap.requests_order_[max_heap.heap_array_[0].request_number],
          max_heap.requests_order_[max_heap.heap_array_[size].request_number]);
  max_heap.SiftDown(0);
  return -max;
}

int GetMin(const Heap& min_heap) { return min_heap.GetMin(); }

int GetMax(const Heap& max_heap) { return -max_heap.GetMin(); }

void Clear(Heap& max_heap, Heap& min_heap) {
  min_heap.size_ = 0;
  max_heap.size_ = 0;
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