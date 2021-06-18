#include "get_next_line.h"
#include "libtest.h"
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/wait.h>

void print_success(char *desc, int success)
{
	ft_putstr(" ");
	if (success) {
		ft_putstr(BOLD GREEN "OK" RESET);
		//ft_putstr(desc);
	} else {
		ft_putstr(BOLD RED "    \nKO ");
		ft_putstr(desc);
	}
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

int main (int argc, char *argv[])
{
	if (argc > 2)
	{
		ft_putstr("wtf??\n");
		return (1);
	}

	char	*line = NULL;
	int		result;
	int		fd;

	if (argc == 1)
	{

		ft_putstr(BOLD "BUFFER_SIZE: " BLUE);
		ft_putnbr(BUFFER_SIZE);
		ft_putstr(RESET "\n");
	}

	if (argc == 2)
	{
		ft_putstr(RESET BOLD);
		ft_putstr(argv[0]);
		ft_putstr(BLUE " ");
		ft_putstr(argv[1]);
		ft_putstr(RESET " ");
		if (strcmp(argv[1], "1") == 0)
		{
			result = get_next_line(-4, &line);
			test_string("Test with a negative fd", NULL, line);
			test_int("Returned value", -1, result);
		}
		else if (strcmp(argv[1], "2") == 0)
		{
			result = get_next_line(8, &line);
			test_string("Test with a positive, not open fd", NULL, line);
			test_int("Returned value", -1, result);
		}
		else if (strcmp(argv[1], "3") == 0)
		{
			fd = open("files/empty.txt", O_RDONLY);
			result = get_next_line(fd, &line);
			test_string("test with empty file", "", line);
			test_int("Returned value", 0, result);
			free(line);
			close(fd);
		}
		else if (strcmp(argv[1], "4") == 0)
		{
			/* valid file with a single character */
			fd = open("files/one_char.txt", O_RDONLY);
			result = get_next_line(fd, &line);
			test_string("Test with a file that has a single char", "a", line);
			test_int("Returned value", 0, result);
			free(line);
			close(fd);
		}
		else if (strcmp(argv[1], "5") == 0)
		{
			/* valid file with a single character, which is a \n */
			fd = open("files/one_char_nl.txt", O_RDONLY);
			result = get_next_line(fd, &line);
			test_string("Test with a file that has a single char, which is a \\n", "", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a file that has a single char, which is a \\n, EOF", "", line);
			test_int("Returned value", 0, result);
			free(line);
			close(fd);

		}
		else if (strcmp(argv[1], "6") == 0)
		{
			/* valid file with a regular character and a \n */
			fd = open("files/one_char_and_nl.txt", O_RDONLY);
			result = get_next_line(fd, &line);
			test_string("Test with a file that has a regular char and a \\n", "a", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a file that has a regular char and a \\n, EOF", "", line);
			test_int("Returned value", 0, result);
			free(line);
			close(fd);
		}
		else if (strcmp(argv[1], "7") == 0)
		{
			fd = open("files/29chars.txt", O_RDONLY);
			result = get_next_line(fd, &line);
			test_string("Test with a multi char file, no \\n", "i'm a file with 29 characters", line);
			test_int("Returned value", 0, result);
			free(line);
			close(fd);

		}
		else if (strcmp(argv[1], "8") == 0)
		{
			fd = open("files/29chars_nl.txt", O_RDONLY);
			result = get_next_line(fd, &line);
			test_string("Test with a multi character file with a \\n", "i'm a file with 29 characters", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a multi character file with a \\n, EOF ", "", line);
			test_int("Returned value", 0, result);
			free(line);
			close(fd);

		}
		else if (strcmp(argv[1], "9") == 0)
		{
			fd = open("files/multi_lines.txt", O_RDONLY);
			result = get_next_line(fd, &line);
			test_string("Test with a multiline file, line #0", "i'm a file with", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a multiline file, line #1", "multiple", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a multiline file, line #2", "lines ", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a multiline file, line #3", "some lines are small,", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a multiline file, line #4", "some are bigger", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a multiline file, line #5", "but all of them are", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a multiline file, line #6", "smaller than 32 chars", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a multiline file, EOF", "", line);
			test_int("Returned value", 0, result);
			free(line);
			close(fd);
		}
		else if (strcmp(argv[1], "10") == 0)
		{
			/* File with lines that are 33 chars, and the 33rd are \n */
			fd = open("files/multi_lines_32_chars.txt", O_RDONLY);
			result = get_next_line(fd, &line);
			test_string("Test with a 33 chars multiline file, line #0", "These lines are exactly 33 chars", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a 33 chars multiline file, line #1", "long. The \\n char is always the ", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a 33 chars multiline file, line #2", "33rd charactere. How does your -", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a 33 chars multiline file, line #3", "code behaves? Pretty good, I'm -", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a 33 chars multiline file, line #4", "sure. Keep up the good work, ok?", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a 33 chars multiline file, EOF", "", line);
			test_int("Returned value", 0, result);
			free(line);
			close(fd);
		}
		else if (strcmp(argv[1], "11") == 0)
		{
			/* File with a big line */
			fd = open("files/big_line.txt", O_RDONLY);
			result = get_next_line(fd, &line);
			test_string("Test with a file with a really big line, line #0", "This file has a very very big line. Regardless of that, your program should be able to read it without major efforts. You'll probably figure out a way to read this whole line with whatever it is the BUFFER_SIZE;", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a file with a really big line, line #1", "glhf", line);
			test_int("Returned value", 1, result);
			free(line);
			result = get_next_line(fd, &line);
			test_string("Test with a file with a really big line, EOF", "", line);
			test_int("Returned value", 0, result);
			free(line);
			close(fd);
		}
		ft_putstr("\n");
	}
}
