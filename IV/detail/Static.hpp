////////////////////////////////////////////////////////////////////////////////
///
////////////////////////////////////////////////////////////////////////////////

#ifndef IV_DETAIL_STATIC_HPP_
#define IV_DETAIL_STATIC_HPP_

#include <type_traits>


namespace IV {
namespace detail {
template <
  typename,
  typename Type
>
class HasOp;

template <
  typename Type,
  typename Ret,
  typename... Args
>
class HasOp<Type, Ret(Args...)> {
private:
  template <typename Functor>
  static constexpr auto
  Test(Functor*) -> typename std::is_same<
                        decltype(std::declval<Functor>().operator()(
                                      std::declval<Args>()...)),
                        Ret
                    >::type;

  template <typename>
  static constexpr std::false_type
  Test(...);

  using type = decltype(Test<Type>(nullptr));

public:
  static constexpr bool Yes = type::value;
};


// -

template <
  bool Enabled,
  typename Type,
  typename Signature
>
struct PerformOpHelp;

template <
  typename Type,
  typename... Args
>
struct PerformOpHelp<true, Type, void(Args...)> {
  static void
  Op(Type& type, Args&&... args)
  { type.operator()(std::forward<Args>(args)...); }

};

template <
  typename Type,
  typename... Args
>
struct PerformOpHelp<false, Type, void(Args...)> {
  static void
  Op(Type&, Args&&...)
  {}
};

template <
  typename Type,
  typename Signature
>
struct PerformOp {
  template <typename... Args>
  static void
  Op(Type& type, Args&&... args)
  {
    PerformOpHelp<
        HasOp<Type, Signature>::Yes,
        Type,
        Signature>::Op(type, std::forward<Args>(args)...);
  }
};
} // ns detail
} // ns IV


#endif // IV_DETAIL_STATIC_HPP_
