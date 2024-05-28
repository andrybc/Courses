package practiceExam;


class MathUtil {
    public static int add(int a, int b) {
        return a + b;
    }
}


public class practiceExams {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
        int result = MathUtil.add(5, 3); // Calling a static method
        System.out.println("Result: " + result);

	}

}
