import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;


public class GameA {
	 public static final String ANSI_RESET = "\u001B[0m";
	    public static final String ANSI_BLACK = "\u001B[30m";
	    public static final String ANSI_RED = "\u001B[31m";
	    public static final String ANSI_GREEN = "\u001B[32m";
	    public static final String ANSI_YELLOW = "\u001B[33m";
	    public static final String ANSI_BLUE = "\u001B[34m";
	    public static final String ANSI_PURPLE = "\u001B[35m";
	    public static final String ANSI_CYAN = "\u001B[36m";
	    public static final String ANSI_WHITE = "\u001B[37m";
	 static int port;
	 static Socket socket;
	static InputStream sin;
	static OutputStream sout;
	static DataInputStream in;
	static DataOutputStream out;
	 static ServerSocket ss;
	 
		static int eADamage=0;
		static int eBDamage=0;
		static int eCDamage=0;
		static int eDDamage=0;
		static int eEDamage=0;
		static int eBaseHP=0;
		static int sum_damageA = 0;
		static int sum_damageB = 0;
		static int sum_damageC = 0;
		static int sum_damageD = 0;
		static int sum_damageE = 0;
		static Base baseA = new Base();
		static int ourBaseHP=baseA.getStructure();
		static int income = 20000;
	static int choosenShip;
	static int choice;
	static int credits = 450000; 
	private final static int LIMIT = 1000000;
	static boolean flag = true;
	static BufferedReader read = new BufferedReader(new InputStreamReader(System.in));
	static ArrayList fieldA = new ArrayList();
	static ArrayList fieldB = new ArrayList();
	static ArrayList fieldC = new ArrayList();
	static ArrayList fieldD = new ArrayList();
	static ArrayList fieldE = new ArrayList();
	
	public static void main(String args[]) {
//		Information info = new Information();
//		Thread th = new Thread(info, "info");
		
		makeConnection();
		while(flag) {
			
			fieldE.addAll(fieldD);		
			fieldD.clear();
			fieldD.addAll(fieldC);
			fieldC.clear();
			fieldC.addAll(fieldB);
			fieldB.clear();
			fieldB.addAll(fieldA);
			fieldA.clear();
			
			
			System.out.println("wait your opponent.");
			shop();
			takeMoneyAndInfo();
			space();
			sendDamage();
//			th.start();
			baseA.destruction(eADamage);
			ourBaseHP = baseA.getStructure();
		     if(baseA.structure<=0) { System.out.println(" Your base structure is: "+ baseA.getStructure());
		    	 System.out.println(" You've lost this game. ");
		    	 flag = false;
		     }
		     takeDamage();

		}
	}
	
