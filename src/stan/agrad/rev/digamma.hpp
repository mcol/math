#ifndef __STAN__AGRAD__REV__DIGAMMA_HPP__
#define __STAN__AGRAD__REV__DIGAMMA_HPP__

#include <boost/math/special_functions/digamma.hpp>
#include <boost/math/special_functions/zeta.hpp>
#include <stan/agrad/rev/var.hpp>
#include <stan/agrad/rev/op/v_vari.hpp>

namespace stan {
  namespace agrad {

    namespace {
      class digamma_vari : public op_v_vari {
      public:
        digamma_vari(vari* avi) :
          op_v_vari(boost::math::digamma(avi->val_), avi) {
        }
        void chain() {
          avi_->adj_ += adj_ * (boost::math::zeta(2.0) - (0.57721566490153286 
                                          + boost::math::digamma(avi_->val_)));
        }
      };
    }

    inline var digamma(const stan::agrad::var& a) {
      return var(new digamma_vari(a.vi_));
    }

  }
}
#endif
