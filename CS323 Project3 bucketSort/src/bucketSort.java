import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;


public class bucketSort {
	
	private int[] hashTable;
	private int maxBucket = -1;
	private File f1, f2;
	
	bucketSort(String file1, String file2){
		try {
		    f1 = new File(file1);
		    f2 = new File(file2);
		    Scanner s;
			s = new Scanner(f1);
			while(s.hasNextInt()){
				int temp = s.nextInt();
				maxBucket = findMax(maxBucket, temp);
			}
			s.close();
			maxBucket = maxBucket + 1;
			hashTable = new int[maxBucket];
			for(int i=0; i<maxBucket; i++) hashTable[i] = 0;
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	public int findMax(int num1, int num2){
		if(num1 > num2) return num1;
		else return num2;
	}

	public void readDataAndSort(){
		try{
		    Scanner s = new Scanner(f1);
		    while(s.hasNextInt()){
				int temp = s.nextInt();
				int index = hashForBucketSort(temp);
				hashTable[index]++;
			}
		    s.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
	
	public void print(){
		FileWriter fw;
		try {
			fw = new FileWriter(f2);
			BufferedWriter bw = new BufferedWriter(fw);
			for(int i=0; i<maxBucket; i++) {
				while(hashTable[i] != 0){
					bw.write(i + " ");
					hashTable[i]--;
				}	
			}
			bw.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	public int hashForBucketSort(int data){
		return data;
	}
}
