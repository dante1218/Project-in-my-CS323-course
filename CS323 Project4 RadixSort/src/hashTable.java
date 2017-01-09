import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;


public class hashTable {
	private int size = 10;
	protected Queue[] q;
	
	public hashTable(){
		q = new Queue[size];
		for(int i=0; i<10; i++){
			q[i] = new Queue();
		}
	}
	
	public void printTable(File f){
		try {
			for(int i=0; i<10; i++) {
				FileWriter fw = new FileWriter(f, true);
				BufferedWriter bw = new BufferedWriter(fw);
				bw.write("Queue " + "[" + i + "] ");
				bw.close();
				q[i].printQueue(f);
			}
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

}
