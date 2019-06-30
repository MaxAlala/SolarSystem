package application;

import com.vse.network.TCPConnection;
import com.vse.network.TCPConnectionListener;
import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.paint.ImagePattern;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;

import java.util.stream.Collectors;



public class SpaceInvadersApp extends Application implements TCPConnectionListener {
	private String myAddress  = "";
	private Pane root = new Pane();
	private final HashMap<String, Sprite> players = new HashMap<>();
	private final HashMap<String, Sprite> enemies = new HashMap<>();
	private final HashMap<String, Sprite> big = new HashMap<>();
	private double t = 0;
	private TCPConnection connection;
	private int deadCount = 0;


//	private String sightSide = "W";
	private Sprite player = new Sprite(300, 750, 40, 40, "player", Color.BLUE, "W", 1);
//	private Sprite player2 = new Sprite(300, 750, 40, 40, "player", Color.GREEN);

	private Parent createContent() {

		root.setId("root");
		root.setPrefSize(500, 800);

		player.setHp(150);
		root.getChildren().add(player);
//		root.getChildren().add(player2);

		AnimationTimer timer = new AnimationTimer() {
			@Override
			public void handle(long now) {
//				onReceiveString();
				update();

			}
		};

		timer.start();

//		nextLevel();

		return root;
	}

	private void nextLevel() {
		for (int i = 0; i < 5; i++) {
			Sprite s = new Sprite(90 + i*100, 150, 30, 30, "enemy", Color.RED);
			Sprite s2 = new Sprite(90 + i*105, 185, 30, 30, "enemy", Color.RED);
			Sprite s3 = new Sprite(90 + i*100, 210, 30, 30, "enemy", Color.RED);
			Sprite s4 = new Sprite(90 + i*105, 255, 30, 30, "enemy", Color.RED);

			root.getChildren().addAll(s,s2,s3,s4);
		}


	}

	private List<Sprite> sprites() {
		return root.getChildren().stream().map(n -> (Sprite)n).collect(Collectors.toList());
	}

	private void update() {

		t += 0.016;

		sprites().forEach(s -> {
			switch (s.type) {

//				case "enemybullet":
//
//					s.moveDown();
//
//
//
//					for(Map.Entry<String, Sprite> entry : players.entrySet()) {
//						String gamers_address = entry.getKey();
//						Sprite gamer = entry.getValue();
//
//						// do what you have to do here
//						// In your case, another loop.
//						if (s.getBoundsInParent().intersects(gamer.getBoundsInParent())) {
//							gamer.dead = true;
//							s.dead = true;
//							players.remove(gamers_address);
//						}
//					}
//
////					if (s.getBoundsInParent().intersects(player2.getBoundsInParent())) {
////						player2.dead = true;
////						s.dead = true;
////					}
//					break;

				case "playerbullet":
					makeBulletFly(s);

					bulletBordersConstraints(s);
					checkAndDelete(s,"robot");
                    checkAndDelete(s,"playerB");
					checkAndDelete(s,"player");

					break;
				case "robotbullet":
					makeBulletFly(s);
					bulletBordersConstraints(s);
					checkAndDelete(s,"player");
//					checkAndDelete(s,"playerB");

					break;
				case "playerBbullet":
					makeBulletFly(s);
					bulletBordersConstraints(s);
//					checkAndDelete(s,"player");
					checkAndDelete(s,"player");

//					checkAndDelete(s,"big");
					break;

			}
		});

		root.getChildren().removeIf(n -> {
			Sprite s = (Sprite) n;
			return s.dead;
		});

		if (t > 2) {
			t = 0;
		}
	}

	void makeBulletFly(Sprite s) {
		switch (s.getDirection()){
			case "W":
				s.moveUp();
				break;
			case "S":
				s.moveDown();
				break;
			case "A":
				s.moveLeft();
				break;
			case "D":
				s.moveRight();
				break;
		}
	}

	private void bulletBordersConstraints(Sprite s) {
		if(s.getTranslateY()>800)root.getChildren().remove(s);
		if(s.getTranslateY()<0)root.getChildren().remove(s);
		if(s.getTranslateX()>500)root.getChildren().remove(s);
		if(s.getTranslateX()<0)root.getChildren().remove(s);
	}

	private void checkAndDelete(Sprite s, String type) {
		sprites().stream().filter(e -> e.type.equals(type)).forEach(player2 -> {
			if (s.getBoundsInParent().intersects(player2.getBoundsInParent())) {
				player2.hp-=1;
				if(player2.hp <= 0){
					deadCount++;

					if(players.containsKey(player2.getAddress()))players.remove(player2.getAddress());
					if(enemies.containsKey(player2.getAddress())){
						System.out.println("bot was deleted//////////////////////////");
						enemyWasDestroyed(player2.getAddress());
						enemies.remove(player2.getAddress());
					}
					if(big.containsKey(player2.getAddress()))big.remove(player2.getAddress());
					player2.dead = true;

					if(player.getAddress().equals(player2.getAddress())){
						scene.setOnKeyPressed(e -> {
							switch (e.getCode()) {
								case ENTER:
									break;
							}
						});

					}
				}

				s.dead = true;




			}

		});
	}

