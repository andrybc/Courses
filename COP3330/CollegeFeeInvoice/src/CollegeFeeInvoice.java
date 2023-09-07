
import java.util.Scanner;
import java.text.DecimalFormat;
public class CollegeFeeInvoice {

	public static void main(String[] args) {
		//creating scanner instance and prompting user for information
		Scanner scan = new Scanner(System.in);
		System.out.println("Welcome student, please fill out the information below?");
		
		System.out.print("Student ID?: ");
		String studentID = scan.next();
		//System.out.println();
		scan.nextLine(); // Consume the newline character

		System.out.print("Full name?: " );
		String studentName = scan.nextLine();
		//System.out.println();
		
		//creating an array to store the two crn/credithour
		String[] classes = new String[2];
		
		for(int i = 0; i < classes.length; i++) {
			System.out.print("Enter crn/credit hours for class #" + (i+1) + " (like 5665/3):");
			classes[i] = scan.next();
			//System.out.println();

		}
		//printing out first part of ticket with student name and ID
		System.out.println("Your invoice is below");
		System.out.println("============================");
		System.out.println();
		System.out.println("SIMPLE COLLEGE");
		System.out.println("ORLANDO FL 10101");
		System.out.println("****************************");
		System.out.println();
		System.out.println("Fee Invoice Prepared for:");
		System.out.println("["+ studentName + "] ["+ studentID + "]");
		System.out.println("1 Credit Hour = %120.25");
		System.out.println();
		System.out.println("CRN            CREDIT HOURS");
		
		//initializing sum variable and preparing the decimal format
		double sum = 35.00;
		DecimalFormat df = new DecimalFormat("0.00");
		//looping through the classes array to split crn and credithour at the "/"
		for(int i = 0; i < classes.length; i++) {
			String crn_credit[];
			
			int crn;
			int creditHours;
			crn_credit = classes[i].split("/");
			
			crn = Integer.parseInt(crn_credit[0]);//didnt really have to do this since I am not doing math with the crn
			creditHours = Integer.parseInt(crn_credit[1]);  
			
			double coursePrice = creditHours * 120.25;
			sum+= coursePrice;
			//printing out the crn, creditHour, and pricePrices
			System.out.println(crn +"           "+ creditHours + "                        " + "$" +df.format(coursePrice));
			
		}
		
		
		
		//printing out the rest of the invoice including the sum
		System.out.println("               Health & id fees"+ "         $35.00");
		System.out.println();
		System.out.println("----------------------------------------------------");
		System.out.println("               Total Payments           $"+df.format(sum));


	}

}
