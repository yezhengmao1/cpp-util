#ifndef BINARYSEARCH_H_
#define BINARYSEARCH_H_

#include <algorithm>

template<class It>
using value_type_t = typename std::iterator_traits<It>::value_type;

template<class It, class T = value_type_t<It>, class Compare = std::less<value_type_t<It>>>
It UpperBound(It first, It end, const T& value, Compare cmp = Compare()) {
    auto count = std::distance(first, end);
    auto it = first;
    while (count > 0) {
        it = first;
        auto step = count / 2;
        std::advance(it, step);
        if (!cmp(value, *it)) {
            first = ++it;
            count -= step + 1;
        }else {
            count = step;
        }
    }
    return first;
}

template<class It, class T = value_type_t<It>, class Compare = std::less<value_type_t<It>>>
It Lowerbound(It first, It end, const T& value, Compare cmp = Compare()) {
    auto count = std::distance(first, end);
    auto it = first;
    while (count > 0) {
        it = first;
        auto step = count / 2;
        std::advance(it, step);
        if (cmp(*it, value)) {
            first = ++it;
            count -= step + 1;
        }else {
            count = step;
        }
    }
    return first;
}

template<class It, class T = value_type_t<It>, class Compare = std::less<value_type_t<It>>>
bool BinarySearch(It first, It end, const T& value, Compare cmp = Compare()) {
    first = Lowerbound(first, end, value, cmp);
    return (!(first == end) && !(cmp(value, *first)));
}

#endif
