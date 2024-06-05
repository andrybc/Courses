import java.util.*;
import java.io.*;


public class Main {
   
    static Scanner in = new Scanner(System.in);
    private int[][] square;
    private boolean[] possible;
    private int totalSqs;
    private int magicConst;
    private int numsquares;
   
   
    public Main(int N){
       
        if(N<=2){
        System.out.print("Only give values > 2 !!!");
        System.exit(1);
        }
       
        square = new int[N][N];
       
        magicConst = this.findMagicConstant(N);
        totalSqs = N*N;
        possible = new boolean[N*N];
       
        for( int i = 0; i < totalSqs; i++){
            possible[i] = true;
        }
        numsquares = 0;
    }
   
    public int findMagicConstant(int n){
       
        return n*((n*n)+1)/2;
    }
   
    public void fill(int row, int col){
       
        if(validSquare()){
           
            System.out.println("Done!!");
            for(int[] rws : square){
                System.out.println(Arrays.toString(rws));
            }
        }
       
        if( row == square.length){
            numsquares++;
            return;
        }
       
        for(int i = 0; i < totalSqs; i++){
           
            if(possible[i]){
                square[row][col] = i + 1 ;
                possible[i] = false;
               
                int nextcol = col +1;
                int nextrow = row;
               
                if(nextcol == square.length){
                    nextrow+=1;
                    nextcol = 0;
                   
                }
               
                fill(nextrow,nextcol);
               
                square[row][col] = 0;
                possible[i] = true;
            }
        }
       
    }
   
    public boolean validSquare(){
    	
    	
    
    	
    	//row check
    	
    	for( int r = 0; r < square.length; r++) {
    		
    		
    		
    		int rowSum = 0;
    		for( int c = 0; c < square.length; c++) {
    			
    			rowSum += square[r][c];
    			if(square[r][c] == 0) {
    				return false;
    			}
    		}
    		
    		if (rowSum != magicConst) {
    			return false;
    		}
    	}
    	
    	//colcheck
    	
    	for( int c = 0; c < square.length; c++) {
    		
    		
    		
    		int colSum = 0;
    		for( int r = 0; r < square.length; r++) {
    			
    			colSum += square[r][c];
    			if(square[r][c] == 0) {
    				return false;
    			}
    		}
    		
    		if (colSum != magicConst) {
    			return false;
    		}
    	}
    	
    	
    	
    	//diag1 check
    	

    		
    		
    		int diag1Sum = 0;
    		for( int r = 0; r < square.length; r++) {
    			
    			diag1Sum += square[r][r];
    			if(square[r][r] == 0) {
    				return false;
    			}
    		}
    		
    		if (diag1Sum != magicConst) {
    			return false;
    		}
    	
    		
    		
    	//diag2 check
    	

    		
    		
    		int diag2Sum = 0;
    		for( int c = square.length - 1; c >=0; c--) {
    			
    			diag2Sum += square[square.length -1 - c][c];
    			if(square[square.length -1 -c][c] == 0) {
    				return false;
    			}
    		}
    		
    		if (diag2Sum != magicConst) {
    			return false;
    		}
    	

    		return true;
       
    }
    public static void main(String[] args) {
       
        int N = in.nextInt();
        System.out.println("N = " + N);
        Main ms = new Main(N);
        ms.fill(0, 0);
       
       
    }
}
