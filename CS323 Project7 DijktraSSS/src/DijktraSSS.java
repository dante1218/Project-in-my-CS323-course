import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class DijktraSSS {
	private int N;
	private int sourceNode;
	private int minNode;
	private int newCost;
	private int currentNode;
	private int costMatrix[][];
	private int fatherArray[];
	private int markedArray[];
	private int bestCostArray[];
	private File in1, in2, out1, out2;
	
	DijktraSSS(String f1, String f2, String f3, String f4){
		in1 = new File(f1);
		in2 = new File(f2);
		out1 = new File(f3);
		out2 = new File(f4);
	}
	
	public void DijkstrasMethod(){
		try {
			Scanner scan = new Scanner(in2);
			FileWriter fw = new FileWriter(out2);
			BufferedWriter bw = new BufferedWriter(fw);
			FileWriter fw1 = new FileWriter(out1);
			BufferedWriter bw1 = new BufferedWriter(fw1);
			while(scan.hasNextInt()) {//if there are N (N equals from 1 to number of nodes) source nodes in input-2 file, then the program will run N times to find result of each source node
				sourceNode = scan.nextInt();
				initialize(bw);//initialize all arrays and other needed variables
				while(true){
				    if(markedArray[sourceNode] == 0){//if the source node doesn't mark yet, then we set the source node be the minNode
				    	minNode = sourceNode;
					    bestCostArray[minNode] = 0;
					    updateMarkedArray(minNode);
					    expendingNode();
					    debugPrint(bw);
				    }
				    else{
					    minNode = findMinNode();
					    updateMarkedArray(minNode);
					    boolean checkMark = false;
					    for(int i=1; i<=N; i++){
				            if(markedArray[i] == 0){
						        checkMark = true;
						        break;
						    }
					    }
					    if(checkMark == true) {
					    	expendingNode();
					    	debugPrint(bw);
						}
					    else {
					    	debugPrint(bw);
					    	break;
						}
				    }
				    bw.newLine();
			    }
				bw.newLine();
				bw.newLine();
				bw.newLine();
				findNprintShortestPath(bw1);
			}
			bw.close();
			bw1.close();
			scan.close();
		 }
	     catch (IOException e) {
			    e.printStackTrace();
		 }
	}
	
	public void initialize(BufferedWriter bw){
		try{
			int num1 = 0;
			int num2 = 0;
			int num3 = 0;
			Scanner scan = new Scanner(in1);
			if(scan.hasNextInt()) N = scan.nextInt();
			
			costMatrix = new int[N+1][];
			for(int i=1; i<=N; i++) costMatrix[i] = new int[N+1];
			
			for(int i=1; i<=N; i++){
				for(int j=1; j<=N; j++){
					if(j == i) costMatrix[i][j] = 0;
					else costMatrix[i][j] = 99999;
				}
			}// Initially, costMatrix[i][i] set to zero and all others set to infinity, 99999
			
			fatherArray = new int[N+1];
			markedArray = new int[N+1];
			bestCostArray = new int[N+1];
			
			for(int i=1; i<=N; i++){
				fatherArray[i] = i;// initially set to itself, i.e., father[i] = i
				markedArray[i] = 0;// initially set to 0 (not marked)
				bestCostArray[i] = 99999;// initially set to 9999 (infinity)
			}
			
			while(scan.hasNextInt()){
				num1 = scan.nextInt();
				num2 = scan.nextInt();
				num3 = scan.nextInt();
				costMatrix[num1][num2] = num3;
			}
			scan.close();
			
			bw.write("The Cost Matrix is: ");
			bw.newLine();
			for(int i=1; i<=N; i++){
				for(int j=1; j<=N; j++){
					bw.write(costMatrix[i][j] + " ");
				}
				bw.newLine();
			}
			bw.newLine();
		} 
	    catch (IOException e) {
			e.printStackTrace();
		}
	}
		
	public int findMinNode(){
			int node = 0;
			int minCost = 999999;
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
		
	public void expendingNode(){
			for(int i=1; i<=N ;i++){
				if(markedArray[i] == 0){
					currentNode = i;
					newCost = computeCost(minNode, currentNode);
					if(newCost < bestCostArray[currentNode]){
						updateFatherArray(currentNode, minNode);
						updateBestCost (currentNode, newCost);
					}
				}
			}
		}
	
	public int computeCost(int minNode, int currentNode){
		return (bestCostArray[minNode] + costMatrix[minNode][currentNode]);
	}
	
	public void  updateMarkedArray(int minNode){
		markedArray[minNode] = 1;
	}
	
	public void updateFatherArray(int currentNode, int minNode){
	    fatherArray[currentNode] = minNode;
    }
    
	public void updateBestCost (int currentNode, int newCost){
    	bestCostArray[currentNode] = newCost;
	}
	
	void debugPrint(BufferedWriter bw){
		try {
			bw.write("The Source Node is: " + sourceNode);
			bw.newLine();
			bw.write("The Minimum Node: " + minNode);
		    bw.newLine();
			bw.write("The Best Cost Array is: ");
			for(int i=1; i<=N; i++) bw.write(bestCostArray[i] + " ");
			bw.newLine();
			bw.write("The Marked Array is: ");
			for(int i=1; i<=N; i++) bw.write(markedArray[i] + " ");
			bw.newLine();
			bw.write("The Father Array is: ");
			for(int i=1; i<=N; i++) bw.write(fatherArray[i] + " ");
			bw.newLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	void findNprintShortestPath(BufferedWriter bw){
		try {
			bw.write("The graph has " + N + " nodes, the source node is " + sourceNode);
			bw.newLine();
			for(int i=1; i<=N; i++){
				String output = "";
				bw.write("The path from " + sourceNode + " to " + i + " : " + sourceNode + "-->"); //+ i + ": cost = " + bestCostArray[i]);
				int temp = i;
				if(temp == fatherArray[temp]) bw.write(+ i + ": cost = " + bestCostArray[i]);
				else {
					while(sourceNode != fatherArray[temp]){
					    temp = fatherArray[temp];
					    output = temp + "-->" + output;
				    }     
				    bw.write(output + i + ": cost = " + bestCostArray[i]);
				}
				bw.newLine();
			}
			bw.newLine();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
