import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

class Subscriptions {
	public long id;
	public long subsctription_id;
	
	Subscriptions(){
    	
    }
    
	Subscriptions( long id, long subsctription_id){


		this.id = id;
		this.subsctription_id = subsctription_id;
	}
	
	public  void fillArrayOfSub() throws NumberFormatException, IOException {
		BufferedReader fin = new BufferedReader(new FileReader("subs"));
		String line;
		int i = 1;
		long subsctription_id = 0;
		long id = 0;
		while ((line = fin.readLine()) != null) {
			switch(i) {
			case 1:{
				i++;
				id = Long.parseLong(line);
				break;
			} 		  
			case 2:{

				Main main = new Main();
				i = 1;
				subsctription_id = Long.parseLong(line);
				Subscriptions sub = new Subscriptions(id, subsctription_id);
				main.subs.add(sub);
				break;
			}

			}

		}
	}
}