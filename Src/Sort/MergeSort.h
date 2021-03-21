#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <Sort.h>

template<class It, class Compare = std::less<value_type_t<It>>>
void MergeSort(It begin, It end, Compare cmp = Compare()) {
    const auto N = std::distance(begin, end);
    if(N <= 1) {
        return;
    }
    const auto mid = std::next(begin, N/2);
    MergeSort(begin, mid, cmp);
    MergeSort(mid, end, cmp);
    std::inplace_merge(begin, mid, end);
}

#endif
