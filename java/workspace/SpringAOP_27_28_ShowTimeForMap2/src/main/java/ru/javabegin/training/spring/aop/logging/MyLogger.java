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
//	&& within(ru.javabegin.training.spring.aop.objects.*)
	@Pointcut("execution(java.util.Map *(..))") // explicit package denotation
	private void allMethods() {     // pointcut method id
	};
	
	@Pointcut("execution(java.util.Set *(..))") // explicit package denotation
	private void allMethods2() {     // pointcut method id
	};
	
	@Pointcut("execution(* *(..))") // explicit package denotation
	private void allMethods3() {     // pointcut method id
	};

	@Around("allMethods2() && @annotation(ru.javabegin.training.spring.aop.annotations.ShowTime)")   //timer
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

	@AfterReturning(pointcut = "allMethods2() &&  @annotation(ru.javabegin.training.spring.aop.annotations.ShowResult)", returning = "obj")
	public void printSet(Object obj) {        //printerSet

		System.out.println("Print info begin >>");

			Set set = (Set) obj;
			for (Object object : set) {
				System.out.println(object);
			}

		System.out.println("Print info end <<");
		System.out.println();

	}
	
	@AfterReturning(pointcut = "allMethods() &&  @annotation(ru.javabegin.training.spring.aop.annotations.ShowResult)", returning = "obj")
	public void printMap(Object obj) {      // printerMap

		System.out.println("Print info begin >>");

			Map map = (Map) obj;
			for (Object object : map.keySet()) {
				System.out.println("key=" + object + ", " + map.get(object));
			}
			System.out.println("Print info end <<");
			System.out.println();
		}

}
