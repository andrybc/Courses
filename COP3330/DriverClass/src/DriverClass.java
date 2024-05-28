/*
 * Andry Canel
 * 11/3/2023
 * DriverClass
 */




import java.util.Scanner;
public class DriverClass {
	public static void main(String args[]) {
		int numRows, numColumns;
		int index, start, end;
		char charAtIndex;
		int length;
		String subSequence;
		
		Scanner myScan = new Scanner(System.in);
		
		System.out.print("Enter how many rows and how many columns to load: ");
		numRows = myScan.nextInt();
		numColumns = myScan.nextInt();
		
		Code codeObject = new Code(numRows, numColumns);
		
		codeObject.loadCodeArray(numRows, numColumns);
		codeObject.printCodeArray(numRows, numColumns);
		
		// __________________________________________
		System.out.print("\n\nTesting charAt: Enter your index [a number greater or equal to 0 and less or equal to ");
		System.out.print((numRows * numColumns - 1) + "]:");
		index = myScan.nextInt();
		
		charAtIndex = codeObject.charAt(index);
		
		System.out.println("The character located at index " + index + " is: " + charAtIndex);
				// __________________________________________
		length = numRows * numColumns;
		System.out.println("\n\nTesting length: there are " + length + " characters.");
						// __________________________________________
		System.out.print("\n\nTesting subSequence: Enter start and end indexes:");
		
		start = myScan.nextInt();
		end = myScan.nextInt();
		subSequence = codeObject.subSequence(start, end);
		System.out.println("The subsequuence is: " + subSequence);
		// __________________________________________
		System.out.println("\nGoodbye!");
	}
}


class Code implements CharSequence {
	private int[][] codeArray;
	private int numRows, numColumns;
	
	public Code(int numRows, int numColumns) {
		this.numRows = numRows;
		this.numColumns = numColumns;
		codeArray = new int[numRows][numColumns];
	}
	
	public void loadCodeArray(int numRows, int numColumns) {
		Scanner myScan = new Scanner(System.in);
		int i, j;
		for (i = 0; i < numRows; i++) {
			System.out.print("Enter Row " + (i + 1) + ": ");
			for (j = 0; j < numColumns; j++) {
				codeArray[i][j] = myScan.nextInt();
			}
		}
	}
	
	public void printCodeArray(int numRows, int numColumns) {
		int i, j;
		System.out.println("\n_____________\n");
		for (i = 0; i < numRows; i++) {
			for (j = 0; j < numColumns; j++) {
				System.out.print(codeArray[i][j] + "\t");
			}
			System.out.println("");
		}
	}
	
// ______________THE CODE ABOVE IS TO REMAIN UNCHANGED______________________
	@Override
	public char charAt(int index) {
		
		int charRow = index / this.numColumns;
		int charCol = index % this.numColumns;
		
		
		return (char)this.codeArray[charRow][charCol];
	}

	@Override
	public int length() {
		// Add your code here...
		
		return this.numColumns *this.numRows;
	}
	
	@Override
	public String subSequence(int start, int end) {
		// Add your code here...
		String sequence = "";
		for(int i = start; i <= end; i++) {
			char currentChar = this.charAt(i);
			System.out.println(currentChar);
			sequence+= currentChar;
		}
		
		return sequence;
	}
	}