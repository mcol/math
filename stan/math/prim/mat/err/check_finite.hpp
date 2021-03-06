#ifndef STAN_MATH_PRIM_MAT_ERR_CHECK_FINITE_HPP
#define STAN_MATH_PRIM_MAT_ERR_CHECK_FINITE_HPP

#include <stan/math/prim/meta.hpp>
#include <stan/math/prim/scal/err/throw_domain_error.hpp>
#include <stan/math/prim/scal/err/check_finite.hpp>
#include <stan/math/prim/mat/fun/value_of.hpp>
#include <stan/math/prim/mat/fun/value_of_rec.hpp>
#include <stan/math/prim/mat/fun/Eigen.hpp>
#include <cmath>

namespace stan {
namespace math {

/*
 * Return <code>true</code> is the specified matrix is finite.
 *
 * @tparam T type of elements in the matrix
 * @tparam R number of rows, can be Eigen::Dynamic
 * @tparam C number of columns, can be Eigen::Dynamic
 *
 * @param function name of function (for error messages)
 * @param name variable name (for error messages)
 * @param y matrix to test
 * @return <code>true</code> if the matrix is finite
 **/
namespace internal {
template <typename T, int R, int C>
struct finite<Eigen::Matrix<T, R, C>, true> {
  static void check(const char* function, const char* name,
                    const Eigen::Matrix<T, R, C>& y) {
    if (!value_of(y).allFinite()) {
      for (int n = 0; n < y.size(); ++n) {
        if (!std::isfinite(value_of_rec(y(n)))) {
          throw_domain_error_vec(function, name, y, n, "is ",
                                 ", but must be finite!");
        }
      }
    }
  }
};

}  // namespace internal
}  // namespace math
}  // namespace stan

#endif
