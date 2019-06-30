package ru.javabegin.training.spring.aop.objects;

import java.io.File;
import java.io.FilenameFilter;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.TreeSet;

import org.springframework.stereotype.Component;

@Component
public class FileManager {

	public Set<String> getExtensionList(String folder) {
		File dir = new File(folder);

		Set<String> extList = new TreeSet<>();

		for (String fileName : dir.list()) {  // an array of  files and folders in the current folder

			File file = new File(dir.getAbsolutePath() + "\\" + fileName);

			int i = fileName.lastIndexOf(".");
			if (file.isFile() && i != -1) {
				extList.add(fileName.substring(i + 1, fileName.length()).toLowerCase());     // get extensions 
			
			}
		}
//		System.out.println("current folder is " + folder);
		return extList;

	}

	public Map<String, Integer> getExtensionCount(String folder) {

		File dir = new File(folder);

		Map<String, Integer> map = new HashMap<>();

		for (String ext : getExtensionList(folder)) {           // extension list
			FilenameFilter filter = new CustomFileFilter(ext);
			map.put(ext, dir.listFiles(filter).length);     // extension == key, count == value
		}
		
//			System.out.println("Extension statistic: ");
//			
//		for(Entry<String, Integer> entry : map.entrySet()) {
//		    String key = entry.getKey();
//		    Integer value = entry.getValue();
//		    System.out.println(key + " " + value);
//	}
		
		return map;
}
}

