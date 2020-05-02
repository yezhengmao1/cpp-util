#ifndef PRIME_H_
#define PRIME_H_

#include <csignal>
#include <utility>

template<unsigned i, typename T>
struct IsPrime { };

template<unsigned i, unsigned head, unsigned ...args>
struct IsPrime<i, std::integer_sequence<unsigned, head, args...>> {
  using value = typename std::conditional<
      i % head == 0,
      std::false_type,
      typename IsPrime<i, std::integer_sequence<unsigned, args...>>::value
  >::type;
};

template<unsigned i, unsigned head>
struct IsPrime<i, std::integer_sequence<unsigned, head>> {
  using value = typename std::conditional<
      i % head == 0,
      std::false_type,
      std::true_type
    >::type;
};

template<typename T, typename U>
struct Concat;

template<unsigned ...l, unsigned ...r>
struct Concat<std::integer_sequence<unsigned, l...>, std::integer_sequence<unsigned, r...>> {
  using value = typename std::integer_sequence<unsigned, l..., r...>;
};

template<unsigned N, typename T>
struct ConcatPrime { };

template<unsigned N, unsigned ...args>
struct ConcatPrime<N, std::integer_sequence<unsigned, args...>> {
  using value = typename std::conditional<
      IsPrime<N, std::integer_sequence<unsigned, args...>>::value::value,
      std::integer_sequence<unsigned, N, args...>,
      std::integer_sequence<unsigned, args...>
    >::type;
};

template<unsigned L, unsigned R, typename T>
struct Table { };

template<unsigned L, unsigned R, unsigned ...args>
struct Table<L, R, std::integer_sequence<unsigned, args...>> {
  using value = typename Concat<
    typename std::conditional<
        IsPrime<R, std::integer_sequence<unsigned, args...>>::value::value,
        std::integer_sequence<unsigned, R>,
        std::integer_sequence<unsigned>
      >::type,
    typename Table<L, R-1, std::integer_sequence<unsigned, args...>>::value
  >::value;
};

template<unsigned N, unsigned ...args>
struct Table<N, N, std::integer_sequence<unsigned, args...>> {
  using value = typename std::conditional<
      IsPrime<N, std::integer_sequence<unsigned, args...>>::value::value,
      std::integer_sequence<unsigned, N>,
      std::integer_sequence<unsigned>
    >::type;
};

template<unsigned N>
struct PrimeTable {
  using value = typename ConcatPrime<N, typename PrimeTable<N-1>::value>::value;
};

template<>
struct PrimeTable<2> {
  using value = std::integer_sequence<unsigned, 2>;
};

#endif
