# autodiff_single_var

Example function to show differentiation w.r.t. a single variable

## Usage

``` r
autodiff_single_var(input)
```

## Arguments

- input:

  Value of independent variable (must be greater than 0)

## Value

A named list with two elements, `value` (the function \\f(x) = 1 + x +
x^2 + 1/x + \log(x)\\ evaluated at `input`) and `derivative` (the
derivative of \\f\\ evaluated at `input`).

## Examples

``` r
res <- autodiff_single_var(2.0)
res$value        # f(2)  = 1 + 2 + 4 + 0.5 + log(2)
#> [1] 8.193147
res$derivative   # f'(2) = 1 + 4 - 0.25 + 0.5 = 5.25
#> [1] 5.25
```
