package ru.javabegin.training.spring.aop.logging;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;
import java.util.Map.Entry;

import org.aspectj.lang.ProceedingJoinPoint;
import org.springframework.stereotype.Component;

@Component        // bean
public class MyLogger {

	public Object watchTime(ProceedingJoinPoint joinpoint) {
		long start = System.currentTimeMillis();
		System.out.println("method begin: " + joinpoint.getSignature().toShortString());  // name of a method
		Object output = null;
		for (Object iterable_element : joinpoint.getArgs()) {
			System.out.println("name of a folder: " + iterable_element);
		}
		
		try {
			output = joinpoint.proceed(); // invoke this method
		} catch (Throwable e) {
			e.printStackTrace();
		}

		long time = System.currentTimeMillis() - start;
		System.out.println("method end: " + joinpoint.getSignature().toShortString() + ", time=" + time + " ms");

		return output;
	}
	
//	public void printStatisticMap(Object obj) {
//		Map<String, Integer> map = (Map) obj;		
//		for(Entry<String, Integer> entry : map.entrySet()) {
//		    String key = entry.getKey();
//		    Integer value = entry.getValue();
//		    System.out.println(key + " " + value);
//	}
//		
//	}
//	
//	public void printStatisticSet(Object obj) {
//		Set<String> extList = (Set) obj;	
//	for (String string : extList) {
//		System.out.println(string);
//		}
//	}
	public void printStatistic(Object obj) {
		if(obj instanceof Map) {
			System.out.println("MapCode: ");
			Map<String, Integer> map = (Map) obj;		
			for(Entry<String, Integer> entry : map.entrySet()) {
				String key = entry.getKey();
				Integer value = entry.getValue();
				System.out.println("name of an extension: "+key + "  count of the extension: " + value);
			}
			
		} else
			if(obj instanceof Set) {
				System.out.println("SetCode: ");
				Set<String> extList = (Set) obj;	
				for (String string : extList) {
					System.out.println(string);
				}
			}
	}
	

}
