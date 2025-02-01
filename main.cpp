#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

void universalSolving(double a, double b, double c) {
    if (a == 0) {
        if (b == 0) {
            if (c == 0) {
                cout << "Infinite solutions" << endl;
            }
            else {
                cout << "No solutions" << endl;
            }
        }
        else {
            cout << "x = " << -c / b << endl;
        }
        return;
    }

    double D = b * b - 4 * a * c;
    if (D < 0) {
        cout << "No real solutions" << endl;
    }
    else if (D == 0) {
        double x = -b / (2 * a);
        cout << "x = " << x << endl;
    }
    else {
        double x1 = (-b + sqrt(D)) / (2 * a);
        double x2 = (-b - sqrt(D)) / (2 * a);
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }
}

void solveQuadraticEquation(const string& equation) {
    double a = 0, b = 0, c = 0;

    // Remove spaces around '='
    size_t pos = equation.find("=");
    if (pos == string::npos) {
        cout << "Invalid equation format" << endl;
        return;
    }

    string left_side = equation.substr(0, pos);
    string right_side = equation.substr(pos + 1);

    // Process the right side of the equation
    if (!right_side.empty() && right_side != "0") {
        double right_value = stod(right_side);
        c -= right_value; // Move the right side to the left side
    }

    // Create a stream to analyze the left side
    stringstream ss(left_side);
    string term;
    double current_sign = 1; // Current sign (+1 or -1)

    while (ss >> term) {
        if (term == "+") {
            current_sign = 1;
            continue;
        }
        else if (term == "-") {
            current_sign = -1;
            continue;
        }

        // Check if the term contains 'x^2'
        if (term.find("x^2") != string::npos) {
            double coeff = 1;
            if (term != "x^2" && term != "-x^2") {
                coeff = stod(term.substr(0, term.find("x^2")));
            }
            else if (term == "-x^2") {
                coeff = -1;
            }
            a += current_sign * coeff;
        }
        // Check if the term contains 'x'
        else if (term.find("x") != string::npos) {
            double coeff = 1;
            if (term != "x" && term != "-x") {
                coeff = stod(term.substr(0, term.find("x")));
            }
            else if (term == "-x") {
                coeff = -1;
            }
            b += current_sign * coeff;
        }
        // If the term is just a number
        else {
            c += current_sign * stod(term);
        }
    }

    universalSolving(a, b, c);
}

void infinity_input() {
    string equation;
    while (true) {
        cout << "Enter the quadratic equation (or exit to quit): ";
        getline(cin, equation);
        if (equation == "exit") {
            break;
        }
        solveQuadraticEquation(equation);
    }
}

int main() {
    infinity_input();
    return 0;
}
