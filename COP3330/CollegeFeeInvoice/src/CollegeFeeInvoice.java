
import java.util.Scanner;
import java.text.DecimalFormat;
public class CollegeFeeInvoice {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		System.out.println("Welcome student, please fill out the information below?");
		
		System.out.print("Student ID?: ");
		String studentID = scan.next();
		//System.out.println();
		scan.nextLine(); // Consume the newline character

		System.out.print("Full name?: " );
		String studentName = scan.nextLine();
		//System.out.println();
		
		String[] classes = new String[2];
		
		for(int i = 0; i < classes.length; i++) {
			System.out.print("Enter crn/credit hours for class #" + (i+1) + " (like 5665/3):");
			classes[i] = scan.next();
			//System.out.println();

		}
		
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
		
		double sum = 35.00;
		DecimalFormat df = new DecimalFormat("0.00");
		for(int i = 0; i < classes.length; i++) {
			String crn_credit[];
			
			int crn;
			int creditHours;
			crn_credit = classes[i].split("/");
			
			crn = Integer.parseInt(crn_credit[0]);
			creditHours = Integer.parseInt(crn_credit[1]);  
			
			double coursePrice = creditHours * 120.25;
			sum+= coursePrice;
			System.out.println(crn +"           "+ creditHours + "                        " + "$" +df.format(coursePrice));
			
		}
		
		
		
		
		System.out.println("               Health & id fees"+ "         $35.00");
		System.out.println();
		System.out.println("----------------------------------------------------");
		System.out.println("               Total Payments           $"+df.format(sum));


	}

}
