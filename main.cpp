#include <cmath>

#include <iostream>

#include <vector>

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
 public:
  SegmentTree(int n, std::vector<int> vec);
  void Update(int new_value, int index);
  int FindNearestNumber(int find_value, int find_index) const;

  ~SegmentTree() { delete[] array_; }

 private:
  int* array_;
  int size_;
  int tree_size_;
};

SegmentTree::SegmentTree(int n, std::vector<int> vec)
        : array_(new int[FindNearest2Power(n) * 2 - 1]), size_(n),
        tree_size_(FindNearest2Power(n) * 2 - 1) {
  int num = (tree_size_ + 1) / 2;
  int index = tree_size_ - num;
  for (int i = 0; i < size_; ++i) {
    array_[index + i] = vec[i];
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

void SegmentTree::Update(int new_value, int index) {
  int current_index = tree_size_ / 2 + index;
  array_[current_index] = new_value;
  while (current_index > 0) {
    current_index = (current_index - 1) / 2;
    array_[current_index] = std::max(array_[current_index * 2 + 1],
                                     array_[current_index * 2 + 2]);
  }
}

int SegmentTree::FindNearestNumber(int find_value, int find_index) const {
  int begin = tree_size_ / 2;
  int index = begin + find_index;
  int last = tree_size_ - 1;
  while (array_[index] < find_value) {
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
    if (array_[index * 2 + 1] >= find_value) {
      index = index * 2 + 1;
    } else {
      index = index * 2 + 2;
    }
  }
  return index - begin + 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> vec;
  for (int i = 0; i < n; ++i) {
    int t;
    std::cin >> t;
    vec.push_back(t);
  }
  SegmentTree tree(n, vec);
  for (int i = 0; i < m; ++i) {
    int op, index, value;
    std::cin >> op >> index >> value;
    if (op == 0) {
      tree.Update(value, index - 1);
      continue;
    }
    int t = tree.FindNearestNumber(value, index - 1);
    std::cout << t << '\n';
  }
}