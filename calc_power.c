#include "main.h"

/**
 * calculate_power - Calculate the value of a number raised to
 * a given exponent.
 *
 * @base: base number.
 * @exp: exponent to which the base is raised.
 *
 * Return: power of base and exp
 */

int calculate_power(int base, int exp)
{
	int res = 1;
	int i;

	/* Loop 'exp' times to repeatedly multiply 'base' with itself. */
	for (i = 0; i < exp; i++)
		res *= base;

	return (res);
}
