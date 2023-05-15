//Требуется построить в двудольном графе минимальное контролирующее множество  
//(вершинное покрытие), если дано максимальное паросочетание.

#include <iostream>
#include <vector>
#include <unordered_set>

int Find2Pow(int x) {
  int i = 1;
  int pow = 0;
  while (i <= x) {
    i *= 2;
    ++pow;
  }
  return pow + 1;
}

class Graph {
 private:
  int l;
  int r;
  std::vector<std::unordered_set<int>> edge_lists_;

 public:
  Graph(int l, int r) : l(l), r(r), edge_lists_(std::vector<std::unordered_set<int>>(l + r)) {}

  Graph() = default;

  void AddEdge(int v1, int v2) { edge_lists_[v1].insert(v2); }

  void EraseEdge(int v1, int v2) { edge_lists_[v1].erase(v2); }

  const std::unordered_set<int>& GetNeighbours(int vv) const {
    return edge_lists_[vv];
  }

  int LVerticesNum() const { return l; }

  int RVerticesNum() const { return r; }
};

std::istream& operator>>(std::istream& in, Graph& gg) {
  for (int i = 0; i < gg.LVerticesNum(); ++i) {
    int v_num;
    in >> v_num;
    for (int j = 0; j < v_num; ++j) {
      int v1;
      in >> v1;
      --v1;
      v1 += gg.LVerticesNum();
      gg.AddEdge(i, v1);
    }
  }
  return in;
}

bool DFS(Graph& g, int v, std::vector<bool>& used) {
  if (used[v]) {
    return false;
  }
  used[v] = true;
  std::unordered_set<int>::const_iterator it;
  for (it = g.GetNeighbours(v).cbegin(); it != g.GetNeighbours(v).cend(); ++it) {
    int to = *it;
    DFS(g, to, used);
  }
  return false;
}

void OrientEdges(Graph& g, std::vector<int>& match) {
  for (size_t i = 0; i < match.size(); ++i) {
    if (match[i] != -1) {
      g.AddEdge(i + g.LVerticesNum(), match[i]);
      g.EraseEdge(match[i], i + g.LVerticesNum());
    }
  }
}

void ConstructSets(Graph&g, std::vector<int>& match, std::vector<int>& l_minus,
                   std::vector<int>& l_plus, std::vector<int>& r_minus, std::vector<int>& r_plus) {
  OrientEdges(g, match);
  int l = g.LVerticesNum();
  int r = g.RVerticesNum();
  std::vector<bool> visited(l + r, false);
  std::vector<bool> used(l + r, false);
  for (size_t i = 0; i < match.size(); ++i) {
    if (match[i] != -1) {
      used[i + l] = true;
      used[match[i]] = true;
    }
  }
  for (size_t i = 0; i < used.size(); ++i) {
    if (!used[i] && i < l) {
      DFS(g, i, visited);
    }
  }
  for (size_t i = 0; i < visited.size(); ++i) {
    if (i < l) {
      if (visited[i]) {
        l_plus.push_back(i);
      } else {
        l_minus.push_back(i);
      }
    } else {
      if (visited[i]) {
        r_plus.push_back(i);
      } else {
        r_minus.push_back(i);
      }
    }
  }
}

int main() {
  int l, r;
  std::cin >> l >> r;
  Graph g(l, r);
  std::vector<int> match(r, -1);
  std::cin >> g;
  for (int i = 0; i < l; ++i) {
    int v;
    std::cin >> v;
    if (v != 0){
      match[v - 1] = i;
    }
  }
  std::vector<int> l_minus;
  std::vector<int> l_plus;
  std::vector<int> r_minus;
  std::vector<int> r_plus;
  ConstructSets(g, match, l_minus, l_plus, r_minus, r_plus);
  std::cout << l_minus.size() + r_plus.size() << '\n';
  std::cout << l_minus.size() << " ";
  for (size_t i = 0; i < l_minus.size(); ++i) {
    std::cout << l_minus[i] + 1 << " ";
  }
  std::cout << '\n' << r_plus.size() << " ";
  for (size_t i = 0; i < r_plus.size(); ++i) {
    std::cout << r_plus[i] - l + 1 << " ";
  }
  return 0;
}
