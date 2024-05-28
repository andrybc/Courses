
import java.util.Collections;
import java.util.PriorityQueue;
import java.util.Scanner;



public class Main {

	
	static Scanner in;
	
	public static void printMedian(int n) {
		
		
		PriorityQueue<Integer> smaller = new PriorityQueue<>(Collections.reverseOrder());
		PriorityQueue<Integer> greater = new PriorityQueue<>();
		
		int data = in.nextInt();
		smaller.add(data);
		double med = data;
		System.out.println(med);
		
		
		for( int i = 1; i < n ; i++) {
			
			int x = in.nextInt();
			
			if(smaller.size() > greater.size())
			{
				if(x < med) {
					greater.add(smaller.remove());
					smaller.add(x);
				
				
					
					}
				else {
					greater.add(x);
				}
				
				med = (double)(smaller.peek() + greater.peek())/2;
			}
			
			
			else if(smaller.size() == greater.size()) {
				
				if(x < med) {
					smaller.add(x);
					med = (double)smaller.peek();
				}
				else {
					greater.add(x);
					med = (double)greater.peek()
;				}
				
			}
			
			
			else {
				
				if(x > med) {
					smaller.add(greater.remove());
					greater.add(x);
				}
				else {
					smaller.add(x);
				}
				med = (double)(smaller.peek() + greater.peek())/2;
				
				
				
				
			}
			
			System.out.println(med);
		}
		
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		in = new Scanner(System.in);
		int n = in.nextInt();
		
		printMedian(n);
		
		
		
	}

}
