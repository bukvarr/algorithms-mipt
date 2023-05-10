/*Дан неориентированный (быть может несвязный) граф. Требуется найти все мосты в нем.*/

#include <iostream>

#include <vector>

#include<set>

struct Edge {
    int vert;
    int num;
    Edge(int vert, int num) : vert(vert), num(num) {}
};

class Graph {
 public:
  Graph(int n) : vert_num_(n), edge_lists_(std::vector<std::vector<Edge>>(n)) {}

  void AddEdge(int v1, Edge e) { edge_lists_[v1].push_back(e); }

  void GetNeighbours(int v, std::vector<Edge>& vertices) const {
    for (size_t i = 0; i < edge_lists_[v].size(); ++i) {
      vertices.push_back(edge_lists_[v][i]);
    }
  }

  int VerticesNum() const { return vert_num_; }

 private:
    int vert_num_;
    std::vector<std::vector<Edge>> edge_lists_;
};

void DFS(const Graph& g, int v, std::vector<int>& time_in,
         std::vector<bool>& visited, std::vector<int>& ret,
         std::vector<int>& parent, std::vector<bool>& bridges) {
  static int t = 0;
  if (visited[v]) {
    return;
  }
  visited[v] = true;
  ++t;
  time_in[v] = t;
  ret[v] = t;
  std::vector<Edge> verts;
  g.GetNeighbours(v, verts);
  std::vector<Edge>::const_iterator it;
  for (it = verts.cbegin(); it != verts.cend(); ++it) {
    if (it->vert == parent[v]) {
      continue;
    }
    if (visited[it->vert]) {
      ret[v] = std::min(ret[v], time_in[it->vert]);
      continue;
    }
    parent[it->vert] = v;
    DFS(g, it->vert, time_in, visited, ret, parent, bridges);
    ret[v] = std::min(ret[v], ret[it->vert]);
    if (ret[it->vert] > time_in[v]) {
      bridges[it->num] = true;
    }
  }
}

std::vector<size_t >&& FindBridges(const Graph& g,
                std::vector<std::pair<int, int>>& edges_order,
                std::multiset<std::pair<int, int>>& edges) {
  int n = g.VerticesNum();
  size_t m = edges.size();
  std::vector<int> time_in(n);
  std::vector<int> parent(n, -1);
  std::vector<int> ret(n);
  std::vector<bool> visited(n, false);
  std::vector<bool> bridges(m, false);
  std::vector<size_t> bridges_nums;
  for (int i = 0; i < n; ++i) {
    DFS(g, i, time_in, visited, ret, parent, bridges);
  }
  std::vector<bool>::const_iterator it;
  int count = 0;
  for (it = bridges.cbegin(); it != bridges.cend(); ++it) {
    if (*it && edges.count(edges_order[it - bridges.cbegin()]) == 1) {
      bridges_nums.push_back(it - bridges.cbegin() + 1);
    }
  }
  return std::move(bridges_nums);
}



int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n);
  std::vector<std::pair<int, int>> edges_order;
  edges_order.reserve(m);
  std::multiset<std::pair<int, int>> edges;
  for (int i = 0; i < m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;
    edges_order.push_back(std::make_pair(std::min(v1 - 1, v2 - 1),
                                         std::max(v1 - 1, v2 - 1)));
    edges.insert(std::make_pair(std::min(v1 - 1, v2 - 1),
                                std::max(v1 - 1, v2 - 1)));
    g.AddEdge(v1 - 1, Edge(v2 - 1, i));
    g.AddEdge(v2 - 1, Edge(v1 - 1, i));
  }
  std::vector<size_t> bridges_nums;
  bridges_nums = std::move(FindBridges(g, edges_order, edges));
  std::cout << bridges_nums.size() << '\n';
  for (auto num : bridges_nums) {
    std::cout << num << " ";
  }
}