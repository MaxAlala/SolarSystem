package ru.javabegin.training.spring.aop.main;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import ru.javabegin.training.spring.aop.objects.FileManager;

public class Start {

	public static void main(String[] args) {
		ApplicationContext context = new ClassPathXmlApplicationContext("context.xml");
		FileManager fileUtil = (FileManager) context.getBean("fileManager");
		fileUtil.getExtensionCount("c:\\Windows\\System32");
		fileUtil.getExtensionCount("c:\\Windows\\");
	}
}
