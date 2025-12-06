#include <iostream>
#include <string>

class Hash {
 public:
  Hash(const std::string& str, size_t begin, size_t end) {
    for (size_t ind = begin; ind < end; ++ind) { hash_ += str[ind]; }
  }

  Hash(const std::string& str) : Hash(str, 0, str.size()) {}

  inline void roll(char left, char right) {
    hash_ = hash_ - left + right;
  }

  inline bool operator==(const Hash& that) const {
    return hash_ == that.hash_;
  }

 private:
  size_t hash_ = 0;
};

void RkSearch(const std::string& str, const std::string& pat) {
  if (pat.size() > str.size()) return;

  Hash p_hash = Hash(pat);
  Hash sub_hash = Hash(str, 0, pat.size());

  for (int i = 0; i < str.size() - pat.size() + 1; ++i) {
    if (i > 0) sub_hash.roll(str[i-1], str[i-1+pat.size()]);
    if (sub_hash == p_hash) {
      int j = 0;
      while (j < pat.size() && str[i+j] == pat[j]) ++j;
      if (j == pat.size()) {
        std::cout << "Found pattern at index " << i << "\n";
      }
    }
  }
}

int main() {
  std::string str;
  std::string pat;
  std::cout << "KMP algorithm: search occurences of a pattern in a string in O(n) time\n"
            << "----------------------------------------------------------------------\n"
            << "string:" << std::endl;
  std::getline(std::cin, str);
  std::cout << "pattern:" << std::endl;
  std::getline(std::cin, pat);
  RkSearch(str, pat);
  return 0;
}
