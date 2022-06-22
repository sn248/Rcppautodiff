#include <Rcpp.h>
#include <iostream>
// autodiff include
#include <autodiff/forward/dual.hpp>

using namespace Rcpp;
using namespace autodiff;

// A type defining parameters for a function of interest
struct Params
{
	dual a;
	dual b;
	dual c;
};

// The function that depends on parameters for which derivatives are needed
dual f3(dual x, const Params& params)
{
	return params.a * sin(x) + params.b * cos(x) + params.c * sin(x)*cos(x);
}


// [[Rcpp::export]]
int autodiff_params(double x_, double y_, double z_)
{
	Params params;   // initialize the parameter variables
	params.a = x_; // default value - 1.0;  // the parameter a of type dual, not double!
	params.b = y_; // default value - 2.0;  // the parameter b of type dual, not double!
	params.c = z_; // default value - 3.0;  // the parameter c of type dual, not double!

	dual x = 0.5;  // the input variable x

	dual u = f3(x, params);  // the output variable u

	double dudx = derivative(f3, wrt(x), at(x, params));        // evaluate the derivative du/dx
	double duda = derivative(f3, wrt(params.a), at(x, params)); // evaluate the derivative du/da
	double dudb = derivative(f3, wrt(params.b), at(x, params)); // evaluate the derivative du/db
	double dudc = derivative(f3, wrt(params.c), at(x, params)); // evaluate the derivative du/dc

	Rcpp::Rcout << "u = " << u << std::endl;         // print the evaluated output u
	Rcpp::Rcout << "du/dx = " << dudx << std::endl;  // print the evaluated derivative du/dx
	Rcpp::Rcout << "du/da = " << duda << std::endl;  // print the evaluated derivative du/da
	Rcpp::Rcout << "du/db = " << dudb << std::endl;  // print the evaluated derivative du/db
	Rcpp::Rcout << "du/dc = " << dudc << std::endl;  // print the evaluated derivative du/dc
	return(0);
}

/*-------------------------------------------------------------------------------------
 === Note ===
 ---------------------------------------------------------------------------------------------------
 This example would also work if real was used instead of dual. Should you
 need higher-order cross derivatives, however, e.g.,:

 double d2udxda = derivative(f, wrt(x, params.a), at(x, params));

 then higher-order dual types are the right choicesince real types are
 optimally designed for higher-order directional derivatives.
 ------------------------------------------------------------------------------------*/
