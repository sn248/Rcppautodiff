<!-- badges: start -->
[![R-CMD-check](https://github.com/sn248/Rcppautodiff/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/sn248/Rcppautodiff/actions/workflows/R-CMD-check.yaml)
<!-- badges: end -->

# Rcppautodiff
An `R` interface to the [autodiff](https://autodiff.github.io/) `C++` library using `Rcpp`. [autodiff](https://autodiff.github.io/) is a modern, header-only `C++17` library which provides an efficient and simple interface to perform automatic differentiation in `C++`. [autodiff](https://autodiff.github.io/) supports both forward and reverse mode of automatic differentiation. `Rcppautodiff` brings these capabilities to `R`. For more details on the [autodiff](https://autodiff.github.io/) library, please see its documentation and tutorials. 

The [vignette](https://sn248.github.io/Rcppautodiff/articles/Introduction-to-Rcppautodiff.html) of this package also reproduces a number of examples from the `autodiff` library in `R` using `Rcpp`.

## Installation
`Rcppautodiff` is not on CRAN yet. It can be installed from github using the following command in the `R` console.
```R
pak::pkg_install('sn248/Rcppautodiff')
```

## Examples
See the package [vignette](https://sn248.github.io/Rcppautodiff/articles/Introduction-to-Rcppautodiff.html) for a variety of examples.

## Acknowledgement
This package would not exist without the wonderful `autodiff`, a modern, fast and expressive C++ library for automatic differentiation (by Allan M. M. Beal), found at https://autodiff.github.io/
