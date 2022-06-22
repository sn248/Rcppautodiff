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
int autodiff_single_var(double input)
{
	dual x = input;                                 // the input variable x
	dual u = f(x);                                // the output variable u

	double dudx = derivative(f, wrt(x), at(x));   // evaluate the derivative du/dx

	std::cout << "u = " << u << std::endl;        // print the evaluated output u
	std::cout << "du/dx = " << dudx << std::endl; // print the evaluated derivative du/dx
	return(0);
}


// // The multi-variable function for which derivatives are needed
// dual f1(dual x, dual y, dual z)
// {
// 	return 1 + x + y + z + x*y + y*z + x*z + x*y*z + exp(x/y + y/z);
// }
//
// // [[Rcpp::export]]
// int autodiff_multivar()
// {
// 	dual x = 1.0;
// 	dual y = 2.0;
// 	dual z = 3.0;
//
// 	dual u = f1(x, y, z);
//
// 	double dudx = derivative(f1, wrt(x), at(x, y, z));
// 	double dudy = derivative(f1, wrt(y), at(x, y, z));
// 	double dudz = derivative(f1, wrt(z), at(x, y, z));
//
// 	std::cout << "u = " << u << std::endl;         // print the evaluated output u = f(x, y, z)
// 	std::cout << "du/dx = " << dudx << std::endl;  // print the evaluated derivative du/dx
// 	std::cout << "du/dy = " << dudy << std::endl;  // print the evaluated derivative du/dy
// 	std::cout << "du/dz = " << dudz << std::endl;  // print the evaluated derivative du/dz
// 	return(0);
// }
