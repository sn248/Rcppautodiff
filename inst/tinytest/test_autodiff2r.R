library(tinytest)
library(Rcpp)


## Derivative of a single variable function ------------------------------------
cppFunction("#include <Rcppautodiff.h>

// autodiff include
#include <autodiff/forward/dual.hpp>

using namespace Rcpp;
using namespace autodiff;

// [[Rcpp::plugins(cpp17)]]

//[[Rcpp::depends(Rcppautodiff)]]

// The single-variable function for which derivatives are needed
dual f(dual x)
{
    dual y = 1/x;     // other variables should also be dual
    return 1 + x + x*x + y + log(x);
}

// [[Rcpp::export]]
double myfun(double input){

    dual x = input;                                 // the input variable x
    dual u = f(x);                                  // the output variable u

    double dudx = derivative(f, wrt(x), at(x));     // evaluate the derivative du/dx

    return(dudx);
}")

## Result should be 5.25
expect_equal(myfun(2.0), 5.25)

## Derivative of a multi-variable function -------------------------------------
cppFunction("#include <Rcppautodiff.h>

// autodiff include
#include <autodiff/forward/dual.hpp>

using namespace Rcpp;
using namespace autodiff;

// [[Rcpp::plugins(cpp17)]]

//[[Rcpp::depends(Rcppautodiff)]]

// The multi-variable function for which derivatives are needed
dual f1(dual x, dual y, dual z)
{
    return 1 + x + y + z + x*y + y*z + x*z + x*y*z + exp(x/y + y/z);
}

// [[Rcpp::export]]
Rcpp::List myfun1(double xin, double yin, double zin)
{
    dual x = xin;
    dual y = yin;
    dual z = zin;

    dual u = f1(x, y, z);

    double dudx = derivative(f1, wrt(x), at(x, y, z));
    double dudy = derivative(f1, wrt(y), at(x, y, z));
    double dudz = derivative(f1, wrt(z), at(x, y, z));

    Rcpp::List myfun1_list = List::create(
    	Named(\"dudx\") = dudx,
    	Named(\"dudy\") = dudy,
    	Named(\"dudz\") = dudz
    );

    return(myfun1_list);
}

")

expect_equivalent(round(myfun1(1.0, 2.0, 3.0)$dudx, 2), 13.61)
expect_equivalent(round(myfun1(1.0, 2.0, 3.0)$dudy, 2), 8.27)
expect_equivalent(round(myfun1(1.0, 2.0, 3.0)$dudz, 2), 5.29)

## Derivatives of a multi-variable function with parameters---------------------
cppFunction("#include <Rcppautodiff.h>

// autodiff include
#include <autodiff/forward/dual.hpp>

using namespace Rcpp;
using namespace autodiff;

// [[Rcpp::plugins(cpp17)]]

//[[Rcpp::depends(Rcppautodiff)]]

// A type defining parameters for a function of interest
struct Params
{
    dual a;
    dual b;
    dual c;
};

// The function that depends on parameters for which derivatives are needed
dual f2(dual x, const Params& params)
{
    return params.a * sin(x) + params.b * cos(x) + params.c * sin(x)*cos(x);
}

// [[Rcpp::export]]
Rcpp::List myfun2(double a_input, double b_input, double c_input, double x_input)
{
    Params params;   // initialize the parameter variables

    dual a = a_input;
    params.a = a;    // the parameter a of type dual, not double!

    dual b = b_input;
    params.b = b;  // the parameter b of type dual, not double!

    dual c = c_input;
    params.c = c;  // the parameter c of type dual, not double!

    dual x = x_input;  // the input variable x

    dual u = f2(x, params);  // the output variable u

    double dudx = derivative(f2, wrt(x), at(x, params));        // evaluate the derivative du/dx
    double duda = derivative(f2, wrt(params.a), at(x, params)); // evaluate the derivative du/da
    double dudb = derivative(f2, wrt(params.b), at(x, params)); // evaluate the derivative du/db
    double dudc = derivative(f2, wrt(params.c), at(x, params)); // evaluate the derivative du/dc

    Rcpp::List myfun2_list = List::create(
    	Named(\"duda\") = duda,
    	Named(\"dudb\") = dudb,
    	Named(\"dudc\") = dudc
    );

    return(myfun2_list);

}


")

myfun2(1.0, 2.0, 3.0, 0.5)

expect_equivalent(round(myfun2(1.0, 2.0, 3.0, 0.5)$duda, 2), 0.48)
expect_equivalent(round(myfun2(1.0, 2.0, 3.0, 0.5)$dudb, 2), 0.88)
expect_equivalent(round(myfun2(1.0, 2.0, 3.0, 0.5)$dudc, 2), 0.42)

## Calculating Gradient vector of a scalar function-----------------------------
cppFunction("#include <RcppEigen.h>

#include <Rcppautodiff.h>

// autodiff include
#include <autodiff/forward/real.hpp>
#include <autodiff/forward/real/eigen.hpp>

using namespace Rcpp;
using namespace autodiff;

// [[Rcpp::plugins(cpp17)]]

//[[Rcpp::depends(RcppEigen, Rcppautodiff)]]

using Eigen::VectorXd;

// The scalar function for which the gradient is needed
real f3(const ArrayXreal& x)
{
    return (x * x.exp()).sum(); // sum([xi * exp(xi) for i = 1:5])
}

// [[Rcpp::export]]
VectorXd myfun3(NumericVector x_input)
{

    // Convert input vector to ArrayXreal manually
    ArrayXreal x(x_input.length());             // declare the input array x
    for (int i = 0; i < x_input.length(); i++){
        x(i) = x_input[i];
    }

    real u;                                     // the output scalar u = f(x) evaluated
                                                // together with gradient below

    VectorXd g = gradient(f3, wrt(x), at(x), u); // evaluate the function value u and its
                                                 // gradient vector g = du/dx

    return(g);
}

")

myfun3_result <- myfun3(c(1,2,3,4,5))
expect_length(myfun3_result, 5)
expect_equivalent(round(myfun3_result[1], 2), 5.44)
expect_equivalent(round(myfun3_result[2], 2), 22.17)
expect_equivalent(round(myfun3_result[3], 2), 80.34)
expect_equivalent(round(myfun3_result[4], 2), 272.99)
expect_equivalent(round(myfun3_result[5], 2), 890.48)
