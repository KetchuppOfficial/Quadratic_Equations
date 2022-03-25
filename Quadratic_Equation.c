#include "Quadratic_Equation.h"

const double EPSILON = 10E-7; /// Is used to compare numbers of the "double" type

/**
    \brief Runs one unit test

    Calls Compare_Double ().
    Tests Solve_Linear_Equation () if coefficient "a" is equal to 0.
    Tests Solve_Quadratic_Equation () if coefficient "a" is not equal to 0.
    If a test fails, the function puts the number of this test,
             actual roots and number of roots and expected roots and number of roots on the screen.

    \param [in] n_test {A number that means (the number of test) - 1}
    \param [in] n_roots_ref {Reference of the number of roots}
    \param [in] a {Quadratic coefficient}
    \param [in] b {Linear coefficient}
    \param [in] c {Free term}
    \param [in] x_1_ref {Reference of the first root}
    \param [in] x_2_ref {Reference of the second root}
    \return 0 if the test fails
    \return 1 if the test does not fail
*/
int Unit_Test (const int n_test, enum N_Roots n_roots_ref, const double a,
               const double b, const double c, const double x_1_ref, const double x_2_ref)
{
    double x_1 = NAN, x_2 = NAN;
    enum N_Roots n_roots = Zero;

    if (Compare_Double (a, 0.0) == Equal)
        n_roots = Solve_Linear_Equation (b, c, &x_1);
    else
        n_roots = Solve_Quadratic_Equation (a, b, c, &x_1, &x_2);

    if (n_roots != n_roots_ref && ((Compare_Double (x_1, x_1_ref) != Equal && Compare_Double (x_2, x_2_ref) != Equal)
                                || (Compare_Double (x_1, x_2_ref) != Equal && Compare_Double (x_2, x_1_ref) != Equal)))
    {
        printf ("Test %d FAILED\n"
                "x_1 = %f, x_2 =  %f, n_roots = %d\n"
                "Should be: x_1 = %f, x_2 = %f and %d roots\n\n",
                n_test + 1, x_1, x_2, n_roots, x_1_ref, x_2_ref, n_roots_ref);
        return 0;
    }
    else
        return 1;
}

/**
    \brief Calls the functions that solve quadratic or linear equation

    If coefficient "a" is equal to 0, this function calls Solve_Linear_Equation ().
    If coefficient "a" is not equal to 0, this function calls Solve_Quadratic_Equation ().

    \param [in] a {Quadratic coefficient}
    \param [in] b {Linear coefficient}
    \param [in] c {Free term}
    \param [out] *first_root {Pointer on the variable that contains the value of the first root}
    \param [out] *second_root {Pointer on the variable that contains the value of the second root}
    \return -1 (Infinite) if the equation has infinite number of roots
    \return 0 (Zero) if the equation has no roots
    \return 1 (One) if the equation has only one root or both roots are equal
    \return 2 (Two) if the equation has only two different roots
*/
enum N_Roots Get_Number_Of_Roots_And_Solve_Equation (const double a, const double b, const double c,
                                                     double *first_root, double *second_root)
{
    assert (first_root  != NULL);
    assert (second_root != NULL);

    if (Compare_Double (a, 0.0) == Equal)
        return Solve_Linear_Equation (b, c, first_root);
    else
        return Solve_Quadratic_Equation (a, b, c, first_root, second_root);
}

/**
    \brief Solves quadratic equation

    Calls Calculate_Discriminant (), Compare_Double ().
    If discriminant is less than 0, both root-variables will still have NAN value.
    If discriminant is equal to 0, both roots will be calculated and will be equal.

    \param [in] a - quadratic coefficient
    \param [in] b - linear coefficient
    \param [in] c - free term
    \param [out] *first_root - pointer on the variable that contains the value of the first root
    \param [out] *second_root - pointer on the variable that contains the value of the second root
    \return 0 (Zero) if the equation has no roots
    \return 1 (One) if the equation has only one root or both roots are equal
    \return 2 (Two) if the equation has only two different roots
*/
enum N_Roots Solve_Quadratic_Equation (const double a, const double b, const double c,
                                       double *first_root, double *second_root)
{
    assert (first_root != NULL);
    assert (second_root != NULL);

    double D = Calc_Discriminant (a, b, c);

    if (Compare_Double (D, 0.0) == Less)
        return Zero;
    else
    {
        double sqrt_D = sqrt (D);
        Calc_Roots_Of_Quadratic_Equation (a, b, sqrt_D, first_root, second_root);

        if (Compare_Double (D, 0.0) == Equal)
            return One;
        else
            return Two;
    }
}

