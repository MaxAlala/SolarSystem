package starter;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.sql.*;
import java.util.Base64;

public class DateBaseRequest {
    public  boolean isThere(String mail, String password) {
        return true;
        //try {

           /* URL url = new URL("http://maximcastlerock.pythonanywhere.com/account/snippets/");
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            String login;
            String parol;
            String authString = mail + ":" + password;       // password, login
            String authStringEnc = new String(Base64.getEncoder().encodeToString(authString.getBytes()));
            conn.setRequestProperty("Authorization", "Basic " + authStringEnc);
            conn.setDoOutput(true);
            conn.setRequestMethod("POST");
            conn.setRequestProperty("Content-Type", "application/json");
            String input = "{\"code\":1234}";
            OutputStream os = conn.getOutputStream();
            os.write(input.getBytes());
            os.flush();
            if (conn.getResponseCode() != HttpURLConnection.HTTP_CREATED) {
                throw new RuntimeException("Failed : HTTP error code : "
                        + conn.getResponseCode());
            }

            BufferedReader br = new BufferedReader(new InputStreamReader(
                    (conn.getInputStream())));

            String output;
            System.out.println("Output from Server .... \n");
            while ((output = br.readLine()) != null) {
                System.out.println(output);
            }

            conn.disconnect();

        } catch (MalformedURLException e) {

            e.printStackTrace();

        } catch (IOException e) {

            e.printStackTrace();

        }

        return true;
        */
    }
}

