#include <Rcpp.h>
using namespace Rcpp;

#include <iostream>

// autodiff include
#include <autodiff/forward/dual.hpp>
using namespace autodiff;

// The single-variable function for which derivatives are needed
dual f(dual x)
{
	return 1 + x + x*x + 1/x + log(x);
}
// [[Rcpp::export]]
int autodiff_hello(double input)
{
	dual x = input;                                 // the input variable x
	dual u = f(x);                                // the output variable u

	double dudx = derivative(f, wrt(x), at(x));   // evaluate the derivative du/dx

	std::cout << "u = " << u << std::endl;        // print the evaluated output u
	std::cout << "du/dx = " << dudx << std::endl; // print the evaluated derivative du/dx
	return(0);
}
