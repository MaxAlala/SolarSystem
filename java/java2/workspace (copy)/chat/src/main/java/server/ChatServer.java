package server;

import network.TCPConnection;
import network.TCPConnectionListener;

import java.net.ServerSocket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;


public class ChatServer implements TCPConnectionListener {
	private int counter = 0;

	public static void main(String[] args) {
		new ChatServer();
	}

	private final HashMap<String, TCPConnection> connections = new HashMap<>();
	private Thread thread;
	private Thread thread2;
	private Thread thread3;
	private HashMap<String, Sprite> enemies = new HashMap<>();
	private HashMap<String, Sprite> friends2= new HashMap<>();

	private void startPublishEnemies() {
		System.out.println("start to pub enemies");
		thread = new Thread(() -> {
			int count = 0;
			int x = 25;
			int y = 25;
			double betta = 0.75;
			int counter = 1;
			try {
				while (!thread.isInterrupted()) {
					count++;
					enemies.put(Integer.toString(count), new Sprite(Integer.toString(count), (int) (x + count % 7 * 100 * betta), y));
// 	enemies.add(new String[]{Integer.toString(count),"AI_robot", Integer.toString((x+count*20)), Integer.toString(y+count)});
					sendToAllConnection(enemies);

				  sendToAllConnection(new Sprite(Integer.toString(count), (int)(x + count%5*100*betta), y));


					sendToAllConnection("robots_shoot");
					if (count % 7 == 0) {

						betta = 0.5;
						y = y + 40;

					}else {
						 betta = 0.75;
					}

					if (y > 250) y = 30;
					System.out.println("pub new en! " + count);
					Thread.sleep(1000);
				}

			} catch (Exception e) {

			} finally {

			}

		});
		thread.start();

		thread2 = new Thread(() -> {
			int count = 0;
			int x = 250;
			int y = 770;
			double betta = 0.75;
			int counter = 1;
			try {
				while (!thread.isInterrupted()) {
//					y = -50;
//					x = 250;
//			sendToAllConnection(new Sprite("3333", x, y));
//	                 x = 150;
//	                 y = -30;
//					sendToAllConnection(new Sprite("6666", x, y));
//					  x = 70;
//					  y = -20;
//					sendToAllConnection(new Sprite("9999", x, y));
//
//
//                    x = 350;
//                    y = -20;
//                    sendToAllConnection(new Sprite("5555", x, y));
//
//                    x = 300;
//                    y = -20;
//                    sendToAllConnection(new Sprite("4444", x, y));
                    y = -20;
					for(int i =0; i< 150; i++){


						y += 7;
						sendToAllConnection(new Sprite("6666", 350, y));
                        sendToAllConnection(new Sprite("4444",  275, y));
                        sendToAllConnection(new Sprite("5555", 200, y));
						sendToAllConnection(new Sprite("9999", 125, y));
						sendToAllConnection(new Sprite("3333", 50, y));
                        sendToAllConnection(new Sprite("2222", 0, y));
                        sendToAllConnection(new Sprite("7777", 440, y));

						Thread.sleep(150);
						sendToAllConnection("9999_shoot");
					}

//				  sendToAllConnection(new Sprite(Integer.toString(count), (int)(x + count%5*100*betta), y));




//					if (y > 325) y = 30;
					System.out.println("pub new en! " + count);
					Thread.sleep(5000);
				}

			} catch (Exception e) {

			} finally {

			}

		});
		thread2.start();

//		thread3 = new Thread(() -> {
//			int count = 0;
//			int x = 25;
//			int y = 800;
//			double betta = 0.75;
//			int counter = 1;
//			try {
//				while (!thread.isInterrupted()) {
//					count++;
//					friends2.put(Integer.toString(count), new Sprite(Integer.toString(count), (int) (x + count % 7 * 100 * betta), y));
//// 	enemies.add(new String[]{Integer.toString(count),"AI_robot", Integer.toString((x+count*20)), Integer.toString(y+count)});
//					sendToAllConnection(friends2);
//
////				  sendToAllConnection(new Sprite(Integer.toString(count), (int)(x + count%5*100*betta), y));
//
//
//					sendToAllConnection("robots_shoot");
//					if (count % 7 == 0) {
//
//						if (counter == 1)
//							betta = 0.5;
//						else {
//							betta = 0.75;
//						}
//						y = y + 35;
//					}
//					if (y > 325) y = 30;
//					System.out.println("pub new en! " + count);
//					Thread.sleep(1500);
//				}
//
//			} catch (Exception e) {
//
//			} finally {
//
//			}
//
//		});
//		thread3.start();
	}

