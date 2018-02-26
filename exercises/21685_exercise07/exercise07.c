#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DATA_FILE	"DataFile.txt"
#define INPUT_SIZE	512		// reasonably large for a line containing one double

double *read_file(const char *file_name, size_t *size);

/*
 * Read a series of floating point values from a file, sort them, and display the
 * sorted values to stdout.
 *
 * Parameters: n/a
 *
 * Returns:
 *		0 on success, else 1
 */


void Z2zsort(double *array, int sz) {
    for (int i=0;i<sz-1;++i) {
        int mn = i;
        for (int j=i+1;j<sz;++j) {
            if (array[mn]>array[j]) {
                mn = j;
            }
        }
        double tmp = array[i];
        array[i] = array[mn];
        array[mn] = tmp;
    }
}

int main(void)
{
	size_t num;		// the number of elements in the array created by read_file

	// Read in the values to sort from the data file
	double *array = read_file(DATA_FILE, &num);
	if (!array) {
		// there was a problem reading the file, error message already printed
		return 1;
	}

	/*******************  Add your code here *********************/

    Z2zsort(array, num); // array+begin, end
    for (size_t i=0;i<num;++i) {
        printf("%f\n", array[i]);
    }

	/*************************************************************/

	// free the array (memory allocated by read_file)
	free(array);

	return 0;
}

/*
 * Read a file.  The file is expected to contain a series of floating point values, one
 * to a line.  Space is allocated for the values in the form of an array of doubles.
 * Memory for the array must be freed by the caller.
 *
 * Parameters:
 * 		in: file_name - the name of the file to read
 *		in: pointer to a value in which to store the number of values read
 *
 * Returns:
 *		A pointer to an array of double values.
 *		Returns NULL and an error message is printed to stderr if an error is encountered.
 */
double *read_file(const char *file_name, size_t *size)
{
	// open the file for reading
	FILE *fp = fopen(file_name, "r");
	if (fp == NULL) {
		fprintf(stderr, "Unable to open %s for reading\n", file_name);
		return NULL;
	}

	// Determine the number of lines in the file (and therefore the number of double
	// values, since the file is expected to have one value per line) by counting
	// the lines.  We need to know this so we can allocated an appropriate sized
	// array for the values.
	char input[INPUT_SIZE];		// space to store the line read from the file
	int num = 0;				// number of items read
	// fgets returns NULL at end of file or if there is an error
	while(fgets(input, INPUT_SIZE, fp) != NULL) {
		num ++;
	}
	rewind(fp);	// move the file pointer back to the start of the file

	// returning the number of values in the file
	*size = num;

	// Allocate space for the contents of the file.  The size to allocate is the number
	// of values in the file multiply by the size, in bytes, of each item (in this case,
	// we are storing doubles in the array)
	double *array = (double *)malloc(num * sizeof(double));
	if(!array) {
		fprintf(stderr, "Unable to allocate %ld bytes for file buffer\n", (long) num);
		return NULL;
	}

	// Read the file one line at a time and parse the value from the line using sscanf.
	int i;
	bool have_error = false;
	for (i=0; i<num && !have_error; i++) {
		// Get the line and put it into a string
		if(fgets(input, INPUT_SIZE, fp) == NULL) {
			fprintf(stderr, "Unable to read values from %s\n", DATA_FILE);
			have_error = true;
		}
		// Parse the value from the input line and store it in the array.
		// sscanf returns the number of values in the string that match the pattern it is given,
		// in this case "%lf" for one double value.
		if(sscanf(input, "%lf", &array[i]) != 1) {
			fprintf(stderr, "Line %d of %s does not contain a valid floating point number\n", i+1, DATA_FILE);
			have_error = true;
		}
	}

	// close the input file
	fclose(fp);

	// check for an error - if there was an error parsing the file, free the space and return NULL
	if (have_error) {
		free(array);
		array = NULL;
		*size = 0;
	}

    return array;
}
