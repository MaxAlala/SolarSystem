package ru.javabegin.training.interceptors;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.handler.HandlerInterceptorAdapter;

import ru.javabegin.training.objects.User;

public class CheckUserInterceptor extends HandlerInterceptorAdapter { // implements HandlerInterceptor{

	
	
	
	@Override
	public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
		if (request.getRequestURI().contains("check-user")) {
			System.out.println("CheckUSER|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
			User user = (User) modelAndView.getModel().get("user");
	 		System.out.println(user.getName() + " " + user.isAdmin());
			if (user == null || !user.isAdmin()) {
				System.out.println("REGRET||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
				response.sendRedirect(request.getContextPath() + "/failed");
			}

		}
	}

}