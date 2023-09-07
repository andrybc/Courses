import java.text.DecimalFormat;
import java.util.Scanner;


public class GradeReport {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scan = new Scanner(System.in);
		String ans = "Y";
		
		do {
			
			int gradeAs = 0;
			int gradeBs = 0;
			int gradeCs = 0;
			int gradeDs = 0;
			int gradeFs = 0;
			int higherThan70= 0;
			double sum = 0;
			int count = 0;
			
			int currentGrade = 0;
			do {
				System.out.print("Enter Score (Enter -1 to Stop): ");
				currentGrade = scan.nextInt();
				
				if(currentGrade > 100) {
					System.out.println("Score " + currentGrade + " Rejected");
				}
				else {
					if (currentGrade<=100 && currentGrade >=90) {
						gradeAs++;
						higherThan70++;
						count++;
						sum += currentGrade;
						
					}
					else if(currentGrade<=89 && currentGrade >=80) {
						gradeBs++;
						higherThan70++;
						count++;
						sum += currentGrade;
					}
					else if(currentGrade<=79 && currentGrade >=70) {
						gradeCs++;
						higherThan70++;
						count++;
						sum += currentGrade;
					}
					else if(currentGrade<=69 && currentGrade >=60) {
						gradeDs++;
						count++;
						sum += currentGrade;
					
					}	
					else if (currentGrade<=59 && currentGrade >=0){
						gradeFs++;
						count++;
						sum += currentGrade;
					}
				}
				
			}
			while(currentGrade != -1);
			DecimalFormat df = new DecimalFormat("0.00");
			double avg = sum/count;
			
			System.out.println("Here is your report:");
			System.out.println("      -    A total of " +count+ " score(s) entered. " + higherThan70 + " of them are higher 70 or higher");
			System.out.println("");
			System.out.println("      -    Letter Grade distribution of scores:");
			System.out.println("               -   "+ gradeAs + " Students earned the grade of A (90-100)");
			System.out.println("               -   "+ gradeBs + " Students earned the grade of B (80-89)");
			System.out.println("               -   "+ gradeCs + " Students earned the grade of C (70-79)");
			System.out.println("               -   "+ gradeDs + " Students earned the grade of D (60-69)");
			System.out.println("               -   "+ gradeFs + " Students earned the grade of F (59 or below)");
			System.out.println("      -    The average score is: "+ df.format(avg));
			
			System.out.print("Would you like to process another class?(Y or N):");
			ans = scan.next();
		}
		while(ans.equals("y") || ans.equals("Y") );

	}

}
