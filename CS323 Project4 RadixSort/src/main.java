
public class main {
	public static void main(String[] args){
		if(args.length < 2)
	    {
	        System.out.println("Invalid number of arguments.");
	        System.exit(1);
	    }//check command line
		
		RadixSort r = new RadixSort(args[0], args[1]);
		r.storeDataToStack();
		r.determineNumOfDigit();
		r.popStackToHashTable();
		r.dataSort();
	}
}
