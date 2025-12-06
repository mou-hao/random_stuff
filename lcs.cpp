#include <string>
#include <algorithm>
#include <iostream>
#include <vector>

// Longest common substring
// DP

int lcs(std::string& str1, std::string& str2) {
  // To achive O(min(M,N)) space, we always pass the shorter string to str1
  size_t M = str1.size();
  std::vector<int> this_row(M+1, 0);
  std::vector<int> last_row(M+1, 0);
  for (const char& c : str2) {
    std::swap(this_row, last_row);
    for (size_t i = 0; i < M; ++i) {
      if (str1[i] == c) {
        this_row[i+1] = last_row[i]+1;
      } else {
        this_row[i+1] = std::max(last_row[i+1], this_row[i]);
      }
    }
  }
  return this_row[M];
}

int main() {
  std::string str1, str2;
  std::cout << "Find the length of longest common substring\n"
            << "-------------------------------------------\n"
            << "string1:" << std::endl;
  std::getline(std::cin, str1);
  std::cout << "string2:" << std::endl;
  std::getline(std::cin, str2);
  int res;
  if (str1.size() <= str2.size())
    res = lcs(str1, str2);
  else
    res = lcs(str2, str1);
  std::cout << "len(lcs): " << res << std::endl;
}
