package ru.javabegin.training.spring.aop.postprocessors;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;
import org.springframework.transaction.support.TransactionSynchronizationManager;

@Aspect
@Component
public class MyLogger {
	
	
	@Pointcut("execution(* ru.javabegin.training.spring.dao.impls.*.*(..))") // explicit package denotation
	private void allMethods() {     // pointcut method id
	};
	
	@Before("allMethods()")   //timer
	public void watchTime() {
		System.out.println(TransactionSynchronizationManager.isActualTransactionActive());
	}

}
