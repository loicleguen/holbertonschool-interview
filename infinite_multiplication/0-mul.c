#include "holberton.h"

/**
 * print_error - Prints "Error" followed by a newline and exits with status 98
 */
void print_error(void)
{
	char *err = "Error\n";
	int i;

	for (i = 0; err[i]; i++)
		_putchar(err[i]);
	exit(98);
}

/**
 * _strlen - Returns the length of a string
 * @s: Input string
 *
 * Return: Length of string
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len])
		len++;
	return (len);
}

/**
 * is_digit - Checks if a string consists only of digits
 * @s: Input string
 *
 * Return: 1 if all digits, 0 otherwise
 */
int is_digit(char *s)
{
	int i = 0;

	if (!s || !s[0])
		return (0);

	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * multiply - Multiplies two numbers represented as strings
 * @n1: First number string
 * @n2: Second number string
 */
void multiply(char *n1, char *n2)
{
	int len1 = _strlen(n1), len2 = _strlen(n2);
	int len_res = len1 + len2;
	int *res, i, j, digit1, digit2, sum, start = 0;

	res = malloc(sizeof(int) * len_res);
	if (!res)
		print_error();

	for (i = 0; i < len_res; i++)
		res[i] = 0;

	for (i = len1 - 1; i >= 0; i--)
	{
		digit1 = n1[i] - '0';
		for (j = len2 - 1; j >= 0; j--)
		{
			digit2 = n2[j] - '0';
			sum = (digit1 * digit2) + res[i + j + 1];
			res[i + j + 1] = sum % 10;
			res[i + j] += sum / 10;
		}
	}

	while (start < len_res - 1 && res[start] == 0)
		start++;

	for (i = start; i < len_res; i++)
		_putchar(res[i] + '0');
	_putchar('\n');

	free(res);
}

/**
 * main - Entry point, multiplies two positive numbers
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: 0 on success, exits with 98 on error
 */
int main(int argc, char *argv[])
{
	if (argc != 3 || !is_digit(argv[1]) || !is_digit(argv[2]))
		print_error();

	multiply(argv[1], argv[2]);

	return (0);
}
