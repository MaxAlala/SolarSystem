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
			output = joinpoint.proceed(new Object[] { "c:\\Python36" });
		} catch (Throwable e) {
			e.printStackTrace();
		}

		long time = System.currentTimeMillis() - start;
		System.out.println("method end: " + joinpoint.getSignature().toShortString() + ", time=" + time + " ms <<");

		return output;
	}

	@SuppressWarnings("rawtypes")
	@AfterReturning(pointcut = "allMethods() && execution(java.util.Map *(String)) && args(folder)", returning = "obj")
	public void printMap(Object obj, String folder) {

		System.out.println("Printing map >>");
		System.out.println("Folder = " + folder);
		Map map = (Map) obj;
		for (Object object : map.keySet()) {
			System.out.println("key=" + object + ", " + map.get(object));
		}

		System.out.println("End printing map <<");
		System.out.println();

	}

	@SuppressWarnings("rawtypes")
	@AfterReturning(pointcut = "allMethods() && execution(java.util.Set *(String)) && args(folder)", returning = "obj")
	public void printSet(Object obj, String folder) {

		System.out.println("Printing set >>");
		System.out.println("Folder = " + folder);
		Set set = (Set) obj;
		for (Object object : set) {
			System.out.println(object);
		}

		System.out.println("End printing set <<");
		System.out.println();

	}

}
