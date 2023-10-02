
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * Write your information 
 */

class Histogram{
    
    private HashMap<String, Integer> mHistogram;  
    
    public Histogram(){
        this.mHistogram = new HashMap<>();
    }
    
    /*
    This function counts the number of occurence of each letter group
    input: letter groups
    output: histogram
    
    example: input: ["an","an","or","or","or"]
             output: [<"an",2>, <"or",3>]
    */
    public void generateHistogram(ArrayList<String> letterGroups){
        
        /*
            You are going to implement body of this function
        */
    }
    
    /*
    This function prints the histogram
    input: histogram
    output: histogram printed on the display
    
    example: input: [<"an",2>, <"or",3>]
             output:
    
    an: **
    or: ***
    
    */
    public void printHistogram(){
        /*
            You are going to implement body of this function
        */
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
      
    /*
    This function splits a string into array of strings separated by space
    character
    input: a string
    output: array of words seperated by space character
    
    example: input: "object oriented"
             output: ["object", "oriented"]
    */
    private String[] getTokens(String line){ 
        /*
            You are going to implement body of this function
            
            
        */
    	String[] newword = {"Barry", "Allen"};
    	return newword;
    }
    
    /*
    This function splits the tokens into letter groups according to 
    this.mLetterGroupLen
    input: array of tokens
    output: letterGroups of size this.mLetterGroupLen appended to 
    this.mLetterGroups
    
    example: input: "object" "oriented"
             output: this.mLetterGroups (of size 4) = this.mLetterGroups + 
                  ["obje","bjec", "ject","orie", "rien", "ient", "ente", "nted"]
    */
    private void splitTokenstoLetterGroups(String[] tokens){
 
        /*
            You are going to implement body of this function
        */
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
    	
    	//setting arguments (file name and letter group length
    	String fileName = args[0];
    	int letterGroupLength = Integer.parseInt(args[1]);
    	Scanner scan = new Scanner(System.in);
    	File inputFile;
    	
    	while(true) {
    		
    		inputFile = new File(fileName);
    		if(inputFile.exists() && inputFile.isFile()) {
    			break;
    		}
    		else {
    			System.out.println("File does not exist. Please enter correct file name: ");
    			fileName = scan.nextLine();
    			
    		}
    	}
    	
    	Scanner fileScanner = null;
		try {
			fileScanner = new Scanner(inputFile);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	
    	String fileContent = "";
    	
    	while(fileScanner.hasNextLine()) {
    		String fileLine = fileScanner.nextLine();
    		fileContent += fileLine;
    		
    		
    	}
        System.out.println("You entered a valid file: " + fileContent);

    	

    }
}
