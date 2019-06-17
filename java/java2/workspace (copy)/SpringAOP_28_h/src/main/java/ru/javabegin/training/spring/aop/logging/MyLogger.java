package ru.javabegin.training.spring.aop.logging;

import java.util.Map;
import java.util.Set;

import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.AfterReturning;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;

@Component
@Aspect
public class MyLogger {

	@Pointcut("execution(* ru.javabegin.training.spring.aop.objects.Manager.*(..))")
	private void allMethods() {
	};

	@Around("allMethods() && execution(java.util.Map *(..))")
	public Object watchTime(ProceedingJoinPoint joinpoint) {
		long start = System.currentTimeMillis();
		System.out.println("method begin: " + joinpoint.getSignature().toShortString() + " >>");
		Object output = null;

		for (Object object : joinpoint.getArgs()) {
			System.out.println("Param : " + object);
		}

		try {
			output = joinpoint.proceed();
		} catch (Throwable e) {
			e.printStackTrace();
		}

		long time = System.currentTimeMillis() - start;
		System.out.println("method end: " + joinpoint.getSignature().toShortString() + ", time=" + time + " ms <<");
		System.out.println();

		return output;
	}

	@AfterReturning(pointcut = "allMethods() && execution(java.util.Map *(..))", returning = "obj")
	public void printMap(Object obj) {

		System.out.println("Printing map >>");

		Map map = (Map) obj;
		for (Object object : map.keySet()) {
			System.out.println("key=" + object + ", " + map.get(object));
		}

		System.out.println("End printing map <<");
		System.out.println();

	}

	@AfterReturning(pointcut = "allMethods() && execution(java.util.Set *(..))", returning = "obj")
	public void printSet(Object obj) {

		System.out.println("Printing set >>");
		Set set = (Set) obj;
		for (Object object : set) {
			System.out.println(object);
		}

		System.out.println("End printing set <<");
		System.out.println();

	}

}
