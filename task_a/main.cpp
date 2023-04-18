/*Найти цикл отрицательного веса*/

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

const int kMaxDist = 10000000;
const int kNoEdge = 100000;

struct Edge {
    Edge(int vert, int len) : vert(vert), len(len) {}

    int vert;
    int len;
};

struct Path {
    Path(int dist, int prev) : dist(dist), prev(prev){};
    Path() = default;
    Path(const Path& other) : dist(other.dist), prev(other.prev){};

    Path& operator=(const Path& other) {
      dist = other.dist;
      prev = other.prev;
      return *this;
    }

    int dist;
    int prev = -1;
};

class Graph {
 private:
  int vert_num_;
  std::vector<std::vector<Edge>> edge_lists_;

 public:
  int loop_found = -1;
  Graph(int n) : vert_num_(n), edge_lists_(std::vector<std::vector<Edge>>(n)) {}

  Graph() = default;

  void AddEdge(int v1, Edge ee) { edge_lists_[v1].push_back(ee); }

  const std::vector<Edge>& GetNeighbours(int vv) const {
    return edge_lists_[vv];
  }

  int VerticesNum() const { return vert_num_; }
};

std::istream& operator>>(std::istream& in, Graph& gg) {
  for (int i = 0; i < gg.VerticesNum(); ++i) {
    for (int j = 0; j < gg.VerticesNum(); ++j) {
      int len;
      in >> len;
      if (len != kNoEdge) {
        gg.AddEdge(j, Edge(i, len));
      }
      if (i == j && len < 0) {
        gg.loop_found = i;
      }
    }
  }
  return in;
}

void AnswerFinding(std::vector<int>& ans, std::vector<std::vector<Path>>& dp,
                   int last_v, int finish, int n) {
  int curr_v = last_v;
  int curr_i = finish;
  std::vector<int> sequence;
  std::vector<int> count(n, 0);
  sequence.push_back(curr_v);
  ++count[curr_v];
  curr_v = dp[finish][curr_v].prev;
  sequence.push_back(curr_v);
  ++count[curr_v];
  int start = -1;
  while (curr_i != 0) {
    curr_v = dp[curr_i][curr_v].prev;
    --curr_i;
    sequence.push_back(curr_v);
    ++count[curr_v];
    if (count[curr_v] == 2) {
      start = curr_v;
      break;
    }
  }
  int ii = static_cast<int>(sequence.size()) - 1;
  while (sequence[ii] != start) {
    --ii;
  }
  ans.push_back(sequence[ii]);
  --ii;
  while (sequence[ii] != start) {
    ans.push_back(sequence[ii]);
    --ii;
  }
  ans.push_back(sequence[ii]);
}

void FindingCycle(Graph& gg, std::vector<std::vector<Path>>& dp, int finish,
                  std::vector<int>& ans) {
  for (int j = 0; j < gg.VerticesNum(); ++j) {
    auto it = gg.GetNeighbours(j).cbegin();
    for (; it != gg.GetNeighbours(j).cend(); ++it) {
      if (dp[finish][it->vert].dist == kMaxDist) {
        continue;
      }
      if (dp[finish][j].dist > dp[finish][it->vert].dist + it->len) {
        dp[finish][j].prev = it->vert;
        AnswerFinding(ans, dp, j, finish, gg.VerticesNum());
        return;
      }
    }
  }
}

void FindNegativeCycleFromStart(Graph& gg, int start_v,
                                std::vector<bool>& unused,
                                std::vector<int>& ans,
                                std::vector<std::vector<Path>>& dp) {
  dp[0][start_v].dist = 0;
  unused[start_v] = false;
  int added_count = 0;
  int finish = gg.VerticesNum() - 1;
  for (int i = 1; i < gg.VerticesNum(); ++i) {
    bool changed = false;
    for (int j = 0; j < gg.VerticesNum(); ++j) {
      dp[i][j] = dp[i - 1][j];
      auto it = gg.GetNeighbours(j).cbegin();
      for (; it != gg.GetNeighbours(j).cend(); ++it) {
        if (dp[finish][it->vert].dist == kMaxDist) {
          continue;
        }
        if (dp[i][j].dist > dp[i - 1][it->vert].dist + it->len) {
          if (dp[i][j].dist == kMaxDist) {
            ++added_count;
          }
          changed = true;
          unused[j] = false;
          dp[i][j].dist = dp[i - 1][it->vert].dist + it->len;
          dp[i][j].prev = it->vert;
        }
      }
    }
    if (!changed) {
      return;
    }
    if (i > added_count) {
      finish = i - 1;
      break;
    }
  }
  FindingCycle(gg, dp, finish, ans);
}

void FindNegativeCycle(Graph& gg, std::vector<int>& ans) {
  if (gg.loop_found != -1) {
    ans.push_back(gg.loop_found);
    ans.push_back(gg.loop_found);
    return;
  }
  std::vector<std::vector<Path>> dp(gg.VerticesNum(),
                                    std::vector<Path>(gg.VerticesNum()));
  std::vector<bool> unused(gg.VerticesNum(), true);
  for (int i = 0; i < gg.VerticesNum(); ++i) {
    if (!unused[i]) {
      continue;
    }
    for (int i = 0; i < gg.VerticesNum(); ++i) {
      dp[0][i].dist = kMaxDist;
    }
    FindNegativeCycleFromStart(gg, i, unused, ans, dp);
    if (!ans.empty()) {
      return;
    }
  }
}

int main() {
  int v_num;
  std::cin >> v_num;
  Graph gg(v_num);
  std::cin >> gg;
  std::vector<int> res;
  FindNegativeCycle(gg, res);
  std::cout << (res.empty() ? "NO" : "YES") << '\n';
  if (!res.empty()) {
    std::cout << res.size() << '\n';
    for (size_t i = 0; i < res.size(); ++i) {
      std::cout << res[i] + 1 << " ";
    }
  }
}