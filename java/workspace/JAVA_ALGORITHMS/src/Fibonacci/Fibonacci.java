package Fibonacci;

import java.util.Scanner;
public class Fibonacci {

    private static int[] fiboElem;
    static Scanner sc = new Scanner(System.in);
    public Fibonacci() {
    }

    // метод высчитывает ряд фибоначчи и заносит его в массив
    public void calcFibo(int n) {
        fiboElem[0] = 0; // первый элемент 0 а не 1
        fiboElem[1] = 1;
        for (int i = 2; i <= n; i++) {
            fiboElem[i] = fiboElem[i-1] + fiboElem[i-2];
        }
        System.out.println(fiboElem[n]);
    }

    // метод выводит ряд фибоначчи на экран
    public void showAllFibo(int n) {
        for (int i = 0; i <= n; i++) {
            System.out.println(fiboElem[i]);
        }
    }

    public static void main(String[] args) {
        int n = Integer.parseInt(sc.nextLine());
        fiboElem =  new int[n+1];
        Fibonacci fibonacci = new Fibonacci();
        fibonacci.calcFibo(n);
    }
}