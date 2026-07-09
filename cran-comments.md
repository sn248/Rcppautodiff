## R CMD check results

0 errors | 0 warnings | 1 note

This is a new release.

### Resolved the initial CRAN comments

-  More details about the package functionality and implemented methods are added to the Description field of DESCRIPTION.

- Package names, software names and API (application programming interface) names are in single quotes in title and description fields of DESCRIPTION.

- Added \\value to .Rd files regarding exported methods and explained the function results in the documentation. 

- Regarding 'uexpected symbol: dual x', this is coming from the data type defined by the 'autodiff' library and is NOT an error.

- Small executable examples in Rd-files to illustrate the use of the exported functions and tests are added.