	static void takeIncome() {
		Ore_miner ore = new Ore_miner();
		income= income + ore.getIncome();
		System.out.println("Your income: " + income);
	}
	static void takeMoneyAndInfo(){
		credits=credits+income;
		System.out.println("Your income: " + income + "\n Your bank account: " + credits);
	}

	
	static void sendDamage() {
		try {
			ourBaseHP = baseA.getStructure();
		out.writeInt(sum_damageA);	
		out.writeInt(sum_damageB);
		out.writeInt(sum_damageC);
		out.writeInt(sum_damageD);
		out.writeInt(sum_damageE);
		out.writeInt(ourBaseHP);
		sum_damageA = 0;
		sum_damageB = 0;
		sum_damageC = 0;
		sum_damageD = 0;
		sum_damageE = 0;
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	static void takeDamage() {
		try {
			eADamage = in.readInt();
			eBDamage = in.readInt();
			eCDamage = in.readInt();
			eDDamage = in.readInt();
			eEDamage = in.readInt()+ 50;
			eBaseHP = in.readInt();
			
		
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	}
	
	private static void makeConnection(){
		 
		try {
			
			System.out.println("Please, write your port");
			port = Integer.parseInt(read.readLine());
		
			  ss = new ServerSocket(port); 
	         System.out.println("Waiting for a client...!!!");

	          socket = ss.accept(); 
	          
	         System.out.println("Opponent is here!");
	         System.out.println();
	         
      sin = socket.getInputStream();
      sout = socket.getOutputStream();


      in = new DataInputStream(sin);
       out = new DataOutputStream(sout);
       
} catch (IOException e) {
			
	System.out.println("Your opponent run away. Thanks. ");
		}
	 }
	

	public static void space( ){
		
		if(!fieldA.isEmpty()||fieldA.isEmpty()) {
			
			int hcC = 0;
			int hcC_HP = 0;
			int lfC = 0;
			int lfC_HP = 0;
			int hcC_dmg = 0;
			int lfC_dmg = 0;
			int pe_HP = 0;
			int pe_dmg = 0;
			int peC = 0;
		    int sum_hp = 0;
		    int sum_c = 0;
		    String a=" ";
		    String b=" ";
		    String c=" ";
		    String d=" ";
		    String e=" ";
		    String f=" ";
		    String g=" ";
		    String h=" ";
		    String k=" ";
		    String j=" ";
		    int wasDestoyed_HC = 0;
		    int wasDestoyed_LF = 0;
		    int wasDestoyed_PE = 0;
		    if(eADamage!=0) {
		    	 a="^";
		    	 b="^";
		    	 c="^";
		    	 d="^";
		    	 e="^";
		    	 f="^";
		    	 g="|";
		    	 h="|";
		    	 k="|";
		    	 j="|";

		    }
			for(int i=0; i<fieldA.size(); i++ ) {
				Object currentShip = fieldA.get(i);
				
				
				
				
				
				
				
				
				if (currentShip instanceof HC){
					
					HC hc= (HC)fieldA.get(i);
					int startHP=hc.structure;
					hc.structure= hc.structure - eADamage;
					
					if(hc.structure <= 0) {            // destroy ship, change damage
						eADamage = eADamage-startHP;
						fieldA.remove(i);
						i--;
						wasDestoyed_HC++;
					} else {
						eADamage = 0;
						hcC++;
					}
						
						if(hc.structure<=0) {
							
						} else hcC_HP=hcC_HP+ hc.structure;
						
					hcC_dmg=hcC_dmg + hc.damage; // take the damage
					
	
					
					
					
				}else if (currentShip instanceof LF){
						LF lf = (LF) fieldA.get(i);
						int startHP = lf.structure;
					                          // count of light ship
					lf.structure= lf.structure - eADamage;
					if(lf.structure <= 0) {            // destroy ship, change damage
						eADamage = eADamage-startHP;
						fieldA.remove(i);
						i--;
						wasDestoyed_PE++;
					} else {
						eADamage = 0;
						lfC++;
					}
					
					if(lf.structure<=0) {
						
					} else lfC_HP=lfC_HP+ lf.structure;
					
					
					
					
					lfC_dmg=lfC_dmg+lf.damage;          // take the damage
					}
				else if (currentShip instanceof Pirate){
					Pirate pe = (Pirate) fieldA.get(i);
					int startHP = pe.structure;
				                          // count of light ship
					pe.structure= pe.structure - eADamage;
				if(pe.structure <= 0) {            // destroy ship, change damage
					eADamage = eADamage-startHP;
					fieldA.remove(i);
					i--;
					wasDestoyed_LF++;
				} else {
					eADamage = 0;
					peC++;
				}
				
				if(pe.structure<=0) {
					
				} else pe_HP= pe_HP+ pe.structure;
				
				
				
				
				pe_dmg=pe_dmg+pe.damage;          // take the damage
				}

			}
			sum_damageA = lfC_dmg + hcC_dmg + pe_dmg; 
             sum_hp=lfC_HP+ hcC_HP + pe_HP;
             sum_c = lfC + hcC + peC;
            
             
             System.out.println("|------|BaseHP:   "+ourBaseHP+"   |------|"); 
             System.out.println("|------|"+ANSI_BLUE +"<<===ABASE====>>"+ANSI_RESET+"|------|");   
             System.out.println("|          |   *               |");
             System.out.println("|    *   "+ANSI_BLUE +"v v v"+ANSI_RESET+"   *    *        |");
             System.out.println("|         v v               *  |");
             System.out.println("|          V      C  DG HP     |");
             System.out.println("|       "+a+"     HC:"+hcC+" "+hcC_dmg+" "+hcC_HP+"   *  |");
             System.out.println("|      "+b+g+c+"    LF:"+lfC+" "+lfC_dmg+" "+lfC_HP+"    * |");
             System.out.println("|   * "+d+" "+e+" "+f+"   PE:"+peC+" "+pe_dmg+" "+pe_HP+"  *   |");
             System.out.println("|      "+h+k+j+"    SUM:"+sum_c +" "+sum_damageA+" "+sum_hp+"  *  |");
             System.out.println("|           *                  |");
             System.out.println("|    *     *          *        |");
		}

		
		if(!fieldB.isEmpty()) {
			int sum_c = 0;
			int hcC = 0;
			int hcC_HP = 0;
			int lfC = 0;
			int lfC_HP = 0;
			int hcC_dmg = 0;
			int lfC_dmg = 0;
			int pe_HP = 0;
			int pe_dmg = 0;
			int peC = 0;
		    int sum_hp = 0;
		    String a=" ";
		    String b=" ";
		    String c=" ";
		    String d=" ";
		    String e=" ";
		    String f=" ";
		    String g=" ";
		    String h=" ";
		    String k=" ";
		    String j=" ";
		    int wasDestoyed_HC = 0;
		    int wasDestoyed_LF = 0;
		    int wasDestoyed_PE = 0;
		    if(eBDamage!=0) {
		    	 a="^";
		    	 b="^";
		    	 c="^";
		    	 d="^";
		    	 e="^";
		    	 f="^";
		    	 g="|";
		    	 h="|";
		    	 k="|";
		    	 j="|";
		    }
		    
			for(int i=0; i<fieldB.size(); i++ ) {
				Object currentShip = fieldB.get(i);
				
				
				
				
				
				
				
				
				if (currentShip instanceof HC){
					
					HC hc= (HC)fieldB.get(i);
					int startHP=hc.structure;
					hc.structure= hc.structure - eBDamage;
					
					if(hc.structure <= 0) {            // destroy ship, change damage
						eBDamage = eBDamage-startHP;
						fieldB.remove(i);
						i--;
						wasDestoyed_HC++;
					} else {
						eBDamage = 0;
						hcC++;
					}
						
						if(hc.structure<=0) {
							
						} else hcC_HP=hcC_HP+ hc.structure;
						
					hcC_dmg=hcC_dmg + hc.damage; // take the damage
					
	
					
					
					
				}else if (currentShip instanceof LF){
						LF lf = (LF) fieldB.get(i);
						int startHP = lf.structure;
					                          // count of light ship
					lf.structure= lf.structure - eBDamage;
					if(lf.structure <= 0) {            // destroy ship, change damage
						eBDamage = eBDamage-startHP;
						fieldB.remove(i);
						i--;
						wasDestoyed_PE++;
					} else {
						eBDamage = 0;
						lfC++;
					}
					
					if(lf.structure<=0) {
						
					} else lfC_HP=lfC_HP+ lf.structure;
					
					
					
					
					lfC_dmg=lfC_dmg+lf.damage;          // take the damage
					}
				else if (currentShip instanceof Pirate){
					Pirate pe = (Pirate) fieldB.get(i);
					int startHP = pe.structure;
				                          // count of light ship
					pe.structure= pe.structure - eBDamage;
				if(pe.structure <= 0) {            // destroy ship, change damage
					eBDamage = eBDamage-startHP;
					fieldB.remove(i);
					i--;
					wasDestoyed_LF++;
				} else {
					eBDamage = 0;
					peC++;
				}
				
				if(pe.structure<=0) {
					
				} else pe_HP= pe_HP+ pe.structure;
				
				
				
				
				pe_dmg=pe_dmg+pe.damage;          // take the damage
				}

			}
			sum_damageB = lfC_dmg + hcC_dmg + pe_dmg; 
             sum_hp=lfC_HP+ hcC_HP + pe_HP;
             sum_c = lfC + hcC + peC;
        
             System.out.println("|-----------field B------------|");
             System.out.println("|          |   *               |");
             System.out.println("|    *   "+ANSI_BLUE +"v v v"+ANSI_RESET+"   *    *        |");
             System.out.println("|         v v               *  |");
             System.out.println("|          V      C  DG HP     |");
             System.out.println("|       "+a+"     HC:"+hcC+" "+hcC_dmg+" "+hcC_HP+"   *  |");
             System.out.println("|      "+b+g+c+"    LF:"+lfC+" "+lfC_dmg+" "+lfC_HP+"    * |");
             System.out.println("|   * "+d+" "+e+" "+f+"   PE:"+peC+" "+pe_dmg+" "+pe_HP+"  *   |");
             System.out.println("|      "+h+k+j+"    SUM:"+sum_c +" "+sum_damageB+" "+sum_hp+"  *  |");
             System.out.println("|           *                  |");
             System.out.println("|    *     *          *        |");
		            
 
		}

		
		
		if(!fieldC.isEmpty()) {
			int sum_c = 0;
			int hcC = 0;
			int hcC_HP = 0;
			int lfC = 0;
			int lfC_HP = 0;
			int hcC_dmg = 0;
			int lfC_dmg = 0;
			int pe_HP = 0;
			int pe_dmg = 0;
			int peC = 0;
		    int sum_hp = 0;
		    String a=" ";
		    String b=" ";
		    String c=" ";
		    String d=" ";
		    String e=" ";
		    String f=" ";
		    String g=" ";
		    String h=" ";
		    String k=" ";
		    String j=" ";
		    int wasDestoyed_HC = 0;
		    int wasDestoyed_LF = 0;
		    int wasDestoyed_PE = 0;
		    if(eCDamage!=0) {
		    	 a="^";
		    	 b="^";
		    	 c="^";
		    	 d="^";
		    	 e="^";
		    	 f="^";
		    	 g="|";
		    	 h="|";
		    	 k="|";
		    	 j="|";

		    }
			for(int i=0; i<fieldC.size(); i++ ) {
				Object currentShip = fieldC.get(i);
				
				
				
				
				
				
				
				
				if (currentShip instanceof HC){
					
					HC hc= (HC)fieldC.get(i);
					int startHP=hc.structure;
					hc.structure= hc.structure - eCDamage;
					
					if(hc.structure <= 0) {            // destroy ship, change damage
						eCDamage = eCDamage-startHP;
						fieldC.remove(i);
						i--;
						wasDestoyed_HC++;
					} else {
						eCDamage = 0;
						hcC++;
					}
						
						if(hc.structure<=0) {
							
						} else hcC_HP=hcC_HP+ hc.structure;
						
					hcC_dmg=hcC_dmg + hc.damage; // take the damage
					
	
					
					
					
				}else if (currentShip instanceof LF){
						LF lf = (LF) fieldC.get(i);
						int startHP = lf.structure;
					                          // count of light ship
					lf.structure= lf.structure - eCDamage;
					if(lf.structure <= 0) {            // destroy ship, change damage
						eCDamage = eCDamage-startHP;
						fieldC.remove(i);
						i--;
						wasDestoyed_LF++;
					} else {
						eCDamage = 0;
						lfC++;
					}
					
					if(lf.structure<=0) {
						
					} else lfC_HP=lfC_HP+ lf.structure;
					
					
					
					
					lfC_dmg=lfC_dmg+lf.damage;          // take the damage
					}
				else if (currentShip instanceof Pirate){
					Pirate pe = (Pirate) fieldC.get(i);
					int startHP = pe.structure;
				                          // count of light ship
					pe.structure= pe.structure - eCDamage;
				if(pe.structure <= 0) {            // destroy ship, change damage
					eCDamage = eCDamage-startHP;
					fieldC.remove(i);
					i--;
					wasDestoyed_LF++;
				} else {
					eCDamage = 0;
					peC++;
				}
				
				if(pe.structure<=0) {
					
				} else pe_HP= pe_HP+ pe.structure;
				
				
				
				
				pe_dmg=pe_dmg+pe.damage;          // take the damage
				}

			}
			sum_damageC = lfC_dmg + hcC_dmg + pe_dmg; 
             sum_hp=lfC_HP+ hcC_HP + pe_HP;
             sum_c = lfC + hcC + peC;
             System.out.println("|-----------field C------------|");
             System.out.println("|          |   *               |");
             System.out.println("|    *   "+ANSI_BLUE +"v v v"+ANSI_RESET+"   *    *        |");
             System.out.println("|         v v               *  |");
             System.out.println("|          V      C  DG HP     |");
             System.out.println("|       "+a+"     HC:"+hcC+" "+hcC_dmg+" "+hcC_HP+"   *  |");
             System.out.println("|      "+b+g+c+"    LF:"+lfC+" "+lfC_dmg+" "+lfC_HP+"    * |");
             System.out.println("|   * "+d+" "+e+" "+f+"   PE:"+peC+" "+pe_dmg+" "+pe_HP+"  *   |");
             System.out.println("|      "+h+k+j+"    SUM:"+sum_c +" "+sum_damageC+" "+sum_hp+"  *  |");
             System.out.println("|           *                  |");
             System.out.println("|    *     *          *        |");
             
 
		}

		if(!fieldD.isEmpty()) {
			int sum_c = 0;
			int hcC = 0;
			int hcC_HP = 0;
			int lfC = 0;
			int lfC_HP = 0;
			int hcC_dmg = 0;
			int lfC_dmg = 0;
			int pe_HP = 0;
			int pe_dmg = 0;
			int peC = 0;
		    int sum_hp = 0;
		    String a=" ";
		    String b=" ";
		    String c=" ";
		    String d=" ";
		    String e=" ";
		    String f=" ";
		    String g=" ";
		    String h=" ";
		    String k=" ";
		    String j=" ";
		    int wasDestoyed_HC = 0;
		    int wasDestoyed_LF = 0;
		    int wasDestoyed_PE = 0;
		    if(eDDamage!=0) {
		    	 a="^";
		    	 b="^";
		    	 c="^";
		    	 d="^";
		    	 e="^";
		    	 f="^";
		    	 g="|";
		    	 h="|";
		    	 k="|";
		    	 j="|";

		    }
			for(int i=0; i<fieldD.size(); i++ ) {
				Object currentShip = fieldD.get(i);
				
				
				
				
				
				
				
				
				if (currentShip instanceof HC){
					
					HC hc= (HC)fieldD.get(i);
					int startHP=hc.structure;
					hc.structure= hc.structure - eDDamage;
					
					if(hc.structure <= 0) {            // destroy ship, change damage
						eDDamage = eDDamage-startHP;
						fieldD.remove(i);
						i--;
						wasDestoyed_HC++;
					} else {
						eDDamage = 0;
						hcC++;
					}
						
						if(hc.structure<=0) {
							
						} else hcC_HP=hcC_HP+ hc.structure;
						
					hcC_dmg=hcC_dmg + hc.damage; // take the damage
					
	
					
					
					
				}else if (currentShip instanceof LF){
						LF lf = (LF) fieldD.get(i);
						int startHP = lf.structure;
					                          // count of light ship
					lf.structure= lf.structure - eDDamage;
					if(lf.structure <= 0) {            // destroy ship, change damage
						eDDamage = eDDamage-startHP;
						fieldD.remove(i);
						i--;
						wasDestoyed_LF++;
					} else {
						eDDamage = 0;
						lfC++;
					}
					
					if(lf.structure<=0) {
						
					} else lfC_HP=lfC_HP+ lf.structure;
					
					
					
					
					lfC_dmg=lfC_dmg+lf.damage;          // take the damage
					}
				else if (currentShip instanceof Pirate){
					Pirate pe = (Pirate) fieldD.get(i);
					int startHP = pe.structure;
				                          // count of light ship
					pe.structure= pe.structure - eDDamage;
				if(pe.structure <= 0) {            // destroy ship, change damage
					eDDamage = eDDamage-startHP;
					fieldD.remove(i);
					i--;
					wasDestoyed_LF++;
				} else {
					eDDamage = 0;
					peC++;
				}
				
				if(pe.structure<=0) {
					
				} else pe_HP= pe_HP+ pe.structure;
				
				
				
				
				pe_dmg=pe_dmg+pe.damage;          // take the damage
				}

			}
			sum_damageD = lfC_dmg + hcC_dmg + pe_dmg; 
             sum_hp=lfC_HP+ hcC_HP + pe_HP;
             sum_c = lfC + hcC + peC;
             System.out.println("|-----------field D------------|");
             System.out.println("|          |   *               |");
             System.out.println("|    *   "+ANSI_BLUE +"v v v"+ANSI_RESET+"   *    *        |");
             System.out.println("|         v v               *  |");
             System.out.println("|          V      C  DG HP     |");
             System.out.println("|       "+a+"     HC:"+hcC+" "+hcC_dmg+" "+hcC_HP+"   *  |");
             System.out.println("|      "+b+g+c+"    LF:"+lfC+" "+lfC_dmg+" "+lfC_HP+"    * |");
             System.out.println("|   * "+d+" "+e+" "+f+"   PE:"+peC+" "+pe_dmg+" "+pe_HP+"  *   |");
             System.out.println("|      "+h+k+j+"    SUM:"+sum_c +" "+sum_damageD+" "+sum_hp+"  *  |");
             System.out.println("|           *                  |");
             System.out.println("|    *     *          *        |");
             
		}
		if(!fieldE.isEmpty()) {
			int sum_c = 0;
			int hcC = 0;
			int hcC_HP = 0;
			int lfC = 0;
			int lfC_HP = 0;
			int hcC_dmg = 0;
			int lfC_dmg = 0;
			int pe_HP = 0;
			int pe_dmg = 0;
			int peC = 0;
		    int sum_hp = 0;
		    String a=" ";
		    String b=" ";
		    String c=" ";
		    String d=" ";
		    String e=" ";
		    String f=" ";
		    String g=" ";
		    String h=" ";
		    String k=" ";
		    String j=" ";
		    int wasDestoyed_HC = 0;
		    int wasDestoyed_LF = 0;
		    int wasDestoyed_PE = 0;
		    if(eEDamage!=0) {
		    	 a="^";
		    	 b="^";
		    	 c="^";
		    	 d="^";
		    	 e="^";
		    	 f="^";
		    	 g="|";
		    	 h="|";
		    	 k="|";
		    	 j="|";

		    }
			for(int i=0; i<fieldE.size(); i++ ) {
				Object currentShip = fieldE.get(i);
				
				
				
				
				
				
				
				
				if (currentShip instanceof HC){
					
					HC hc= (HC)fieldE.get(i);
					int startHP=hc.structure;
					hc.structure= hc.structure - eEDamage;
					
					if(hc.structure <= 0) {            // destroy ship, change damage
						eEDamage = eEDamage-startHP;
						fieldE.remove(i);
						i--;
						wasDestoyed_HC++;
					} else {
						eEDamage = 0;
						hcC++;
					}
						
						if(hc.structure<=0) {
							
						} else hcC_HP=hcC_HP+ hc.structure;
						
					hcC_dmg=hcC_dmg + hc.damage; // take the damage
					
	
					
					
					
				}else if (currentShip instanceof LF){
						LF lf = (LF) fieldE.get(i);
						int startHP = lf.structure;
					                          // count of light ship
					lf.structure= lf.structure - eEDamage;
					if(lf.structure <= 0) {            // destroy ship, change damage
						eEDamage = eEDamage-startHP;
						fieldE.remove(i);
						i--;
						wasDestoyed_LF++;
					} else {
						eEDamage = 0;
						lfC++;
					}
					
					if(lf.structure<=0) {
						
					} else lfC_HP=lfC_HP+ lf.structure;
					
					
					
					
					lfC_dmg=lfC_dmg+lf.damage;          // take the damage
					}
				else if (currentShip instanceof Pirate){
					Pirate pe = (Pirate) fieldE.get(i);
					int startHP = pe.structure;
				                          // count of light ship
					pe.structure= pe.structure - eEDamage;
				if(pe.structure <= 0) {            // destroy ship, change damage
					eEDamage = eEDamage-startHP;
					fieldE.remove(i);
					i--;
					wasDestoyed_LF++;
				} else {
					eEDamage = 0;
					peC++;
				}
				
				if(pe.structure<=0) {
					
				} else pe_HP= pe_HP+ pe.structure;
				
				
				
				
				pe_dmg=pe_dmg+pe.damage;          // take the damage
				}

			}
			sum_damageE = lfC_dmg + hcC_dmg + pe_dmg; 
             sum_hp=lfC_HP+ hcC_HP + pe_HP;
              sum_c = lfC + hcC + peC;
              System.out.println("|------------------------------|");
              System.out.println("|          |   *               |");
              System.out.println("|    *   "+ANSI_BLUE +"v v v"+ANSI_RESET+"   *    *        |");
              System.out.println("|         v v               *  |");
              System.out.println("|          V      C  DG HP     |");
              System.out.println("|       "+a+"     HC:"+hcC+" "+hcC_dmg+" "+hcC_HP+"   *  |");
              System.out.println("|      "+b+g+c+"    LF:"+lfC+" "+lfC_dmg+" "+lfC_HP+"    * |");
              System.out.println("|   * "+d+" "+e+" "+f+"   PE:"+peC+" "+pe_dmg+" "+pe_HP+"  *   |");
              System.out.println("|      "+h+k+j+"    SUM:"+sum_c +" "+sum_damageE+" "+sum_hp+"  *  |");
             System.out.println("|------|"+ANSI_RED +"<<===EBASE====>>"+ANSI_RESET+"|------|");
             System.out.println("|------|BaseHP:   "+eBaseHP+"   |------|"); 
             
         
		}
		
	}
	
	static void shop(){
		int purse = 0;
		System.out.println("your bank account: "+ credits);
		System.out.println("choose thing, ships: 1-hc(1), 2-lf(m),3-pe(m), 4-om(1), 5 repair(1), 0-exit. ");
		
		while(purse < LIMIT) {
			
	      try {
	    	  choice= Integer.parseInt(read.readLine());
		} catch (NumberFormatException | IOException e) {
			e.printStackTrace();
		}
			if((choice == 1) && (credits >= 1000000) ) {
				HC hc = new HC();
				fieldA.add(hc);
				credits=credits - 500000;
				purse = purse + 500000;
			}
			
		if(choice == 2 && credits >= 50000) {
			LF lf = new LF();
			fieldA.add(lf);
			credits=credits - 50000;
			purse= purse + 50000;
		}
		
		if(choice == 3 && credits>=100000) {
			Pirate pe = new Pirate();
			fieldA.add(pe);
			credits=credits - 100000;
			purse= purse + 100000;
		}
		
		if(choice == 4 && credits>=100000){               // increase sum of income
			
			credits= credits-100000;
			purse= purse + 100000;
			takeIncome();
			break;
		}
		
		if(choice == 5 && credits>=100000){                // repair the base
			RepairShip rep = new RepairShip();
		baseA.structure = baseA.structure + rep.getRepair();

			credits= credits-100000;
			purse= purse + 100000;
			break;
		}
		if(choice == 0 )break;
		System.out.println("Your purse: " + purse);
		

	}
	
}
}
class Information implements Runnable {
	GameA game = new GameA();
	public void run() {
		
		System.out.println("current moneys: " + game.credits );
		
		
	}
}

