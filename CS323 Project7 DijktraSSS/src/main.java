
public class main {
	public static void main(String[] args){
		if(args.length < 2)
	    {
	        System.out.println("Invalid number of arguments.");
	        System.exit(1);
	    }//check command line
		
		String in1, in2, out1, out2;
		in1 = args[0];
		in2 = args[1];//if there are N (N equals from 1 to number of nodes) source nodes in the input-2 file, then the program will run N times to print results for each source node 
		out1 = args[2];
		out2 = args[3];
		
		DijktraSSS d = new DijktraSSS(in1, in2, out1, out2);
		d.DijkstrasMethod();
	}
		
}
