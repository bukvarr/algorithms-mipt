#include <algorithm>

#include <iostream>

class Hashmap {
 public:
  Hashmap(unsigned int max_key, unsigned int size);

  void Insert(unsigned int x);

  bool FindEntry(unsigned int x);

  void Erase(unsigned int x);

  ~Hashmap() { delete[] array_; }

 private:
  unsigned int max_key_;
  unsigned int size_;
  unsigned int* array_;
  unsigned int Hash1(unsigned int x) { return x % (size_); }
  unsigned int Hash2(unsigned int x) { return ((x % 1997) * 2 + 1) % (size_); }
};

Hashmap::Hashmap(unsigned int max_key, unsigned int size)
        : max_key_(max_key), size_(size), array_(new unsigned int[size]) {
  std::fill(array_, array_ + (size_), max_key_ + 1);
}

void Hashmap::Insert(unsigned int x) {
  unsigned int probe_point = Hash1(x);
  unsigned int inc = Hash2(x);
  while (array_[probe_point] < (max_key_ + 1) && array_[probe_point] != x) {
    probe_point = (probe_point + inc) % (size_);
  }
  array_[probe_point] = x;
}

bool Hashmap::FindEntry(unsigned int x) {
  unsigned int probe_point = Hash1(x);
  unsigned int inc = Hash2(x);
  while (array_[probe_point] != (max_key_ + 1) && array_[probe_point] != x) {
    probe_point = (probe_point + inc) % (size_);
  }
  return (array_[probe_point] == x);
}

void Hashmap::Erase(unsigned int x) {
  unsigned int probe_point = Hash1(x);
  unsigned int inc = Hash2(x);
  while (array_[probe_point] != (max_key_ + 1) && array_[probe_point] != x) {
    probe_point = (probe_point + inc) % (size_);
  }
  if (array_[probe_point] == x) {
    array_[probe_point] = max_key_ + 2;
  }
}

int main() {
  Hashmap hashmap(1'000'000'000, 1024 * 1024);
  int q;
  std::cin >> q;
  for (int i = 0; i < q; ++i) {
    char c;
    std::cin >> c;
    unsigned int x;
    std::cin >> x;
    if (c == '+') {
      hashmap.Insert(x);
    }
    if (c == '-') {
      hashmap.Erase(x);
    }
    if (c == '?') {
      if (hashmap.FindEntry(x)) {
        std::cout << "YES" << '\n';
      } else {
        std::cout << "NO" << '\n';
      }
    }
  }
}