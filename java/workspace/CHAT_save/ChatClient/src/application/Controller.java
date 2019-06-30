package application;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;


import com.vse.network.TCPConnection;
import com.vse.network.TCPConnectionListener;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;



  

public class Controller implements TCPConnectionListener, Initializable {
	
	
	
	@FXML
	private TextField input1;
	@FXML
	private Button button1;
	@FXML
	private TextField input2;
	@FXML
	private TextArea text;
	
	TCPConnection connection;
	@Override
	public void onConnectionReady(TCPConnection tcpConnection) {
		// TODO Auto-generated method stub
		printMsg("connection ready...");
	}

	@Override
	public void onReceiveString(TCPConnection tcpConnection, String value) {
		printMsg(value);
		
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
		System.out.println("tsetsetse");
		String msg = input1.getText();
		if(msg.equals("")) return;
		input1.setText(null);
		connection.sendString(input2.getText() + ": " + msg);
    }
	
	@FXML
    private void signUp2(ActionEvent event) throws IOException {
  
    }
	
	private synchronized void printMsg(String msg) {
		Platform.runLater(() -> {

			text.appendText(msg + "\n");
//	 awesome short !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		});
//
//		Platform.runLater(new Runnable() {
//			@Override
//			public void run() {
//
//				text.appendText(msg + "\n");
////				text.setText(msg + "\n");
//			}
//		});
	}

	@Override
	public void initialize(URL location, ResourceBundle resources) {

      try {
		 connection = new TCPConnection(this, "192.168.1.235", 8189);
	} catch (IOException e) {

		e.printStackTrace();
		
	}
	}
	
	

}
