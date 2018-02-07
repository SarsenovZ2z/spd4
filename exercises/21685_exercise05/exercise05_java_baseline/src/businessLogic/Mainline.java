package businessLogic;

/**********
* <p> Title: Compute Square Root of Two </p>
* 
* <p> Description: A sample program to show how to compute square root of two using doubles </p>
* 
* <p> Copyright: Copyright © 2009 </p>
* 
* @author Lynn Robert Carter
* @version 1.00	The initial version
* 
*/

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.lang.Double;

public class Mainline {
	public static void main (String [] args) {		
		
		double sig = 1E+10;								// Used to establish the limit for ending the loop
		double value = 2.0;								// We want the square root of this value
		
		// This is the initial guess
		double oldGuess = value / 2;
		
		// We set up the newGuess to be the same as the guess
		double newGuess = oldGuess;
		
		// The variables used to control the loop
		double limit;		// The limit that determines the end of the loop

		// Initialize the loop iteration counter
		int iteration = 0;
		do {	// This is the implementation of Newton's method for finding square root
			iteration++;							// Keep track of the number of iterations
			oldGuess = newGuess;					// Establish the current guess based on the newGuess from before
//			System.out.println("        oldGuess: " + oldGuess);
			newGuess = (oldGuess + value / oldGuess) / 2.0;	// compute the new guess based on the oldGuess
			limit = newGuess / sig;					// Establish the limit to be relative to the size of the guess...
//			System.out.println("Interation: " + iteration + " has completed.");
//			System.out.println();
//			System.out.println("        newGuess: " + newGuess);
			
			// Keep looping as long as the difference between the two guesses is larger than the relative limit and the
		} while (Math.abs(oldGuess-newGuess) > limit && iteration < 20);	// number of iterations is not too large
		
		// Display the calculated square root
		System.out.println();
		System.out.println("The square root of two is: " + newGuess);
		System.out.println();
	
		// Read in the square root that NASA has computed from a file 
		try {
			Scanner checkReader = new Scanner(new File("SquareRootTwo.txt"));
			String checkNumber = "";
			
			// Read in the value from NASA
			while (checkReader.hasNextLine())
				checkNumber += checkReader.nextLine().trim();
			
			// Convert the computed value to a string
			String answer = Double.valueOf(newGuess).toString();
			
			// Compare the two strings
			int diff = -1;
			for (int i = 0; i < answer.length(); i++)
				if (checkNumber.charAt(i) != answer.charAt(i)){
					diff = i;
					break;
				}
			
			// Display the results
			System.out.println();
			System.out.println("The value from NASA is:");
			System.out.println(checkNumber);
			System.out.println();
			System.out.println("The value we computed is:");
			System.out.println(answer);
			System.out.println();

			if (diff == -1)
				System.out.println("The numbers are identical to " + (answer.length()- 1) + " significant digits.");
			else
				System.out.println("The numbers differ at position " + diff);
			
		} catch (FileNotFoundException e) {
			System.out.println("TNot able to find the file: SquareRootTwo.txt");
		}
	}
}
