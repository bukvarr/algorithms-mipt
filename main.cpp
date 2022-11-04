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

class Heap {
 private:
  std::pair<int, int> max_heap_[200'000];
  std::pair<int, int> min_heap_[200'000];
  int* requests_order_min_;
  int* requests_order_max_;
  int size_ = 0;

  void SiftDownMin(int index) {
    while (2 * index + 1 < size_) {
      int u = 2 * index + 1;
      if (u + 1 < size_ && min_heap_[u + 1].first < min_heap_[u].first) {
        ++u;
      }
      if (min_heap_[u].first < min_heap_[index].first) {
        std::swap(min_heap_[index], min_heap_[u]);
        std::swap(requests_order_min_[min_heap_[index].second],
                  requests_order_min_[min_heap_[u].second]);
        index = u;
      } else {
        break;
      }
    }
  }

  void SiftDownMax(int index) {
    while (2 * index + 1 < size_) {
      int u = 2 * index + 1;
      if (u + 1 < size_ && max_heap_[u + 1].first > max_heap_[u].first) {
        ++u;
      }
      if (max_heap_[u].first > max_heap_[index].first) {
        std::swap(max_heap_[index], max_heap_[u]);
        std::swap(requests_order_max_[max_heap_[index].second],
                  requests_order_max_[max_heap_[u].second]);
        index = u;
      } else {
        break;
      }
    }
  }

  void SiftUpMin(int index) {
    while (index > 0) {
      if (min_heap_[index].first < min_heap_[(index - 1) / 2].first) {
        std::swap(min_heap_[index], min_heap_[(index - 1) / 2]);
        std::swap(requests_order_min_[min_heap_[index].second],
                  requests_order_min_[min_heap_[(index - 1) / 2].second]);
        index = (index - 1) / 2;
      } else {
        break;
      }
    }
  }

  void SiftUpMax(int index) {
    while (index > 0) {
      if (max_heap_[index].first > max_heap_[(index - 1) / 2].first) {
        std::swap(max_heap_[index], max_heap_[(index - 1) / 2]);
        std::swap(requests_order_max_[max_heap_[index].second],
                  requests_order_max_[max_heap_[(index - 1) / 2].second]);
        index = (index - 1) / 2;
      } else {
        break;
      }
    }
  }

 public:
  Heap(int size)
      : requests_order_min_(new int[size]),
        requests_order_max_(new int[size]){};

  std::string Size() { return std::to_string(size_); }

  std::string Insert(int request_number, int value) {
    int index = size_;
    ++size_;
    requests_order_min_[request_number] = index;
    requests_order_max_[request_number] = index;
    min_heap_[index].first = value;
    min_heap_[index].second = request_number;
    max_heap_[index].first = value;
    max_heap_[index].second = request_number;
    SiftUpMin(index);
    SiftUpMax(index);
    return "ok";
  }

  std::string ExtractMin() {
    if (size_ == 0) {
      return "error";
    }
    std::string out = std::to_string(min_heap_[0].first);
    int index = requests_order_max_[min_heap_[0].second];
    --size_;
    if (index != size_) {
      std::swap(max_heap_[index], max_heap_[size_]);
      std::swap(requests_order_max_[max_heap_[index].second],
                requests_order_max_[max_heap_[size_].second]);
      SiftDownMax(index);
      SiftUpMax(index);
    }
    std::swap(min_heap_[0], min_heap_[size_]);
    std::swap(requests_order_min_[min_heap_[0].second],
              requests_order_min_[min_heap_[size_].second]);
    SiftDownMin(0);
    return out;
  }

  std::string ExtractMax() {
    if (size_ == 0) {
      return "error";
    }
    std::string out = std::to_string(max_heap_[0].first);
    int index = requests_order_min_[max_heap_[0].second];
    --size_;
    if (index != size_) {
      std::swap(min_heap_[index], min_heap_[size_]);
      std::swap(requests_order_min_[min_heap_[index].second],
                requests_order_min_[min_heap_[size_].second]);
      SiftDownMin(index);
      SiftUpMin(index);
    }
    std::swap(max_heap_[0], max_heap_[size_]);
    std::swap(requests_order_max_[max_heap_[0].second],
              requests_order_max_[max_heap_[size_].second]);
    SiftDownMax(0);
    return out;
  }

  std::string GetMin() {
    if (size_ == 0) {
      return "error";
    }
    return std::to_string(min_heap_[0].first);
  }

  std::string GetMax() {
    if (size_ == 0) {
      return "error";
    }
    return std::to_string(max_heap_[0].first);
  }

  std::string Clear() {
    size_ = 0;
    return "ok";
  }

  ~Heap() {
    delete[] requests_order_min_;
    delete[] requests_order_max_;
  }
};

std::string RequestProcessing(Heap& heap, const std::string& s) {
  if (s == "get_min") {
    return heap.GetMin();
  }
  if (s == "get_max") {
    return heap.GetMax();
  }
  if (s == "extract_min") {
    return heap.ExtractMin();
  }
  if (s == "extract_max") {
    return heap.ExtractMax();
  }
  if (s == "size") {
    return heap.Size();
  }
  if (s == "clear") {
    return heap.Clear();
  }
  return "error";
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::basic_ostream<char, std::char_traits<char> >* aboba = 0;
  std::cin.tie(aboba);
  int q;
  std::cin >> q;
  Heap heap(q);
  for (int i = 0; i < q; ++i) {
    std::string s;
    std::cin >> s;
    if (s == "insert") {
      int value;
      std::cin >> value;
      std::cout << heap.Insert(i, value) << '\n';
    } else {
      std::cout << RequestProcessing(heap, s) << '\n';
    }
  }
}