import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;


public class RadixSort {
	private int currentTable;
	private int currentDigit;
	private int previousTable;
	private int totalDigits;
	private int currentQueue;
	private Stack s;
	private String maxNum;
	private hashTable[] HT;
	private File file1, file2;
	
	public RadixSort(String f1, String f2){
		maxNum = "0";
		s = new Stack();
		HT = new hashTable[2];
		for(int i=0; i<2; i++) HT[i] = new hashTable();
		file1 = new File(f1);
		file2 = new File(f2);
	}
	
	public int hashFunction(int digit){
		return digit;
	}

	public void storeDataToStack(){
	    try{
			String temp;
			Scanner scan = new Scanner(file1);
			while(scan.hasNextInt()){
				temp = scan.next();
				if(Integer.parseInt(temp) > Integer.parseInt(maxNum)) maxNum = temp;
				s.push(temp);
			}
			scan.close();
			FileWriter fw = new FileWriter(file2);
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write("Print Stack: ");
			bw.newLine();
			bw.close();
			s.printStack(file2);
		} 
	    catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void determineNumOfDigit(){
		totalDigits = maxNum.length();
		currentDigit = 0;
		currentTable = 0;
	}
	
	void popStackToHashTable(){
		try {
			while(!s.isEmpty()){
				String result = s.pop();
				String temp = result;
				if(temp.length() < totalDigits){
					int count = totalDigits - temp.length();
			        for(int i=0; i<count; i++) temp = "0" + temp;
			    }
				int digit = temp.charAt(totalDigits-currentDigit-1) - '0';
				int index = hashFunction(digit);
				HT[currentTable].q[index].addTail(result);
			}
			FileWriter fw = new FileWriter(file2, true);
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write("Print currentTable: ");
			bw.newLine();
			bw.close();
			HT[currentTable].printTable(file2);
			currentDigit++;
		    currentTable = 1;
		    previousTable = 0;
		    currentQueue = 0;
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public void dataSort(){
		try {
			int digit;
			int index;
			while(currentDigit < totalDigits){
				FileWriter fw = new FileWriter(file2, true);
				BufferedWriter bw = new BufferedWriter(fw);
				bw.write("Print previousTable: ");
				bw.newLine();
				bw.close();
				HT[previousTable].printTable(file2);
				while(currentQueue < 10){
			    	while(!HT[previousTable].q[currentQueue].isEmpty()){
			    		String result = HT[previousTable].q[currentQueue].deleteHead();
			    	    String temp = result;
			    	    if(temp.length() < totalDigits){
			    	    	 int count = totalDigits - temp.length();
			    	         for(int i=0; i<count; i++) temp = "0" + temp;//if the string length is less than totalDigits, than we fill 0 to it to get max length
			    	    }
			    	    digit = temp.charAt(totalDigits-currentDigit-1) -'0';
						index = hashFunction(digit);
			    	    HT[currentTable].q[index].addTail(result);
			    	}
			    	currentQueue++;
				}
				int temp = currentTable;
				currentTable = previousTable;
				previousTable = temp;
				currentQueue = 0;
				currentDigit++;
			}
			FileWriter fw = new FileWriter(file2, true);
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write("Final Result: ");
			bw.newLine();
			bw.close();
			HT[previousTable].printTable(file2);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
