import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;


public class Stack {
	private Node top;

	public Stack(){
		top = null;
	}
	
	public void push(String num){
		Node n = new Node(num);
		n.next = top;
		top = n;
	}
	
	public String pop(){
		Node temp = top;
		String result = top.data;
		top = top.next;
		temp.next = null;
		return result;
	}
	
	public boolean isEmpty(){
		return (top == null);
	}
	
	public void printStack(File f){
		try {
			FileWriter fw = new FileWriter(f, true);
			BufferedWriter bw = new BufferedWriter(fw);
			Node temp = top;
			String result = "listHead ";
			while(temp != null){
				if(temp.next == null) result = result + " --> " + "(" + temp.data + "," + -1 +")";
				else result = result + " --> " + "(" + temp.data + "," + temp.next.data + ")";
				temp = temp.next;
		    }
			bw.write(result);
			bw.newLine();
			bw.newLine();
			bw.close();
		}
			catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	
}
