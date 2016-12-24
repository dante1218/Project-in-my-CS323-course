#include <iostream>
#include <fstream>
using namespace std;

class DijktraSSS{
	private:
		int N;
		int sourceNode;
		int minNode;
		int newCost;
		int** costMatrix;
		int* fatherArray;
		int* markedArray;
		int* bestCostArray;
		ifstream in;
		ofstream out;
		string in1, in2, out1, out2;
		
	public:
		DijktraSSS(string f1, string f2, string f3, string f4){
			in1 = f1;
			in2 = f2;
			out1 = f3;
			out2 = f4;
		}
		
		~DijktraSSS(){
			delete[] fatherArray;
			delete[] markedArray;
			delete[] bestCostArray;
			for(int i=1; i<=N; i++) delete[] costMatrix[i];
			delete[] costMatrix;
		}
		
		void initialize(){
			in.open(in1);
			int num1, num2, num3;
			if(in>>num1) N = num1;
			
			costMatrix = new int*[N+1];
			for(int i=1; i<=N; i++) costMatrix[i] = new int[N+1];
			
			for(int i=1; i<=N; i++){
				for(int j=1; j<=N; j++){
					if(j == i) costMatrix[i][j] = 0;
					else costMatrix[i][j] = 99999;
				}
			}
			
			fatherArray = new int[N+1];
			markedArray = new int[N+1];
			bestCostArray = new int[N+1];
			
			for(int i=1; i<=N; i++){
				fatherArray[i] = i;
				markedArray[i] = 0;
				bestCostArray[i] = 9999;
			}
			
			//readFile
			while(in>>num1 && in>>num2 && in>>num3){
				costMatrix[num1][num2] = num3;
			}
			in.close();
			
			//sourceNode
			in.open(in2);
			if(in>>num1) sourceNode = num1;
			in.close();
			
			out.open(out2.c_str());
			out<<"The costMatrix:"<<endl;
			for(int i=1; i<=N; i++){
				for(int j=1; j<=N; j++){
					out<<costMatrix[i][j]<<" ";
				}
				out<<endl;
			}
			out<<endl<<endl;
			out.close();	
		}
		
		void DijkstrasMethod(){
			out.open(out2.c_str(), std::ios::in | std::ios::out | std::ios::ate);
			while(true){
			    if(markedArray[sourceNode] == 0){
			    	minNode = sourceNode;
				    bestCostArray[minNode] = 0;
				    updateMarkedArray(minNode);
				    out<<"Minimum Node: "<<minNode<<endl;
				    expendingNode();
				    debugPrint(out);
			    }
			    else{
				    minNode = findMinNode();
				    updateMarkedArray(minNode);
				    out<<"Minimum Node: "<<minNode<<endl;
				    bool checkMark = false;
				    for(int i=1; i<=N; i++){
			            if(markedArray[i] == 0){
					        checkMark = true;
					        break;
					    }
				    }
				    if(checkMark == true) {
				    	expendingNode();
				    	debugPrint(out);
					}
				    else {
				    	debugPrint(out);
				    	break;
					}
			    }
			    out<<endl;
		    }
		    out.close();
	    }
		
		int findMinNode(){
			int node;
			int minCost = 99999;
			for(int i=1; i<=N; i++){
				if(markedArray[i] == 0){
					if(bestCostArray[i] < minCost){
						minCost = bestCostArray[i];
						node = i;
					}
				}
			}
			return node;
		}
		
		void expendingNode(){
			for(int i=1; i<=N ;i++){
				if(markedArray[i] == 0){
					int currentNode = i;
					int newCost = computeCost(minNode, currentNode);
					if(newCost < bestCostArray[currentNode]){
						updateFatherArray(currentNode, minNode);
						updateBestCost (currentNode, newCost);
					}
				}
			}
		}
		
		int computeCost(int minNode, int currentNode){
			return (bestCostArray[minNode] + costMatrix[minNode][currentNode]);
		}
		
		void  updateMarkedArray(int minNode){
			markedArray[minNode] = 1;
		}
		
		void updateFatherArray(int currentNode, int minNode){
		    fatherArray[currentNode] = minNode;
	    }
	    
	    void updateBestCost (int currentNode, int newCost){
	    	bestCostArray[currentNode] = newCost;
		}
		
		void debugPrint(ostream & out){
			out<<"bestCostArray: "<<endl;
			for(int i=1; i<=N; i++) out<<bestCostArray[i]<<" ";
			out<<endl;
			out<<"markedArray: "<<endl;
			for(int i=1; i<=N; i++) out<<markedArray[i]<<" ";
			out<<endl;
			out<<"fatherArray: "<<endl;
			for(int i=1; i<=N; i++) out<<fatherArray[i]<<" ";
			out<<endl;
		}
		
		void printFinalResult(){
			out.open(out1.c_str());
			out<<"The graph has "<<N<<" nodes, the source node is "<<sourceNode<<endl;
			for(int i=1; i<=N; i++){
				out<<"The path from "<<sourceNode<<" to "<<i<<": "<<sourceNode<<"-->"<<i<<": cost = "<<bestCostArray[i]<<endl;
			}
			out.close();
		}
};

int main(int argc, char* argv[]){
	if(argc < 4){
		cout << "usage : " << argv[0] << " <input file>  <output file>\n";
		return -1;
	}//check the command-line arguments
	
	string in1, in2, out1, out2;
	in1 = argv[1];
	in2 = argv[2];
	out1 = argv[3];
	out2 = argv[4];
	
	DijktraSSS d(in1, in2, out1, out2);
	d.initialize();
	d.DijkstrasMethod();
	d.printFinalResult();
}
