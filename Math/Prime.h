#ifndef PRIME_H_
#define PRIME_H_

#include <utility>

template<unsigned i, unsigned head, unsigned ...tail>
struct IsPrime {
  using value = typename std::conditional<i % head != 0,
                                 typename IsPrime<i, tail...>::value,
                                 std::false_type>::type;
};

template<unsigned i, unsigned head>
struct IsPrime<i, head> {
  using value = typename std::conditional<i % head != 0,
                                std::true_type,
                                std::false_type>::type;
};

template<unsigned i, typename T>
struct AppendPrime;

template<unsigned i, unsigned ...args>
struct AppendPrime<i, std::integer_sequence<unsigned, args...>> {
  using value = typename std::conditional<IsPrime<i, args...>::value::value,
                           std::integer_sequence<unsigned, i, args...>,
                           std::integer_sequence<unsigned, args...>>::type;
};

template<unsigned N>
struct PrimeTable {
  using value = typename AppendPrime<N, typename PrimeTable<N-1>::value>::value;
};

template<>
struct PrimeTable<2> {
  using value = std::integer_sequence<unsigned, 2>;
};

#endif
