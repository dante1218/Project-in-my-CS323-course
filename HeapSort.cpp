#include <iostream>
#include <fstream>
using namespace std;

class HeapSort{
	private:
		int *array;
		int arraySize;
		int currentSize;
		ifstream inputFile;
		ofstream outputFile;
	public:
		HeapSort(string file);
		
		~HeapSort();
		
		void buildHeap(string file1, string file2);
		
		void insertOneDataItem(int num);
		
		void bubbleUp(int currentIndex);
		
		void deleteHeap();
		
		void deleteRoot();
		
		void bubbleDown();
		
		bool isHeapEmpty();
		
		bool isHeapFull();
		
		void PrintHeap();
};

HeapSort::HeapSort (string file){
	inputFile.open(file.c_str());
	int num;
	int count = 0;
	while(inputFile>>num) ++count;//read and count the number of date item in the  input file
	inputFile.close();//close the file	
	
	arraySize = count+1;
	array = new int[arraySize];
	array[0] = 0;
	currentSize = 1;
}

HeapSort::~HeapSort(){
	delete[] array;
}

void HeapSort::buildHeap(string file1, string file2){
	int num;
	inputFile.open(file1.c_str());
	outputFile.open(file2.c_str());//because we need output the heap to output file for checking, so we need to open output file in here
	outputFile<<"Bulid Heap: "<<endl;
	while(inputFile>>num) {//data <-- get a data item from the input file
	    ++currentSize;
	    outputFile<<"insert "<<num<<"     ";
	    insertOneDataItem(num);//call insertOneDataItem 
        PrintHeap();//printHeap for checking
    }
    outputFile<<"Final Heap :"<<endl;
    for(int i = 1; i<arraySize; i++ ) outputFile<<array[i]<<" ";
    outputFile<<endl<<endl;
    inputFile.close();// close the input file
}

void HeapSort::insertOneDataItem(int num){
	int currentIndex;
	if(!isHeapFull()) {
	    array[0] = array[0] + 1;
	    currentIndex = array[0];
	    array[currentIndex] = num;
	    bubbleUp(currentIndex);//call bubbleUp
    }
}

void HeapSort::bubbleUp(int currentIndex){
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

void HeapSort::deleteHeap(){
    for(int i = 1; i<arraySize; i++){
		--currentSize;
	    deleteRoot();//call deleteRoot 
        PrintHeap(); //printHeap for checking
    }
    outputFile<<endl<<endl<<"Final Heap: ";
    for(int i=1; i<currentSize; i++) outputFile<<array[i]<<" ";
	outputFile.close();//close the output file
}

void HeapSort::deleteRoot(){	
	if(!isHeapEmpty()){
	    int result = array[1];
	    array[1] = array[array[0]];
	    array[0] = array[0] - 1;
        outputFile<<"delete "<< result<<"     ";
	    bubbleDown();
    }
}

void HeapSort::bubbleDown(){
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

void HeapSort::PrintHeap(){
	if(array[0] == 0) return;
	if(currentSize<=10){
		    //outputFile<<"Elements in the heap: ";
	        for(int i = 1; i<currentSize; i++) outputFile<<array[i]<<" ";
	        outputFile<<endl;
        }
        else {
        	//outputFile<<"Elements in the heap: ";
    	    for(int i = 1; i<=10; i++) outputFile<<array[i]<<" ";
	        outputFile<<endl;
       }
    outputFile<<endl;
}

bool HeapSort::isHeapEmpty(){
	if(array[0] == 0) return true;
	return false;
}

bool HeapSort::isHeapFull(){
	if(array[0] == arraySize) return true;
	return false;
}

int main(int argc, char* argv[]){
	if( argc < 3){
		cout << "usage : " << argv[0] << " <input file>  <output file>\n";
		return -1;
	}//check the command-line arguments
	
	HeapSort h(argv[1]);
	h.buildHeap(argv[1], argv[2]);
	h.deleteHeap();
	return 0;
}
