
double sqrt2() {
	double value = 2;				// Find the square root of this number
	double sig = 1E+10;				// Used to establish the limit for ending the loop
	double old_guess = value / 2;	// This is the initial guess
	double new_guess = old_guess; 	// set up the newGuess to be the same as the guess
	double limit;					// The limit that determines the end of the loop
	int i = 0;						// Loop iteration counter

	// This is the implementation of Newton's method for finding square root
	do {
		i++;						// Keep track of the number of iterations
		old_guess = new_guess;		// Establish the current guess based on the new_guess from before
		new_guess = (old_guess + value / old_guess) / 2.0;	// compute new guess based on old_guess
		limit = new_guess / sig;		// Establish the limit to be relative to the size of the guess...
		// Keep looping as long as the difference between the two guesses is larger than the relative
		// limit and the number of iterations is not too large
	} while (fabs(old_guess - new_guess) > limit && i < 20);
    return new_guess;
}
