package Nod;

import java.util.Scanner;

class Main {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int a;
        int b;
            a = in.nextInt();
            b = in.nextInt();
        System.out.print(gcd(a, b));
    }
    public static int gcd(int a, int b) {
        if (a == 0) {
            return b;
        } else if (b == 0) {
            return a;
        }
        
        if (a >= b) {
            return gcd(a % b, b);
        } else if (a <= b) {
            return gcd(a, b % a);
        }
        return 0;
    }
}