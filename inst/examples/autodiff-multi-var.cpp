#include <Rcpp.h>
#include <iostream>
// autodiff include
// #include <autodiff/forward/dual.hpp>
#include "../include/autodiff/forward/dual/dual.hpp"

using namespace Rcpp;
using namespace autodiff;

// The multi-variable function for which derivatives are needed
dual f1(dual x, dual y, dual z)
{
	return 1 + x + y + z + x*y + y*z + x*z + x*y*z + exp(x/y + y/z);
}

// [[Rcpp::export]]
int autodiff_multivar(double x_, double y_, double z_)
{
	dual x = x_; // default starting value 1.0;
	dual y = y_; // default starting value 2.0;
	dual z = z_; // default starting value 3.0;

	dual u = f1(x, y, z);

	double dudx = derivative(f1, wrt(x), at(x, y, z));
	double dudy = derivative(f1, wrt(y), at(x, y, z));
	double dudz = derivative(f1, wrt(z), at(x, y, z));

	Rcpp::Rcout << "u = " << u << std::endl;         // print the evaluated output u = f(x, y, z)
	Rcpp::Rcout << "du/dx = " << dudx << std::endl;  // print the evaluated derivative du/dx
	Rcpp::Rcout << "du/dy = " << dudy << std::endl;  // print the evaluated derivative du/dy
	Rcpp::Rcout << "du/dz = " << dudz << std::endl;  // print the evaluated derivative du/dz

	return(0);
}
