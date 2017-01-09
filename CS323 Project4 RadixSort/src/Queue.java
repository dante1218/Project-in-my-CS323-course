import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;


public class Queue {
	private Node head;
	
	private Node tail;
	
	public Queue(){
		head = new Node("-9999");
		tail = head;
	}
	
	public void addTail(String num){
		Node n = new Node(num);
		tail.next = n;
		tail = n;
	}
	
	public String deleteHead(){
		Node temp = head.next;
		String result = temp.data;
		head.next = head.next.next;
		if(head.next == null) tail = head;
		temp.next = null;
		return result;
	}
	
	public boolean isEmpty(){
		return (head.next == null);
	}

	public void printQueue(File f){
		try {
			FileWriter fw = new FileWriter(f, true);
			BufferedWriter bw = new BufferedWriter(fw);
			Node temp = head;
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
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
