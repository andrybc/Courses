
public class Questions {

	public static void main(String args[]){
		Employee[] company;
		company = new Employee[3];
		
		  for (int i = 0; i < 3; i++)
	            company[i] = new Employee(); 

		for( int i = 0; i < 3; i++)
			System.out.print(company[i]);

	}
}

class Employee{
	public String toString() {
		return "employee";
	}
}
