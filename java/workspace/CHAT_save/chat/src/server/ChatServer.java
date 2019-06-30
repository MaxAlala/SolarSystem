package server;

import network.TCPConnection;
import network.TCPConnectionListener;

import java.net.ServerSocket;
import java.util.ArrayList;


public class ChatServer implements TCPConnectionListener {
  public static void main(String[] args) {
	  new ChatServer();
  }
  
  private final ArrayList<TCPConnection> connections = new ArrayList<>();
  
  
  private ChatServer( ) {         // server  waits connection and than create tcpConnection with client socket inside. After that put it in the arList.
	  System.out.println("server running..."); // run thread with on receive . If have message than send it to all in collections.
	 try(ServerSocket serverSocket = new ServerSocket(8189)){
			 
		while(true) {
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
	connections.add(tcpConnection);
	System.out.println("4");
	sendToAllConnection("Client connected: " + tcpConnection);
	
}


@Override
public synchronized void onReceiveString(TCPConnection tcpConnection, String value) {
	// TODO Auto-generated method stub
	System.out.println("3");
	sendToAllConnection(value);
}


@Override
public synchronized void onDisconnect(TCPConnection tcpConnection) {
	// TODO Auto-generated method stub
	sendToAllConnection("Client disconnected: " + tcpConnection);
	connections.remove(tcpConnection);
}

@Override
public synchronized void onException(TCPConnection tcpConnection, Exception e) {
	// TODO Auto-generated method stub
	System.out.println("TCPConnection exception: " + e);
}

private void sendToAllConnection(String value) {
	System.out.println(value);
	final int cnt = connections.size();
	for (int i = 0; i < cnt; i++) {
		
		connections.get(i).sendString(value);
	}
}
  
  
  
  
  
  
}
