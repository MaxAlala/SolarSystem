
public  class Ships {

	protected int destruction(int structure, int damage){
		  
		  return structure = structure - damage;
 
	  }
	 
	 protected int damages(int x, int y){
		 
		 return (int)((Math.random()*x+y));
	 }
	 
 protected int money(int x, int y){
		 
		 return (int)((Math.random()*x+y));
	 }
	 
	 
	 protected double chance(double  x, double y){
		 return (Math.random()*x+y);
	 }
	
 protected int repair(int x, int y){
		 
		 return (int)((Math.random()*x+y));
	 }
	 
//		public int setOreMoney(int money) {     // ores method
//			int income=0;
//			return income = income + money;
//		}
		
}

class HC extends Ships{       //heavy cruiser
	int structure=250;
	double chance = chance(0.6, 0.4);
	int  damage = (int) (damages(70,30) * chance) ;
	String name ="HC";
	HC(){}
	
	HC(int damageOUT){

		structure = destruction(structure, damageOUT);
	}

}

class LF extends Ships{ //light fighter
	public int structure=20;
	double chance = chance(0.3, 0.6);
	int damage = (int) ( damages(20,5)* chance ) ;
	String name ="LK";
	LF(){}
	LF(int damageOUT){

		structure = destruction(structure, damageOUT);
	}
    

}

class Pirate extends Ships{       //heavy cruiser
	int structure=35;
	double chance = chance(0.6, 0.4);
	int damage =  (int) (damages(40,30)* chance) ;
	
	Pirate(){}
	Pirate(int damageOUT){

		structure = destruction(structure, damageOUT);
	}

}

class Ore_miner extends Ships{       //ores
	static int sumOfIncome = 0;

	Ore_miner(){
		sumOfIncome= money(50000, 0);
	}

    public int getIncome(){
    	return sumOfIncome;
    }
    
	}
class RepairShip extends Ships{       //ores


    public int getRepair(){
    	return repair(70, 30);
    }
    
	}
  

