#include <fstream>
#include <iostream>
#include <limits>
#include <utility>
#include <queue>
#include <vector>

#include "util.h"

std::vector<int> dijkstra(const std::vector<std::vector<int>> &adjacency) {
  if (adjacency.empty()) return {};

  std::vector<int> res(adjacency.size(), std::numeric_limits<int>::max());
  using Pii = std::pair<int, int>;
  auto cmp = [](Pii left, Pii right) { return left.second > right.second; };
  std::priority_queue<Pii, std::vector<Pii>, decltype(cmp)> to_visit(cmp);
  to_visit.push({0, 0});

  while (to_visit.size()) {
    auto [node, dist] = to_visit.top();
    to_visit.pop();
    if (dist >= res[node]) continue;
    res[node] = dist;

    const std::vector<int>& neighbors = adjacency[node];
    for (int i = 0; i < neighbors.size(); ++i) {
      if (i == node || neighbors[i] == std::numeric_limits<int>::max()) continue;
      int new_dist = res[node] + neighbors[i];
      if (new_dist < res[i]) {
        res[i] = new_dist;
        to_visit.push({i, new_dist});
      }
    }
  }

  return res;
}

int main(int argc, char **argv) {
  const char *usage = "Usage: dijkstra GRAPH_FILE\n";
  if (argc != 2) {
    std::cerr << usage;
    return 1;
  }

  std::ifstream graph_file(argv[1]);
  auto adjacency = load_graph_file(graph_file);

  std::vector<int> shortest_dists = dijkstra(adjacency);
  std::cout << "Shortest distance from node 0 to each node:\n";
  for (int dist : shortest_dists) {
    std::cout << dist << ' ';
  }
  std::cout << '\n';

  return 0;
}
