#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define SQR2_FILE	"SquareRootTwo.txt"

char *read_file(const char *file_name);

/*
 * Calculate the square root of 2, compare the result to a known value for the
 * square root of two, and display both.
 *
 * Parameters: n/a
 *
 * Returns:
 *		0 on success, else 1
 */
int main(void)
{
	int i;		// looper

    long double new_guess = 0;
	long double l = (long double)sqrt(2), r = 2, precision = 1e-18;
	while(r-l>precision) {
		new_guess = (r+l)/2;
		if (new_guess*new_guess>2) {
			r = new_guess-precision;
		}
		else if (new_guess*new_guess<2) {
			l = new_guess+precision;
		}
		else {
			break;
		}
	}

	// Display the calculated square root
	printf("\nThe square root of two is: %Lf\n", new_guess);

	// Read in the square root that NASA has computed from a file
	// read_file allocates memory for check_number, so we will
	// have to free it later.
	char *check_number = read_file(SQR2_FILE);
	if (!check_number) {
		// there was a problem reading the file, error message already printed
		return 1;
	}

	int bufsize = strlen(check_number) + 1;	// plus the null character
	char *answer_buf = (char *)malloc((size_t)bufsize);
	if (!answer_buf) {
		fprintf(stderr, "Unable to allocate %d bytes for answer\n", bufsize);
		free(check_number);
		return 1;
	}

	// convert the answer from a double to a string
	// the precision (number of digits after the decimal point) is the number
	// of digits after the decimal point in the data from NASA, which is
	// assumed to be bufsize-2
	sprintf(answer_buf, "%.*Lf", bufsize-2, new_guess);

	// Compare the two strings.  Can't use strcmp here because we want to know
	// at what character the strings differ.
	char *a = answer_buf;
	char *c = check_number;
	i = 0;
	while(*a != '\0' && *c != '\0') {
		if (*a != *c) {
			break;
		}
		i++; a++; c++;
	}

	// Display the results
	printf("\nThe value from NASA is:\n%s\n", check_number);
	printf("The value we computed is:\n%s\n", answer_buf);

	if (i == bufsize)
		printf("The numbers are identical to %d significant digits.\n", i);
	else
		printf("The numbers differ at position %d.\n", i+1);

	// free the memory we used
	free(check_number);
	free(answer_buf);

	return 0;
}

/*
 * Read a file.  Return the contents in a string.  Memory for the string is allocated and must
 * be freed by the caller.
 *
 * This function discards all nondigit characters except for allowing one decimal point, if
 * present.  (The input file is expected to contain a decimal number, possibly with leading
 * and/or trailing spaces and embedded newlines).
 *
 * Parameters:
 * 		in: file_name - the name of the file to read
 *
 * Returns:
 *		A pointer to a string containing the number in the file.  The string is null-terminated.
 *		Returns NULL if an error is encountered (file not found, memory allocation, etc).
 */
char *read_file(const char *file_name)
{
	// open the file for reading
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		fprintf(stderr, "Unable to open %s for reading\n", file_name);
		return NULL;
	}

	// determine the size of the file by reading each character one by one until we get
	// to end of file, then rewinding the file pointer back to the beginning
	size_t size = 0;
	while(fgetc(fp) != EOF) {
		size++;
	}
	rewind(fp);

	size ++;	// add one for the null byte on the end

	// allocate space for the contents of the file, include space for the null at the end
	// of the string
	char *buf = (char *)malloc(size);
	if(!buf) {
		fprintf(stderr, "Unable to allocate %ld bytes for file buffer\n", (long) size);
		return NULL;
	}

	// Read the file one character at a time and store the characters in
	// the buffer.  Skip newlines. In fact, skip all characters that are not digits.
	// Allow one decimal point.  This has the side effect of validing that the input
	// file actually contains a float number.
	bool have_decimal = false;
	int i;
	char *p = buf;
	for (i=0; i<size; i++) {
		char c = (char)fgetc(fp);
		if (c == '.') {
			if(have_decimal) {
				// found more than one decimal point
				fprintf(stderr, "Input from %s is not a valid float in decimal format\n", file_name);
				free(buf);
				fclose(fp);
				return NULL;
			}
			have_decimal = true;
			*(p++) = c;		// save the decimal point
		} else if (isdigit(c)) {
			*(p++) = c;		// save the digit
		}
		// else do nothing - do not save the character
	}

	// null-terminate the buffer (so that it becomes a string)
	*p = '\0';

	// close the input file
	fclose(fp);

	// return the data from the file as a null-terminated string
    return buf;
}
