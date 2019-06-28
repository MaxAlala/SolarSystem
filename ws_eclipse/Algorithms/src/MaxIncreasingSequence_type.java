import java.util.Arrays;
import java.util.Scanner;


public class MaxIncreasingSequence_type {
	    public static void main(String[] args) {
	    Scanner sc = new Scanner(System.in);
	    int n = sc.nextInt();
	    int [] A = new int[n];
	    int [] D = new int[n];
	    for(int i = 0; i < n; i++){
	        A[i] = sc.nextInt();

	    }
	    for(int i = 0; i < n; i ++){
	        D[i] = 1;
	        for(int j = 0; j < i; j++ ){
	            if(((double)(A[i] % A[j]) == 0) & (D[j]+1 > D[i]) ){
	                D[i] = D[j] + 1;
	            }
	        }
	    }
//	        System.out.println(Arrays.toString(D));
//	        System.out.println(Arrays.toString(A));
	    int max = 0;
	    for(int i = 0; i < n; i++){
	        if(max < D[i]) max = D[i];
	    }
	        System.out.println(max);
	    }
	}

