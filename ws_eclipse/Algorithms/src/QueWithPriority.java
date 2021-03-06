

import java.util.ArrayList;
import java.util.Scanner;

public class QueWithPriority {
   static  Scanner sc = new Scanner(System.in);
    static int n = Integer.parseInt(sc.nextLine());
   static  ArrayList<Integer> arr = new ArrayList<>();


    public static void main(String[] args) {
//        for(int r = 0; r< arr.length; r++){
//            arr[r] = -1;
//        }
        for(int i = 0; i < n; i++){
         String str = sc.nextLine();
         if(str.startsWith("Insert")){
             int x = Integer.parseInt(str.substring(7));

             add(x);

         }else if (str.equals("ExtractMax")){
            System.out.println(getMax());
//             getMax();
         }
        }
//for(int x: arr){
//    System.out.println(x);
//}
    }
    public static void add(int value)
    {
        arr.add(value);
        int i = arr.size() - 1;
        int parent = (i - 1) / 2;

        while (i > 0 && arr.get(parent) < arr.get(i))
        {
            int temp = arr.get(i);
             arr.set(i, arr.get(parent));
            arr.set(parent, temp);

            i = parent;
            parent = (i - 1) / 2;

        }
              //      for(int x: arr){
            //    System.out.println(x);
          //  }

    }

    public static void heapify(int i)
    {
        int leftChild;
        int rightChild;
        int largestChild;

        for (; ; )
        {
            leftChild = 2 * i + 1;
            rightChild = 2 * i + 2;
            largestChild = i;

            if (leftChild < arr.size() && arr.get(leftChild) > arr.get(largestChild))
            {
                largestChild = leftChild;
            }

            if (rightChild < arr.size() && arr.get(rightChild) > arr.get(largestChild))
            {
                largestChild = rightChild;
            }

            if (largestChild == i)
            {
                break;
            }

            int temp = arr.get(i);
            arr.set(i, arr.get(largestChild));
            arr.set(largestChild, temp);
            i = largestChild;
        }
    }
    public static int getMax()
    {
        int result = arr.get(0);
        arr.set(0,arr.get(arr.size() - 1));
        arr.remove(arr.size()-1);
        heapify(0);
        return result;
    }
}
