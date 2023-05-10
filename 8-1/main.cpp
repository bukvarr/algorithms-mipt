#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

const int kMaxDist = 2009000999;

struct Edge {
 public:
  int vert;
  int len;
  Edge(int vert, int num) : vert(vert), len(num) {}
};

struct Node {
 public:
  int vert;
  long long dist;

  Node() = default;

  Node(int vert, long long dist) : vert(vert), dist(dist) {}

  Node(const Node& other) : vert(other.vert), dist(other.dist) {}

  Node(Node&& other)
          : vert(std::move(other.vert)), dist(std::move(other.dist)) {}

  bool operator<(const Node& other) const {
    if (dist != other.dist) {
      return dist < other.dist;
    }
    return vert < other.vert;
  }

  Node& operator=(const Node& other) {
    vert = other.vert;
    dist = other.dist;
    return *this;
  }

  ~Node() = default;
};

struct Comp {
 public:
  bool operator()(const Node& left, const Node& right) const {
    return left < right;
  }
};

class Graph {
 public:
  Graph(int n) : vert_num_(n), edge_lists_(std::vector<std::vector<Edge>>(n)) {}

  Graph() = delete;

  void AddEdge(int v1, Edge ee) { edge_lists_[v1].push_back(ee); }

  const std::vector<Edge>& GetNeighbours(int vv) const {
    return edge_lists_[vv];
  }

  int VerticesNum() const { return vert_num_; }

 private:
  int vert_num_;
  std::vector<std::vector<Edge>> edge_lists_;
};

std::istream& operator>>(std::istream& in, Graph& gg) {
  int mm;
  in >> mm;
  for (int i = 0; i < mm; ++i) {
    int v1;
    int v2;
    int len;
    in >> v1 >> v2 >> len;
    gg.AddEdge(v1, Edge(v2, len));
    gg.AddEdge(v2, Edge(v1, len));
  }
  return in;
}

std::vector<long long> FindDistsToStart(Graph& gg, int start_v) {
  std::vector<long long> dists =
          std::vector<long long>(gg.VerticesNum(), kMaxDist);
  std::set<Node, Comp> unused;
  for (int i = 0; i < gg.VerticesNum(); ++i) {
    unused.insert(Node(i, dists[i]));
  }
  int vert = start_v;
  unused.erase(Node(vert, dists[vert]));
  dists[vert] = 0;
  unused.insert(Node(vert, dists[vert]));
  auto it = unused.begin();
  Node nearest = *it;
  unused.erase(it);
  dists[nearest.vert] = nearest.dist;
  int curr_v = nearest.vert;
  while (!unused.empty()) {
    auto vit = gg.GetNeighbours(curr_v).begin();
    long long dist = dists[curr_v];
    for (; vit != gg.GetNeighbours(curr_v).end(); ++vit) {
      if (dist + vit->len < dists[vit->vert]) {
        int vert = vit->vert;
        unused.erase(Node(vert, dists[vert]));
        dists[vert] = dist + vit->len;
        unused.insert(Node(vert, dists[vert]));
      }
    }
    it = unused.begin();
    Node nearest = *it;
    unused.erase(it);
    dists[nearest.vert] = nearest.dist;
    curr_v = nearest.vert;
  }
  return dists;
}

int main() {
  int kk;
  std::cin >> kk;
  for (int i = 0; i < kk; ++i) {
    int v_num;
    std::cin >> v_num;
    Graph gg(v_num);
    std::cin >> gg;
    int start_v;
    std::cin >> start_v;
    std::vector<long long> dists = FindDistsToStart(gg, start_v);
    for (auto dist : dists) {
      std::cout << dist << ' ';
    }
  }
}