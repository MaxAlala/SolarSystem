package connection;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;
import java.util.Base64;
import java.util.List;
import java.util.logging.Logger;

public class SignIn {
    private static Logger log = Logger.getLogger(SignIn.class.getName());// DONE +++++++++++++++++!
//    private final String baseUrl;
//    private final String username;
//    private final String password;
//
//    public SignIn(String baseUrl, String username, String password) {
//        this.baseUrl = baseUrl;
//        this.username = username;
//        this.password = password;
//        getDataFromServer(baseUrl);
//    }

//    public String getRESTResponse(String accountId){
//       return getDataFromServer("account/" + accountId);
//    }

    public static boolean signIn(String login, String password) {

        try {

            URL url = new URL("http://milkywayitis.pythonanywhere.com/api/new_record");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();

            String authString = login + ":" + password;       // password, login
            String authStringEnc = new String(Base64.getEncoder().encodeToString(authString.getBytes()));
            conn.setRequestProperty("Authorization", "Basic " + authStringEnc);

            conn.setDoOutput(true);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/json");
//            String input = "{\"code\":555}";
            String input = "{\"game_type\":5, \"score\":555, \"date\":\"9999-01-29T12:12:12Z\", \"username\":\""+StateOfauthentication.getLogin()+"\"}";

            OutputStream os = conn.getOutputStream();
            os.write(input.getBytes());
            os.flush();

            if (conn.getResponseCode() != HttpURLConnection.HTTP_CREATED) {
                log.info("NOT SUCH ACCOUNT! ERROR IN SIGN IN");
            }else{
                log.info("SUCCESS AUTH. OF CLIENT.");
                StateOfauthentication.setLogin(login);
                StateOfauthentication.setPassword(password);
                StateOfauthentication.setIsSignedUp(true);
                conn.disconnect();
                return true;
            }

//            BufferedReader br = new BufferedReader(new InputStreamReader(
//                    (conn.getInputStream())));
//
//            String output;
//            System.out.println("Output from Server .... \n");
//            while ((output = br.readLine()) != null) {
//                System.out.println(output);
//            }



        } catch (MalformedURLException e) {

            e.printStackTrace();

        } catch (IOException e) {

            e.printStackTrace();

        }
        return  false;
    }


//    private URLConnection setUsernamePassword(URL url) throws IOException {
//        URLConnection urlConnection = url.openConnection();
//        String authString = username + ":" + password;
//        String authStringEnc = new String(Base64.getEncoder().encodeToString(authString.getBytes()));
//        urlConnection.setRequestProperty("Authorization", "Basic " + authStringEnc);
//        return urlConnection;
//    }
}