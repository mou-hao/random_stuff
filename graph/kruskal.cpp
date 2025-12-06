#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <unordered_set>
#include <vector>

#include "util.h"

using AdjacencyMatrix = std::vector<std::vector<int>>;

class DisjointSets {
 public:
  DisjointSets(int n) : parent_(n, -1), rank_(n, 0) {}

  int find(int v) {
    if (parent_[v] == -1) {
      return v;
    }
    return parent_[v] = find(parent_[v]);
  }

  void join(int u, int v) {
    int s1 = find(u);
    int s2 = find(v);
    if (s1 != s2) {
      if (rank_[s1] < rank_[s2]) {
        parent_[s1] = s2;
        rank_[s2] += rank_[s1];
      } else {
        parent_[s2] = s1;
        rank_[s1] += rank_[s2];
      }
    }
  }

 private:
  std::vector<int> parent_;
  std::vector<int> rank_;
};

int kruskal(const AdjacencyMatrix& adjacency) {
  int N = adjacency.size();

  // Add edges to a priority queue.
  using Edge = std::pair<int, std::pair<int, int>>;
  std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> q;
  for (int i = 0; i < N; ++i) {
    for (int j = i + 1; j < N; ++j) {
      if (adjacency[i][j] == std::numeric_limits<int>::max()) continue;
      q.push({adjacency[i][j], {i, j}});
    }
  }

  // Kruskal.
  DisjointSets sets(N);
  int res = 0;
  int num_edge = 0;
  while (num_edge < N - 1) {
    Edge e = q.top();
    q.pop();
    int u = e.second.first;
    int v = e.second.second;
    if (sets.find(u) != sets.find(v)) {
      res += e.first;
      sets.join(u, v);
      ++num_edge;
    }
  }

  return res;
}

int main(int argc, char **argv) {
  const char *usage = "Usage: kruskal GRAPH_FILE\n";
  if (argc != 2) {
    std::cerr << usage;
    return 1;
  }

  std::ifstream graph_file(argv[1]);
  auto adjacency = load_graph_file(graph_file);

  std::cout << "Total of cost in the minimum spanning tree: " << kruskal(adjacency)
            << "\n";
  return 0;
}
