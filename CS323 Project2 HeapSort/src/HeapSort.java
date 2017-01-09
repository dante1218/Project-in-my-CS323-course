import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class HeapSort {
	
	private int[] array;
	private int arraySize;
	private int currentSize;
	private File f1, f2;
	
	public HeapSort(String file1, String file2){
		try {
		    int count = 0;
	        f1 = new File(file1);//input file
	        f2 = new File(file2);//output file
	        Scanner s = new Scanner(f1);//open the input file 
			while(s.hasNextInt()) {
				s.nextInt();
				count++;
				//System.out.print(count);
			}
			s.close();//close input file
			
			arraySize = count+1;
			array = new int[arraySize];//dynamically allocate a 1-D array of the size count+1
			array[0] = 0;
			currentSize = 1;
		} 
		catch (IOException e) {
			e.printStackTrace();
		}
	}//constructor
	
	//buildHeap--------------------------------
	public void buildHeap(){
		try{
			Scanner input = new Scanner(f1);//open the input file for the second time
			FileWriter fw = new FileWriter(f2);
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write("Build Heap: ");
			bw.newLine();
			bw.close();
			int num;
			while(input.hasNextInt()){
				++currentSize;
				num = input.nextInt();//get a data item from the input file
				insertOneDataItem(num);//call insertOneDataItem 
				PrintHeap();//call printHeap for checking
			}
			input.close();//close the input file
			
			fw = new FileWriter(f2, true);
			bw = new BufferedWriter(fw);
			bw.write("Final Heap: ");
			bw.newLine();
			for(int i=1; i<currentSize; i++) bw.write(array[i] + " ");
			bw.newLine();
			bw.newLine();
			bw.close();
		}
		catch (IOException e){
			e.printStackTrace();
		}
	}
	
	public void insertOneDataItem(int num){
		int currentIndex;	
		try {
			FileWriter fw = new FileWriter(f2, true);
			BufferedWriter bw = new BufferedWriter(fw);
			if(!isHeapFull()) {//make sure the heap is not full
			    array[0] = array[0] + 1;
			    currentIndex = array[0];
			    array[currentIndex] = num;
			    bw.write("insert " + num + "     ");
			    bw.close();
			    bubbleUp(currentIndex);//call bubbleUp
		    }
			else {
				System.out.print("The Heap Is Full!");
				System.exit(1);
			}
		}
			catch (IOException e) {
			e.printStackTrace();
		}
}
	
	public void bubbleUp(int currentIndex){
		while(currentIndex != 1){
			if(array[currentIndex] < array[currentIndex/2]) {
				int temp = array[currentIndex];
				array[currentIndex] = array[currentIndex/2];
				array[currentIndex/2] = temp;
			}//swap
			else return;
			currentIndex = currentIndex/2;
		}
	}
	
	//deleteHeap-----------------------------------
	public void deleteHeap(){
		try {
			FileWriter fw = new FileWriter(f2, true);//open the output file
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write("Delete Heap:");
			bw.newLine();
			bw.close();
			for(int i = 1; i<arraySize; i++){
				--currentSize;
			    deleteRoot();//call deleteRoot 
		        PrintHeap(); //call printHeap for checking
		    } 
			fw = new FileWriter(f2, true);
			bw = new BufferedWriter(fw);
			bw.write("Final Heap: ");
			bw.newLine();
			for(int i=1; i<currentSize; i++) bw.write(array[i] + " ");
			bw.newLine();
			bw.newLine();
			bw.close();//close the output file
		}
			catch (IOException e) {
			e.printStackTrace();
		}
}
	public void deleteRoot(){
		if(!isHeapEmpty()){//make sure the heap is not empty
			try {
				FileWriter fw = new FileWriter(f2, true);
				BufferedWriter bw = new BufferedWriter(fw);
			    int result = array[1];
			    array[1] = array[array[0]];
			    array[0] = array[0] - 1;
		        bw.write("delete " + result + "     ");//print the root to the output file
		        bw.close();
			    bubbleDown();//call bubbleDown
			} catch (IOException e) {
				e.printStackTrace();
			}
	    }
		else {
			System.out.print("The Heap Is Empty!");
			System.exit(1);
		}
	}
	
	public void bubbleDown(){
		int currentIndex, minChild;
		currentIndex = 1;//the root is in array[1], so we always begin in 1
		while(currentIndex < array[0]){
			if(currentIndex*2+1 <= array[0]){
			    if(array[currentIndex*2] < array[currentIndex*2+1]) minChild = currentIndex*2;
			    else minChild = currentIndex*2+1;
		    }
		    else if(currentIndex*2 <= array[0]) minChild = currentIndex*2;
		         else return;
			if(array[currentIndex] > array[minChild]){
				int temp = array[currentIndex];
				array[currentIndex] = array[minChild];
				array[minChild] = temp;
			}//swap
			else return;
			currentIndex = minChild;
		}
	}
	
	public void PrintHeap(){
		try {
			FileWriter fw = new FileWriter(f2, true);
			BufferedWriter bw = new BufferedWriter(fw);
			if(currentSize<=10){
		        for(int i = 1; i<currentSize; i++) bw.write(array[i] + " ");
		        bw.newLine();
	        }
	        else {
	    	    for(int i = 1; i<=10; i++) bw.write(array[i] + " ");
	    	    bw.newLine();
		    }
			bw.newLine();
			bw.close();
		} 
		catch (IOException e) {
			e.printStackTrace();
		}
	}//printHeap
	
	public Boolean isHeapEmpty(){
		if(array[0] == 0) return true;
		return false;
	}
	
	public Boolean isHeapFull(){
		if(array[0] == arraySize) return true;
		return false;
	}

}
