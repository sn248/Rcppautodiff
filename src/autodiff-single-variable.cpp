#include <Rcpp.h>

using namespace Rcpp;

// autodiff include
#include <autodiff/forward/dual.hpp>
using namespace autodiff;

// The single-variable function for which derivatives are needed
dual f(dual t)
{
	return 1 + t + t*t + 1/t + log(t);
}

//' autodiff_single_var
//'
//' Example function to show differentiation w.r.t. a single variable
//' @param input Value of independent variable (must be greater than 0)
//' @return A named list with two elements, \code{value} (the function
//'   \eqn{f(x) = 1 + x + x^2 + 1/x + \log(x)} evaluated at \code{input}) and
//'   \code{derivative} (the derivative of \eqn{f} evaluated at \code{input}).
//' @examples
//' res <- autodiff_single_var(2.0)
//' res$value        # f(2)  = 1 + 2 + 4 + 0.5 + log(2)
//' res$derivative   # f'(2) = 1 + 4 - 0.25 + 0.5 = 5.25
// [[Rcpp::export]]
Rcpp::List autodiff_single_var(double input)
{
	dual x = input;                                 // the input variable x
	dual u = f(x);                                  // the output variable u

	double dudx = derivative(f, wrt(x), at(x));     // evaluate the derivative du/dx

	return Rcpp::List::create(
		Rcpp::Named("value") = static_cast<double>(u),
		Rcpp::Named("derivative") = dudx
	);
}

/*** R
autodiff_single_var(2.0)
*/


