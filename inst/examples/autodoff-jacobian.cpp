#include <RcppEigen.h>

// autodiff include
#include <autodiff/forward/dual.hpp>

// via the depends attribute we tell Rcpp to create hooks for
// RcppEigen so that the build process will know what to do
//
// [[Rcpp::depends(RcppEigen)]]


using namespace Rcpp;
using namespace autodiff;

// autodiff include
#include <autodiff/forward/real.hpp>
#include <autodiff/forward/real/eigen.hpp>
using namespace autodiff;

// via the depends attribute we tell Rcpp to create hooks for
// RcppEigen so that the build process will know what to do
//
// [[Rcpp::depends(RcppEigen)]]

// The vector function for which the Jacobian is needed
VectorXreal f4(const VectorXreal& x)
{
	return x * x.sum();
}

// [[Rcpp::export]]
int autodiff_jacobian()
{
	using Eigen::MatrixXd;

	VectorXreal x(5);                           // the input vector x with 5 variables
	x << 1, 2, 3, 4, 5;                         // x = [1, 2, 3, 4, 5]

	VectorXreal F;                              // the output vector F = f(x) evaluated together with Jacobian matrix below

	MatrixXd J = jacobian(f4, wrt(x), at(x), F); // evaluate the output vector F and the Jacobian matrix dF/dx

	Rcpp::Rcout << "F = \n" << F << std::endl;    // print the evaluated output vector F
	Rcpp::Rcout << "J = \n" << J << std::endl;    // print the evaluated Jacobian matrix dF/dx
	return(0);
}
