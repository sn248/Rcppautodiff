#include <Rcpp.h>
#include <boost/math/differentiation/autodiff.hpp>
#include <iostream>

template <typename T>
T fourth_power(T const& x) {
	T x4 = x * x;  // retval in operator*() uses x4's memory via NRVO.
	x4 *= x4;      // No copies of x4 are made within operator*=() even when squaring.
	return x4;     // x4 uses y's memory in main() via NRVO.
}

// [[Rcpp::depends(BH)]]

using namespace Rcpp;

// Calculate derivatives of f(x)=x^4 at x (input to be provided).
// In this example, make_fvar<double, Order>(2.0) instantiates the polynomial 2+epsilon.
// The Order=5 means that enough space is allocated (on the stack) to hold a polynomial of up to degree 5 during the proceeding computation.
// Internally, this is modeled by a std::array<double,6> whose elements {2, 1, 0, 0, 0, 0} correspond to the 6 coefficients of the polynomial upon initialization. Its fourth power, at the end of the computation, is a polynomial with coefficients y = {16, 32, 24, 8, 1, 0}.
// The derivatives are obtained using the formula f(n)(2)=n!*y[n].
// https://www.boost.org/doc/libs/master/libs/math/doc/html/math_toolkit/autodiff.html
// [[Rcpp::export]]
int autoDiffExample(double x_input) {
	using namespace boost::math::differentiation;


	constexpr unsigned Order = 5;                  // Highest order derivative to be calculated.
	auto const x = make_fvar<double, Order>(x_input);  // Find derivatives at x=2.
	auto const y = fourth_power(x);
	for (unsigned i = 0; i <= Order; ++i)
		Rcpp::Rcout << "y.derivative(" << i << ") = " << y.derivative(i) << std::endl;
	return 0;
}
