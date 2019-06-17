package sample;

public class Try {
    public static void main(String[] args) {
        int ad_exp = 10000, popularity = 50;
//        System.out.println(2*ad_exp/10000 +(int) (Math.random() * (ad_exp/10000*5))); //3 - 5
        System.out.println(  ((int) (Math.random() * popularity / 4)));

        System.out.println((0+ (int) (Math.random() * popularity/6)));
        System.out.println((0+ (int) (Math.random() * 20/100*(100-popularity))));
        System.out.println((double)20/100/(popularity));
//        left_profi = (0+ (int) (Math.random() * last_profi/100*(100-popularity)));

    }
}
