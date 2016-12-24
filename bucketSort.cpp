#include <iostream>
#include <fstream>
using namespace std;

class bucketSort{
	private:
		int *heap;
		int maxSize = -999;
		ifstream inputFile;
		ofstream outputFile;
	public:
		bucketSort (string file){
			inputFile.open(file.c_str());
			int num;
			while (inputFile>>num){
				if(maxSize < num) maxSize = num;
			}
			heap = new int[maxSize];
			cout<<maxSize+1;
			for(int i=0; i<maxSize+1; i++) heap[i] = 0;
			inputFile.close(); 
		}
		
		~bucketSort (){
			delete[] heap;
		}
		
		void heapID(string file){
			inputFile.open(file.c_str());
			int num;
			while(inputFile >> num){
				int index = num;
				heap[index]++;
			}
			inputFile.close();
		}
		
		void heapPrint(string file){
			outputFile.open(file.c_str());
			for(int i=0; i<maxSize+1; i++){
				while(heap[i] != 0) {
				    outputFile<<i<<" ";
				    heap[i] = heap[i]-1;
				    cout<<heap[i]<<" ";
			    }
			}
		}
};

int main(int argc, char* argv[]){
	if( argc < 3){
		cout << "usage : " << argv[0] << " <input file>  <output file>\n";
		return -1;
	}//check the command-line arguments
	
	bucketSort h(argv[1]);
	h.heapID(argv[1]);
	h.heapPrint(argv[2]);

	return 0;
}

