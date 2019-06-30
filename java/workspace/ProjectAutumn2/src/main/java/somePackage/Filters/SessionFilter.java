package somePackage.Filters;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

public class SessionFilter implements javax.servlet.Filter
{

//    private ArrayList<String> urlList;

    public void destroy() {

    }

    public void doFilter(ServletRequest req, ServletResponse res, FilterChain chain)
            throws IOException, ServletException {

        HttpServletRequest request = (HttpServletRequest) req;
        HttpServletResponse response = (HttpServletResponse) res;

            HttpSession session = request.getSession(false);
            if (session == null) {
                response.sendRedirect("http://localhost:8080/");
            } else if (session.getAttribute("fio") == null) {
                    response.sendRedirect("http://localhost:8080/");
        } else chain.doFilter(req, res);
    }


    public void init(FilterConfig fConfig) throws ServletException {

    }

}