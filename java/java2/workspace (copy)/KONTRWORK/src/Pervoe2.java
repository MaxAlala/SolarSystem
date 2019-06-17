import java.util.Arrays;
import java.util.Scanner;

public class Pervoe2 {
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		int [] array = new int[n];
		boolean flag = true;

		for(int i = 0; i< n; i++) 
			array[i] = (int)(Math.random()*10);


		for(int i = 0; i< n; i++) {

			if (array[i] % 3 == 0) {
				if((chetnie(array[i])) == false) {
					flag = false;
					System.out.println("есть четная цифра в числе, делящ. на 3, проверка не пройдена ");
					break;
				}
			}
		}
		
		System.out.println(Arrays.toString(array));
		if(flag == true) System.out.println("Проверка пройдена");
	}
	
	public static boolean chetnie(int x){
		int buf = 0;
		if(x == 0) return false;
		while(x > 0) {
			buf = x % 10;
			if (buf % 2 != 0); else
				return false;



		}
		return true;
	}
}