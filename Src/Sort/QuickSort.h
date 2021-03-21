#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include <Sort.h>

template<class It, class Compare = std::less<value_type_t<It>>>
void QuickSort(It begin, It end, Compare cmp = Compare()) {
    auto const N = std::distance(begin, end);
    if(N <= 1) {
        return;
    }
    auto const pivot = *std::next(begin, N/2);
    auto const midl = std::partition(begin, end, [=](value_type_t<It> const& elem) {
        return cmp(elem, pivot);
    });
    auto const midg = std::partition(midl, end, [=](value_type_t<It> const &elem) {
        return !cmp(pivot, elem);
    });
    QuickSort(begin, midl, cmp);
    QuickSort(midg, end, cmp);
}

#endif