/**
    \brief Calculates discriminant of a quadratic equation
    \param [in] a - quadratic coefficient
    \param [in] b - linear coefficient
    \param [in] c - free term
    \return The value of discriminant
*/
inline double Calc_Discriminant (const double a, const double b, const double c)
{
    return b * b - 4 * a * c;
}

/**
    \brief Calculates roots of a quadratic equation
    \param [in] a - quadratic coefficient
    \param [in] b - linear coefficient
    \param [in] c - free term
    \param [in] sqrt_D - square root of discriminant
    \param [out] *first_root - pointer on the variable that contains the value of the first root
    \param [out] *second_root - pointer on the variable that contains the value of the second root
*/
void Calc_Roots_Of_Quadratic_Equation (const double a, const double b, const double sqrt_D,
                                       double *first_root, double *second_root)
{
    assert (a != 0);
    assert (first_root != NULL);
    assert (second_root != NULL);

    double double_a = 2 * a;
    *first_root  = (-b - sqrt_D) / double_a;
    *second_root = (-b + sqrt_D) / double_a;
}

/**
    \brief Solves a linear equation

    Calls Compare_Double ().
    Runs when quadratic coefficient ("a") is equal to 0.
    If there are infinite roots, both root-variables will still have NAN value.
    If there are no roots, both root-variables will still have NAN value.
    If there is only one root, x_1 from main will change the value and x_2 from main will still have NAN value.

    \param [in] b {Linear coefficient}
    \param [in] c {Free term}
    \param [out] *root {Pointer on the variable that contains the value of the first root}
    \return -1 (Infinite) if the equation has infinite number of roots
    \return 0 (Zero) if the equation has no roots
    \return 1 (One) if the equation has only one root or both roots are equal
*/
enum N_Roots Solve_Linear_Equation (const double b, const double c, double *root)
{
    assert (root != NULL);

    if (Compare_Double (b, 0.0) == Equal)
    {
        if (Compare_Double (c, 0.0) == Equal)
            return Infinite;
        else
            return Zero;
    }
    else
    {
        *root = -c / b;
        return One;
    }
}

/**
    \brief Gets three coefficients

    Calls Get_One_Coefficient () for three times.

    \param [out] *ptr_a {Pointer on a variable that contains the value of "a" coefficient}
    \param [out] *ptr_b {Pointer on a variable that contains the value of "b" coefficient}
    \param [out] *ptr_c {Pointer on a variable that contains the value of "c" coefficient}
*/
void Get_Three_Coefficients (double *ptr_a, double *ptr_b, double *ptr_c)
{
    assert (ptr_a != NULL);
    assert (ptr_b != NULL);
    assert (ptr_c != NULL);

    Get_One_Coefficient (ptr_a, 'a');
    Get_One_Coefficient (ptr_b, 'b');
    Get_One_Coefficient (ptr_c, 'c');
}

/**
    \brief Gets one coefficient of the equation

    Calls Get_Double ().
    Asks for a certain coefficient, gets it and prints the symbol of a new line.

    \param [out] *coeff_value {Pointer on a variable that contains the value of a coefficient}
    \param [in] coeff {The coefficient symbol}
*/
void Get_One_Coefficient (double *coeff_value, const char coeff)
{
    assert (coeff_value != NULL);

    printf ("Coefficient \"%c\": ", coeff);
    Get_Double (coeff_value);
    putchar ('\n');
}

/**
    \brief Gets the number of the "double" type

    Calls Print_Inappropriate_Symbols (), Warn_About_Inappropriate_Symbols_After_Correct_Input ().
    If the input is not a single number of the "double" type, the function will ask for input again.

    \param [out] *num {Pointer on the variable in which the function puts obtained number}
*/
void Get_Double (double *num)
{
    assert (num != NULL);

    bool error = true;

    while (error)
    {
        if (scanf ("%lf", num) != 1)
        {
            Print_Inappropriate_Symbols ();
            printf (" is not a number. Try again\n");
        }
        else
            error = Warn_About_Inappropriate_Symbols_After_Correct_Input ();
    }
}

/**
    \brief Gets the number of the "int" type

    Calls Print_Inappropriate_Symbols (), Warn_About_Inappropriate_Symbols_After_Correct_Input ().
    If the input is not a single number of the "int" type, the function will ask for input again.

    \param [out] *num {Pointer on the variable in which the function puts obtained number}
*/
void Get_Int (int *num)
{
    assert (num != NULL);

    bool error = true;

    while (error)
    {
        if (scanf ("%d", num) != 1)
        {
            Print_Inappropriate_Symbols ();
            printf (" is not an integer not negative number. Try again\n");
        }
        else
            error = Warn_About_Inappropriate_Symbols_After_Correct_Input ();
    }
}

