/*============================================================================
| Assignment: pa02 - - Calculating an 8, 16, or 32 bit
| checksum on an ASCII input file
|
| Author: Andry Canel
| Language: Java
|
| To Compile: javac pa02.java

|
| To Execute: java -> java pa02.java inputFile.txt 8


| Note: All input files are simple 8 bit ASCII input
|
| Class: CIS3360 - Security in Computing - Spring 2024
| Instructor: McAlpin
| Due Date: 03/31/2024

+===========================================================================*/

package pa02;
import java.io.*;



public class pa02 {
   // private static final int MAX_TEXT_SIZE = 10000;
    private static String checkSumFileName;
    private static int checksumSize;
    private static String fileContent;
    private static int finalSize;
    
    private static void readFileContent(String fileName) throws IOException {
        StringBuilder contentBuilder = new StringBuilder();
        File file = new File(fileName);
    	//System.out.println("here 2");

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;
          //  System.out.println("here 3");
            while ((line = br.readLine()) != null) {
                contentBuilder.append(line).append('\n'); // preserve line breaks
            }
        }
    	


        fileContent = contentBuilder.toString();
    }
    private static void echoInputText(String text) {
        for (int i = 0; i < text.length(); i += 80) {
            System.out.println(text.substring(i, Math.min(text.length(), i + 80)));
        }
    }

    private static long calculateChecksum(String content, int bits) {
        long checksum = 0;
        int blockSize = bits / 8; //  the block size based on checksum size.
        finalSize = content.length();
    
        int paddingRequirement = blockSize - (content.length() % blockSize);
        if (paddingRequirement > 0 && paddingRequirement < blockSize) {
            // padding  with 'X' to align with block size.
            for (int i = 0; i < paddingRequirement; i++) {
                content += "X";
                System.out.print('X');
                finalSize++;
            }
        }
        System.out.println();
        // Process the content in blocks according to the checksum size.
        for (int i = 0; i < content.length(); i += blockSize) {
            long blockValue = 0;
            for (int j = 0; j < blockSize; j++) {
                blockValue = (blockValue << 8) + (content.charAt(i + j) & 0xFF); // combine the blocks characters.
            }
            checksum = (checksum + blockValue) & ((1L << bits) - 1); // add to checksum and apply bitmask.
        }

        return checksum;
    }


	public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Usage: java ChecksumCalculator <file name> <checksum size>");
            return;
        }

        checkSumFileName = args[0];
        checksumSize = Integer.parseInt(args[1]);
        if (checksumSize != 8 && checksumSize != 16 && checksumSize != 32) {
            System.err.println("Valid checksum sizes are 8, 16, or 32");
            return;
        }
        
        try {
        	//System.out.println("here 1");
        	readFileContent(checkSumFileName);
          //  System.out.println("here 1");
            echoInputText(fileContent);
            long checksum = calculateChecksum(fileContent, checksumSize);
            System.out.printf("%2d bit checksum is %8x for all %4d chars\n",
                    checksumSize, checksum, finalSize);
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
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