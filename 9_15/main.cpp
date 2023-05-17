/*2020 год. Ковид. Санитарные ограничения не позволяют собираться толпам людей. Толпу людей удобно представлять в виде графа, где люди — вершины, а ребро обозначает факт меньшего чем 15 метров расстояния между ними (очевидно, петель и кратных ребер нет).

Ядром неориентированного графа назовем подграф максимальной плотности. Плотностью графа называется отношение числа его рёбер к числу вершин.

Вам нужно найти ядро толпы, чтобы наиболее эффективно разогнать его. */

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

const int INF = 1000000000;
const int kIterationNum = 50;

int start, dest;

struct SimpleEdge {
    int v1, v2;

    SimpleEdge(int v1, int v2) : v1(v1), v2(v2) {}
};

struct Edge {
    int v1;
    int v2;
    double cap;
    double f;

    Edge() = default;

    Edge(int v1, int v2, double cap, double f) : v1(v1), v2(v2), cap(cap), f(f) {}
};

struct UsedContainers {
std::vector<int> min_path, ptr; //min_path - shortest path from start to v
std::vector<bool> visited;

UsedContainers(int n) : min_path(n), ptr(n), visited(n, false) {}
};

using UC = UsedContainers;

class Graph {
 public:
  Graph(int n, int m)
      : vertices_num(n), edges_num(m),
        edge_nums(n, std::vector<size_t>()),
        edges() {}
  int VerticesNum() const { return vertices_num; }
  int EdgesNum() const { return edges_num; }

  void AddEdges(int v1, int v2, double cap) {
    edge_nums[v1].push_back(edges.size());
    edges.push_back({v1, v2, cap, 0});
    edge_nums[v2].push_back(edges.size());
    edges.push_back({v2, v1, cap, 0});
  }

  void AddEdge(int v1, int v2, double cap) {
    edge_nums[v1].push_back(edges.size());
    edges.push_back({v1, v2, cap, 0});
    edge_nums[v2].push_back(edges.size());
    edges.push_back({v2, v1, 0, 0});
  }

  std::vector<size_t>& GetEdgesNums(int v) { return edge_nums[v]; }

  Edge& GetEdge(size_t num) { return edges[num]; }

 private:
  int vertices_num;
  int edges_num;
  std::vector<std::vector<size_t>> edge_nums;
  std::vector<Edge> edges;
};

void SimpleDFS(Graph& gr, int v, UC& uc) {
  uc.visited[v] = true;
  for (auto id  : gr.GetEdgesNums(v)) {
    if (gr.GetEdge(id).f < gr.GetEdge(id).cap && !uc.visited[gr.GetEdge(id).v2]) {
      SimpleDFS(gr, gr.GetEdge(id).v2, uc);
    }
  }
}

double DFS(Graph& gr, int u, double f, UC& uc) {
  if (f == 0) {
    return 0;
  }
  if (u == dest) {
    return f;
  }
  while (uc.ptr[u] < gr.GetEdgesNums(u).size()) {
    int id = gr.GetEdgesNums(u)[uc.ptr[u]];
    int v = gr.GetEdge(id).v2;
    if (uc.min_path[v] == uc.min_path[u] + 1) {
      double curr_f = DFS(gr, v, std::min(f, gr.GetEdge(id).cap - gr.GetEdge(id).f), uc);
      if (curr_f != 0) {
        gr.GetEdge(id).f += curr_f;
        gr.GetEdge(id ^ 1).f -= curr_f;
        return curr_f;
      }
    }
    ++uc.ptr[u];
  }
  return 0;
}

int BFS(Graph& gr, UC& uc) {
  int n = gr.VerticesNum();
  uc.min_path = std::vector<int> (n, INF);
  uc.min_path[start] = 0;
  std::queue<int> queue;
  queue.push(start);
  while (!queue.empty()) {
    int u = queue.front();
    queue.pop();
    for (int i = 0; i < gr.GetEdgesNums(u).size(); ++i) {
      int id = gr.GetEdgesNums(u)[i];
      int v = gr.GetEdge(id).v2;
      if (uc.min_path[v] == INF && gr.GetEdge(id).f < gr.GetEdge(id).cap) {
        uc.min_path[v] = uc.min_path[u] + 1;
        queue.push(v);
      }
    }
  }
  return uc.min_path[dest];
}

