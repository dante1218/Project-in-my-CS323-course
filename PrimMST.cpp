#include <iostream>
#include <fstream>
using namespace std;

class graphNode{
	friend class linkListForGraphNode;
	friend class PrimMST;
	
	private:
	    int nodeID;
	    graphNode* next;
	
	public: 
	    graphNode(int id){
	    	nodeID = id;
	    	next = NULL;
		}
		
		~graphNode(){
			delete next;
		}
		
		void insertion(int id, graphNode* head){
			graphNode* temp = new graphNode(id);
			temp->next = head->next;
			head->next = temp;
		}
		
		void deletion(int id, graphNode* head){
			graphNode *temp = head->next;
			graphNode *pre = head;
			
			while(temp != NULL){
				if(temp->nodeID == id){
					pre->next = temp->next;
					temp->next = NULL;
					break;
				}
				pre = pre->next;
				temp = temp->next;
			}
		}
		
		void printGraphNode(ostream & out, graphNode* head){
	    	graphNode *temp = head->next;
			while(temp != NULL){
	    	    out<<temp->nodeID<<" ";
	    	    temp = temp->next;
			}
			out<<endl;
		}
};

class edgeNode{
	friend class linkListForEdgeNode;
	friend class PrimMST;
	
	private:
		int Ni;
		int Nj;
		int edgeCost;
	    edgeNode* next;
	
	public:
		edgeNode(int i, int j, int cost){
			Ni = i;
			Nj = j;
			edgeCost = cost;
			next = NULL;
		}
		
	    ~edgeNode(){
		    delete next;
	    }
	    
	    void insertionSort(int ni, int nj, int cost, edgeNode* head){
	    	edgeNode *temp = new edgeNode(ni, nj, cost);
	    	edgeNode *spot = head;
			
			while(spot->next != NULL && spot->next->edgeCost < temp->edgeCost){
    	        spot = spot->next;
	        }
	        temp->next = spot->next;
            spot->next = temp;
		}
		
		void insertFront(int ni, int nj, int cost, edgeNode* head){
			edgeNode *temp = new edgeNode(ni, nj, cost);
			temp->next = head->next;
			head->next = temp;
		}//insert in the front
		
		void deletion(edgeNode* temp, edgeNode* previous){
			previous->next = temp->next;
			temp->next = NULL;
		}
	    
	    void printEdgeNodeOfEdgeList(ostream & out, edgeNode* head){
	    	edgeNode *temp = head->next;
			int count = 0;
			while(temp != NULL && count != 10){
	    	    out<<temp->Ni<<" "<<temp->Nj<<" "<<temp->edgeCost<<" "<<endl;
	    	    temp = temp->next;
				count++;
			}
			out<<endl<<endl;
		}
		
		 void printEdgeNodeOfMST(ostream & out, edgeNode* head){
	    	edgeNode *temp = head->next;
			while(temp != NULL){
	    	    out<<temp->Ni<<" "<<temp->Nj<<" "<<temp->edgeCost<<" "<<endl;
	    	    temp = temp->next;
			}
			out<<endl<<endl;
		}	
};

class PrimMST{
	private:
		int N;
		int totalCost;
		int* graphNodeIDarray;
        edgeNode* edgeList;
        graphNode* setA;
        graphNode* setB;
        edgeNode* MSTofG;
		ifstream in;
		ofstream out;
		string in1, out1, out2;
		
	public:
		PrimMST(string f1, string f2, string f3){
			in1 = f1;
			out1 = f2;
			out2 = f3;
		}
		
		~PrimMST(){
			delete[] graphNodeIDarray;
		}
		
