package connection;

import data.ScoreElement;

import java.io.IOException;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Base64;
import java.util.Date;
import java.util.Locale;
import java.util.logging.Logger;

public class PostResults {     // GEMACHT ++++++++++++++++++++!

    private static Logger log = Logger.getLogger(PostResults.class.getName());// DONE +++++++++++++++++!

//    http POST http://127.0.0.1:8000/snippets/ code="print 123"
//    http://localhost:8080/RESTfulExample/json/product/post
//    http -a admin:password123 POST http://127.0.0.1:8000/snippets/ code="print 789"


//    "http://maximcastlerock2.pythonanywhere.com/snippets/"
//    static private SignUp signUp  = SignUp.getInstance();



    public static boolean postArray(ArrayList<ScoreElement> arrayList){
        if(StateOfauthentication.isIsSignedUp() == true){
            for(ScoreElement scoreElement: arrayList){
                if(postData(scoreElement.getScore(), scoreElement.getGameName()) == false){
                    return false;
                }
            }
        }
        return true;
    }


    public static boolean postData(int score, int game) {

        try {

            URL url = new URL("http://milkywayitis.pythonanywhere.com/api/new_record");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();

            String authString = StateOfauthentication.getLogin() + ":" + StateOfauthentication.getPassword();       // password, login
            String authStringEnc = new String(Base64.getEncoder().encodeToString(authString.getBytes()));
            conn.setRequestProperty("Authorization", "Basic " + authStringEnc);

            conn.setDoOutput(true);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/json");
//            String input = "{\"code\":555}";
            DateFormat format = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss", Locale.ENGLISH);
            Date date = new Date();
            date.toString();
            String date2 = format.format(date).toString();
            String[] date2Ar = date2.split(" ");
            date2 = date2Ar[0] + "T" + date2Ar[1] + "Z";


            String input = "{\"game_type\":"+game+", \"score\":"+ score +", \"date\":\""+date2+"\", \"username\":\""+ StateOfauthentication.getLogin()+"\"}";

            OutputStream os = conn.getOutputStream();
            os.write(input.getBytes());
            os.flush();

            if (conn.getResponseCode() != HttpURLConnection.HTTP_CREATED) {
                log.info("ERROR IN POSTING OF RESULTS.");
            }else{
                log.info("SUCCESS POSTING OF DATE.");
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

        }finally {
        }
        return  false;
    }

}
