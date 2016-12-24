#include <iostream>
#include <fstream>
using namespace std;

class Linklist{
    struct Node{
	    int data;
    	Node *next;
    };//struct of Node

    friend ostream& operator<<(ostream& output, const Linklist& list);

    public:
	    Node *first = new Node;//dommy node
	    int length;//list length
	
    public:
	    Linklist(); //constructor
	    
	    ~Linklist();//destructor
	
	    void insertion(int input);// insertion sort
	    
};// class of Linklist

Linklist::Linklist(){
	first->next = NULL;
	first->data = -9999;
	length = 0;
}//constructor: set dommy node

Linklist::~Linklist(){
	Node *current = first;
	while(current != NULL){
		Node* nextNode = current->next;
		delete current;
		current = nextNode;
	}
}//destructor: delete list

void Linklist::insertion(int input){
	Node *temp = new Node;
	temp->data = input;
	temp->next = NULL;
    Node *spot = first;
    
    while(spot->next != NULL && spot->next->data < temp->data){
    	spot = spot->next;
    	if(spot->data >= temp->data){//insertion, allow duplicate
    		temp->next = spot->next;
    		spot->next = temp;
    		length++;
    		return;
		}
	}
	temp->next = spot->next;
    spot->next = temp;
    length++;
}//method of insertion 

ostream& operator<<(ostream& output, const Linklist& list){
	Linklist::Node *temp = list.first;
	int count = 1;
	output<<"listHead";
	while(temp->next != NULL && count <= 10){
		output << " --> " << "("  << temp->data << "," << temp->next->data << ")";
		if(count < 10 && temp->next->next == NULL)	output << " --> " << "(" << temp->next->data << "," << -1 << ")";
		temp = temp->next;
		count++;
	}
	output << endl;
	return output;
}

int main(int argc, char* argv[]){
	if( argc < 3){
		cout<<" Command-line Arguments Error! ";
		return -1;
	}//check the command-line arguments
	ifstream inputFile(argv[1]);//read file from argv[1]
	ofstream outputFile(argv[2]);//we will write list to argv[2] without overwrite the file 
	if ( inputFile.peek() == std::ifstream::traits_type::eof() ){
		cout << "Error: The input file is empty!";
	    return -1;
	}//check the the inputfile.
	Linklist l;//create new Linklist
	int num;
	while(inputFile>>num) {
	    l.insertion(num);
	    outputFile<<l;//write list to argv[2]
    }
	return 0;
}//main 