		void initialize(){
			edgeList = new edgeNode(-9999, -9999, 0);
			setA = new graphNode(-9999);
			setB = new graphNode(-9999);
			MSTofG = new edgeNode(-9999, -9999, 0);
			totalCost = 0;
			
			in.open(in1.c_str());
			int num1, num2, num3;
			
			if(in>>num1) N = num1;
			
			graphNodeIDarray = new int[N+1];
			for(int i=1; i<=N; i++) graphNodeIDarray[i] = 0;
			
			while(in>>num1&&in>>num2&&in>>num3){
				edgeList->insertionSort(num1, num2, num3, edgeList);
				graphNodeIDarray[num1]++;
				graphNodeIDarray[num2]++;
			}
			in.close();
			
			out.open(out2.c_str());
			out<<"Print edge list (only the fist 10 edges): "<<endl;
			edgeList->printEdgeNodeOfEdgeList(out, edgeList);
			out<<"Print Array: "<<endl;
			for(int i=1; i<=N; i++) out<<graphNodeIDarray[i]<<" ";
			out<<endl<<endl;
			out.close();
		}
		
		void inertToSetA(){
			int k;
			for(int i=1; i<=N; i++)
	            if(graphNodeIDarray[i] != 0){
	            	k=i;
	            	break;
				} 
			setA->insertion(k, setA);//insert newGraphNode into SetA 
		}
		
		void insertToSetB(){
			int k;
			for(int i=2; i<=N; i++){
				k = i;
				setB->insertion(k, setB);//insert newGraphNode in the front of setB
			}
		}
		
		void findMSG(){
			out.open(out2.c_str(), std::ios::in | std::ios::out | std::ios::ate);
			while(setB->next != NULL){
				findNewEdge(out);
			}
			out.close();
		}
		
		void findNewEdge(ostream & out){
			edgeNode *temp = edgeList->next;
			edgeNode* previous = edgeList;
			bool test1 = false;
			bool test2 = false;
			edgeNode *newEdge;
			
			while(temp != NULL){
				graphNode* a = setA->next;
				graphNode* b = setB->next;
				while(a != NULL){
					if(temp->Ni == a->nodeID){
						while(b != NULL){
							if(temp->Nj == b->nodeID) {
								test1 =true;
								deleteAndInsert(temp->Ni, temp->Nj, temp->edgeCost, temp, previous);
							}
							if(test1 == true) break;
							b = b->next;
						}
					}
					if(test1 == true) break;
					a = a->next;
				}
				if(test1 == true) break;
				
				a = setA->next;
				b = setB->next;
				while(a != NULL){
					if(temp->Nj == a->nodeID){
						while(b != NULL){
							if(temp->Ni == b->nodeID) {
								test2 =true;
								deleteAndInsert(temp->Nj, temp->Ni, temp->edgeCost, temp, previous);
							}
							if(test2 == true) break;
							b = b->next;
						}
					}
					if(test2 == true) break;
					a = a->next;
				}
				if(test2 == true) break;
				temp = temp->next;
				previous = previous->next;
			}				
		    debugPrint(out);
		}
		
		void deleteAndInsert(int i, int j, int k, edgeNode* temp, edgeNode* previous){
			edgeList->deletion(temp, previous);
			MSTofG->insertFront(i, j, k, MSTofG);
			setA->insertion(j, setA);
			setB->deletion(j, setB);
			totalCost = totalCost + k;
		}
		
		void debugPrint(ostream & out){
			out<<"setA: "<<endl;
			setA->printGraphNode(out, setA);
			out<<"setB: "<<endl;
			setB->printGraphNode(out, setB);
			out<<"MST of the Graph: "<<endl;
			MSTofG->printEdgeNodeOfMST(out, MSTofG);
		}
		
		void printFinalResult(){
			out.open(out1.c_str());
			out<<"Final Result: "<<endl;
			out<<N<<endl;
		    MSTofG->printEdgeNodeOfMST(out, MSTofG);
			out<<"Total Cost is: "<<totalCost;
		}		
};

int main(int argc, char* argv[]){
	if(argc < 4){
		cout << "usage : " << argv[0] << " <input file>  <output file>\n";
		return -1;
	}//check the command-line arguments
	
	string in1, out1, out2;
	in1 = argv[1];
	out1 = argv[2];
	out2 = argv[3];
	
	PrimMST p(in1, out1, out2);
	p.initialize();
	p.inertToSetA();
	p.insertToSetB();
	p.findMSG();
	p.printFinalResult();		
}
