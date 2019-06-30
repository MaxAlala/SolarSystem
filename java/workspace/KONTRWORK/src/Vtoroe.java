import java.util.Arrays;
import java.util.Scanner;

public class Vtoroe {
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int [] array = new int[n];
		boolean flag = true;

		double b = 1;
		double c = 1;
		int i_fact=1;
		int descr = 0; 
		for(int i = 0; i< n; i++) 
			array[i] = (int)(Math.random()*10);
		System.out.println(Arrays.toString(array));


		for(int i = 1; i< array.length; i++) {

			b = degree(i) + factA(i);
			c = factA(array[i]);



		}




	}
	public static int degree(int x ) {
		int degre = 1;
		for(int i = 0; i < x; i++) {
			degre = 2*2;


		}
		return degre;


	}

	public static int factA(int x) {
		int fact = 1;
		for(int i = 2; i<=x; i++ ) {
			fact = fact*i;
		}
		return fact;


	}

}
