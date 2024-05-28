/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Andry Canel
| Language: Java
|
| To Compile: javac pa01.java

|
| To Execute: java -> java pa01.java kX.txt pX.txt

| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2023
| Instructor: McAlpin
| Due Date: 03/06/2024
+===========================================================================*/

package pa01;
import java.io.*;
import java.util.Arrays;

public class pa01 {
    private static final int MAX_TEXT_SIZE = 10000;
    private static String encryptionKeyFileName;
    private static String plainTextFileName;
    private static int[][] encryptionMatrix;
    private static char[] plainText;
    private static char[] cryptedText;
    private static int finalSize;
    
    
    private static void readEncryptionKey(String fileName) throws IOException {
        File file = new File(fileName);
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            int n = Integer.parseInt(br.readLine());
            encryptionMatrix = new int[n][n];
            
           // System.out.println(n);
            for (int i = 0; i < n; i++) {
                String line = br.readLine();
                String[] values = line.trim().split("\\s+");

                for (int j = 0; j < n; j++) {
                    encryptionMatrix[i][j] = Integer.parseInt(values[j]);
                }
            }
        }
    }
    private static void processPlainTextFile(String fileName) throws IOException {
    	finalSize  = 0;
        File file = new File(fileName);
        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            plainText = new char[MAX_TEXT_SIZE];
            int index = 0;
            int c;

            while ((c = br.read()) != -1) {
                char character = (char) c;
                if (Character.isLetter(character)) {
                    if (index >= MAX_TEXT_SIZE) break;
                    plainText[index++] = Character.toLowerCase(character);
                    finalSize++;
                }
            }

            // Padding with 'x' if necessary
            while (index % encryptionMatrix.length != 0) {
                if (index >= MAX_TEXT_SIZE) break;
                plainText[index++] = 'x';
                finalSize++;
            }
        }
    }
    private static void printEncryptionMatrix() {
        System.out.println("Key Matrix:");
        for (int[] row : encryptionMatrix) {
            for (int value : row) {
                System.out.print(value + " ");
            }
            System.out.println();
        }
    }
    private static void encryptText(int[][] keyMatrix, char[] plaintext) {
        int n = keyMatrix.length;
        int length = finalSize;
        cryptedText = new char[length];

        for (int i = 0; i < length; i += n) {
            for (int j = 0; j < n; j++) {
                cryptedText[i + j] = 0;
                for (int k = 0; k < n; k++) {
                	//System.out.println(keyMatrix[j][k] + " * " + (int)(plaintext[i + k] - 'a'));
     
                    cryptedText[i + j] += keyMatrix[j][k] * (int)(plaintext[i + k] - 'a');
                }
                cryptedText[i + j] = (char)(cryptedText[i + j] % 26 + 'a');
            }
        }
    }

    private static void printProcessedText() {
        System.out.println("Plaintext:");
        int charCount = 0;
        for (char c : plainText) {
            if (c != '\u0000') {
                System.out.print(c);
                charCount++;
                if (charCount == 80) {
                    System.out.println();
                    charCount = 0;
                }
            }
        }
        if (charCount > 0) {
            System.out.println(); // Print the newline if there are characters in the last line
        }
    }
    private static void printEncyptedText() {
        System.out.println("Ciphertext:");
        int charCount = 0;
        for (char c : cryptedText) {
            if (c != '\u0000') {
                System.out.print(c);
                charCount++;
                if (charCount == 80) {
                    System.out.println();
                    charCount = 0;
                }
            }
        }
        if (charCount > 0) {
            System.out.println(); // Print the newline if there are characters in the last line
        }
    }
    public static void main(String[] args) {
        if (args.length != 2) {
            System.out.println("Please provide two filenames as arguments.");
            return;
        }

        encryptionKeyFileName = args[0];
        plainTextFileName = args[1];

        try {
            readEncryptionKey(encryptionKeyFileName);
            processPlainTextFile(plainTextFileName);
            
            encryptText(encryptionMatrix,plainText);
         
            printEncryptionMatrix();
            System.out.println();
            printProcessedText();
            System.out.println();
            printEncyptedText();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}

/*=============================================================================
| I Andry Canel (4262970) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/