	private void shoot(Sprite who) {
		Sprite s = null;
		if(who.getDirection().equals("W")){
			 s = new Sprite((int) who.getTranslateX() + 20, (int) who.getTranslateY() - 45, 5, 20, who.type + "bullet", Color.BLUE, who.direction, 0);
		}else if(who.getDirection().equals("S")){
			 s = new Sprite((int) who.getTranslateX() + 20, (int) who.getTranslateY() + 45, 5, 20, who.type + "bullet", Color.BLUE, who.direction, 0);
		}else
		if(who.getDirection().equals("A")){
			 s = new Sprite((int) who.getTranslateX() - 45, (int) who.getTranslateY() + 20, 20, 5, who.type + "bullet", Color.BLUE, who.direction, 0);
		}else
		if(who.getDirection().equals("D")){
			 s = new Sprite((int) who.getTranslateX() + 45, (int) who.getTranslateY() + 20, 20, 5, who.type + "bullet", Color.BLUE, who.direction, 0);
		}


		root.getChildren().add(s);

	}

	Scene scene;
	@Override
	public void start(Stage stage) throws Exception {
//root.getStylesheets().addAll(this.getClass().getResource("style.css").toExternalForm());

		scene = new Scene(createContent());
		scene.getStylesheets().addAll(this.getClass().getResource("/style.css").toExternalForm());



		//////////

		/////////

		scene.setOnKeyPressed(e -> {
			Image img;
			switch (e.getCode()) {
				case A:
					player.moveLeft();
					player.setDirection("A");
					connection.sendString(myAddress + " " + (int)player.getTranslateX() + " " + (int)player.getTranslateY() + " " + "A");
					 img = new Image("/images/s1_left.jpg");
//					player.setFill(new ImagePattern(img));
					player.setRotate(270);
					break;
				case D:
					player.moveRight();
					player.setDirection("D");
					connection.sendString(myAddress + " " + (int)player.getTranslateX() + " " + (int)player.getTranslateY() + " " + "D");
//					 img = new Image("/images/s1_right.jpg");
//					player.setFill(new ImagePattern(img));
//					root.getChildren().remove(player);
////					root.getChildren().add(player);
					player.setRotate(90);
					break;
				case W:
					player.moveUp();
					player.setDirection("W");
					connection.sendString(myAddress + " " + (int)player.getTranslateX() + " " + (int)player.getTranslateY() + " " + "W");
					player.setRotate(0);


// img = new Image("/images/s1.jpg");
//					player.setFill(new ImagePattern(img));
//					root.getChildren().remove(player);
////					root.getChildren().add(player);
					break;
				case S:
					player.moveDown();
					player.setDirection("S");
					connection.sendString(myAddress + " " + (int)player.getTranslateX() + " " + (int)player.getTranslateY() + " " + "S");
					player.setRotate(180);
					break;
				case SPACE:
					shoot(player);
					connection.sendString(myAddress + " SPACE");
					break;
//					default: root.getChildren().add(player);
			}
		});


		stage.setScene(scene);
		stage.setResizable(false);
//		stage.initStyle(StageStyle.UNDECORATED);
		stage.show();
		init();

	}
//	public void setRotation(Sprite sprite, String string){
//		if(sprite.equals("A"))
//	}

	public void init() {
		System.out.println("i am in init");
		try {
			System.out.println("i am in init");
			connection = new TCPConnection(this, "10.17.1.69", 8189);
		} catch (IOException e) {

			e.printStackTrace();

		}
	}

	private static class Sprite extends Rectangle {
		boolean dead = false;
		final String type;
		String address;

		public boolean isDead() {
			return dead;
		}

		public void setDead(boolean dead) {
			this.dead = dead;
		}

		public String getType() {
			return type;
		}

		public int getHp() {
			return hp;
		}

		public void setHp(int hp) {
			this.hp = hp;
		}

		int hp = 1;


		public String getDirection() {
			return direction;
		}

		public void setDirection(String direction) {
			this.direction = direction;
		}

		String direction = null; // aswd

		Sprite(int x, int y, int w, int h, String type, Color color) {
			super(w, h, color);

			this.type = type;
			setTranslateX(x);
			setTranslateY(y);

			Image img = new Image("/image/p1.jpg");
			setFill(new ImagePattern(img));
		}