	private ChatServer() {         // server  waits connection and than create tcpConnection with client socket inside. After that put it in the arList.

		System.out.println("server running..."); // run thread with on receive . If have message than send it to all in collections.
		startPublishEnemies();
		try (ServerSocket serverSocket = new ServerSocket(8189)) {

			System.out.println(serverSocket.getInetAddress() + " " + serverSocket.getLocalSocketAddress() + " " + serverSocket.getReuseAddress() + " " + serverSocket.getChannel());


			while (true) {
				try {

					new TCPConnection(serverSocket.accept(), this); // wait and after create socket
				} catch (Exception e) {
					System.out.println("TCPConnection exc: " + e);
				}
			}

		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}


	@Override
	public synchronized void onConnectionReady(TCPConnection tcpConnection) {
		// TODO Auto-generated method stub

		connections.put(Integer.toString((++counter + 3000)), tcpConnection);
		System.out.println("4");
		System.out.println("YourA " + (counter + 3000));
		tcpConnection.sendString("YourA " + (counter + 3000));
//	sendToAllConnection("Client connected: " + tcpConnection);
	}


	@Override
	public synchronized void onReceiveString(TCPConnection tcpConnection, String value) {
		// TODO Auto-generated method stub
		String[] ad = value.split(" ");
		if (ad[0].equals("dead")) {
			enemies.remove(ad[1]);
			System.out.println("bot was deleted");
		} else {
			System.out.println("3");
			sendToAllConnection(value);
		}
	}


	@Override
	public synchronized void onDisconnect(TCPConnection tcpConnection) {
		// TODO Auto-generated method stub
//	sendToAllConnection("Client disconnected: " + tcpConnection);
//	connections.remove(tcpConnection);
		connections.values().remove(tcpConnection);
	}

	@Override
	public synchronized void onException(TCPConnection tcpConnection, Exception e) {
		// TODO Auto-generated method stub
		System.out.println("TCPConnection exception: " + e);
	}

	private void sendToAllConnection(String value) {
		System.out.println(value);
//	final int cnt = connections.size();
		System.out.println(connections.size() + " size");
		for (Map.Entry<String, TCPConnection> entry : connections.entrySet()) {
			System.out.println(entry.getKey() + " " + entry.getValue());
			entry.getValue().sendString(value);

//		connections.get(i).sendString(value);
		}
	}

	private void sendToAllConnection(HashMap<String, Sprite> ar) {

//	final int cnt = connections.size();
//		System.out.println(connections.size() + " size");
		for (Map.Entry<String, TCPConnection> entry : connections.entrySet()) {
			System.out.println(entry.getKey() + " " + entry.getValue());
			for (Sprite spr : ar.values()) {
				String str = spr.getAddress() + " " + spr.getType() + " " + spr.getX() + " " + spr.getY();
				System.out.println(str);
				entry.getValue().sendString(str);
			}

//		connections.get(i).sendString(value);
		}


	}




	private void sendToAllConnection(Sprite s) {

//	final int cnt = connections.size();
//		System.out.println(connections.size() + " size");
		for (Map.Entry<String, TCPConnection> entry : connections.entrySet()) {
			System.out.println(entry.getKey() + " " + entry.getValue());

			String str = s.getAddress() + " " + s.getX() + " " + s.getY();
			System.out.println(str);
			entry.getValue().sendString(str);


//		connections.get(i).sendString(value);
		}
	}
  
  
}
