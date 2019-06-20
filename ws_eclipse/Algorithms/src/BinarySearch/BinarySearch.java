package BinarySearch;

public class BinarySearch {
    public static void main (String args [] ) {

        int[] ar = {1,2,3,4,5,6,7,8,9};
        System.out.println(binarySearch(ar,1));
    }

    private static int binarySearch0(int[] a, int key) {
        int low = 0;
        int high = a.length-1;

        while (low <= high) {
            int mid = (low + high) >>> 1;
            int midVal = a[mid];

            if (midVal < key)
                low = mid + 1;
            else if (midVal > key)
                high = mid - 1;
            else
                return mid; // key found
        }
        return -(low + 1);  // key not found.
    }

    public static int binarySearch(int[] a, int key) {
        return binarySearch0(a, key);
    }


}