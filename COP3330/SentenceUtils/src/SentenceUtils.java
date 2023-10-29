
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


/**
 *Andry Canel
 *10/02/23
 *COP 3330
 */

class Histogram{
    
    private HashMap<String, Integer> mHistogram;  
    
    public Histogram(){
        this.mHistogram = new HashMap<>();
    }
    

    public void generateHistogram(ArrayList<String> letterGroups){
    	//loop through the arraylist with all the letter Groups
    	
    	for(int i = 0; i < letterGroups.size(); i++) {
    		//if hashmap already contains a lettergroup keyse then add 1 to the current value
    		if(this.mHistogram.containsKey(letterGroups.get(i))){
    			int newValue = this.mHistogram.get(letterGroups.get(i)) + 1;
    			this.mHistogram.put(letterGroups.get(i), newValue);
    			
    		}
    		//if not then just add new set to hashmap with keyset as the lettergroup and value as 1
    		else {
    			this.mHistogram.put(letterGroups.get(i), 1);
    		}
    	}
        

    }
    

    public void printHistogram(){
    	//loop through each set in hashmap and set i to the string lettergroup

    	for(String i : this.mHistogram.keySet()) {
    		
    		//print out lettergroup and store the value at that keyset to a variable that will be use to count up to
    		System.out.print(i + ": ");
    		int iteration = this.mHistogram.get(i);
    		
    		for(int j = 0; j < iteration; j++) {
    			//print out an asteriks up to iterations amount
    			System.out.print("*");
    		}
    		System.out.print("\n");
    	}
    
    }
    
}





public class SentenceUtils {  
    private ArrayList<String> mLetterGroups;
    private int mLetterGroupLen;
    
    public SentenceUtils(int letterGroupLen){
        this.mLetterGroups = new ArrayList<>();
        this.mLetterGroupLen = letterGroupLen;
    }
    public void addWords(String line){
        
        String[] tokens = this.getTokens(line);
        this.splitTokenstoLetterGroups(tokens);
    }
    public ArrayList<String> getLetterGroups(){
        return (this.mLetterGroups);
    }

    private String[] getTokens(String line){ 
      //using the regex professer provided. simply split string line at empty spaces
    	String[] tokens = line.split("\\s+");
    	//System.out.println(tokens[0]);
    	
    	return tokens;
    }
    
   
    private void splitTokenstoLetterGroups(String[] tokens){
    	//for each string in tokens 
    	for(String token: tokens) {
    		//check to see if string is less than lettergroupstrength, if so then skip
    		if(token.length()< this.mLetterGroupLen) {
    			continue;
    		}
    		//if not iterate this amount using this formula
    		int iterations = token.length()- this.mLetterGroupLen +1;
    		//then add 1 to firstIndex and last index each iteration
    		for(int i = 0; i < iterations; i++) {
    			int firstIndex = i;
    			int lastIndex = i+ this.mLetterGroupLen;//lastIndx is just the first Index plus the lettergroup length
    			String letterGroup = token.substring(firstIndex, lastIndex);
    			this.mLetterGroups.add(letterGroup);
    		}
     		
    		
    	}
 
    }
    
  
    public static void main(String[] args) {
    	
    	//setting arguments file name and letter group length
    	String fileName = args[0];
    	int letterGroupLength = Integer.parseInt(args[1]);
    	Scanner scan = new Scanner(System.in);
    	File inputFile;
    	//while the file does not exist keep prompting user for correct file name and scan it into that variable fileName
    	while(true) {
    		
    		inputFile = new File(fileName);
    		if(inputFile.exists() && inputFile.isFile()) {//checks to see if file is in storage and is normal
    			break;
    		}
    		else {
    			System.out.println("File does not exist. Please enter correct file name: ");
    			fileName = scan.nextLine();
    			
    		}
    	}
    	
    	Scanner fileScanner = null;
    	//try and catch block in case file was not found just in case..but segment up above should check that honestly
		try {
			fileScanner = new Scanner(inputFile);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	
    	//String fileContent = "";
		//creating a sentencutils object called newText with constructor
    	SentenceUtils newText = new SentenceUtils(letterGroupLength);
    	
    	//as long as the file has a line to be scanned keep running this loop
    	while(fileScanner.hasNextLine()) {
    		//setting a string to the next line in the file
    		String fileLine = fileScanner.nextLine();
    		//System.out.println(fileLine);
    		//fileContent += fileLine + " ";
    		
    		//calling newText object addWords method to add the tokens and letterGroups in object's arraylist
    		newText.addWords(fileLine);
    		
    		
    		
    	}
    	
    	//creating new histogram class called newHisto and generating the histogram by passing newTexts getLetterGroups method as an argument
    	Histogram newHisto = new Histogram();
    	newHisto.generateHistogram(newText.getLetterGroups());
    	newHisto.printHistogram();
    	
    	//System.out.println(newText.getLetterGroups());
      ///  System.out.println("You entered a valid file: " + fileContent);

    	

    }
}
