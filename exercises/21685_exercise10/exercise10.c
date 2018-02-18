#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_SIZE	512		// plenty large for one input line

typedef struct unumber_struct {
	char *unum;		// an array containing the unumber in numeric form
	int size;		// the number of elements in unum
	int dp;			// the decimal power of the unum
	bool sign;		// the sign (true = positive)
} UNumber;

#ifdef MEMORY_TRACE
// a global to count the number of allocated memory blocks
// increment once when memory is allocated, decrement once when memory
// is freed.  If this is not zero at the end of the program, there is
// a memory leak somewhere.
//
// This must be initialized to zero at the start of the program.
int allocated_memory_blocks;

/*
 * A utility function for printing debugging output associated with
 * allocating memory.  Use paired with debug_free_memory to get output
 * for a rudimentary heap trace.  This function is only defined if the
 * program is compiled with the -DDEBUG_TRACE option.
 *
 * Parameters:
 *		in: msg - a message to print for debugging
 *		in: num - the number of items to be allocated
 *		in: size - the size of each item
 *		in: zero - if true, calloc is used to zero allocated memory, else malloc
 *					(memory not zeroed)
 *
 * Returns: pointer to the allocated memory or NULL if memory could not be
 * 		allocated.  The returned pointer must be cast to the appropriate
 * 		pointer type by the caller.
 */
void *allocate_memory(const int num, const int size, const bool zero)
{
	// if the boolean zero is true, use calloc, which allocates
	// memory and writes zeroes to it.  Use malloc otherwise, which
	// does not initialize the memory.  Calloc is much less efficient,
	// so we avoid using it when malloc will suffice.
	void *p = (zero ? calloc(num, size) : malloc(num * size));
	if (p)
		allocated_memory_blocks ++;
	return p;
}

/*
 * A utility function for printing debugging output associated with freeing memory.
 * Use paired with debug_allocate_memory to get output for a rudimentary heap trace.
 * This function is only defined if the program is compiled with the -DDEBUG_TRACE option.
 *
 * Parameters:
 *		in: msg - a message to print for debugging
 *		in: p - pointer to the memory to be freed
 *
 * Returns: n/a
 */
void free_memory(void *p)
{
	free(p);
	allocated_memory_blocks --;
	return;
}
#else
// We only want to use the allocate_memory and free_memory functions if we are tracing
// memory usage.  So if we are not tracing memory usage, define the names of those
// functions to be macros that are replaced at compile time with actual calls to malloc,
// calloc and free.
//
// See function definitions above for parameters.
#define allocate_memory(n,s,z)    (z ? calloc(n,s) : malloc(n*s));
#define free_memory(p)            free(p)

#endif

/*
 * Delete a unumber - this frees the memory of a unumber.  Allows the programs that use
 * this library to not look into the structure (they still can, but they shouldn't have
 * toa).
 *
 * Parameters:
 *		in: msg - a message to print for debugging
 *		in: del - pointer to a UNumber structure to delete
 *
 * Returns: n/a
 */
void free_unumber(UNumber *del)
{
	// wrapping this up in a function will allow us to include this function in
	// a unumber library later so that the program that uses the unumber library
	// doesn't have to know what's in the structure (mimicking Java private data)
	free_memory(del->unum);
	return;
}

/*
 * Convert a unumber to a string.  Allocates memory for the string, which must later be freed.
 *
 * Parameters:
 * 		in: num - the number to convert to a string
 *
 * Returns: NULL if unable to allocate memory, else a pointer to the new string
 */
char *get_number_as_string(const UNumber *num)
{
	// size of the byte array plus decimal point, sign, leading zero, null terminator,
	// and space for trailing zeroes, if needed (e.g. 12000000)
	int end_size = num->size + 4 + num->dp;
	if (num->dp < 0)
		end_size -= num->dp;		// need room for leading zeros

	char *p = (char *) allocate_memory(end_size, 1, false);
	if (!p)
		return NULL;	// unable to allocated memory

	int i;
	int pi = 0;

	int added_characters = 0;
	if (!num->sign) {
		p[pi++] = '-';
		added_characters += 1;
	}

	if (num->dp <= 0) {
		p[pi++] = '0';
		added_characters += 1;
	}

	if (num->dp < 0) {
		p[pi++] = '.';
		for (i=0; i>num->dp; i--) {
			p[pi++] = '0';
		}
		for (i=0; i<num->size; i++) {
			p[pi++] = num->unum[i] + 0;//48
		}
	} else {
		for (i=0; i< num->size; i++) {
			if(pi - added_characters == num->dp) {
				p[pi++] = '.';
			}
			p[pi++] = num->unum[i] + 0;	// e.g. 0 + 48 = '0' (ascii)
		}

		for (i=pi; i< num->dp; i++)
			p[pi++] = '0';
		p[pi] = '\0';
	}

	return p;
}

