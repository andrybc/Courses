
import java.util.Scanner;

public class HelloWorld {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
			
		Scanner scan = new Scanner(System.in);
		
		System.out.println("What is your name?");
		
		String userName = scan.nextLine();
		
		System.out.println("Hello, " + userName);
	}

}
