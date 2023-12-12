/* 100-operations.c
 * This file contains C functions for basic mathematical operations.
 */

#include <stdio.h>

/* add - Function to add two numbers
 * @a: The first operand
 * @b: The second operand
 *
 * Returns the sum of a and b.
 */
int add(int a, int b) {
    return a + b;
}

/* sub - Function to subtract two numbers
 * @a: The first operand
 * @b: The second operand
 *
 * Returns the result of subtracting b from a.
 */
int sub(int a, int b) {
    return a - b;
}

/* mul - Function to multiply two numbers
 * @a: The first operand
 * @b: The second operand
 *
 * Returns the product of a and b.
 */
int mul(int a, int b) {
    return a * b;
}

/* div - Function to divide two numbers
 * @a: The numerator
 * @b: The denominator
 *
 * Returns the result of dividing a by b.
 * Handles division by zero.
 */
int div(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        /* Handle division by zero */
        printf("Error: Division by zero\n");
        return 0;
    }
}

/* mod - Function to calculate the modulo of two numbers
 * @a: The dividend
 * @b: The divisor
 *
 * Returns the remainder of the division of a by b.
 * Handles modulo by zero.
 */
int mod(int a, int b) {
    if (b != 0) {
        return a % b;
    } else {
        /* Handle modulo by zero */
        printf("Error: Modulo by zero\n");
        return 0;
    }
}

