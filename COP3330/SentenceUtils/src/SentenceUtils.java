
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
    	
    	for(int i = 0; i < letterGroups.size(); i++) {
    		if(this.mHistogram.containsKey(letterGroups.get(i))){
    			int newValue = this.mHistogram.get(letterGroups.get(i)) + 1;
    			this.mHistogram.put(letterGroups.get(i), newValue);
    			
    		}
    		else {
    			this.mHistogram.put(letterGroups.get(i), 1);
    		}
    	}
        

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

    	for(String i : this.mHistogram.keySet()) {
    		
    		System.out.print(i + ": ");
    		int iteration = this.mHistogram.get(i);
    		
    		for(int j = 0; j < iteration; j++) {
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
      
    /*
    This function splits a string into array of strings separated by space
    character
    input: a string
    output: array of words seperated by space character
    
    example: input: "object oriented"
             output: ["object", "oriented"]
    */
    private String[] getTokens(String line){ 
      
    	String[] tokens = line.split("\\s+");
    	//System.out.println(tokens[0]);
    	
    	return tokens;
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
    	
    	for(String token: tokens) {
    		if(token.length()< this.mLetterGroupLen) {
    			continue;
    		}
    		
    		int iterations = token.length()- this.mLetterGroupLen +1;
    		
    		for(int i = 0; i < iterations; i++) {
    			int firstIndex = i;
    			int lastIndex = i+ this.mLetterGroupLen;
    			String letterGroup = token.substring(firstIndex, lastIndex);
    			this.mLetterGroups.add(letterGroup);
    		}
     		
    		
    	}
 
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
    	SentenceUtils newText = new SentenceUtils(letterGroupLength);
    	
    	while(fileScanner.hasNextLine()) {
    		String fileLine = fileScanner.nextLine();
    		//System.out.println(fileLine);
    		fileContent += fileLine + " ";
    		
    		newText.addWords(fileLine);
    		
    		
    		
    	}
    	
    	
    	Histogram newHisto = new Histogram();
    	newHisto.generateHistogram(newText.getLetterGroups());
    	newHisto.printHistogram();
    	
    	System.out.println(newText.getLetterGroups());
      ///  System.out.println("You entered a valid file: " + fileContent);

    	

    }
}
