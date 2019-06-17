
public class Base {
	int structure=500;
	public int getStructure() {
		return structure;
	}
  Base(){  
  }
  public void destruction(int damage){
	  
	  structure = structure - damage;
	  
  }
  
}
