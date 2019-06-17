import java.util.Arrays;
import java.util.Scanner;

public class Pervoe {
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int [] a = new int[n];
		int k=0;
		boolean flag = true;
		
		for(int i= 0; i< n; i++) {
			a[i] = (int)(Math.random()*10);
			if (a[i]%3 == 0) k++; 

		}
		System.out.println(Arrays.toString(a));
		int buf_k = 0;
	
		while(k>0) {
			if(k%2==1) ;
			else {
				flag = false;
				System.out.println("Есть четная цифра в числе, являющ. количеством чисел, делющ. на 3. false");
				break;
			}
			
			k=k/10;
		}
	if(flag==true) System.out.println("проверка прошла удачно");
	}
}

