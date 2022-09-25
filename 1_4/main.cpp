

/*Гоблины Мглистых гор очень любях ходить к своим шаманам. Так как гоблинов много, к шаманам часто образуются очень длинные очереди. А поскольку много гоблинов в одном месте быстро образуют шумную толку, которая мешает шаманам проводить сложные медицинские манипуляции, последние решили установить некоторые правила касательно порядка в очереди.

Обычные гоблины при посещении шаманов должны вставать в конец очереди. Привилегированные же гоблины, знающие особый пароль, встают ровно в ее середину, причем при нечетной длине очереди они встают сразу за центром.

Так как гоблины также широко известны своим непочтительным отношением ко всяческим правилам и законам, шаманы попросили вас написать программу, которая бы отслеживала порядок гоблинов в очереди.

Формат ввода

В первой строке входных данный записано число N (1 ≤ N ≤ 105) — количество запросов к программе. Следующие N строк содержат описание запросов в формате:

«+ i» — гоблин с номером i (1 ≤ i ≤ N) встает в конец очереди;
«* i» — привилегированный гоблин с номером i встает в середину очереди;
«-» — первый гоблин из очереди уходит к шаманам. Гарантируется, что на момент такого запроса очередь не пуста.

Формат вывода

Для каждого запроса типа «-» программа должна вывести номер гоблина, который должен зайти к шаманам.*/

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