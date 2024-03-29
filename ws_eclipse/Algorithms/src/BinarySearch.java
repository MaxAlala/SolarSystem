import java.util.Scanner;

public class BinarySearch {
    private static int [] arr;
    static Scanner sc;
    static int  n ;
    static StringBuilder str = new StringBuilder();;
    public static void main(String[] args) {
        sc = new Scanner(System.in);
        n = sc.nextInt();
        arr = new int[n];
        for(int i = 0; i < n; i++){
            arr[i] = sc.nextInt();
        }
        int k = sc.nextInt();
        for(int i = 0; i < k; i++){
            int b = sc.nextInt();
            str.append(proccess(b));
            str.append(" ");
        }
        System.out.println(str);
    }

    public static int proccess(int b){
      int l = 0 ;
      int r = n-1;
      while(l <= r){
          int m = l+(r-l)/2;
          if(arr[m] == b) return m+1;
          else if(arr[m] > b) r = m-1;
          else if(arr[m] < b) l = m+1;
      }
      return -1;
    }
}
