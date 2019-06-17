package ru.javabegin.training.spring.main;

import java.util.ArrayList;
import java.util.List;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

import ru.javabegin.training.spring.dao.impls.SQLiteDAO;
import ru.javabegin.training.spring.dao.objects.MP3;

public class Start {

	public static void main(String[] args) {
//		MP3 firstMP3 = new MP3();
//		firstMP3.setName("Sonne");
//		firstMP3.setAuthor("Greta");
//		
//
//		MP3 secondMP3 = new MP3();
//		secondMP3.setName("Wall");
//		secondMP3.setAuthor("Black");
		
		MP3 firstMP3 = new MP3();
		firstMP3.setName("Sonne222");
		firstMP3.setAuthor("Greta");
		firstMP3.setId(39);

		MP3 secondMP3 = new MP3();
		secondMP3.setName("Wall");
		secondMP3.setAuthor("Black999");
		secondMP3.setId(40);
		
		List<MP3> list = new ArrayList<>();

		list.add(firstMP3);
		list.add(secondMP3);

		// new SQLiteDAO().insertWithJDBC(mp3);

		ApplicationContext context = new ClassPathXmlApplicationContext("context.xml");
		SQLiteDAO sqLiteDAO = (SQLiteDAO) context.getBean("sqliteDAO");

//		System.out.println(sqLiteDAO.insertList(list));
		System.out.println(sqLiteDAO.batchUpdate(list));
	}
}
