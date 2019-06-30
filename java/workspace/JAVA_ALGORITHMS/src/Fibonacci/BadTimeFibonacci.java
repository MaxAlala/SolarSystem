package Fibonacci;

public class BadTimeFibonacci {

    private int fib(int n){
        if(n < 2){
            return n;
        }
        return fib(n - 1) + fib(n - 2);
    }

    private void run(int n){
        System.out.println(n + ": " + fib(n));
    }

    public static void main(String[] args) {
        System.out.println("he");
        for(int i=0; i < 100; i ++){
            long start = System.currentTimeMillis();
            new BadTimeFibonacci().run(i);
            long end = System.currentTimeMillis();
            System.out.println(end - start + " ms.");
        }
    }
}
