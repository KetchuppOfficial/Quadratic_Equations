/**
    \file main.cpp
    \brief Contains all functions and one global constant
*/
/// \page 1

#include "Quadratic_Equation.h"

int main (void)
{
    double a = NAN, b = NAN, c = NAN, x_1 = NAN, x_2 = NAN;

    Run_Unit_Test ();

    printf ("This program will solve quadratic equations\n");

    enum Choice repeat_or_not = Yes;
    enum N_Roots n_roots = Zero;
    int num_of_digits_after_decimal_point = 0;

    while (repeat_or_not == Yes)
    {
        printf ("Write coefficients \"a\", \"b\" and \"c\"\n\n");
        Get_Three_Coefficients (&a, &b, &c);

        n_roots = Get_Number_Of_Roots_And_Solve_Equation (a, b, c, &x_1, &x_2);

        Print_Roots (n_roots, x_1, x_2, &num_of_digits_after_decimal_point);

        repeat_or_not = Yes_No ("Do you want to solve another equation?\n");

        putchar ('\n');
    }

    printf ("Good bye!\n");

    return 0;
}
