
public class main {
	public static void main(String args[]) {
		if(args.length < 2)
	    {
	        System.out.println("Invalid number of arguments.");
	        System.exit(1);
	    }//check command line
		
		System.out.println("args[0] : " + args[0]);
		System.out.println("args[1] : " + args[1]);
		
		
		bucketSort b = new bucketSort(args[0], args[1]);
		b.readDataAndSort();
		b.print();
	}

}