/*
 * Create a new UNumber with the given member values.  The specified input number
 * is in the form of a string of ascii digits ('1', '2', etc.).  The ascii digits are
 * converted to numeric values by substracting 48.  This function allocates memory
 * which must later be freed.
 *
 * Parameters:
 *		in: num - pointer to a UNumber structure to hold the return values
 *		in: number - string containing the number to create
 *		in: dP - the decimal power to be used for the new number
 *		in: sign - the sign for the new number
 *
 * Returns: false if there were no errors, else true
 */
bool new_unumber_from_string(UNumber *num, const char *number, const int dp, const char sign)
{

	if (sign != '-' && sign != '+') {
		fprintf(stderr, "invalid sign '%c'\n", sign);
		return true;
	}

	// Allocate space for the new number
	num->unum = (char *)allocate_memory(strlen(number), 1, true);
	if(!num->unum)
		return true;	// unable to allocate memory

	/************************* Student's Code Goes Here ************************/

    strcpy(num->unum, number);
    num->sign = (sign=='+');
    num->size = strlen(number);
    num->dp = dp;

	/***************************************************************************/

	return false;
}

/*
 * A utility function for printing the contents of a UNumber
 * struct to stdout.
 *
 * Parameters:
 *		in: us - a pointer to the UNumber structure to be printed
 *
 * Returns: n/a
 */
void print_unum_struct(const UNumber *us)
{
	/************************* Student's Code Goes Here ************************/
    bool sign = us->sign;
    int decimal_power = us->dp;
    int size = us->size;
    char *value = us->unum;

    char *sign_str = sign?"positive":"negative";

    printf("sign = %s, decimal power = %d, size = %d, value = %s\n", sign_str, decimal_power, size, value);

	/***************************************************************************/

	return;
}

/*
 * Read information about a UNumber from stdin, store that information in a UNumber
 * structure, print the components of the structure, and display the number as a
 * floating point number.
 *
 * Parameters: n/a
 *
 * Returns:
 *		0 on success, else 1
 */
int main(void)
{
#ifdef MEMORY_TRACE
	allocated_memory_blocks = 0;
#endif
	const char prompt[] = "Enter a unumber (format sign,dp,digits): ";
	char input[INPUT_SIZE];	// for the user's input
	UNumber unum;			// A UNUmber structure for the input values
	char sign;				// the sign entered by the user
	int dp;					// the decimal power entered by the user
	char digits[INPUT_SIZE];// The digits entered by the user

	// prompt for input
	printf(prompt);

	// loop until the user hits return at the prompt (1st character will be a newline)
	while(fgets(input, INPUT_SIZE, stdin) && input[0] != '\n') {
		// get the components of the user's input, which is comprised of one character, one integer,
		// and one string separated by commas.  The string is simply the remainder of the input on
		// the line after the last comma.
		if(sscanf(input, "%c,%d,%s", &sign, &dp, digits) != 3) {
			// Did not get the expected input
			fprintf(stderr, "invalid input: %s\n", input);
		} else {
			// Input has the expected format
			// populate a UNumber structure with the input values
			if(new_unumber_from_string(&unum, digits, dp, sign)) {
				fprintf(stderr, "Error getting unumber from string\n");
			} else {
				// Print the components of the unumber structure that the user entered
				print_unum_struct(&unum);

				// Convert the UNumber to a string (e.g. -1.123) for display
				char *p = get_number_as_string(&unum);
				printf("You entered the number %s\n", p);

				// free memory allocated by get_number_as_string
				free_memory(p);

				// free the UNumber structure
				free_unumber(&unum);
			}
		}
		// prompt the user for input again
		printf(prompt);
	}

#ifdef MEMORY_TRACE
	if(allocated_memory_blocks)
		printf("There was a memory leak!! %d memory blocks not freed\n", allocated_memory_blocks);
	else
		printf("Congratulations!  All memory that was allocated was freed!\n");
#endif

	return 0;
}
