package ru.javabegin.training.controllers;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.stereotype.Controller;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.SessionAttributes;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;
import org.springframework.web.servlet.view.RedirectView;

import ru.javabegin.training.exceptions.BadFileNameException;
import ru.javabegin.training.objects.UploadedFile;
import ru.javabegin.training.validators.FileValidator;

@Controller
@SessionAttributes("filename")        //session
public class FileController {

	@Autowired                        
	private FileValidator fileValidator;             //validator

	private static final Logger logger = LoggerFactory.getLogger(FileController.class);

	@RequestMapping(value = "/uploadFile", method = RequestMethod.POST)   //url path
	@ResponseBody
	public ModelAndView uploadFile(@ModelAttribute("uploadedFile") UploadedFile uploadedFile, BindingResult result) throws IOException, BadFileNameException {// имена параметров - как на форме jsp

		ModelAndView modelAndView = new ModelAndView();

		String fileName = null;
		
		
// the user is responsible for copying file contents to a session-level or persistent store 
		MultipartFile file = uploadedFile.getFile();
		fileValidator.validate(uploadedFile, result);

		if (result.hasErrors()) {
			modelAndView.setViewName("main");
		} else {

			byte[] bytes = file.getBytes();

			fileName = file.getOriginalFilename();

//			String rootPath = System.getProperty("catalina.home"); // save in the tomcat`s home folder
			String rootPath2 = "C:\\Users\\BETELGEIZE\\Desktop\\files"; // save in the tomcat`s home folder
			File dir = new File(rootPath2 + File.separator + "tmpFiles");

			if (!dir.exists()) {
				dir.mkdirs();
			}

			File loadFile = new File(dir.getAbsolutePath() + File.separator + fileName);

			BufferedOutputStream stream = new BufferedOutputStream(new FileOutputStream(loadFile));
			stream.write(bytes);
			stream.flush();
			stream.close();

			logger.info("uploaded: " + loadFile.getAbsolutePath());

			RedirectView redirectView = new RedirectView("fileuploaded");    // RPG sake
			redirectView.setStatusCode(HttpStatus.FOUND);
			modelAndView.setView(redirectView);
			modelAndView.addObject("filename", fileName);
 
			// throw new IOException("Folder not found!");                               // test sake
			// throw new BadFileNameException("Bad filename:" + fileName);

		}

		return modelAndView;
	}

	@RequestMapping(value = "/fileuploaded", method = RequestMethod.GET)     // rpg sake
	public String fileUploaded() {
		return "fileuploaded";
	}

	@ResponseStatus(value = HttpStatus.BAD_REQUEST, reason = "IOException exception! check arguments!")  // ioExceptions
	@ExceptionHandler(IOException.class)
	public void handleIOException() {
		logger.error("IOException handler executed");
	}

	@ExceptionHandler(BadFileNameException.class)
	public ModelAndView handleBadFileNameException(Exception ex) {            // badFileNameExecptions
		logger.error("IOException handler executed");
		ModelAndView modelAndView = new ModelAndView("error");
		modelAndView.addObject("error", ex.getMessage());
		return modelAndView;
	}

}