/**
    \brief Prints any symbols

    The function is called if there is a need to print symbols from stdin up to '\n'.
*/
void Print_Inappropriate_Symbols (void)
{
    int inappropriate_symbole = 0;

    while ((inappropriate_symbole = getchar ()) != '\n' || inappropriate_symbole != EOF)
        putchar (inappropriate_symbole);
}

/**
    \brief Warns About Inappropriate Symbols After Correct Input

    If the user have written a number of a correct type and some inappropriate symbols after that,
             the function will warn him/her about it and ask for input again.

    \return False if no inappropriate symbols have been found
    \return True if at least one inappropriate symbol has been found
*/
bool Warn_About_Inappropriate_Symbols_After_Correct_Input (void)
{
    bool error = true;

    if (getchar() == '\n')
         error = false;
    else
    {
        Clear_Stdin ();
        printf ("You have written a number and some inappropriate symbols after that. Try again\n");
    }

    return error;
}

/**
    \brief Clears stdin

    Calls getchar () until finds '\\n' or EOF and counts int number of inappropriate syumbols.

    \return The number of inappropriate symbols
*/
int Clear_Stdin (void)
{
    int inappropriate_symbol = 0;
    int n_symb = 0;

    while ((inappropriate_symbol = getchar ()) != '\n' && inappropriate_symbol != EOF)
        n_symb++;

    return n_symb;
}

/**
    \brief Gets a not negative number

    Calls Get_Int ().
    If obtained number is negative, the function asks for input again.

    \return A number obtained from stdin
*/
int Get_Not_Negative_Int (void)
{
    int input_number = 0;

    Get_Int (&input_number);
    while (input_number < 0)
    {
        printf ("The number should not be negative. Try again\n");
        Get_Int (&input_number);
    }

    return input_number;
}

/**
    \brief Compares two numbers of the "double" type
    \param [in] first {The number that is on the left of the comparison sign}
    \param [in] second {The number that is on the right of the comparison sign}
    \return 1 (Greater) if "first" is greater than "second"
    \return 0 (Equal) if the numbers are equal (even if both of them are NAN), -1 (Less) if "first" is less than "second"
    \return -1 (Less) if "first" is less than "second"
    \return -2 (Not_Equal) if only one number is NAN
*/
enum Compare Compare_Double (const double first, const double second)
{
    if (IsNAN (first) && IsNAN (second))
        return Equal;

    else if (IsNAN (first) ^ IsNAN (second))
        return Not_Equal;

    else
    {
        double absolute_value = fabs (first - second);

        if (absolute_value > EPSILON)
            return (first > second) ? Greater : Less;
        else
            return Equal;
    }
}

/**
    \brief Checks if a number of the "double" type is equal to NAN
    \param [in] value {A number of the "double" type}
    \return 0 if a number is not equal to NAN
    \return 1 if a number is equal to NAN
*/
inline int IsNAN (const double value)
{
    return (value != value) ? 1 : 0;
}

/**
    \brief Prints roots of the equation

    Calls Ask_For_Number_Of_Digits_After_Decimal_Point ().

    \param [in] number_of_roots {The number of roots that was obtained from Get_Number_Of_Roots_And_Solve_Equation}
    \param [in] first_root {Contains the value of the first root (a real number or NAN)}
    \param [in] second_root {Contains the value of the second root (a real number or NAN)}
    \param [out] *number_of_digits_after_decimal_point {The pointer on the variable that contains the number of digits after decimal point}
*/
void Print_Roots (const int number_of_roots, const double first_root,
                  const double second_root, int *num_of_digits_after_decimal_point)
{
    assert (num_of_digits_after_decimal_point != NULL);

    switch (number_of_roots)
    {
        case Infinite:
                printf ("There is infinite number of roots: every real number is a root\n\n");
                break;

        case Zero:
                printf ("There are no roots\n\n");
                break;

        case One:
                *num_of_digits_after_decimal_point = Ask_For_Number_Of_Digits_After_Decimal_Point ();
                printf ("The only one root is %.*f\n\n",
                        *num_of_digits_after_decimal_point, first_root);
                break;

        case Two:
                *num_of_digits_after_decimal_point = Ask_For_Number_Of_Digits_After_Decimal_Point ();
                printf ("The roots are %.*f and %.*f\n\n",
                        *num_of_digits_after_decimal_point, first_root,
                        *num_of_digits_after_decimal_point, second_root);
                break;

        default:
                printf ("Unexpected number of roots\n");
    }
}

