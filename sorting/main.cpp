#include <vector>
#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <utility>

#include "merge_sort.hpp"
#include "heap_sort.hpp"
#include "quick_sort.hpp"

int main() {
    std::cerr << "Enter a whitespace separated list of intergers, "
              << "and I will sort it for you:\n";
    std::string nums_s;
    std::getline(std::cin, nums_s);
    std::istringstream nums_ss(nums_s);
    std::vector<int> nums;
    int num;
    while (nums_ss >> num) nums.push_back(num);

    std::vector<std::pair<std::string, std::function<void(std::vector<int>&)>>> sorting_algos = {
        {"Merge sort (iterative)", merge_sort_iterative},
        {"Merge sort (recursive)", merge_sort_recursive},
        {"Heap sort", heap_sort},
        {"Quick sort", quick_sort},
    };
    int algo_num = -1;
    while (algo_num < 0 || algo_num >= sorting_algos.size()) {
        std::cerr << "\nChoose the algorithm to do the sorting:\n";
        for (int i = 0; i < sorting_algos.size(); ++i) {
            std::cerr << i << ". " << sorting_algos[i].first << "\n";
        }
        std::cin >> algo_num;
    }
    sorting_algos[algo_num].second(nums);

    std::cerr << "\nSorted list:";
    for (auto num : nums) {
        std::cout << std::to_string(num) << " ";
    }
    std::cout << std::endl;
    return 0;
}
