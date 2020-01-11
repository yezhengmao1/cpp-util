#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_

#include <Sort.h>

template<class It, class Compare = std::less<value_type_t<It>>>
void BubbleSort(It begin, It end, Compare cmp = Compare()) {
    bool sorted = false;
    for(auto it = end; it != begin && !sorted;) {
        sorted = true;
        auto nit = std::prev(it);
        for(auto fwdit = std::next(begin); fwdit != it; fwdit = std::next(fwdit)) {
            if(cmp(*fwdit, *std::prev(fwdit))) {
                std::iter_swap(fwdit, std::prev(fwdit));
                sorted = false;
                nit = fwdit;
            }
        }
        it = nit;
    }
}

#endif
