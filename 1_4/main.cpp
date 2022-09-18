#include <iostream>

#include <deque>

std::deque<int> d1 = {}, d2 = {};
int i;

void PriorityInsert() {
  if (d1.size() == d2.size()) {
    d1.push_back(i);
  } else {
    d2.push_front(i);
  }
}

void NormalInsert() {
  if (d1.empty()) {
    d1.push_back(i);
  } else if (d1.size() == d2.size()) {
    d1.push_back(d2.front());
    d2.pop_front();
    d2.push_back(i);
  } else {
    d2.push_back(i);
  }
}

void Next() {
  std::cout << d1.front() << '\n';
  d1.pop_front();
  if (d1.size() < d2.size()) {
    d1.push_back(d2.front());
    d2.pop_front();
  }
}

int main() {
  int n;
  std::string s;
  std::cin >> n;
  for (int j = 0; j < n; ++j) {
    std::cin >> s;
    if (s == "+") {
      std::cin >> i;
      NormalInsert();
    } else if (s == "*") {
      std::cin >> i;
      PriorityInsert();
    } else {
      Next();
    }
  }
}