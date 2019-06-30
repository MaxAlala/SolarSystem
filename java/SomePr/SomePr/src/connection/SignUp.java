package connection;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Base64;
import java.util.logging.Logger;

public class SignUp {      // REGISTRATION, INCLUDE STATE - IF REGISTRATION WAS SUCCESS THAN TRUE ELSE FALSE
    private static Logger log = Logger.getLogger(SignUp.class.getName());
//    http POST http://127.0.0.1:8000/snippets/ code="print 123"
//    http://localhost:8080/RESTfulExample/json/product/post
//    http -a admin:password123 POST http://127.0.0.1:8000/snippets/ code="print 789"


//    "http://maximcastlerock2.pythonanywhere.com/snippets/"

//     private static SignUp instance = new SignUp();
//     private static String currentName = "max22";
//
//     private static String currentPassword = "1234qwer";
//     public static boolean state = true;       // is signup had success?
//
//     public static String getCurrentName() {
//         return currentName;
//     }
//
//     public static String getCurrentPassword() {
//         return currentPassword;
//     }
//
//     public static boolean isState() {
//         return state;
//     }
//
//     SignUp() {
//
//    }

//    public static SignUp getInstance(){
//        return instance;
//    }
//public static boolean signUp(String name, String password) {
//
//        try {
////            "http://maximcastlerock.pythonanywhere.com/account/register2/"
//            URL url = new URL("http://127.0.0.1:8000/account/register2/");
//            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
//
////            String authString = "admin" + ":" + "1234qwer";       // password, login
////            String authStringEnc = new String(Base64.getEncoder().encodeToString(authString.getBytes()));
////            conn.setRequestProperty("Authorization", "Basic " + authStringEnc);
//
//            conn.setDoOutput(true);
//            conn.setRequestMethod("POST");
//            conn.setRequestProperty("Content-Type", "application/json");
////            "{\"username\":\"maxim\",\"email\":\"amax209@gmail.com\",\"password\":\"1234qwer\",\"password2\":\"1234qwer\"}"
//            String input = "{\"username\":\""+ name + "\", \"password\":\""+ password +"\"}";
//// code="print 123
//            OutputStream os = conn.getOutputStream();
//            os.write(input.getBytes());
//            os.flush();
//
//            if (conn.getResponseCode() != HttpURLConnection.HTTP_CREATED) {
//                throw new RuntimeException("Failed : HTTP error code : "
//                        + conn.getResponseCode());
//            } else {
//                System.out.println("register was success");
//                StateOfauthentication.setLogin(name);
//                StateOfauthentication.setPassword(password);
//                StateOfauthentication.setIsSignedUp(true);
//                conn.disconnect();
//                return true;
//            }
//
////            BufferedReader br = new BufferedReader(new InputStreamReader(
////                    (conn.getInputStream())));
////
////            String output;
////            System.out.println("Output from Server .... \n");
////            while ((output = br.readLine()) != null) {
////                System.out.println(output);
////            }
//        } catch (MalformedURLException e) {
//
//            e.printStackTrace();
//
//        } catch (IOException e) {
//
//            e.printStackTrace();
//        }
//    return false;
//    }

    public static boolean signUp(String name, String password){
        try {
//            "http://maximcastlerock.pythonanywhere.com/account/register2/"
            URL url = new URL("http://milkywayitis.pythonanywhere.com/api/users/register/");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();

//            String authString = "admin" + ":" + "1234qwer";       // password, login
//            String authStringEnc = new String(Base64.getEncoder().encodeToString(authString.getBytes()));
//            conn.setRequestProperty("Authorization", "Basic " + authStringEnc);

            conn.setDoOutput(true);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/json");
//            "{\"username\":\"maxim\",\"email\":\"amax209@gmail.com\",\"password\":\"1234qwer\",\"password2\":\"1234qwer\"}"
            String input = "{\"username\":\""+ name + "\", \"password\":\""+ password +"\"}";
// code="print 123
            OutputStream os = conn.getOutputStream();
            os.write(input.getBytes());
            os.flush();

            if (conn.getResponseCode() != HttpURLConnection.HTTP_CREATED) {
                log.info("SOME ERROR IN SIGN UP!");
            } else{
                log.info("SUCCESS REGISTER OF CLIENT.");
                StateOfauthentication.setLogin(name);
                StateOfauthentication.setPassword(password);
                StateOfauthentication.setIsSignedUp(true);
                conn.disconnect();
                return true;
            }

//                 BufferedReader br = new BufferedReader(new InputStreamReader(
//                         (conn.getInputStream())));
//
//                 String output;
//                 System.out.println("Output from Server .... \n");
//                 while ((output = br.readLine()) != null) {
//                     System.out.println(output);
//                 }



        } catch (MalformedURLException e) {

            e.printStackTrace();

        } catch (IOException e) {

            e.printStackTrace();

        }
        return false;

    }


}


