
import java.util.Scanner;
import java.util.Random;
import java.util.Arrays;





public class Main {

      public static void main(String args[]) {

           // Instantiate the class BookList here ...
		  BookList LibraryBooks = new BookList();
		  BookList BookstoreBooks = new BookList();
    	  System.out.println("Welcome to the book program!");
    	  
    	  Scanner scan = new Scanner(System.in);
    	  
    	  System.out.println("Would you like to create a book object? (yes/no):");
    	  
    	  String answer = scan.next();
    	  
    	  while(!answer.toUpperCase().equals("NO")){
    		  
    		  if(!answer.toUpperCase().equals("YES")) {
    			  System.out.println("I'm sorry but "+ answer +" is not a valid answer. Please enter either yes or no: ");
    			  answer = scan.next();
    			  continue;
    		  }
    		 
    		  
    		  scan.nextLine();
    		  System.out.println("Please enter the author, title, and the isbn of the book seperated by /:");
    		  String stringInput = scan.nextLine();
    		  String input[]= stringInput.split("/");
    		  System.out.println(input[1]);
    		  
    		  System.out.println("Got it!");
    		  System.out.println("Now, tell me if is a bookstore book or a library book (enter BB for bookstore book or LB for library book):");
    		  String typeOfBook = scan.next();
    		  
    		  while(!typeOfBook.equals("BB") && !typeOfBook.equals("LB")) {
    			  
    			  System.out.println("Oops! That is not a valid entry. Please try again: ");
    			  
    			  typeOfBook = scan.next();
    			  
    		  }
    		  System.out.println("Got it!");
    		  

    		  
    		  if(typeOfBook.equals("BB")) {
    			  System.out.println("Please enter the list price of "+ input[1].toUpperCase()+ " by "+ input[0].toUpperCase()+": ");
    			  double bookPrice = scan.nextDouble();
    			  double percentage;
    			  
    			  System.out.println("Is it on sale? (y/n): ");
    			  
    			  String isSale = scan.next();
    			  
    			  if(isSale.equals("y")) {
    				  
    				  System.out.println("Deduction percentage: ");
    				  percentage = scan.nextDouble();
    			  }
    			  else {
    				  percentage = 0;
    			  }
    			  
    			  BookstoreBook book = new BookstoreBook(input[0],input[1],input[2],bookPrice, percentage/100);
    			  BookstoreBooks.addBook(book);
        		  System.out.println("Here is your bookstore book information");
        		  book.toString();

    		  }
    		  
    		  else {
    			  LibraryBook book = new LibraryBook(input[0],input[1],input[2]);
    			  LibraryBooks.addBook(book);
        		  System.out.println("Here is your library book information");
        		  book.toString();
    			  
    		  }
    		  
    		  
    		  
        	  System.out.println("Would you like to create a book object? (yes/no): ");
        	  answer = scan.next();

    		  
    	  }
    	  
    	  System.out.println("Here are all your books..");
    	  
    	  if(LibraryBooks.getSize() ==0) {
    		  System.out.println("There was no library books in all the books you provided");
    	  }
    	  else {
    		  System.out.println("Library Books ("+ LibraryBooks.getSize()+")");
    		  LibraryBooks.printList();
    	  }
    	  
    	  if(BookstoreBooks.getSize() ==0) {
    		  System.out.println("There was no bookstore books in all the books you provided");
    	  }
    	  else {
    		  System.out.println("Bookestore Books ("+ BookstoreBooks.getSize()+")");

    		  BookstoreBooks.printList();
    	  }
    	  
    	  
    	  

      }

}

//___________________________

abstract class Book {

//code of the abstract class Book

//You may add an abstract method if you see that fits…
private String author;
private String title;
private String isbn;

     
     public Book(){
         this.author = "N/A";
         this.title = "N/A";
         this.isbn = "N/A";
         
     }
     
    public Book(String author, String title, String isbn){
         this.author = author;
         this.title = title;
         this.isbn = isbn;
         
     }
     
     void setTitle(String title){
         this.title = title;
     }
     String getTitle (){
         return this.title;
     }
     void setAuthor (String author){
         this.author = author;
     }
     String getAuthor (){
         return this.author;
     }
     void setISBN (String isbn){
         this.isbn  = isbn;
     }
     String getISBN (){
         return this.isbn;
     }
     
         
     

}

//___________________________

class BookstoreBook extends Book {

      // fields and specific code to the BookstoreBook class goes here
     private double price;
     private double discountedPercentage;
     
     
     public BookstoreBook(String author, String title, String isbn, double price, double discount) {
    	 
    	 super(author, title, isbn);
    	 this.price = price;
    	 this.discountedPercentage = discount;
     }
     
     
     public void setPrice(double price) {
    	 this.price = price;
     }
     
     public double getPrice() {
    	 return this.price;
     }
     
     public void setDiscount(double discount) {
    	 this.discountedPercentage = discount;
     }
     public double getDiscount() {
    	 return discountedPercentage;
     }
     
     
     public String toString() {
    	 
    	 return "["+ getISBN() + "-" + getTitle().toUpperCase()+ " by "+ getAuthor().toUpperCase()+", $"+this.price+"]"; 
    	 
     }

     

}

//___________________________

class LibraryBook extends Book {

      // fields and specific code to the LibraryBook class goes here
      private String callNumber;
      public LibraryBook(String author, String title, String isbn) {
     	 
     	 super(author, title, isbn);
     	 this.callNumber = initializeCallNumber(author, isbn);
     	 
      }
      
      private String initializeCallNumber(String author, String isbn) {
    	  
    	  Random random = new Random();
    	  int randomFloor = random.nextInt(99)+1;
    	  
    	  String formatFloor = String.format("%02d", randomFloor);
    	  formatFloor += "."+ author.substring(0,2).toUpperCase() +"."+ isbn.charAt(isbn.length()-1); 
    	  
    	  return formatFloor;
    	  
      }
      public void setCallNumber(String callNumber) {
     	 this.callNumber = callNumber;
      }
      
      public String getCallNumber() {
     	 return this.callNumber;
      }

      
      public String toString() {
     	 
     	 return "["+ getISBN() + "-" + getTitle().toUpperCase()+ " by "+ getAuthor().toUpperCase()+"-"+this.callNumber+"]"; 
     	 
      }
      


}

//___________________________

class BookList {

      private Book[] list;
      private int count;

      public BookList() {

           list = new Book[100];
           this.count = 0;
      // Additional code goes here if needed...

      }
      
      public void addBook(Book book) {
    	  
    	  
    	  list[count] = book;
    	  count++;
      }
      public int getSize() {
    	  return this.count;
      }
      
    
      
      public void printList () {
    	  
    	  for(int i = 0; i < this.count; i++) {
    		  
    		  System.out.println(this.list[i].toString());
    	  }
    	  
      }
      
      

}
