package Fibonacci;

import java.util.Scanner;
public class LastDigitOfFibonacci {

    //    private static int[] fiboElem;
    static Scanner sc = new Scanner(System.in);
    public LastDigitOfFibonacci() {
    }

    // метод высчитывает ряд фибоначчи и заносит его в массив
    public void calcFibo(int n) {
        int fiboElem1 = 0; // первый элемент 0 а не 1
        int fiboElem2 = 1;
        int current = 0;
        for (int i = 2; i <= n; i++) {
            current = (fiboElem1 + fiboElem2) % 10 ;
            fiboElem1 = fiboElem2 %10 ;
            fiboElem2 = current;
        }
        System.out.println(current);
    }

    // метод выводит ряд фибоначчи на экран
    public void showAllFibo(int n) {
        for (int i = 0; i <= n; i++) {
//            System.out.println(fiboElem[i]);
        }
    }

    public static void main(String[] args) {

        int n = Integer.parseInt(sc.nextLine());
//        fiboElem =  new int[n+1];
        LastDigitOfFibonacci fibonacci = new LastDigitOfFibonacci();
        fibonacci.calcFibo(n);
    }
}