/**
    \brief Asks for number of digits after decimal point

    Calls Get_Not_Negative_Int ().

    \return Number of digits after decimal point
*/
int Ask_For_Number_Of_Digits_After_Decimal_Point (void)
{
    int after_point = 0;

    printf ("Write how many digits after the decimal point will be in the solution\n");
    printf ("The number of digits: ");

    after_point = Get_Not_Negative_Int ();

    printf ("\n");

    return after_point;
}

/**
    \brief Asks the user to choose between "yes" and "no"

    Calls Get_String (), Strcmp_Pro ().
    It does not matter if any symbol of the answer is in lowercase or uppercase.
    If the input is not either "yes" or "no", the program asks for input again.

    \param [in] *string_ptr {Pointer on the string that should be put on the screen}
    \return 1 (Yes) if the input is "yes"
    \return 0 (No) if the input is "no"
*/
enum Choice Yes_No (const char *string_ptr)
{
    assert (string_ptr != NULL);

    const char *Yes_String = "YES";
    const char *No_String  = "NO";
    const size_t Yes_Length = strlen (Yes_String);
    const size_t No_Length  = strlen (No_String);

    size_t length_of_the_input = 0;
    char written_word[4] = "";
    enum Choice yes_or_no = Error;

    while (yes_or_no == Error)
    {
        puts (string_ptr);
        printf ("YES/NO\n");

        length_of_the_input = Get_String (written_word, 4, false, false);

        if      (Strncmp_Pro (written_word, Yes_String, Yes_Length) == Equal && length_of_the_input == Yes_Length)
            yes_or_no = Yes;
        else if (Strncmp_Pro (written_word, No_String, No_Length)   == Equal && length_of_the_input == No_Length)
            yes_or_no = No;
        else
        {
            printf ("There is no such option. Try again\n");
            continue;
        }
    }

    return yes_or_no;
}

/**
    \brief Gets first "length" symbols of a string

    Calls fgets () but changes '\\n' into '\0'.
    Calls Clear_Stdin () to clear stdin and count inappropriate symbols.

    \param [out] *buffer {Pointer on the array where the string should be put}
    \param [in] length {The maximal length of the string that can be obtained}
    \param [in] upcase {Variable that is used to/not to change the symbols of the string into uppercase}
    \param [in] lowcase {Variable that is used to/not to change the symbols of the string into lowercase}
    \return The length of the string that user has written (even if it is greater of less than "length")

*/
int Get_String (char *buffer, const int length, bool upcase, bool lowcase)
{
    assert (buffer != NULL);
    assert (length > 0);

    fgets (buffer, length, stdin);

    if (upcase)
        for (int i = 0; i < length; i++)
            buffer[i] = toupper (buffer[i]);
    if (lowcase)
        for (int i = 0; i < length; i++)
            buffer[i] = tolower (buffer[i]);

    int length_of_the_input = 0;

    while (*buffer != '\n' && *buffer != '\0')
    {
        buffer++;
        length_of_the_input++;
    }
    if (*buffer == '\n')
        *buffer = '\0';
    else
        while (getchar () != '\n')
            length_of_the_input++;

    return length_of_the_input;
}

/**
    \brief Compares strings

    It does not matter if the symbols are in lowercase of uppercase.

    \param [out] *string_1 {Pointer on the array that contains first string}
    \param [out] *string_2 {Pointer on the array that contains second string}
    \param [in] length {The maximal number of symbols of both strings that will be compared}
    \return 1 (Greater) if  ASCII code of any symbol of the first string is greater than ASCII code of the symbol of the second string with the same index
    \return 0 (Equal) if first "length" symbols of both strings are equal
    \return -1 (Less) if  ASCII code of any symbol of the first string is less than ASCII code of the symbol of the second string with the same index
*/
enum Compare Strncmp_Pro (const char *string_1, const char *string_2, const size_t length)
{
    assert (string_1 != NULL);
    assert (string_2 != NULL);
    assert (length > 0);

    size_t number_of_letters = 0;
    enum Compare equal_or_not = Equal;

    while (toupper (*string_1) == toupper (*string_2) && number_of_letters++ < length)
    {
        if (*string_1 == '\0')
            break;
            
        string_1++;
        string_2++;
    }

    if (toupper (*string_1) > toupper (*string_2))
        equal_or_not = Greater;
    if (toupper (*string_1) < toupper (*string_2))
        equal_or_not = Less;

    return equal_or_not;
}
