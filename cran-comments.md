## R CMD check results

0 errors | 0 warnings | 2 notes

Both notes are specific to the local check machine: a non-portable compilation flag from the system R configuration, and HTML validation skipped because 'tidy' is not installed.

## Update

This is a maintenance release requested by the 'RcppEigen' maintainers. It updates the bundled 'autodiff' header `autodiff/common/eigen.hpp` so that the package compiles with the upcoming 'RcppEigen' based on Eigen 5, and it continues to compile with the current 'RcppEigen'. See https://github.com/RcppCore/RcppEigen/issues/151.

## Reverse dependencies

There are no reverse dependencies on CRAN.