double FindMaxFlow(Graph& gr, UC& uc) {
  double f = 0;
  int n = gr.VerticesNum();
  while (BFS(gr, uc) != INF) {
    uc.ptr.assign(n, 0);
    double curr_f = DFS(gr, start, INF, uc);
    while (curr_f) {
      f += curr_f;
      curr_f = DFS(gr, start, INF, uc);
    }
  }
  return f;
}

double FindCut(Graph& gr, std::unordered_set<int>& cut, UC& uc) {
  double min_cut_f = FindMaxFlow(gr, uc);
  int m = gr.EdgesNum();
  SimpleDFS(gr, start, uc);
  for (int i = 0; i < 2 * m; i += 2) {
    int v1 = gr.GetEdge(i).v1;
    int v2 = gr.GetEdge(i).v2;
    if ((uc.visited[v1] && !uc.visited[v2]) || (!uc.visited[v1] && uc.visited[v2])) {
      cut.insert(v1);
      cut.insert(v2);
    }
  }
  return min_cut_f;
}

std::unordered_set<int> RestoreKernel(Graph&& gr) {
  std::vector<bool> used(gr.VerticesNum(), false);
  used[0] = true;
  std::queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int v = q.front();
    used[v] = true;
    q.pop();
    for (int i = 0; i < gr.GetEdgesNums(v).size(); i++) {
      int v2 = gr.GetEdge(gr.GetEdgesNums(v)[i]).v2;
      if (!used[v2] && gr.GetEdge(gr.GetEdgesNums(v)[i]).cap > gr.GetEdge(gr.GetEdgesNums(v)[i]).f) {
        q.push(v2);
      }
    }
  }
  std::unordered_set<int> ker;
  for (int i = 1; i < gr.VerticesNum(); i++) {
    if (!used[i]) {
      ker.insert(i);
    }
  }
  ker.erase(dest);
  ker.erase(start);
  return ker;
}

std::unordered_set<int> FindKernel(int n, std::vector<SimpleEdge>&& input_edges, std::vector<int>&& deg) {
  size_t m = input_edges.size();
  double l = 0, r = m;
  for (int j = 0; j < kIterationNum; j++) {
    double mid = (l + r) / 2;
    UC uc(n + 2);
    Graph gr(n + 2, m + 2 * n);
    for (int i = 0; i < m; ++i) {
      gr.AddEdges(input_edges[i].v1, input_edges[i].v2, 1);
      //gr.AddEdges(input_edges[i].v2, input_edges[i].v1, 1);
    }
    for (int i = 1; i <= n; ++i) {
      gr.AddEdge(start, i, mid * 2);
      gr.AddEdge(i, dest, deg[i]);
    }
    if (FindMaxFlow(gr, uc) < (double)(2 * m) - double(1)/INF) {
      l = mid;
    } else {
      r = mid;
    }
    if (j == kIterationNum - 1) return std::move(RestoreKernel(std::move(gr)));
  }
}

int main() {
  int n, m;
  std::cin >> n >> m;
  if (m == 0) {
    std::cout << 1 << '\n' << 1;
    return 0;
  }
  std::vector<int> deg(n + 1, 0);
  std::vector<SimpleEdge> input_edges;
  start = 0;
  dest = n + 1;
  for (int i = 0; i < m; ++i) {
    int v1, v2;
    std::cin >> v1 >> v2;
    ++deg[v1];
    ++deg[v2];
    input_edges.push_back(SimpleEdge(v1, v2));
  }
  std::unordered_set<int> ker_verts =
          std::move(FindKernel(n, std::move(input_edges), std::move(deg)));
  std::cout << ker_verts.size() << '\n';
  for (auto vert : ker_verts) {
    std::cout << vert << '\n';
  }
}
