#include <fstream>
#include <iostream>
#include <limits>
#include <vector>

#include "util.h"

std::vector<std::vector<int>> floyd_warhsall(const std::vector<std::vector<int>>& adjacency) {
  if (adjacency.empty()) return {};

  std::vector<std::vector<int>> dists = adjacency;
  int N = adjacency.size();
  for (int i = 0; i < N; ++i) {
    dists[i][i] = 0;
  }
  for (int k = 0; k < N; ++k) {
    for (int u = 0; u < N; ++u) {
      for (int v = 0; v < N; ++v) {
        if (dists[u][k] != std::numeric_limits<int>::max() &&
            dists[k][v] != std::numeric_limits<int>::max() &&
            dists[u][v] > dists[u][k] + dists[k][v]) {
          dists[u][v] = dists[u][k] + dists[k][v];
        }
      }
    }
  }
  return dists;
}

int main(int argc, char **argv) {
  const char *usage = "Usage: floyd_warhsall GRAPH_FILE\n";
  if (argc != 2) {
    std::cerr << usage;
    return 1;
  }

  std::ifstream graph_file(argv[1]);
  auto adjacency = load_graph_file(graph_file);

  std::vector<std::vector<int>> shortest_dists = floyd_warhsall(adjacency);
  for (int i = 0; i < shortest_dists.size(); ++i) {
    for (int j = 0; j < shortest_dists.size(); ++j) {
      std::cout << shortest_dists[i][j] << '\t';
    }
    std::cout << '\n';
  }

  return 0;
}
