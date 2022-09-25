
/* Распределяющая шляпа — крайне древний артефакт, способный по ее носителю понять, какой факультет ему подойдет для наиболее полного раскрытия характера. Но некто решил заколдовать шляпу, теперь она определяет уровень IQ носителя. Вам предстоит реализовать заколдованную шляпу, чтобы с оригинальной сняли проклятье.

У вас есть сама шляпа и набор действий, который будет с ней происходить. К шляпе стоит очередь из первокурсников Хогвартса, которая желает протестировать себя. Возможные действия:

«enqueue n» Добавить в внутреннюю очередь шляпы уровень интеллекта очередного первокурсника n (1 ≤ n ≤ 109) (значение n задается после команды). Шляпа должна сказать «ok».
«dequeue» Удалить из внутренней очереди шляпы уровень интеллекта последнего студента, которого она еще помнит. Шляпа должна сказать его значение.
«front» Шляпа должна сказать уровень интеллекта последнего студента, которого она еще помнит, не забывая его.
«size» Шляпа скажет, уровень интеллекта какого числа студентов она помнит.
«clear» Перезагрузка шляпы, она забывает все, что было до этого. Шляпа должна сказать «ok».
«min» Шляпа должна сказать уровень интеллекта самого неодаренного умственными способностями первокурсника. При этом, конечно же, не забыть его.

Перед исполнением операций «front», «dequeue» и «min» шляпа должна проверять, содержится ли в внутренней очереди хотя бы один элемент.
Если шляпа помнит ноль студентов на момент таких запросов, то она должна вместо числового значения сказать слово «error».

 Формат ввода

В первой строке входных данных записано единственное число M (1 ≤ M ≤ 2 ⋅ 105) — количество команд. В следующих М строках дано по одной команде из тех, что идут выше.

 Формат вывода

Для каждой команды выведите одну строчку — то, что скажет шляпа.*/

#include <iostream>

#include <string>

struct Context {
    int left_index, right_index;
    int first_minimum, last_minimum;
    int queue[200'000], minimums_array[200'000];
    int current_iq, popped_iq;
};

void FirstInitialization(Context* queue_p) {
  queue_p->left_index = 0;
  queue_p->right_index = 0;
  queue_p->first_minimum = queue_p->last_minimum = 0;
  queue_p->current_iq = queue_p->popped_iq = 0;
  for (int i = 0; i < 200'000; ++i) {
    queue_p->minimums_array[i] = 0;
  }
}

void PushBack(Context* queue_p) {
  int index = queue_p->right_index % 200'000;
  queue_p->queue[index] = queue_p->current_iq;
  ++queue_p->right_index;
  std::cout << "ok" << std::endl;
}

int PopFront(Context* queue_p) {
  if (queue_p->right_index == queue_p->left_index) {
    std::cout << "error" << std::endl;
    return 0;
  }
  int index = queue_p->left_index % 200'000;
  std::cout << queue_p->queue[index] << std::endl;
  ++queue_p->left_index;
  return queue_p->queue[index];
}

void OutputFront(Context* queue_p) {
  if (queue_p->right_index == queue_p->left_index) {
    std::cout << "error" << std::endl;
    return;
  }
  int index = queue_p->left_index % 200'000;
  std::cout << queue_p->queue[index] << std::endl;
}

void Clear(Context* queue_p) {
  queue_p->left_index = queue_p->right_index = 0;
  queue_p->first_minimum = queue_p->last_minimum = 0;
  std::cout << "ok" << std::endl;
}

void AddToMinimums(Context* queue_p) {
  if (queue_p->right_index == queue_p->left_index + 1) {
    queue_p->minimums_array[queue_p->last_minimum] = queue_p->current_iq;
    return;
  }
  while (queue_p->last_minimum >= queue_p->first_minimum &&
         queue_p->minimums_array[queue_p->last_minimum % 200'000] >
         queue_p->current_iq) {
    --queue_p->last_minimum;
  }
  ++queue_p->last_minimum;
  queue_p->minimums_array[queue_p->last_minimum % 200'000] =
          queue_p->current_iq;
}

void RemoveFromMinimums(Context* queue_p) {
  if (queue_p->minimums_array[queue_p->first_minimum % 200'000] ==
      queue_p->popped_iq) {
    if (queue_p->first_minimum != queue_p->last_minimum) {
      ++queue_p->first_minimum;
    }
  }
}

void OutputMinimum(Context* queue_p) {
  if (queue_p->right_index == queue_p->left_index) {
    std::cout << "error" << std::endl;
    return;
  }
  std::cout << queue_p->minimums_array[queue_p->first_minimum % 200'000]
            << std::endl;
}

void ProcessingRequest(Context* queue_p) {
  std::string s;
  std::cin >> s;
  if (s == "enqueue") {
    std::cin >> queue_p->current_iq;
    PushBack(queue_p);
    AddToMinimums(queue_p);
  }
  if (s == "dequeue") {
    queue_p->popped_iq = PopFront(queue_p);
    if (queue_p->popped_iq != 0) {
      RemoveFromMinimums(queue_p);
    }
  }
  if (s == "front") {
    OutputFront(queue_p);
  }
  if (s == "clear") {
    Clear(queue_p);
  }
  if (s == "size") {
    std::cout << queue_p->right_index - queue_p->left_index << std::endl;
  }
  if (s == "min") {
    OutputMinimum(queue_p);
  }
}

int main() {
  int m;
  Context queue_p;
  FirstInitialization(&queue_p);
  std::cin >> m;
  for (int i = 0; i < m; ++i) {
    ProcessingRequest(&queue_p);
  }
}