#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

const int kBlockLen = 3;

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
 private:
  int vert_num_;
  std::vector<std::vector<Edge>> edge_lists_;
  std::vector<long long> dists_;
  std::set<Node, Comp> unused_;

 public:
  Graph(int n)
          : vert_num_(n),
            edge_lists_(std::vector<std::vector<Edge>>(n)),
            dists_(std::vector<long long>(vert_num_, kMaxDist)) {
    for (int i = 0; i < vert_num_; ++i) {
      unused_.insert(Node(i, dists_[i]));
    }
  }

  Graph() = default;

  void AddEdge(int v1, Edge ee) { edge_lists_[v1].push_back(ee); }

  const std::vector<Edge>& GetNeighbours(int vv) const {
    return edge_lists_[vv];
  }

  int VerticesNum() const { return vert_num_; }

  void DistUpd(int vert, long long new_dist) {
    unused_.erase(Node(vert, dists_[vert]));
    dists_[vert] = new_dist;
    unused_.insert(Node(vert, dists_[vert]));
  }

  int GetDist(int vv) { return dists_[vv]; }

  bool UnusedExists() { return !(unused_.empty()); }

  int GetNearestUnused() {
    auto it = unused_.begin();
    Node nearest = *it;
    unused_.erase(it);
    dists_[nearest.vert] = nearest.dist;
    return nearest.vert;
  }
};

void AddEdges(Graph& gg, const std::vector<int>& inp) {
  size_t b_len = kBlockLen;
  for (size_t i = 0; i < inp.size() / b_len; ++i) {
    int v1 = inp[i * b_len];
    int v2 = inp[i * b_len + 1];
    long long len = static_cast<long long>(inp[i * b_len + 2]);
    gg.AddEdge(v1, Edge(v2, len));
    gg.AddEdge(v2, Edge(v1, len));
  }
}

std::string FindDistsToStart(Graph& gg, int start_v) {
  gg.DistUpd(start_v, 0);
  int curr_v = gg.GetNearestUnused();
  while (gg.UnusedExists()) {
    auto it = gg.GetNeighbours(curr_v).begin();
    long long dist = gg.GetDist(curr_v);
    for (; it != gg.GetNeighbours(curr_v).end(); ++it) {
      if (dist + it->len < gg.GetDist(it->vert)) {
        gg.DistUpd(it->vert, dist + it->len);
      }
    }
    curr_v = gg.GetNearestUnused();
  }
  std::string ss;
  for (int i = 0; i < gg.VerticesNum(); ++i) {
    ss += std::to_string(gg.GetDist(i)) + " ";
  }
  return ss;
}

void Main1() {
  int kk;
  int nn;
  int mm;
  std::cin >> kk;
  for (int i = 0; i < kk; ++i) {
    std::cin >> nn >> mm;
    Graph gg(nn);
    std::vector<int> inp(mm * kBlockLen);
    for (int j = 0; j < mm * kBlockLen; ++j) {
      std::cin >> inp[j];
    }
    AddEdges(gg, inp);
    int start_v;
    std::cin >> start_v;
    std::cout << FindDistsToStart(gg, start_v) << '\n';
  }
}

int main() { Main1(); }