#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

class Node{
	friend class Linklist;
	friend class K_mean;
	
	private:
		int X_coordinate;
		int Y_coordinate;
		int ClusterLabel;
		double Distance;
		Node *next;
		
	public:
	    Node(int x, int y, int label){
		    X_coordinate = x;
		    Y_coordinate = y;
		    ClusterLabel = label;
		    Distance = 0;
		    next = NULL;
	    }
	    
	    ~Node(){
			delete next;
		}
	
	    void printNode(ostream & out){
	    	if(ClusterLabel == 0) out<<endl<<endl;
		    else out<<"X-coordinate: "<<X_coordinate<<" "<<" Y-coordinate: "<<Y_coordinate<<" ClusterLabel: "<<ClusterLabel<<" Distance: "<<Distance<<endl<<endl;
	}
};

class Linklist{
	friend class K_mean;
	
	private:
		Node *listHead;
		Node *tail;
		int length;
		
	public:
		Linklist(){
			listHead = new Node(-1, -1, 0);//dommy node
			tail = listHead;
			length = 0;
		}
		
		~Linklist(){
	        Node *temp = listHead;
			while(temp != NULL){
				Node *nextNode = temp->next;
				temp = NULL;
				delete temp;
				temp = nextNode;
			}
    	}
    	
    	void insertion(int x, int y, int label){
    		Node *newNode = new Node(x, y, label);
    		tail->next = newNode;
    		tail = newNode;
    		length++;
		}//insert a node to the tail
		
		void deletion(){
			Node *temp = listHead->next;
		    listHead->next = listHead->next->next;
		    if(listHead->next == NULL) tail = listHead;
		    length--;
		}
		
		bool isEmpty(){
			return (listHead->next==NULL);
		}
		
		void printList(ostream & out){
			Node *temp = listHead->next;
			while(temp != NULL){
				if(temp->ClusterLabel == 0)  out<<endl<<endl;
				else out<<temp->X_coordinate<<" "<<temp->Y_coordinate<<" "<<temp->ClusterLabel<<endl<<endl;
			    temp = temp->next;
			}
		}	
};

class K_mean{
	struct xycoord{
		int X_coordinate;
		int Y_coordinate;
	};
	
	private: 
	    int k;
	    xycoord* Kcentroids;
	    Linklist l;
	    int countForTimes;//count for how many times of clustering we did
	    int numRow;
	    int numCol;
	    int** imageArray;
	    ifstream in;
	    ofstream out;
	    string file1, file2, file3;
	    
	public:
		K_mean(string input, string output1, string output2){
			file1 = input;
			file2 = output1;
			file3 = output2;
			countForTimes = 0;
		}
		
		~K_mean(){
			delete[] Kcentroids;
			for(int i=0 ; i<numRow; i++) delete[] imageArray[i];
            delete[] imageArray;
		}
		
		void initialize(){
			in.open(file1.c_str());
			int nextNum1, nextNum2;
			int randomLabel = 1;
			if(in>>nextNum1) k = nextNum1;
			if(in>>nextNum1) numRow = nextNum1;
			if(in>>nextNum1) numCol = nextNum1;
			
			Kcentroids = new xycoord[k+1];
			
			imageArray = new int*[numRow];
			for(int i=0; i<numRow; i++) imageArray[i] = new int[numCol];
			
			for(int i=0; i<numRow; i++){
				for(int j=0 ; j<numCol ; j++){
					imageArray[i][j] = 0;
				}
			}
			
			while(in>>nextNum1 && in>>nextNum2){
				l.insertion(nextNum1, nextNum2, randomLabel);
				randomLabel++;
				if(randomLabel > k) randomLabel = 1;
			}//assign a label from 1 to k to each node in the linklist 
						
			in.close();
		}//do all things in step0 and step1
		
		void clustering(){
			bool check = true;
			int checkForOscillate[l.length];
			out.open(file2.c_str());
			
			for(int i=0; i<l.length; i++) checkForOscillate[i] = 0;
			
			while(check){
				if(countForTimes == 0) out<<"Randomly partition all points to K gropus: "<<endl<<endl<<k<<endl<<endl<<numRow<<" "<<numCol<<endl<<endl;
				else out<<countForTimes<<" times clustering: "<<endl<<endl<<k<<endl<<endl<<numRow<<" "<<numCol<<endl<<endl;
			    l.printList(out);
			    out<<endl<<endl;
			    displayImage(out);
			    out<<endl<<endl;//step2, print the link list and 2-D image to output-1
			    computeCentroids();
			    check = computeDistance(checkForOscillate);//step6, if no point is changed, then the method will return false to "check" which means clustering is finished
			    countForTimes++;
	     	}
	     	out<<"Last times clustering: "<<endl<<endl<<k<<endl<<endl<<numRow<<" "<<numCol<<endl<<endl;
	     	l.printList(out);
			out<<endl<<endl;
			displayImage(out);
			out<<endl<<endl;
			out.close();
		}//do all things from step2 to step6
		
