/* COP 3503C Assignment 2
This program is written by: Andry Bruel Canel */



import java.util.Scanner;
import java.util.Arrays;

public class Main {

	private static char[][] puzzle;
	private static int row, col;
	//	private static boolean[][] hasVisited;

	static boolean isSafe(char puzzle[][], int x, int y, int index, String word, boolean[][] hasVisited)
	{
		// if (x, y outside puzzle and not the correct letter in word) return false
		if (x >= 0 && x < row && y >= 0 && y < col && puzzle[x][y] == word.charAt(index) && !hasVisited[x][y] ) {
			return true;

		}

		return false;
	}

	static boolean findWordUtil(char puzzle[][], int x, int y, int index, String word, char sol[][], boolean[][] hasVisited)//backtracking function
	{

		if (isSafe(puzzle, x, y, index, word, hasVisited) == true) {// Check if puzzle[x][y] is valid
			// if (x, y is goal) return true
			if (index == word.length()-1 && puzzle[x][y] == word.charAt(index) ) {
				sol[x][y] = puzzle[x][y];
				return true;
			}
			

			// mark x, y as part of solution path
			sol[x][y]= word.charAt(index);
			hasVisited[x][y] = true;

	

			//handling the backtracking for up, down, left , and right
			if (findWordUtil(puzzle, x, y + 1, index + 1, word, sol, hasVisited) == true)
				return true;

			if (findWordUtil(puzzle, x, y - 1, index + 1, word, sol, hasVisited) == true)
				return true;


			if (findWordUtil(puzzle, x + 1, y, index +1, word, sol, hasVisited) == true)
				return true;

			if (findWordUtil(puzzle, x - 1, y, index + 1, word, sol, hasVisited) == true)
				return true;


			//handling the backtracking for diagonals

			if (findWordUtil(puzzle, x + 1, y + 1, index + 1, word, sol, hasVisited) == true)
				return true;

			
			if (findWordUtil(puzzle, x - 1, y + 1, index + 1, word, sol, hasVisited) == true)
				return true;

			if (findWordUtil(puzzle, x+1, y - 1, index + 1, word, sol, hasVisited) == true)
				return true;


			if (findWordUtil(puzzle, x-1, y - 1, index + 1, word, sol, hasVisited) == true)
				return true;


			sol[x][y] = ' ';//if rest of word not found in this iteration then backtrack and set to false
			hasVisited[x][y] = false;
			return false;
		}


		return false;
	}


	static void printSolution(char sol[][])//regular solution to print where the word is found in the puzzle (will be in solution 2D array)
	{
		for (int i = 0; i < row; i++) {
			System.out.print("[");
			for (int j = 0; j < col; j++) {
				if(sol[i][j]!= '\0') {
					System.out.print(sol[i][j]);

				}
				else {
					System.out.print(' ');
				}
				if (j < col - 1) {
					System.out.print(", ");
				}
			}
			System.out.println("]");
		}
		System.out.println();
	}

	private static boolean  findWord(char puzzle[][],int row, int col, String word)//wrapper function to call backtracking function on each cell in the puzzle
	{

		System.out.println("Looking for " + word);
		char[][] sol = new char[row][col];
		boolean[][]hasVisited = new boolean[row][col];//create a boolean array to check if the cell has been visited so same letter cant be counted multiple times

		for(int i = 0; i <row; i++) {//double for loop to go through every cell in the puzzle to find the word
			for(int j = 0; j < col; j++) {
				if (findWordUtil(puzzle, i, j, 0 , word, sol,hasVisited) == true) {
					printSolution(sol);

					return true;
				}
			}
		}
		//if the word not found then mention that
		System.out.println(word + " not found!");
		System.out.println();
		return false;
	}


	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		row = scan.nextInt();
		col = scan.nextInt();
		int wordsToFind = scan.nextInt();
		scan.nextLine();


		puzzle = new char[row][col];

		for (int i = 0; i < row; i++) {//thing to scan in the puzzle into a 2D array
			String line = scan.nextLine();
			int colIndex = 0; // initialize column index for each row
			for (int j = 0; j < line.length(); j++) {
				if (line.charAt(j) != ' ') {
					puzzle[i][colIndex] = line.charAt(j);
					colIndex++; // only increment column index when a character is added
				}
			}

		}

		/*  for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                System.out.print(puzzle[i][j] + " ");
            }
            System.out.println();
        }*/

		for(int i = 0; i < wordsToFind; i++) {//loop to find all the words given to us
			String word = scan.next();
			// System.out.println(word);
			findWord(puzzle, row, col,word );

		}


	}

}
