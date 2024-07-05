#include <Rcpp.h>

using namespace Rcpp;

// autodiff include
#include <autodiff/forward/dual.hpp>
using namespace autodiff;

// The single-variable function for which derivatives are needed
dual f(dual x)
{
	return 1 + x + x*x + 1/x + log(x);
}

//' autodiff_single_var
//'
//' Example function to show differentiation w.r.t. a single variable
//' @param input Value of independent variable (must be greater than 0)
// [[Rcpp::export]]
int autodiff_single_var(double input)
{
	dual x = input;                                 // the input variable x
	dual u = f(x);                                  // the output variable u

	double dudx = derivative(f, wrt(x), at(x));     // evaluate the derivative du/dx
    // Below is just for explanation
	Rcpp::Rcout << "Let the input variable be x" << std::endl;
	Rcpp::Rcout << "Function is defined asL f(x) -> (1 + x + x^2 + 1/x + log(x)) " << std::endl;
	Rcpp::Rcout << "Function value at x = " << input << " is " << u << std::endl;        // print the evaluated output u
	Rcpp::Rcout << "Derivative of the function at x = " << input << " is " << dudx << std::endl;         // print the evaluated derivative du/dx
	return(0);
}
