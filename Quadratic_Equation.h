#ifndef QUADRATIC_EQUATION_H_INCLUDED
#define QUADRATIC_EQUATION_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

///For processing boolean values
enum Choice
{
    No,     ///< Is used as synonym of 0 in boolean operations
    Yes,    ///< Is used as synonym of 1 in boolean operations
    Error   ///< Is used when result of an operation with int numbers differs from boolean values
};

///Possible results of comparison
enum Compare
{
    Not_Equal = -2,  ///< For comparing NAN and an ordinary double
    Less,   ///< Is used as synonym of -1 in operations of comparison
    Equal,  ///< Is used as synonym of 0 in operations of comparison
    Greater     ///< Is used as synonym of 1 in operations of comparison
};

///Possible number of roots of a quadratic equation
enum N_Roots
{
    Infinite = -1,  ///< For infinite number of roots
    Zero,   ///< For no roots
    One,    ///< For only one root or only two equal roots
    Two     ///< For only two different roots
};

int Run_Unit_Test (void);
int Unit_Test (const int n_test, enum N_Roots n_roots_ref, const double a,
               const double b, const double c, const double x_1_ref, const double x_2_ref);
enum N_Roots Get_Number_Of_Roots_And_Solve_Equation (const double a, const double b, const double c,
                                                     double *first_root, double *second_root);
enum N_Roots Solve_Quadratic_Equation (const double a, const double b, const double c,
                                       double *first_root, double *second_root);
double Calc_Discriminant (const double a, const double b, const double c);
void Calc_Roots_Of_Quadratic_Equation (const double a, const double b, const double sqrt_D,
                                       double *first_root, double *second_root);
enum N_Roots Solve_Linear_Equation (const double b, const double c, double *root);
void Get_Three_Coefficients (double *ptr_a, double *ptr_b, double *ptr_c);
void Get_One_Coefficient (double *coeff_value, const char coeff);
void Get_Double (double *num);
int  IsNAN (const double value);
void Get_Int (int *num);
void Print_Inappropriate_Symbols (void);
bool Warn_About_Inappropriate_Symbols_After_Correct_Input (void);
int  Clear_Stdin (void);
enum Compare Compare_Double (const double first, const double second);
int  Ask_For_Number_Of_Digits_After_Decimal_Point (void);
int  Get_Not_Negative_Int (void);
void Print_Roots (const int number_of_roots, const double first_root,
                  const double second_root, int *number_of_digits_after_decimal_point);
enum Choice Yes_No (const char *string_ptr);
int  Get_String (char *buffer, const int length, bool upcase, bool lowcase);
enum Compare Strncmp_Pro (const char *string_1, const char *string_2, const size_t length);

#endif
