import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

import com.vse.network.TCPConnection;
import com.vse.network.TCPConnectionListener;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

//import static com.sun.org.apache.xerces.internal.util.PropertyState.is;
import static org.hamcrest.core.Is.is;
import static org.junit.Assert.*;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;

public class Tests implements TCPConnectionListener {

//    @Before
//    public void before() {
//        System.out.println("@Before");
//        Thread myThread = new Thread() {
//            public void run() {
//                System.out.println("@Before myThread run()");
//                Socket myServerSocket = null;
//                try {
//                    ServerSocket myServer = new ServerSocket(8189);
//                    System.out
//                            .println("@Before myThread run() - server socket created.");
//                    myServerSocket = myServer.accept();
//                    System.out
//                            .println("@Before myThread run() - accepted connection");
//                } catch (IOException e) {
//                    e.printStackTrace();
//                }
//            }
//        };
//        myThread.start();
//    }

    @Test
    public void test1() throws Exception {
        System.out.println("test1");
        synchronized (this) {
            try {
                wait(1000);
            } catch (InterruptedException e) {
                // do nothing.
            }
        }
        System.out.println("test1 - after wait");
        new Socket("10.17.1.69", 8189);
        synchronized (this) {
            try {
                wait(1000);
            } catch (InterruptedException e) {
                // do nothing.
            }
        }
        System.out.println("test1 - after second wait");
    }

    @Test
    public void test2() throws IOException {



        Socket s = new Socket("10.17.1.69", 8189);
        BufferedReader input =
                new BufferedReader(new InputStreamReader(s.getInputStream()));
        String answer = input.readLine();

        assertEquals("YourA 3002",answer);
        }

    @Test
    public void test3() throws IOException, InterruptedException {



        ArrayList<String> ar = new ArrayList();
        Socket s = new Socket("10.17.1.69", 8189);


        BufferedReader input =
                new BufferedReader(new InputStreamReader(s.getInputStream()));
//        String answer = input.readLine();
        int counter = 20;
        while(counter > 0){
            Thread.sleep(100);
            ar.add(input.readLine());
            counter--;
        }
        assertTrue(ar.contains("1 AI_robot 100 25"));
//        assertEquals("YourA 3001", answer); // address of the first player!
    }


    @Test
    public void test4() throws IOException, InterruptedException {

        ArrayList<String> ar = new ArrayList();
        Socket s = new Socket("10.17.1.69", 8189);


        BufferedReader input =
                new BufferedReader(new InputStreamReader(s.getInputStream()));
//        String answer = input.readLine();
        int counter = 100;
        while(counter > 0){

            ar.add(input.readLine());
            counter--;
            Thread.sleep(100);
        }

        assertTrue(ar.contains("robots_shoot"));
        assertTrue(ar.contains("9999_shoot"));
//        assertEquals("YourA 3001", answer); // address of the first player!

    }


    @Override
    public void onConnectionReady(TCPConnection tcpConnection) {

    }

    @Override
    public void onReceiveString(TCPConnection tcpConnection, String value) {

    }

    @Override
    public void onDisconnect(TCPConnection tcpConnection) {

    }

    @Override
    public void onException(TCPConnection tcpConnection, Exception e) {

    }

}
