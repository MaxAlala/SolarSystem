import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class User {
	long id;
	String userName;
	String password;
	String email;
	
    User(){
    	
    }
    
	User(long id, String userName, String password, String email){


		this.id = id;
		this.userName = userName;
		this.password = password;
		this.email = email;
	}
	
	public  void fillArrayOfUsers() throws NumberFormatException, IOException {
		BufferedReader fin = new BufferedReader(new FileReader("users"));
		String line;
		int i = 1;
		long id = 0;
		String userName = "";
		String password = "";
		String email = "";
		while ((line = fin.readLine()) != null) {
			switch(i) {
			case 1:{
				i++;
				id = Long.parseLong(line);
				break;
			} 		  
			case 2:{
				i++;
				userName = line; 
               break;


			}case 3:{
				i++;
				password = line; 	  
              break;

			}case 4:{
				Main main = new Main();
				i = 1;
				email = line; 
				User user = new User(id, userName, password, email);
				main.users.add(user);
				break;
			}

			}

		}
	}
}