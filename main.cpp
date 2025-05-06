#include <iostream>
#include <regex>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

// Epsilon for floating-point comparison
const long double EPS = 1e-12L;

// Trim whitespace from both ends of a string
static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    size_t end = s.find_last_not_of(" \t\n\r");
    return (start == string::npos) ? string() : s.substr(start, end - start + 1);
}

// Parse a polynomial side (e.g., "2x^2-3x+4") and accumulate coefficients
bool parseSide(const string& side, long double& a, long double& b, long double& c) {
    // Regex: optional sign, digits (with optional decimal), optional variable part (x or x^2)
    static const regex term_regex(R"(([+-]?)(\d*(?:\.\d+)?)(x(?:\^2)?)?)");
    auto s = side;
    // Remove all whitespace
    s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
    if (s.empty()) return false;

    auto begin = sregex_iterator(s.begin(), s.end(), term_regex);
    auto end_it = sregex_iterator();
    bool found = false;
    for (auto it = begin; it != end_it; ++it) {
        smatch m = *it;
        if (m.length(0) == 0) continue;
        found = true;
        string sign = m[1];
        string num  = m[2];
        string var  = m[3];

        long double coeff = 0;
        // Determine coefficient
        if (num.empty()) {
            // If no number but has variable, coefficient is 1
            coeff = var.empty() ? 0 : 1;
        } else {
            coeff = stold(num);
        }
        if (sign == "-") coeff = -coeff;
        // Assign to a, b, or c
        if (var == "x^2")      a += coeff;
        else if (var == "x")   b += coeff;
        else                     c += coeff;
    }
    return found;
}

void universalSolve(long double a, long double b, long double c) {
    cout << fixed << setprecision(6);
    if (fabsl(a) < EPS) {
        // Linear or degenerate
        if (fabsl(b) < EPS) {
            if (fabsl(c) < EPS)
                cout << "Infinite solutions" << endl;
            else
                cout << "No solutions" << endl;
        } else {
            cout << "x = " << -c / b << endl;
        }
        return;
    }

    long double D = b*b - 4*a*c;
    if (D < -EPS) {
        cout << "No real solutions" << endl;
    } else if (fabsl(D) < EPS) {
        long double x = -b / (2*a);
        cout << "x = " << x << endl;
    } else {
        long double sqrtD = sqrtl(D);
        long double x1 = (-b + sqrtD) / (2*a);
        long double x2 = (-b - sqrtD) / (2*a);
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
}

void solveEquation(const string& equation) {
    // Split at '='
    auto pos = equation.find('=');
    if (pos == string::npos) {
        cerr << "Error: Equation must contain '='." << endl;
        return;
    }
    string left = trim(equation.substr(0, pos));
    string right = trim(equation.substr(pos + 1));
    if (left.empty() || right.empty()) {
        cerr << "Error: Both sides of the equation must be non-empty." << endl;
        return;
    }

    long double a = 0, b = 0, c = 0;
    // Parse left side
    if (!parseSide(left, a, b, c)) {
        cerr << "Error: Unable to parse the left side." << endl;
        return;
    }
    // Parse right side and subtract from left
    long double ar = 0, br = 0, cr = 0;
    if (!parseSide(right, ar, br, cr)) {
        cerr << "Error: Unable to parse the right side." << endl;
        return;
    }
    a -= ar;  b -= br;  c -= cr;

    // Solve
    universalSolve(a, b, c);
}

int main() {
    cout << "Quadratic Equation Solver (format: ax^2 + bx + c = 0)\n";
    cout << "Type 'exit' to quit.\n";
    while (true) {
        cout << "Enter equation: ";
        string eq;
        if (!getline(cin, eq) || eq == "exit") break;
        solveEquation(eq);
    }
    return 0;
}
