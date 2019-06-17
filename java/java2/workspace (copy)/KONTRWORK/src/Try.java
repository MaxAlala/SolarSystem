import java.util.Arrays;
import java.util.Scanner;

public class Try {
	public static void main(String args[]) {
		Scanner sc = new Scanner(System.in);
//		int n = sc.nextInt();
		int [] a = {12, 4, 3, 1};
		boolean flag = true;

		for(int i= 0; i< a.length; i++) {
//			a[i] = (int)(Math.random()*10);
			if (a[i]%3 == 0) {
				if((chetnie(a[i])) == false) {
					flag = false;
					System.out.println("есть четная цифра в числе, делящ. на 3, проверка не пройдена ");
					break;
				}
		    }
		}
		if(flag == true) System.out.println("Проверка пройдена");
	}
	
	public static boolean chetnie(int x){
		int buf = 0;
		while(x > 0) {
			buf = x % 10;
			if (buf %2 != 0); else
				return false;



		}
		return true;
	}
}