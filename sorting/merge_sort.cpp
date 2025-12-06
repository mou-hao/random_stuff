#include "merge_sort.hpp"
#include <utility>

inline void merge(std::vector<int>& from, std::vector<int>& to, int start, int mid, int end) {
    int i = start, j = start, k = mid;
    for (; i < end && j < mid && k < end; ++i) {
        if (from[j] < from[k]) to[i] = from[j++];
        else to[i] = from[k++];
    }
    if (i != end) {
        j = (k == end) ? j : k;
        while (i < end) to[i++] = from[j++];
    }
}

void r_helper(std::vector<int>& nums, int start, int end, std::vector<int>& helper_v) {
    if (start+1 >= end) return;
    int mid = start + (end - start) / 2;
    r_helper(nums, start, mid, helper_v);
    r_helper(nums, mid, end, helper_v);
    merge(nums, helper_v, start, mid, end);
    for (int i = start; i < end; ++i) nums[i] = helper_v[i];
}

void iter_sort(std::vector<int>& nums1, std::vector<int>& nums2) {
    bool need_swap = false;
    int sorted_chunk_size = 1;
    int N = nums1.size();
    while (sorted_chunk_size < N) {
        std::vector<int>& from = need_swap ? nums2 : nums1;
        std::vector<int>& to = need_swap ? nums1 : nums2;
        for (int start = 0; start < N; start += sorted_chunk_size * 2) {
            int mid = std::min(start + sorted_chunk_size, N);
            int end = std::min(start + sorted_chunk_size * 2, N);
            merge(from, to, start, mid, end);
        }
        sorted_chunk_size *= 2;
        need_swap = !need_swap;
    }
    if (need_swap) swap(nums1, nums2);
}

void merge_sort_recursive(std::vector<int>& nums) {
    if (nums.size() < 2) return;
    std::vector<int> helper_v(nums.size());
    r_helper(nums, 0, nums.size(), helper_v);
}

void merge_sort_iterative(std::vector<int>& nums) {
    if (nums.size() < 2) return;
    std::vector<int> helper_v(nums.size());
    iter_sort(nums, helper_v);
}
