package somePackage.servlets;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import somePackage.beans.Author;
import somePackage.beans.AuthorList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.OutputStream;

/**
 *
 * @author Tim
 */
public class ShowPersonImage extends HttpServlet {

    /**
     * Processes requests for both HTTP
     * <code>GET</code> and
     * <code>POST</code> methods.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        System.out.println(999999999);
        response.setContentType("image/jpeg");
        OutputStream out = response.getOutputStream();
        try {
//            int index = Integer.valueOf(request.getParameter("index"));
            AuthorList authorList = new AuthorList();
            String name = null;
//            String name2 = (String) request.getParameter("name2");

//
//            if(name2 == null) {
                name = (String) request.getSession().getAttribute("nameImage");
                System.out.println("name1" + name);
                Author author = authorList.getAuthorByName(name);
                response.setContentLength(author.getImage().length);
                out.write(author.getImage());
//            } else {
//                System.out.println("name2 " + name2);
//                Author author2 = authorList.getAuthorByName(name2);
//                response.setContentLength(author2.getImage().length);
//                out.write(author2.getImage());
//            }

        }catch (Exception ex){
            ex.printStackTrace();
        } finally {
            out.close();
        }
    }

    // <editor-fold defaultstate="collapsed" desc="HttpServlet methods. Click on the + sign on the left to edit the code.">
    /**
     * Handles the HTTP
     * <code>GET</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Handles the HTTP
     * <code>POST</code> method.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    /**
     * Returns a short description of the servlet.
     *
     * @return a String containing servlet description
     */
    @Override
    public String getServletInfo() {
        return "Short description";
    }// </editor-fold>
}
