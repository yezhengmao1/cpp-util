#ifndef SELECTSORT_H_
#define SELECTSORT_H_

#include <Sort.h>

template<class It, class Compare = std::less<value_type_t<It>>>
void SelectionSort(It begin, It end, Compare cmp = Compare()) {
    for(auto it = begin; it != end; it = std::next(it)) {
        std::iter_swap(it, std::min_element(it, end, cmp));
    }
}

#endif
