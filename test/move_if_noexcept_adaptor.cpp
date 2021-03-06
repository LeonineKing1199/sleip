#include <sleip/dynamic_array.hpp>

#include <type_traits>
#include <vector>

#include <boost/core/lightweight_test.hpp>

struct X
{
  X()             = default;
  X(X const&)     = delete;
  X(X&&) noexcept = default;
};

struct Y
{
  Y()             = default;
  Y(Y const&)     = default;
  Y(Y&&) noexcept = delete;
};

struct Z
{
  Z()         = default;
  Z(Z const&) = default;
  Z(Z&&){};
};

static_assert(std::is_same_v<X&&,
                             decltype(*std::declval<sleip::detail::move_if_noexcept_adaptor<
                                        typename std::vector<X>::iterator>&>())>);

static_assert(std::is_same_v<Y const&,
                             decltype(*std::declval<sleip::detail::move_if_noexcept_adaptor<
                                        typename std::vector<Y>::iterator>&>())>);

static_assert(std::is_same_v<Z const&,
                             decltype(*std::declval<sleip::detail::move_if_noexcept_adaptor<
                                        typename std::vector<Z>::iterator>&>())>);

int
main()
{
  return boost::report_errors();
}
