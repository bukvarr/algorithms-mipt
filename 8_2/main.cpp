//Требуется найти в связном графе остовное дерево минимального веса.

#include <iostream>
#include <vector>

struct Edge {
    Edge(int v1, int v2, int len) : v1(v1), v2(v2), len(len) {}

    int v1;
    int v2;
    int len;
};

class Graph {
 public:
  Graph(int n, int m) : vert_num_(n), edge_num_(m) {}

  Graph() = delete;

  void AddEdge(Edge ee) { edge_list_.push_back(ee); }

  const Edge& GetEdge(int num) const { return edge_list_[num]; }

  int VerticesNum() const { return vert_num_; }

  int EdgesNum() const { return edge_num_; }

 private:
  int vert_num_;
  int edge_num_;
  std::vector<Edge> edge_list_;
};

std::istream& operator>>(std::istream& in, Graph& gg) {
  for (int i = 0; i < gg.EdgesNum(); ++i) {
    int v1, v2, len;
    std::cin >> v1 >> v2 >> len;
    gg.AddEdge(Edge(v1 - 1, v2 - 1, len));
  }
  return in;
}

struct DSU {
 private:
  int el_count;
  std::vector<int> parent;
  std::vector<int> size;

 public:
  void MakeSet (int vert) {
    parent[vert] = vert;
    size[vert] = 1;
  }

  int FindSet (int vert) {
    if (vert == parent[vert]) {
      return vert;
    }
    return parent[vert] = FindSet(parent[vert]);
  }

  void UnionSets (int v1, int v2) {
    v1 = FindSet(v1);
    v2 = FindSet(v2);
    if (v1 != v2) {
      if (size[v1] < size[v2]) {
        std::swap(v1, v2);
      }
      parent[v1] = v2;
      size[v1] += size[v2];
    }
  }

  bool CheckConnection (int v1, int v2) {
    return FindSet(v1) == FindSet(v2);
  }

  DSU(int el_count) : el_count(el_count), parent(std::vector<int>(el_count)), size(std::vector<int>(el_count)) {
    for (int i = 0; i < el_count; ++i) {
      MakeSet(i);
    }
  }
};

int FindMST (const Graph& gg) {
  int min_len = 0;
  std::vector<int> min_len_edge(gg.VerticesNum());
  DSU dsu(gg.VerticesNum());
  int comp_count = gg.VerticesNum();
  while (comp_count != 1) {
    for (size_t i = 0; i < min_len_edge.size(); ++i) {
      min_len_edge[i] = -1;
    }
    for (int i = 0; i < gg.EdgesNum(); ++i) {
      Edge curr_edge = gg.GetEdge(i);
      int set1 = curr_edge.v1;
      int set2 = curr_edge.v2;
      set1 = dsu.FindSet(set1);
      set2 = dsu.FindSet(set2);
      if (set1 == set2) {
        continue;
      }
      if (min_len_edge[set1] == -1 || curr_edge.len < gg.GetEdge(min_len_edge[set1]).len) {
        min_len_edge[set1] = i;
      }
      if (min_len_edge[set2] == -1 || curr_edge.len < gg.GetEdge(min_len_edge[set2]).len) {
        min_len_edge[set2] = i;
      }
    }
    for (int i = 0; i < gg.VerticesNum(); ++i) {
      if (min_len_edge[i] != -1) {
        Edge curr_edge = gg.GetEdge(min_len_edge[i]);
        if (dsu.FindSet(curr_edge.v1) != dsu.FindSet(curr_edge.v2)) {
          dsu.UnionSets(curr_edge.v1, curr_edge.v2);
          min_len += curr_edge.len;
          --comp_count;
        }
      }
    }
  }
  return min_len;
}

int main() {
  int v_num, e_num;
  std::cin >> v_num >> e_num;
  Graph gg(v_num, e_num);
  std::cin >> gg;
  std::cout << FindMST(gg);
  return 0;
}

