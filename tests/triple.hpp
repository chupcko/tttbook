#ifndef __TRIPLET__HPP__
#define __TRIPLET__HPP__

namespace test_utility
{

  template <class C1, class C2, class C3>
  struct triplet
  {
    typedef C1 type_1;
    typedef C2 type_2;
    typedef C3 type_3;

    C1 element_1;
    C2 element_2;
    C3 element_3;
  };

  template <std::size_t N, class C>
  struct tuple_element;

  template <class C1, class C2, class C3>
  struct tuple_element<0, triplet<C1, C2, C3>>
  {
    typedef C1 type;
  };

  template <class C1, class C2, class C3>
  struct tuple_element<1, triplet<C1, C2, C3>>
  {
    typedef C2 type;
  };

  template <class C1, class C2, class C3>
  struct tuple_element<2, triplet<C1, C2, C3>>
  {
    typedef C3 type;
  };

  template <std::size_t N>
  struct __triple_get;

  template<>
  struct __triple_get<0>
  {
    template <typename C1, typename C2, typename C3>
    static constexpr C1& __get(triplet<C1, C2, C3>& t) noexcept
    {
      return t.element_1;
    }
    template <typename C1, typename C2, typename C3>
    static constexpr C1&& __move_get(triplet<C1, C2, C3>&& t) noexcept
    {
      return std::forward<C1>(t.element_1);
    }
    template <typename C1, typename C2, typename C3>
    static constexpr const C1& __const_get(const triplet<C1, C2, C3>& t) noexcept
    {
      return t.element_1;
    }
  };

  template<>
  struct __triple_get<1>
  {
    template <typename C1, typename C2, typename C3>
    static constexpr C2& __get(triplet<C1, C2, C3>& t) noexcept
    {
      return t.element_2;
    }
    template <typename C1, typename C2, typename C3>
    static constexpr C2&& __move_get(triplet<C1, C2, C3>&& t) noexcept
    {
      return std::forward<C1>(t.element_2);
    }
    template <typename C1, typename C2, typename C3>
    static constexpr const C2& __const_get(const triplet<C1, C2, C3>& t) noexcept
    {
      return t.element_2;
    }
  };

  template<>
  struct __triple_get<2>
  {
    template <typename C1, typename C2, typename C3>
    static constexpr C3& __get(triplet<C1, C2, C3>& t) noexcept
    {
      return t.element_3;
    }
    template <typename C1, typename C2, typename C3>
    static constexpr C3&& __move_get(triplet<C1, C2, C3>&& t) noexcept
    {
      return std::forward<C1>(t.element_2);
    }
    template <typename C1, typename C2, typename C3>
    static constexpr const C3& __const_get(const triplet<C1, C2, C3>& t) noexcept
    {
      return t.element_3;
    }
  };

  template <std::size_t N, class C1, class C2, class C3>
  constexpr typename tuple_element<N, triplet<C1, C2, C3>>::type& get(triplet<C1, C2, C3>& t) noexcept
  {
    return __triple_get<N>::__get(t);
  }

  template <std::size_t N, class C1, class C2, class C3>
  constexpr typename tuple_element<N, triplet<C1, C2, C3>>::type&& get(triplet<C1, C2, C3>&& t) noexcept
  {
    return __triple_get<N>::__move_get(std::move(t));
  }

  template <std::size_t N, class C1, class C2, class C3>
  constexpr const typename tuple_element<N, triplet<C1, C2, C3>>::type& get(const triplet<C1, C2, C3>& t) noexcept
  {
    return __triple_get<N>::__const_get(t);
  }

}

#endif
