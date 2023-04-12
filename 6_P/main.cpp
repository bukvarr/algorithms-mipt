/*В последних миссиях Балласы воспользовались неразберихой в Лос-Сантосе.
 Cиджей готовится к обороне своего города. Его город представляет собой клетчатый прямоугольник размера n×m,
 в котором каждая клетка — отдельный район. Балласы могут либо атаковать район, либо пощадить его.
 При этом есть районы, в которых достаточно оборонительных сооружений до следующего конца света,
 и балласы не в силах их захватить, а есть те, в которых никакой защиты нет, и им в любом случае придется капитулировать.

Балласы все ещё справедливы, а это значит,
 что в любом квадрате размера 2×2 должно быть поровну до зубов защищенных и безоружных районов.
 Теперь балласы хотят узнать количество различных вариантов распределения районов города на безоружные и излишне защищенные.*/

#include <iostream>

#include <vector>

const long long kMod = 1'000'000'007;

long long BinPow(long long t, int pow) {
  if (pow == 0) {
    return 1;
  }
  if (pow == 1) {
    return t;
  }
  long long tt = BinPow(t * t % kMod, pow / 2);
  return (BinPow(t, pow % 2) * tt) % kMod;
}

struct Row { //эта структура хранит четность черных и белых клеток в ряду(строчке/столбце) и в случае, если четность белых == четности черных,
    int black_odd = -1; //либо же какой-то цвет встречается как на четных, так и на нечетных местах, то ряд называется плохим(bad_cons).
    int white_odd = -1;//ряд так же может быть неопределен(IsUndef) в случае, если там нет ни черных, ни белых клеток
    bool bad_cons = false;

    bool IsUndef() const { return black_odd == -1 && white_odd == -1; }
};

void Initialization(std::vector<Row>& rows, std::vector<Row>& columns, //иницализируем строку i, столбец j с учетом символа
                    int i, int j, char c) {
  if (c == '+') {
    if (rows[i].black_odd == -1 || rows[i].black_odd == j % 2) {
      rows[i].black_odd = j % 2;
    } else {
      rows[i].bad_cons = true;
    }
    if (columns[j].black_odd == -1 || columns[j].black_odd == i % 2) {
      columns[j].black_odd = i % 2;
    } else {
      columns[j].bad_cons = true;
    }
  } else if (c == '-') {
    if (rows[i].white_odd == -1 || rows[i].white_odd == j % 2) {
      rows[i].white_odd = j % 2;
    } else {
      rows[i].bad_cons = true;
    }
    if (columns[j].white_odd == -1 || columns[j].white_odd == i % 2) {
      columns[j].white_odd = i % 2;
    } else {
      columns[j].bad_cons = true;
    }
  }
  if (rows[i].black_odd == rows[i].white_odd && rows[i].black_odd != -1) {
    rows[i].bad_cons = true;
  }
  if (columns[j].black_odd == columns[j].white_odd &&
      columns[j].black_odd != -1) {
    columns[j].bad_cons = true;
  }
}

bool AlterIsPossible(const std::vector<Row>& rows, int n) { // проверка возможности чередования* по рядам(строкам или столбцам
  int black_odd = -1;
  int white_odd = -1;
  for (int i = 0; i < n; ++i) {
    if (rows[i].black_odd != -1) {
      if (black_odd == -1 || black_odd == (rows[i].black_odd + i) % 2) {
        black_odd = (rows[i].black_odd + i) % 2;
      } else {
        return false;
      }
      if (white_odd == -1 || white_odd == (rows[i].black_odd + i + 1) % 2) {
        white_odd = (rows[i].black_odd + i + 1) % 2;
      } else {
        return false;
      }
    }
    if (rows[i].white_odd != -1) {
      if (black_odd == -1 || black_odd == (rows[i].white_odd + i + 1) % 2) {
        black_odd = (rows[i].white_odd + i + 1) % 2;
      } else {
        return false;
      }
      if (white_odd == -1 || white_odd == (rows[i].white_odd + i) % 2) {
        white_odd = (rows[i].white_odd + i) % 2;
      } else {
        return false;
      }
    }
  }
  return !(white_odd == black_odd && white_odd != -1);
}

long long CountVarieties(int n, int m, const std::vector<Row>& rows,
                            const std::vector<Row>& columns,
                            std::pair<bool, bool> bad) { // pair of flags of existing bad row or bad column
  bool bad_row_exists = bad.first;
  bool bad_col_exists = bad.second;
  int undef_row_num = 0;
  for (int i = 0; i < n; ++i) {
    if (rows[i].IsUndef()) {
      ++undef_row_num;
    }
  }
  int undef_col = 0;
  for (int j = 0; j < m; ++j) {
    if (columns[j].IsUndef()) {
      ++undef_col;
    }
  }
  bool alter_possibility =
          AlterIsPossible(rows, n) || AlterIsPossible(columns, m);
  if ((!bad_row_exists && bad_col_exists) || m == 1) {
    return BinPow(2, undef_row_num);
  }
  if ((bad_row_exists && !bad_col_exists) || n == 1) {
    return BinPow(2, undef_col);
  }
  if (!bad_row_exists && !bad_col_exists) {
    if (undef_row_num == n && undef_col == m) {
      return (BinPow(2, n) + BinPow(2, m) - 2) % kMod;
    }
    if (alter_possibility) {
      return (BinPow(2, undef_col) + BinPow(2, undef_row_num) - 1) % kMod;
    }
    return (BinPow(2, undef_col) + BinPow(2, undef_row_num)) % kMod;
  }
  return 0;
}

int FindVarietiesNum(int n, int m, std::vector<std::vector<char>>& input) {
  std::vector<Row> rows(n);
  std::vector<Row> columns(m);
  bool bad_row_exists = false;
  bool bad_col_exists = false;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      Initialization(rows, columns, i, j, input[i][j]);
      if (rows[i].bad_cons) {
        bad_row_exists = true;
      }
      if (columns[j].bad_cons) {
        bad_col_exists = true;
      }
    }
  }
  return CountVarieties(n, m, rows, columns,std::make_pair(bad_row_exists, bad_col_exists));
}

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<Row> rows(n);
  std::vector<Row> columns(m);
  bool bad_row_exists = false;
  bool bad_col_exists = false;
  std::vector<std::vector<char>> input(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char c;
      std::cin >> c;
      input[i].push_back(c);
      Initialization(rows, columns, i, j, c);
      if (rows[i].bad_cons) {
        bad_row_exists = true;
      }
      if (columns[j].bad_cons) {
        bad_col_exists = true;
      }
    }
  }
  std::cout << FindVarietiesNum(n, m, input);
}