		void computeCentroids(){
			int countLabel[k+1];
			int sumOfX[k+1];
			int sumOfY[k+1];
			for(int i=1; i<=k; i++) {
				countLabel[i] = 0;
				sumOfX[i] = 0;
				sumOfY[i] = 0;
			}
			Node *temp = l.listHead->next;
			
			while(temp != NULL){
				for(int i=1; i<=k; i++)
					if(temp->ClusterLabel == i) {
						countLabel[i]++;
						sumOfX[i] = sumOfX[i] + temp->X_coordinate;
						sumOfY[i] = sumOfY[i] + temp->Y_coordinate;
					}
				temp = temp->next;
			}
			for(int i=1; i<=k; i++){
				Kcentroids[i].X_coordinate = sumOfX[i]/countLabel[i];
				Kcentroids[i].Y_coordinate = sumOfY[i]/countLabel[i];
			}
		}//step3 compute K-Centroids
		
		bool computeDistance(int checkForOscillate[]){
			bool checkForLabelChange = false;
			Node *temp = l.listHead->next;
			int count = 0;
			
			while(temp != NULL){
				double min = 1000000.00;
				int centroidLabel;
				double distance[k+1];
				if(temp->ClusterLabel != 0){//if a point's label is 0 which means it is an oscillate, and we should not compute it anymore
				    for(int i=1; i<=k; i++){
					    distance[i] = sqrt(pow((Kcentroids[i].X_coordinate-temp->X_coordinate), 2) + pow((Kcentroids[i].Y_coordinate-temp->Y_coordinate), 2));
			    	}
				    for(int i=1; i<=k; i++){
					    if(distance[i] < min){
						    min = distance[i];//find the minimun distance
						    centroidLabel = i;//get the label of this centroid
				    	}
				    }
				    temp->Distance = min;
			    	if(temp->ClusterLabel != centroidLabel) {
			    		checkForOscillate[count]++;
					    if(checkForOscillate[count] > 4) temp->ClusterLabel = 0;//if a point changed its label more than 4 times, that means it is a oscillate, and we will delete it (set its label to be zero)
					    else {
					    	temp->ClusterLabel = centroidLabel;
					        checkForLabelChange = true;
						}
			    	}
			    }
			    count++;
				temp = temp->next;
			}
			return checkForLabelChange;
		}//step4 to step5 compute distance from every point p to each centroid, and find minimun distance. If the label is not same, then reassign a label to p
		
		void displayImage(ostream & out){
			Node *temp = l.listHead->next;
			while(temp != NULL){
				imageArray[temp->X_coordinate][temp->Y_coordinate] = temp->ClusterLabel;
				temp = temp->next;
			}
			
			out<<"The Image: "<<endl;
			for(int i=0; i<numRow; i++){
				for(int j=0 ; j<numCol ; j++){
					for(int h=1; h<=k; h++){
						int num = 1;
						char c = 'A'; 
							if(i == Kcentroids[h].X_coordinate && j == Kcentroids[h].Y_coordinate && countForTimes != 0){
								while(true){
									if(h == num) {
										out<<c;
										break;
									}
									else {
										num++;
										c = c+1;
									}
								}
								break;
							}
					}//output the central points to the 2-D array image
					if(imageArray[i][j] == 0) out<<" ";
					else out<<imageArray[i][j];
				}
				out<<endl;
			}
		}
		
		void finalResult(){
			out.open(file3.c_str());
			out<<"Final Result: "<<endl<<"K is: "<<k<<endl<<"number of row: "<<numRow<<endl<<"number of column: "<<numCol<<endl;
			Node *temp = l.listHead->next;
			while(temp != NULL){
				temp->printNode(out);
				temp = temp->next;
			}
			out<<endl<<endl;
			displayImage(out);
			out.close();
		}//step 7, output the link list and 2-D image to output-2
};

int main(int argc, char* argv[]){
	if(argc < 4){
		cout << "usage : " << argv[0] << " <input file>  <output file>\n";
		return -1;
	}//check the command-line arguments
	
	string f1, f2, f3;
	f1 = argv[1];
	f2 = argv[2];
	f3 = argv[3];
	
	K_mean k(f1, f2, f3);
	k.initialize();
	k.clustering();
	k.finalResult();
	return 0;
}
