#include <iostream>

#include <cmath>

int FindNearest2Power(int n) {
  if (n == 1) {
    return 1;
  }
  int max = 18;
  int min = 0;
  while (max > min + 1) {
    int m = (min + max) / 2;
    if (((n - 1) >> m) == 0) {
      max = m;
    } else {
      min = m;
    }
  }
  return static_cast<int>(std::pow(2, max));
}

class SegmentTree {
 private:
  int* array_;
  int index_ = 0;
  int size_;
  int tree_size_;
  int value_ = 0;

 public:
  SegmentTree(int n, int n2, const int* arr)
      : array_(new int[n2]), size_(n), tree_size_(n2) {
    int num = (tree_size_ + 1) / 2;
    int index = tree_size_ - num;
    for (int i = 0; i < size_; ++i) {
      array_[index + i] = arr[i];
    }
    for (int i = size_; i < num; ++i) {
      array_[index + i] = 0;
    }
    while (num > 0) {
      num /= 2;
      index = index - num;
      for (int i = 0; i < num; i++) {
        array_[index + i] =
                std::max(array_[(index + i) * 2 + 1], array_[(index + i) * 2 + 2]);
      }
    }
  }

  void Update(int new_value, int index) {
    int current_index = tree_size_ / 2 + index;
    array_[current_index] = new_value;
    while (current_index > 0) {
      current_index = (current_index - 1) / 2;
      array_[current_index] = std::max(array_[current_index * 2 + 1],
                                       array_[current_index * 2 + 2]);
    }
  }

  int FindNearestNumber() {
    int begin = tree_size_ / 2;
    int index = begin + index_;
    int last = tree_size_ - 1;
    while (array_[index] < value_) {
      if (index % 2 == 0) {
        if (index == last) {
          return -1;
        }
        index++;
      } else {
        if (index == 0) {
          return -1;
        }
        index = (index - 1) / 2;
        last = (last - 2) / 2;
      }
    }
    while (index < begin) {
      if (array_[index * 2 + 1] >= value_) {
        index = index * 2 + 1;
      } else {
        index = index * 2 + 2;
      }
    }
    return index - begin + 1;
  }

  int PreFNN(int value, int index) {
    index_ = index;
    value_ = value;
    return FindNearestNumber();
  }

  ~SegmentTree() { delete[] array_; }
};

int main() {
  int n, m;
  std::cin >> n >> m;
  int n2 = FindNearest2Power(n);
  int* arr = new int[n];
  for (int i = 0; i < n; ++i) {
    int t;
    std::cin >> t;
    arr[i] = t;
  }
  SegmentTree tree(n, n2 * 2 - 1, arr);
  for (int i = 0; i < m; ++i) {
    int op, index, value;
    std::cin >> op >> index >> value;
    if (op == 0) {
      tree.Update(value, index - 1);
      continue;
    }
    int t = tree.PreFNN(value, index - 1);
    std::cout << t << '\n';
  }
  delete[] arr;
}