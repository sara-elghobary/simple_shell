#include "main.h"

/**
 * _strlen - returns the length of a string
 *
 * @s: pointer to a char
 * Return: int
 *
 */

 int _strlen(char *s)
{
	int length = 0;

	while (*s != '\0')
	{
		length++;
		s++;
	}
	return (length);
}

/**
 * _strcpy - copies a string to another string
 *
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 * Return: pointer to the destination string
 */

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strdup - duplicates a string
 *
 * @str: the string to duplicate
 * Return: a pointer to the duplicated string
 *
**/

char *_strdup(char *str)
{
	int len;
	char *s;

	if (str == NULL)
		return (NULL);

	len = _strlen(str);

	s = (char *)malloc(len + 1);

	if (s == NULL)
		return (NULL);

	_strcpy(s, str);

	return (s);
}

/**
 * _strcmp - compares two strings
 *
 * @s1: the first string
 * @s2: the second string
 *
 * Return: an integer less than, equal to, or greater than zero if s1 is found,
**/

int _strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}


/**
 * itoa - converts an integer to a string in a given base
 *
 * @val: the integer to convert
 * @base: the base to use, between 2 and 16
 *
 * Return: a pointer to a static buffer that contains the converted string
**/

char *itoa(int val, int base)
{
	static char buf[32] = {0};
	int i = 30;

	for (; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return (&buf[i + 1]);
}
