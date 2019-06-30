import java.util.Scanner;

public class Tretee {
public static void main(String args[]) {
	Scanner sc = new Scanner(System.in);
	int m = sc.nextInt();
	int n = sc.nextInt();
	int[][] array = new int [m][n];
	 zapolnimArray(array);
		int[][] array2 = new int [m][n];
		 zapolnimArray(array2);

	
	
}

public static void zapolnimArray(int[][] x) {
	 for (int i=0;i < x.length;i++) {
         for (int j=0;j < x[i].length;j++) {
        	 
        	 x[i][j]= (int)(Math.random()*10);
         }		 
   }
}
}
