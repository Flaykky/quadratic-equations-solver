# Quadratic Equation Solver

This C++ program solves quadratic equations of the form:

```
ax^2 + bx + c = 0
```

It supports parsing and solving both sides of an equation (e.g., `2x^2 - 3x + 1 = x^2 + x - 2`), and handles special cases like linear equations and infinite/no solutions.

## Features

* Parses and simplifies both sides of the equation.
* Handles floating-point coefficients.
* Supports quadratic, linear, and degenerate cases.
* User input loop with interactive prompt.
* Handles invalid or malformed equations gracefully.

---

## Code Overview

### Constants

```cpp
const long double EPS = 1e-12L;
```

* A small epsilon value used for safe floating-point comparison.

---

### Helper Functions

#### `trim(const string& s)`

Removes leading and trailing whitespace from a string.

#### `parseSide(const string& side, long double& a, long double& b, long double& c)`

Parses one side of a polynomial equation and accumulates the coefficients for:

* `a` — Coefficient of `x^2`
* `b` — Coefficient of `x`
* `c` — Constant term

Uses regular expressions to identify and extract polynomial terms.

---

### `universalSolve(long double a, long double b, long double c)`

Solves the equation based on the provided coefficients:

* If `a ≈ 0`, treats the equation as linear or constant.
* Calculates discriminant `D = b² - 4ac` and determines:

  * **No real solutions** if `D < 0`
  * **One real solution** if `D ≈ 0`
  * **Two real solutions** if `D > 0`

Outputs the result with a fixed precision of 6 decimal places.

---

### `solveEquation(const string& equation)`

Splits the input equation at `'='`, parses both sides using `parseSide`, and reduces it to standard quadratic form by subtracting the right side from the left. Then calls `universalSolve`.

---

### `main()`

Interactive loop that:

* Prompts the user for an equation.
* Calls `solveEquation()` to compute and display the result.
* Exits when user types `"exit"`.

---

## Example Usage

**Input:**

```
Enter equation: 2x^2 - 4x + 2 = 0
```

**Output:**

```
x = 1.000000
```

**Input:**

```
Enter equation: x^2 - 5x + 6 = 0
```

**Output:**

```
x1 = 3.000000
x2 = 2.000000
```

---

## Notes

* Coefficients like `x^2`, `-x`, or `+4` are all valid.
* Handles floating-point numbers: e.g., `0.5x^2 + 1.2x - 3 = 0`
* All white spaces are ignored during parsing.

## License

Distributed under the MIT License. See [LICENSE](LICENSE) file for details.