		Sprite(int x, int y, int w, int h, String type, Color color, String direction, String address) {
			super(w, h, color);
			setDirection(direction);
			this.type = type;
			setTranslateX(x);
			setTranslateY(y);
			setAddress(address);
		}
		Sprite(int x, int y, int w, int h, String type, Color color, String direction, int typeS, String address, int hp) {
			super(w, h, color);
			setDirection(direction);
			this.type = type;
			setTranslateX(x);
			setTranslateY(y);
			setAddress(address);
			Image img = null;
			if(typeS != 0){
				img = new Image("/images/p1.jpg");
				setFill(new ImagePattern(img));
			}
			if(typeS == 2){
//				Random rnd = new Random(System.currentTimeMillis());
//				int number = 0 + rnd.nextInt(2 - 0 + 1);
				img = new Image("/images/dk2.jpg");
//				img = new Image("/images/dk3.jpg");
//				img = new Image("/images/dk4.jpg");
				setFill(new ImagePattern(img));
			}
			if(typeS == 3){
//				Random rnd = new Random(System.currentTimeMillis());
//				int number = 0 + rnd.nextInt(2 - 0 + 1);
				img = new Image("/images/dk5.jpg");
//				img = new Image("/images/dk3.jpg");
//				img = new Image("/images/dk4.jpg");
				setFill(new ImagePattern(img));
			}
		}
		Sprite(int x, int y, int w, int h, String type, Color color, String direction, int typeS, String address) {
			super(w, h, color);
			setDirection(direction);
			this.type = type;
			setTranslateX(x);
			setTranslateY(y);
			setAddress(address);
			Image img = null;
			if(typeS != 0){
				img = new Image("/images/p1.jpg");
				setFill(new ImagePattern(img));
			}
			if(typeS == 2){
//				Random rnd = new Random(System.currentTimeMillis());
//				int number = 0 + rnd.nextInt(2 - 0 + 1);
				img = new Image("/images/dk2.jpg");
//				img = new Image("/images/dk3.jpg");
//				img = new Image("/images/dk4.jpg");
				setFill(new ImagePattern(img));
			}
			if(typeS == 3){
//				Random rnd = new Random(System.currentTimeMillis());
//				int number = 0 + rnd.nextInt(2 - 0 + 1);
				img = new Image("/images/dt5.jpg");
//				img = new Image("/images/dk3.jpg");
//				img = new Image("/images/dk4.jpg");
				setFill(new ImagePattern(img));
			}
		}

		Sprite(int x, int y, int w, int h, String type, Color color, String direction, int typeS) {
			super(w, h, color);
			setDirection(direction);
			this.type = type;
			setTranslateX(x);
			setTranslateY(y);
			setAddress(address);
			Image img;
			if(typeS != 0){
				img = new Image("/images/p1.jpg");
				setFill(new ImagePattern(img));
			}
			if(typeS == 2){
				img = new Image("/images/dk2.jpg");
				setFill(new ImagePattern(img));
			}
		}
		public String getAddress() {
			return address;
		}

		public void setAddress(String address) {
			this.address = address;
		}

		void moveLeft() {
			setTranslateX(getTranslateX() - 5);
		}

		void moveRight() {
			setTranslateX(getTranslateX() + 5);
		}

		void moveUp() {
			setTranslateY(getTranslateY() - 5);
		}

		void moveDown() {
			setTranslateY(getTranslateY() + 5);
		}


		void moveLeft2() {
			setTranslateX(getTranslateX() - 5);
		}

		void moveRight2() {
			setTranslateX(getTranslateX() + 5);
		}

		void moveUp2() {
			setTranslateY(getTranslateY() - 5);
		}

		void moveDown2() {
			setTranslateY(getTranslateY() + 5);
		}
	}

	public static void main(String[] args) {
		launch(args);
	}




	@Override
	public void onConnectionReady(TCPConnection tcpConnection){
		// TODO Auto-generated method stub
		printMsg("connection ready...");
	}

