/*Вам задан ориентированный граф с N вершинами и M ребрами (1 ≤ N ≤ 20000, 1 ≤ M ≤ 200000).
Найдите компоненты сильной связности заданного графа и топологически отсортируйте его конденсацию.*/

#include <algorithm>

#include <iostream>

#include <vector>

bool Comp(const std::pair<int, int>& p1, const std::pair<int, int>& p2) {
  return (p1.first >= p2.first);
}

class Graph {
 private:
  int vert_num_;
  std::vector<std::vector<int>> edge_lists_;

 public:
  Graph(int n) : vert_num_(n), edge_lists_(std::vector<std::vector<int>>(n)) {}

  Graph() = default;

  void AddEdge(int v1, int v2) { edge_lists_[v1].push_back(v2); }

  void GetNeighbours(int v, std::vector<int>& vertices) const {
    for (size_t i = 0; i < edge_lists_[v].size(); ++i) {
      vertices.push_back(edge_lists_[v][i]);
    }
  }

  int VerticesNum() const { return vert_num_; }
};

void DFSWithTime(const Graph& g, int v, std::vector<int>& time_in,
                 std::vector<int>& time_out, std::vector<int>& color) {
  static int t = 0;
  if (color[v] != 1) {
    return;
  }
  ++t;
  time_in[v] = t;
  color[v] = 2;
  std::vector<int> verts;
  verts.reserve(g.VerticesNum());
  g.GetNeighbours(v, verts);
  std::vector<int>::const_iterator it;
  for (it = verts.cbegin(); it != verts.cend(); ++it) {
    DFSWithTime(g, *it, time_in, time_out, color);
  }
  time_out[v] = t;
  color[v] = 3;
  ++t;
}

bool DFSCompFound(const Graph& g, int v, std::vector<int>& color,
                  std::vector<int>& components, int comp_num) {
  if (color[v] != 1) {
    return false;
  }
  color[v] = 2;
  components[v] = comp_num;
  std::vector<int> verts;
  verts.reserve(g.VerticesNum());
  g.GetNeighbours(v, verts);
  std::vector<int>::const_iterator it;
  for (it = verts.cbegin(); it != verts.cend(); ++it) {
    DFSCompFound(g, *it, color, components, comp_num);
  }
  color[v] = 3;
  return true;
}

void TopSort(const Graph& g, std::vector<int>& order) {
  int n = g.VerticesNum();
  std::vector<int> time_in(n);
  std::vector<int> time_out(n);
  std::vector<int> color(n, 1);
  for (int i = 0; i < n; ++i) {
    DFSWithTime(g, i, time_in, time_out, color);
  }
  if (time_in[0] == -1) {
    order[0] = -1;
    return;
  }
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; ++i) {
    a[i].first = time_out[i];
    a[i].second = i;
  }
  std::sort(a.begin(), a.end(), Comp);
  for (int i = 0; i < n; ++i) {
    order[i] = a[i].second;
  }
}

int FindComponents(const Graph& gt, const std::vector<int>& order,
                      std::vector<int>& components) {
  int comp_num = 1;
  int n = gt.VerticesNum();
  std::vector<int> color(n, 1);
  std::vector<int>::const_iterator it;
  for (it = order.cbegin(); it != order.cend(); ++it) {
    if (DFSCompFound(gt, *it, color, components, comp_num)) {
      ++comp_num;
    }
  }
  return comp_num;
}

int FindComponentsNum(const Graph& g, const Graph& gt, std::vector<int>& components) {
  int n = g.VerticesNum();
  std::vector<int> order(n);
  TopSort(g, order);
  return FindComponents(gt, order, components);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n);
  Graph gt(n);
  for (int i = 0; i < m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;
    g.AddEdge(v1 - 1, v2 - 1);
    gt.AddEdge(v2 - 1, v1 - 1);
  }
  std::vector<int> components(n);
  int comp_num = FindComponentsNum(g, gt, components);
  std::cout << comp_num - 1 << '\n';
  std::vector<int>::const_iterator it;
  for (it = components.cbegin(); it != components.cend(); ++it) {
    std::cout << *it << " ";
  }
}