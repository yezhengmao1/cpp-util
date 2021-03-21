#ifndef HEAPSORT_H_
#define HEAPSORT_H_

#include <Sort.h>

template<class It, class Compare = std::less<value_type_t<It>>>
void MakeHeap(It begin, It end, Compare cmp = Compare()) {
    for(It fwdit = begin; fwdit != end;) {
        fwdit = std::next(fwdit);
        std::make_heap(begin, fwdit, cmp);
    }
}

template<class It, class Compare = std::less<value_type_t<It>>>
void SortHeap(It begin, It end, Compare cmp = Compare()) {
    for(It bakit = end; bakit != begin;) {
        std::pop_heap(begin, bakit, cmp);
        bakit = std::prev(bakit);
    }
}

template<class It, class Compare = std::less<value_type_t<It>>>
void RandomAccessAdjustHeap(It begin, It end, It root, Compare cmp = Compare()) {
    auto son = (root - begin) * 2 + 1 + begin;
    while(son < end) {
        if(son + 1 < end && cmp(*son, *(son+1))) {
            son++;
        }
        if(cmp(*son, *root)) return;
        std::iter_swap(son, root);
        root = son;
        son = (root - begin) * 2 + 1 + begin;
    }
}

template<class It, class Compare = std::less<value_type_t<It>>>
void RandomAccessMakeHeap(It begin, It end, Compare cmp = Compare()) {
    const auto N = std::distance(begin, end);
    if(N <= 1) {
        return;
    }
    for(auto root = std::next(begin, (N-2)/2); root >= begin; --root) {
        RandomAccessAdjustHeap(begin, end, root, cmp);
    }
}

template<class It, class Compare = std::less<value_type_t<It>>>
void RandomAccessSortHeap(It begin, It end, Compare cmp = Compare()) {
    const auto N = std::distance(begin, end);
    if(N <= 1) {
        return;
    }
    auto last = std::prev(end);
    while(begin != last) {
        std::iter_swap(begin, last);
        RandomAccessAdjustHeap(begin, last, begin, cmp);
        last = std::prev(last);
    }
}


template<class It, class Compare = std::less<value_type_t<It>>>
void HeapSort(It begin, It end, Compare cmp = Compare()) {
    RandomAccessMakeHeap(begin, end, cmp);
    RandomAccessSortHeap(begin, end, cmp);
}


#endif
