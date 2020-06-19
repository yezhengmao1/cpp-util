#ifndef PERMUTATION_H_
#define PERMUTATION_H_

#include <algorithm>

template<class It, class Compare = std::less<typename std::iterator_traits<It>::value_type>>
constexpr bool NextPermutation(It first, It last, Compare Cmp = Compare()) {
  if(first == last) { return false; }
  It i = last;
  if(first == --i) { return false; }
  while(true) {
    It ii = i;
    if(Cmp(*--i, *ii)) {
      It j = last;
      while(!Cmp(*i, *--j)) {}
      std::iter_swap(i, j);
      std::reverse(ii, last);
      return true;
    }
    if(i == first) {
      std::reverse(first, last);
      return false;
    }
  }
}

template<class It, class Compare = std::less<typename std::iterator_traits<It>::value_type>>
constexpr bool PrevPermutation(It first, It last, Compare Cmp = Compare()) {
  if(first == last) { return false; }
  It i = last;
  if(first == --i) { return false; }
  while(true) {
    It ii = i;
    if(Cmp(*ii, *--i)) {
      It j = last;
      while(!Cmp(*--j, *i)) {}
      std::iter_swap(i, j);
      std::reverse(ii, last);
      return true;
    }
    if(i == first) {
      std::reverse(first, last);
      return false;
    }
  }
}

#endif
