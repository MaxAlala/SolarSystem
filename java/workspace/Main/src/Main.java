import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
public class Main{

	public static ArrayList users = new ArrayList();
	public static ArrayList subs = new ArrayList();
	public static void main(String args[]) throws FileNotFoundException, IOException {
		User user = new User();
		Subscriptions sub = new Subscriptions();
		user.fillArrayOfUsers();
		sub.fillArrayOfSub();

		for(int i=0; i<users.size();i++) {
			user = (User) users.get(i);

			System.out.println(user.id);
		}
		for(int i=0; i<subs.size();i++) {
			sub = (Subscriptions) subs.get(i);
			System.out.println(sub.id);
		}

		for(int i = 0; i<subs.size(); i++) {
			for(int j = 0; i<users.size(); i++) {
				Subscriptions sub2 = (Subscriptions) subs.get(i);
				User user2 = (User) users.get(j);



				if(user2.id == sub2.id ) {
					User userSub;
					
					
					System.out.println(" friend of "+ user2.userName + " is " + sub2.subsctription_id );
				}

			}
		}
	}
}