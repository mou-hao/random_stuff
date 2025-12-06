#include <iostream>
#include <vector>
#include <string>

// KMP is an O(n) algorithm that searches a pattern W in a string S.

// Compute a partial match table T,
// where T[i] gives us the amount of skipping we need to do
// when a mismatch happens when S[m+i] != W[i].
// The next possible match will start at m+i-T[i],
// and we do not need to check the first T[i] characters.
// In practice, we just need to check whether S[m+i] == W[T[i-1]] if i > 0.
std::vector<int> computeLPS(std::string& pat) {
    std::vector<int> lps (pat.size());
    lps[0] = 0;
    int len = 0, i = 1;
    while (i < pat.size()) {
        if (pat[i] == pat[len]) {
            lps[i++] = ++len;
        } else {
            if (len) {
                len = lps[len-1];
            } else {
                lps[i++] = 0;
            }
        }
    }
    return lps;
}

void KMPsearch(std::string& str, std::string& pat) {
    if (!str.size() || !pat.size()) { return; }
    std::vector<int> lps { computeLPS(pat) };
    int i = 0, j = 0;
    while (i < str.size()) {
        if (str[i] == pat[j]) {
            ++i;
            ++j;
            if (j == pat.size()) {
                std::cout << "Found pattern at index " << i-j << "\n";
                j = lps[j-1];
            }
        } else {
            if (j) {
                j = lps[j-1];
            } else {
                ++i;
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
    KMPsearch(str, pat);
    return 0;
}
