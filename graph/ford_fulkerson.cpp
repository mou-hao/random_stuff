#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

#include "util.h"

using AdjacencyMatrix = std::vector<std::vector<int>>;

bool find_path(AdjacencyMatrix& adjacency, std::vector<int>& path) {
  int N = adjacency.size();
  std::queue<int> q;
  q.push(0);
  while (q.size()) {
    int v = q.front();
    q.pop();
    for (int i = 0; i < N; ++i) {
      if (i == v || path[i] >= 0 || adjacency[i][v] == 0
          || adjacency[i][v] == std::numeric_limits<int>::max()) {
        continue;
      }
      path[i] = v;
      if (i == N - 1) return true;
      q.push(i);
    }
  }
  return false;
}

int find_flow(AdjacencyMatrix& adjacency, const std::vector<int>& path) {
  int N = adjacency.size();
  int flow = std::numeric_limits<int>::max();

  int v = N - 1;
  while (v) {
    flow = std::min(flow, adjacency[v][path[v]]);
    v = path[v];
  }

  v = N - 1;
  while (v) {
    adjacency[v][path[v]] -= flow;
    adjacency[path[v]][v] -= flow;
    v = path[v];
  }

  return flow;
}

int ford_fulkerson(AdjacencyMatrix& adjacency) {
  int N = adjacency.size();

  int max_flow = 0;
  std::vector<int> path(N, -1);
  while (find_path(adjacency, path)) {
    max_flow += find_flow(adjacency, path);
    path = std::vector<int>(N, -1);
  }

  return max_flow;
}

int main(int argc, char **argv) {
  const char *usage = "Usage: ford_fulkerson GRAPH_FILE\n";
  if (argc != 2) {
    std::cerr << usage;
    return 1;
  }

  std::ifstream graph_file(argv[1]);
  auto adjacency = load_graph_file(graph_file);

  std::cout << "Maximum flow: " << ford_fulkerson(adjacency) << '\n';
  return 0;
}
