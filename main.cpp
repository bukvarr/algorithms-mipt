#include <iostream>

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

struct Row {
    int black_odd = -1;
    int white_odd = -1;
    bool bad_cons = false;

    bool IsUndef() const { return black_odd == -1 && white_odd == -1; }
};

void Initialization(Row* rows, Row* columns, int i, int j, char c) {
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

bool AlterIsPossible(const Row* rows, int n) {
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

long long Answer(int n, int m, const Row* rows, const Row* columns,
                 std::pair<bool, bool> bad) {
  bool bad_row_exists = bad.first;
  bool bad_col_exists = bad.second;
  int undef_row = 0;
  for (int i = 0; i < n; ++i) {
    if (rows[i].IsUndef()) {
      ++undef_row;
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
    return BinPow(2, undef_row);
  }
  if ((bad_row_exists && !bad_col_exists) || n == 1) {
    return BinPow(2, undef_col);
  }
  if (!bad_row_exists && !bad_col_exists) {
    if (undef_row == n && undef_col == m) {
      return (BinPow(2, n) + BinPow(2, m) - 2) % kMod;
    }
    if (alter_possibility) {
      return (BinPow(2, undef_col) + BinPow(2, undef_row) - 1) % kMod;
    }
    return (BinPow(2, undef_col) + BinPow(2, undef_row)) % kMod;
  }
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Row* rows = new Row[n];
  Row* columns = new Row[m];
  bool bad_row_exists = false;
  bool bad_col_exists = false;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      char c;
      std::cin >> c;
      Initialization(rows, columns, i, j, c);
      if (rows[i].bad_cons) {
        bad_row_exists = true;
      }
      if (columns[j].bad_cons) {
        bad_col_exists = true;
      }
    }
  }
  std::cout << Answer(n, m, rows, columns,
                      std::make_pair(bad_row_exists, bad_col_exists));
  delete[] rows;
  delete[] columns;
}