#include <algorithm>

#include <iostream>

#include <vector>

class Hashmap {
 private:
  const unsigned int kN = 1'000'000'000;
  unsigned int cnt_ = 0;
  unsigned int* array_ = new unsigned int[4 * 1024 * 1024];
  unsigned int* count_ = new unsigned int[4 * 1024 * 1024];
  unsigned int Hash1(unsigned int x) { return x % (4 * 1024 * 1024); }
  unsigned int Hash2(unsigned int x) {
    return ((x % 997) * 2 + 1) % (4 * 1024 * 1024);
  }

 public:
  Hashmap() {
    std::fill(array_, array_ + (4 * 1024 * 1024), kN + 1);
    std::fill(count_, count_ + (4 * 1024 * 1024), 0);
  }

  void Insert(unsigned int x) {
    unsigned int probe_point = Hash1(x);
    unsigned int inc = Hash2(x);
    while (array_[probe_point] < (kN + 1) && array_[probe_point] != x) {
      probe_point = (probe_point + inc) % (4 * 1024 * 1024);
    }
    array_[probe_point] = x;
    ++count_[probe_point];
  }

  bool Extract(unsigned int x) {
    unsigned int probe_point = Hash1(x);
    unsigned int inc = Hash2(x);
    while (array_[probe_point] != (kN + 1) && array_[probe_point] != x) {
      probe_point = (probe_point + inc) % (4 * 1024 * 1024);
    }
    if (array_[probe_point] == x && count_[probe_point] != 0) {
      ++cnt_;
      --count_[probe_point];
      return true;
    }
    return false;
  }

  unsigned int Cnt() { return cnt_; }

  ~Hashmap() {
    delete[] array_;
    delete[] count_;
  }
};

int main() {
  Hashmap hashmap;
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    unsigned int x;
    std::cin >> x;
    hashmap.Insert(x);
  }
  std::cin >> q;
  std::vector<unsigned int> vec;
  for (int i = 0; i < q; ++i) {
    unsigned int x;
    std::cin >> x;
    if (hashmap.Extract(x)) {
      vec.push_back(x);
    }
  }
  std::cout << hashmap.Cnt() << std::endl;
  for (size_t i = 0; i < vec.size(); ++i) {
    std::cout << vec[i] << " ";
  }
} 