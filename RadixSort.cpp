#include <iostream>
#include <fstream>
using namespace std;

class Node{
	friend class Stack;
	friend class Queue;
	
	private:
		string data;
		Node *next;
		
	public:	
		Node(string num){
			data = num;
			next = NULL;
		}
		
		~Node(){
			delete next;
		}
};

class Stack{
	private:
		Node *top;
		
	public:
		Stack(){
			top = NULL;
		}
		
		~Stack(){
			Node *temp = top;
			while(temp != NULL){
				Node *nextNode = temp->next;
				temp = NULL;
				delete temp;
				temp = nextNode;
			}
		}
		
		void Push(string num){
			Node *temp = new Node(num);
			temp->next = top;
			top = temp;
		}
		
		string Pop(){
			Node *temp = top;
			string result = temp->data;
			top = top->next;
			return result;
		}
		
        bool isEmpty(){
			return (top == NULL);
		} 	

		void printStack(ostream& outputFile){
			Node *temp = top;
			outputFile<<"listHead ";
			while(temp != NULL){
	          	if(temp->next == NULL) outputFile << " --> " << "(" << temp->data << "," << -1 << ")";
	          	else outputFile << " --> " << "("  << temp->data << "," << temp->next->data << ")";
				temp = temp->next;
			}
			outputFile<<"\n\n";
		}
};

class Queue{
	friend class hashTable;
	
	private:
	    Node* head;
		Node* tail;
		
	public:
		Queue(){
			head = new Node("-9999");
			tail = head;
		}
		
		~Queue(){
			Node *temp = head;
			while(temp != NULL){
				Node *nextNode = temp->next;
				temp = NULL;
				delete temp;
				temp = nextNode;
			}
		}
		
	void addTail(string num){
		Node *temp = new Node(num);
		tail->next = temp;
		tail = temp;
	}
	
	string deleteHead(){
	    	Node *temp = head->next;
		    string result = temp->data;
		    head->next = head->next->next;
		    if(head->next == NULL) tail = head;
		    return result;
	}
	
	bool isEmpty(){
		return (head->next == NULL);
	}
	
	void printQueue(ostream& outputFile){
		Node *temp = head;
		outputFile<<"listHead ";
		while(temp != NULL){
			if(temp->next == NULL) outputFile << " --> " << "(" << temp->data << "," << -1 << ")";
	        else outputFile << " --> " << "("  << temp->data << "," << temp->next->data << ")";
			temp = temp->next;
		}
		outputFile<<"\n"<<"\n";
	}
};

struct hashNode{
	Node *head;
	Node *tail;
};

class hashTable{
	friend class RadixSort;
	
	private:
		int size;
		Queue *q;
		
	public:
		
		hashTable(){
			size = 10;
			q = new Queue[size];
		}
		
		~hashTable(){
			delete[] q;
		}
		
		void printTable(ostream& outputFile){
			for(int i=0; i<10; i++){
				outputFile<<"Queue "<<"["<<i<<"]: ";
				q[i].printQueue(outputFile);
			}
		}
};

class RadixSort{
	private:
		int currentTable;
		int currentDigit;
		int previousTable;
		int totalDigits;
		int currentQueue;
		Stack s;
		string maxNum;
		ifstream inputFile;
		ofstream outputFile;
		string file1, file2;
		hashTable HT[2];
		
	public:
		RadixSort(string f1, string f2){
			maxNum = "0";
			file1 = f1;
			file2 = f2;
		}
		
		int hashFunction(int digit){
			return digit;
		}
		
		void storeDataToStack(){
			inputFile.open(file1.c_str());
			outputFile.open(file2.c_str());
			outputFile<<"Print Stcak: "<<"\n";
			string temp;
			//get data item from input file as string
			while(inputFile>>temp){
				//find the max number
				if(temp.length() == maxNum.length()) {
					    if(temp.compare(maxNum) > 0) maxNum = temp;
			    }
			    else if(temp.length() > maxNum.length()) maxNum = temp;
				s.Push(temp);
			}
			s.printStack(outputFile);
			inputFile.close();
			outputFile.close();
		}
		
		void determineNumOfDigit(){
			totalDigits = maxNum.length();//get the length of max number
			currentDigit = 0;//find the first digit's position which we will sort
			currentTable = 0;
		}
		
		void popStackToHashTable(){
			while(!s.isEmpty()){
			    string result = s.Pop();			
			    string temp = result;
			    if(temp.length() < totalDigits){
			    	int count = totalDigits - temp.length();
			        for(int i=0; i<count; i++) temp = "0" + temp;//if the string length is less than totalDigits, than we fill 0 to it to get max length
			    }
			    int digit = temp[totalDigits-currentDigit-1] -'0';//get the digit which we want to sort
			    int index = hashFunction(digit);//get the index of a queue in the array which we will insert next node into it
                HT[currentTable].q[index].addTail(result);//insert the node by calling addTail
		    }
		    outputFile.open(file2.c_str(), std::ios::in | std::ios::out | std::ios::ate);
		    outputFile<<"\n"<<"Print currentTable: "<<"\n";
		    HT[currentTable].printTable(outputFile);
		    outputFile.close();
		    currentDigit++;
		    currentTable = 1;
		    previousTable = 0;
		    currentQueue = 0;
		}
		
		void dateSort(){
			outputFile.open(file2.c_str(), std::ios::in | std::ios::out | std::ios::ate);
			while(currentDigit < totalDigits){
				outputFile<<"Print proviousTable: "<<endl;
			    HT[previousTable].printTable(outputFile);
			    while(currentQueue < 10){
			    	while(!HT[previousTable].q[currentQueue].isEmpty()){
			    		string result = HT[previousTable].q[currentQueue].deleteHead();
			    	    string temp = result;
			    	    if(temp.length() < totalDigits){
			    	    	int count = totalDigits - temp.length();
			    	        for(int i=0; i<count; i++) temp = "0" + temp;//if the string length is less than totalDigits, than we fill 0 to it to get max length
			    	    }
			    	    int digit = temp[totalDigits-currentDigit-1] -'0';//get the digit which we want to sort
						int index = hashFunction(digit);//get the index of a queue in the array which we will insert next node into it
			    	    HT[currentTable].q[index].addTail(result);
			    	}
			    	++currentQueue;
				}
				int temp = currentTable;
				currentTable = previousTable;
				previousTable = temp;
				currentQueue = 0;
				currentDigit++;
		    }
		    outputFile<<"Final Result: "<<endl;
		    HT[previousTable].printTable(outputFile);
		    outputFile.close();
		}	
};

int main(int argc, char* argv[]){
	if( argc < 3){
		cout << "usage : " << argv[0] << " <input file>  <output file>\n";
		return -1;
	}//check the command-line arguments
	
    RadixSort r(argv[1], argv[2]);
    r.storeDataToStack();
    r.determineNumOfDigit();
    r.popStackToHashTable();
    r.dateSort();
}
