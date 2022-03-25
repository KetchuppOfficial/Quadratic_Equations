#include "Quadratic_Equation.h"

#define NUMBER_OF_TESTS 10     ///The number of unit tests

///Data for one unit test
struct Equation
{
    enum N_Roots N_Roots_Ref;   ///< Expected number of roots
    double Coeff_A;     ///< Quadratic coefficient
    double Coeff_B;     ///< Linear coefficient
    double Coeff_C;     ///< Free term
    double X_1_Ref;     ///< Expected value of the first root
    double X_2_Ref;     ///< Expected value of the second root
};

///Array of the structures that contains data for all unit tests

static const struct Equation Tests[NUMBER_OF_TESTS] =
{
    ///Unit test 1
    // a = 1, b = -3, c = 2
    { Two,      1.0, -3.0, 2.0, 1.0, 2.0 },

    ///Unit test 2
    // a = 1, b = -2, c = 1
    { One,      1.0, -2.0, 1.0, 1.0, 1.0},

    ///Unit test 3
    // a = 0, b = 0, c = 3
    { Zero,     0.0,  0.0, 3.0, NAN, NAN },

    ///Unit test 4
    // a = 0, b = 0, c = 0
    { Infinite, 0.0,  0.0, 0.0, NAN, NAN },

    ///Unit test 5
    // a = 1.2, b = -5.3, c = 4.8
    { Two,      1.2, -5.3,  4.8,  1.271991, 3.144675 },

    ///Unit test 6
    // a = 0.0, b = -20.4, c = 32.7
    { One,      0.0, -20.4, 32.7, NAN,      1.602941 },

    ///Unit test 7
    // a = 207.53, b = -1054.72, c = 385.03
    { Two, 207.53, -1054.72, 385.03, 4.686359, 0.395893 },
    
    ///Unit test 8
    // a = 0.00043, b = -0.00021, c = 0.00028
    { Zero, 0.00043, -0.00021, 0.00028, NAN, NAN },

    ///Unit test 9
    // a = 34.0, b = 0.0, c = 0.0
    { One, 34.0, 0.0, 0.0, 0.0, 0.0 },

    ///Unit test 10
    // a = 20.78, b = 3.74, c = 8.23
    { Zero, 20.78, 3.74, 8.23, NAN, NAN }
};

/**
    \brief Runs all unit tests.

    Calls Yes_No (). Asks user if he/she wants to run unit tests.
    If the answer is yes, the function calls Unit_Test ().

    \return The number of failed unit tests
*/
int Run_Unit_Test (void)
{
    int failed = 0, n_test = 0;

    if (Yes_No ("Do you want to run unit test?\n") == Yes)
    {
        for (n_test = 0; n_test < NUMBER_OF_TESTS; n_test++)
            if (Unit_Test (n_test,
                           Tests[n_test].N_Roots_Ref,
                           Tests[n_test].Coeff_A, Tests[n_test].Coeff_B, Tests[n_test].Coeff_C,
                           Tests[n_test].X_1_Ref, Tests[n_test].X_2_Ref) == 0)
                failed++;

        if (!failed)
            printf ("There are no errors\n");
    }

    putchar ('\n');

    return failed;
}
