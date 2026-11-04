# Rcppautodiff 0.1.1

* The bundled 'autodiff' header `autodiff/common/eigen.hpp` now compiles with
  Eigen 5, in preparation for the 'RcppEigen' update. Older versions of Eigen
  are unaffected (#1, thanks to Dirk Eddelbuettel).

* The `autodiff-multi-var.cpp` example now includes
  `<autodiff/forward/dual.hpp>`, as the other examples do.

# Rcppautodiff 0.1.0

* Initial CRAN release.