	@Override
	public void onReceiveString(TCPConnection tcpConnection, String value) {

//		int dotPosition = value.indexOf('.');
//		String Str = new String("Разделяем эту строку на слова");
		System.out.println(value);
		if(value.startsWith("YourA")){
			System.out.println(value);
			String [] ad = value.split(" ");
			myAddress = ad[1];
			System.out.println(myAddress + " is my address");
			player.setAddress(myAddress);
		} else{
			Platform.runLater(() -> {
//					root.getChildren().add(players.get(myAddress));



		String [] newPlayer = value.split(" ");
			 if(newPlayer[0].equals("robots_shoot")){
				allEnemyShoot();
			} else
			 if(newPlayer[0].equals("9999_shoot")){
				 bigShot();
			 }
		else if(newPlayer[1].equals("SPACE")) {
				if (player.getAddress().equals(newPlayer[0])) {
				} else
					shoot(players.get(newPlayer[0]));
			}
		else if(newPlayer[1].equals("AI_robot")){
			String nameOfPlayer = newPlayer[0];
			int x = Integer.parseInt(newPlayer[2]);
			int y = Integer.parseInt(newPlayer[3]);
			String direct = "S";
			System.out.println(newPlayer + " enemy_bot arrived!");

			if (!enemies.containsKey(nameOfPlayer)) {
				enemies.put(nameOfPlayer, new Sprite(x, y, 40, 40, "robot", Color.BLUEVIOLET, direct, 2, nameOfPlayer));

			}
			enemies.get(nameOfPlayer).setTranslateX(x);
			enemies.get(nameOfPlayer).setTranslateY(y);
			enemies.get(nameOfPlayer).setDirection(direct);
			enemies.get(nameOfPlayer).setRotate(createRotation(enemies.get(nameOfPlayer).getDirection()));
			root.getChildren().remove(enemies.get(nameOfPlayer));
			root.getChildren().add(enemies.get(nameOfPlayer));
			System.out.println(enemies.keySet().size() + " number of robots.");

		}else if(newPlayer[0].equals("9999") || newPlayer[0].equals("6666") || newPlayer[0].equals("3333") || newPlayer[0].equals("4444") || newPlayer[0].equals("5555")|| newPlayer[0].equals("2222")|| newPlayer[0].equals("7777")){
				 String nameOfPlayer = newPlayer[0];
				 int x = Integer.parseInt(newPlayer[1]);
				 int y = Integer.parseInt(newPlayer[2]);
				 String direct = "S";
				 System.out.println(newPlayer + " enemy_bot arrived!");

				 if (!big.containsKey(nameOfPlayer)) {
					 big.put(nameOfPlayer, new Sprite(x, y, 80, 120, "playerB", Color.BLUEVIOLET, direct, 3, nameOfPlayer, 45));
				 }

				 big.get(nameOfPlayer).setTranslateX(x);
				 big.get(nameOfPlayer).setTranslateY(y);
//				 big.get(nameOfPlayer).setHp(5000);
				 big.get(nameOfPlayer).setDirection(direct);
				 big.get(nameOfPlayer).setRotate(createRotation(big.get(nameOfPlayer).getDirection()));
				 root.getChildren().remove(big.get(nameOfPlayer));
				 root.getChildren().add(big.get(nameOfPlayer));
				 System.out.println(big.keySet().size() + " number of bigs.");

			 }
		else{

			System.out.println(newPlayer[0] + " player is here!" + newPlayer[1] + " " + newPlayer[2] + " " + newPlayer[3]); // address x y direction
			String nameOfPlayer = newPlayer[0];
			int x = Integer.parseInt(newPlayer[1]);
			int y = Integer.parseInt(newPlayer[2]);
			String direct = newPlayer[3];
			System.out.println(newPlayer + " player is here!");

			if (player.getAddress().equals(nameOfPlayer)) {
			} else {
				if (!players.containsKey(nameOfPlayer)) {
					players.put(nameOfPlayer, new Sprite(x, y, 40, 40, "player", Color.BLUEVIOLET, direct, 1, nameOfPlayer));

				}

				players.get(nameOfPlayer).setTranslateX(x);
				players.get(nameOfPlayer).setTranslateY(y);
				players.get(nameOfPlayer).setDirection(direct);
				players.get(nameOfPlayer).setRotate(createRotation(players.get(nameOfPlayer).getDirection()));
				root.getChildren().remove(players.get(nameOfPlayer));
				root.getChildren().add(players.get(nameOfPlayer));
				System.out.println(players.keySet().size() + " number of players.");

			}
		}
		});



		printMsg(value + " val is");


		}
	}




	private void allEnemyShoot(){
		for (Sprite spr:
			 enemies.values()) {
			shoot(spr);
		}
	}

	private void bigShot(){
		for (Sprite spr:
				big.values()) {
			shoot(spr);
		}
	}
	private void enemyWasDestroyed(String address){
		System.out.println("bot was destroyed:////////////////////////////////// " + address);
		connection.sendString("dead "+ address);
	}

	public int createRotation(String direction){
		switch (direction) {
			case "A":
				return  270;

			case "D":
				return  90;

			case "W":
				return  0;

			case "S":
				return  180;
		}
		return 0;
	}

	@Override
	public void onDisconnect(TCPConnection tcpConnection) {
		// TODO Auto-generated method stub
		printMsg("connection closed");
	}

	@Override
	public void onException(TCPConnection tcpConnection, Exception e) {
		// TODO Auto-generated method stub
		printMsg("connection exception: " + e);
	}

	@FXML
	private void ActionPerformed(ActionEvent event) throws IOException {

	}



	private synchronized void printMsg(String msg) {
		System.out.println(msg);
	}



}