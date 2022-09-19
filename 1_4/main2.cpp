#include <iostream>

#include <deque>

void PriorityInsertion(std::deque<int>& first_half,
                       std::deque<int>& second_half, int current_number) {
  if (first_half.size() == second_half.size()) {
    first_half.push_back(current_number);
  } else {
    second_half.push_front(current_number);
  }
}

void NormalInsertion(std::deque<int>& first_half, std::deque<int>& second_half,
                     int current_number) {
  if (first_half.empty()) {
    first_half.push_back(current_number);
  } else if (first_half.size() == second_half.size()) {
    first_half.push_back(second_half.front());
    second_half.pop_front();
    second_half.push_back(current_number);
  } else {
    second_half.push_back(current_number);
  }
}

void PopFront(std::deque<int>& first_half, std::deque<int>& second_half) {
  std::cout << first_half.front() << '\n';
  first_half.pop_front();
  if (first_half.size() < second_half.size()) {
    first_half.push_back(second_half.front());
    second_half.pop_front();
  }
}

int main() {
  int n;
  std::cin >> n;
  std::deque<int> first_half = {}, second_half = {};
  for (int j = 0; j < n; ++j) {
    std::string s;
    std::cin >> s;
    if (s == "+") {
      int current_number;
      std::cin >> current_number;
      NormalInsertion(first_half, second_half, current_number);
    } else if (s == "*") {
      int current_number;
      std::cin >> current_number;
      PriorityInsertion(first_half, second_half, current_number);
    } else {
      PopFront(first_half, second_half);
    }
  }
}