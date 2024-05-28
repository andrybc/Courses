
/* COP 3503C Assignment 1
This program is written by: Andry Bruel Canel */
import java.util.Scanner;
import java.util.HashSet;
import java.math.*;




public class Main {
	
	
	static Scanner in;
	private static int[] pair = {0,0};
	
	
	private static int[] getCandidatePair(int A[], int target) {
		
		
		int i = 0, j = A.length - 1;//pointer to the beginning and end of the array
		int newPair[] = {0,0};
		
		while( i < j ) {//as long as the pointers do not meet
			int sum = A[i] + A[j]; //add the two numbers on opposite ends
			
			if(sum == target) {//if two numbers add to target return the two numbers
				newPair[0] = A[i];
				newPair[1] = A[j];
				return newPair;
			}
			else if (sum > target) {//if sum is larger than target than move right point back up the array
				j--;
			}
			else {//else move the left run down 
				i++;
			}
			
		}
		
		return newPair;// No pair found returns {0,0}
	}
	
	private static int[] findPairUnsortedList(int[] numbers, int target) {
		
        HashSet<Integer> hasSeen = new HashSet<>();
		int newPair[] = {0,0};

        for (int i = 0; i < numbers.length; i ++) {
            int complement = target - numbers[i];//find the difference between the target and the current point
            if (hasSeen.contains(complement)) {//if this number has already been seen  the return the two pairs O(1)
				newPair[0] = Math.min(complement, numbers[i]);
				newPair[1] = Math.max(complement, numbers[i]);
                return newPair;
            }
            hasSeen.add(numbers[i]);//else add the difference into the set O(1)
        }

        return newPair; // No pair found returns {0,0}
    }

	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		in = new Scanner(System.in);
		int n = in.nextInt();
		
		for(int i = 0; i < n; i++) {
					
			int sortedStatus = in.nextInt();
			int pointSize = in.nextInt();
			int numbers[]= new int[pointSize];
			
			for(int k = 0; k < pointSize; k++) {//scan in the points
				numbers[k] = in.nextInt();
				}
			
			int target = in.nextInt();
			//System.out.println(Arrays.toString(numbers));
			
			if(sortedStatus ==1) {
				pair = getCandidatePair(numbers, target);
			}
			else {
				pair = findPairUnsortedList(numbers, target);
			}
			System.out.print("Test case#" + (i+1) + ": ");
			if(pair[0] == 0 && pair[1]==0) {
				System.out.println("No way you can spend exactly "+ target + " points.");
			}
			else {
				System.out.println("Spend "+ target + " points by playing the games with "+ pair[0] + " points and " + pair[1]+ " points.");
			}
		}
	}

}
