#include "get_next_line.h"
#include "libtest.h"
#include <fcntl.h>
#include <sys/resource.h>

void print_success(char *desc, int success)
{
	ft_putstr("    ");
	if (success) {
		ft_putstr(BOLD GREEN "OK " RESET);
		ft_putstr(desc);
	} else {
		ft_putstr(BOLD RED "KO ");
		ft_putstr(desc);
	}
	ft_putstr("\n");
}

void test_string(char *description, char *expected, char *got)
{
	int success = 1;

	if (expected == NULL)
	{
		if (got != NULL)
			success = 0;
	}
	else if (got == NULL)
		success = 0;
	else if (strcmp(expected, got) != 0)
		success = 0;
	print_success(description, success);
	if (!success)
		explain_expected_diff(expected, got, strlen(expected) + 1);
}

void test_int(char *description, int expected, int result)
{
	int success = 1;

	if (expected != result)
		success = 0;
	if (!success)
	{
		print_success(description, success);
		explain_expected_int(expected, result);
	}
}

int main (void)
{
	char	*line = NULL;
	int		result;
	int		fd;

	ft_putstr(BOLD "BUFFER_SIZE: " BLUE);
	ft_putnbr(BUFFER_SIZE);
	ft_putstr(RESET "\n");

	/* Invalid FDs */
	result = get_next_line(-4, &line);
	test_string("Test with a negative fd", NULL, line);
	test_int("Returned value", -1, result);

	result = get_next_line(8, &line);
	test_string("Test with a positive, not open fd", NULL, line);
	test_int("Returned value", -1, result);

	/* Empty file */
	fd = open("files/empty.txt", O_RDONLY);
	result = get_next_line(fd, &line);
	test_string("Test with empty file", "", line);
	test_int("Returned value", 0, result);
	close(fd);

	/* valid file with a single character */
	fd = open("files/one_char.txt", O_RDONLY);
	result = get_next_line(fd, &line);
	test_string("Test with a file that has a single char", "a", line);
	test_int("Returned value", 0, result);
	close(fd);

	/* valid file with a single character, which is a \n */
	fd = open("files/one_char_nl.txt", O_RDONLY);
	result = get_next_line(fd, &line);
	test_string("Test with a file that has a single char, which is a newline", "", line);
	test_int("Returned value", 1, result);
	close(fd);

	/* valid file with a regular character and a \n */
	fd = open("files/one_char_and_nl.txt", O_RDONLY);
	result = get_next_line(fd, &line);
	test_string("Test with a file that has a regular char and a newline", "a", line);
	test_int("Returned value", 1, result);
	close(fd);
}
