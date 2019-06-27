package com.example.sweater.controller;

import com.example.sweater.domain.Group;
import com.example.sweater.domain.Message;
import com.example.sweater.domain.User;
import com.example.sweater.domain.dto.MessageDto;
import com.example.sweater.repos.ChatMessageRepo;
import com.example.sweater.repos.GroupRepo;
import com.example.sweater.repos.MessageRepo;
import com.example.sweater.repos.SkillRepo;
import com.example.sweater.service.MessageService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.security.core.annotation.AuthenticationPrincipal;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import org.springframework.web.util.UriComponents;
import org.springframework.web.util.UriComponentsBuilder;

import javax.validation.Valid;
import java.io.File;
import java.io.IOException;
import java.util.*;


@Controller
public class MainController {

    @Autowired
    private MessageService messageService;
    @Autowired
    private MessageRepo messageRepo;
    private ChatMessageRepo chatMessageRepo;
    @Autowired
    GroupRepo groupRepo;
    @Autowired
    SkillRepo skillRepo;
    @Autowired
    public MainController(ChatMessageRepo chatMessageRepo) {
        this.chatMessageRepo = chatMessageRepo;
    }


    @Value("${upload.path}")
    private String uploadPath;

    @GetMapping("/chat")
    public String main(Model model, @AuthenticationPrincipal User user) {
        HashMap<Object, Object> data = new HashMap<>();
        if(user!=null) {
            data.put("profile", user);
            data.put("messages", chatMessageRepo.findAll());
        }
        model.addAttribute("frontendData", data);
        System.out.println("hello! Index.");
        return "index";
    }


    @GetMapping("/main/group/{group}")
    public String getgroup(
            @RequestParam(required = false, defaultValue = "") String filter,
            @AuthenticationPrincipal User cur_user,
            Model model,
            @PathVariable long group) {

        Optional<Group> gr = groupRepo.findById(group);
        System.out.println(gr.get().getName() + "//////////////////////////////");
        model.addAttribute("group",groupRepo.findById(group).get());
        System.out.println();
        return "group";
    }


    @GetMapping("/")
    public String greeting(Map<String, Object> model) {
        return "greeting";
    }

    @GetMapping("/main")
    public String main(@RequestParam(required = false, defaultValue = "") String filter, Model model,
                       Pageable pageable,
                       @AuthenticationPrincipal User  user) {
        Page<MessageDto> page =  messageService.messageList(pageable, filter, user);

        System.out.println(page.getTotalElements() + "all elements!!!!!!!!!!!!!!!!!!!!!!1");

        model.addAttribute("page", page);
        model.addAttribute("url", "/main");
        model.addAttribute("filter", filter);
        return "main";
    }

    @GetMapping("/main/{user}")
    public String mainUser_Id(
            @RequestParam(required = false, defaultValue = "") String filter,
            @AuthenticationPrincipal User cur_user,
            Model model,
            @PathVariable User user,
            Pageable pageable) {
        Page<MessageDto> page = null;

        if (filter != null && !filter.isEmpty()) {

//            messages = messageRepo.findByTag(filter);
            page = messageRepo.findByTagAndAuthor(filter, user, pageable);
        } else {

            page = messageRepo.findByAuthor(user, pageable);
        }
//        System.out.println( "////////////////\\\\\\\\\\\\///////////\\\\\\\\/////////Hello! " + page.getContent());
//        System.out.println(page.getContent().get(0).getId() + "////////////////\\\\\\\\\\\\///////////\\\\\\\\/////////Hello! " + page.getContent().get(0).getAuthor());

        model.addAttribute("page", page);
        model.addAttribute("url", "/main");
        model.addAttribute("messages", page);
        model.addAttribute("filter", filter);
        model.addAttribute("userChannel", user);
        model.addAttribute("subscriptionsCount", user.getSubscriptions().size());
        model.addAttribute("subscribersCount", user.getSubscribers().size());
        System.out.println(user.getSubscribers().size());
        model.addAttribute("isSubscriber", user.getSubscribers().contains(cur_user));
        System.out.println( user.getSubscribers().contains(cur_user));
        model.addAttribute("isCurrentUser", cur_user.equals(user));
        model.addAttribute("group",groupRepo.findUsersGroup(user.getId()));
        model.addAttribute("skill",skillRepo.findUsersSkills(user.getId()));
//        System.out.println("i am HEEEEEEEEEEEEEEEEEEEEEEEEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE33399992s");

        return "main";
    }


    // request param = get info from form or URL param
    @PostMapping("/main/{user}")
    public String add2(
            @PathVariable User user,
    @RequestParam("file") MultipartFile file,
            @AuthenticationPrincipal User cur_user,
            @Valid Message message,
            BindingResult bindingResult,
            Model model
    ) throws IOException {
        System.out.println("i am HEEEEEEEEEEEEEEEEEEEEEEEEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE3339999");
        return getString(file, cur_user, message, bindingResult, model, user);
    }

    @PostMapping("/main")
    public String add(
            @RequestParam("file") MultipartFile file,
            @AuthenticationPrincipal User cur_user,
            @Valid Message message,
            BindingResult bindingResult,
            Model model
    ) throws IOException {
//        System.out.println("i am HEEEEEEEEEEEEEEEEEEEEEEEEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE333");
        return getString(file, cur_user, message, bindingResult, model, null);
    }



    @PostMapping("/maindelete")
    public String delete(
            @Valid Message message,
            Model model,
            Pageable pageable,
            @AuthenticationPrincipal User  user
    ) {

        Page<MessageDto> page =  messageService.messageList(pageable, null, user);
        System.out.println(message.getAuthorName() + "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!||| " + message.getText() + " " + message.getId());
        messageRepo.delete(message);
//        message = null;

//        for(Message msg: messages){
//            System.out.println(msg.getAuthor() + " " + msg.getText());
//        }
        model.addAttribute("messages", page);
        model.addAttribute("url", "/main");


        return "redirect:/main";
    }


    @PostMapping("/mainchange")
    public String update(
            @RequestParam("file") MultipartFile file,
            @AuthenticationPrincipal User user,
            @Valid Message message,
            BindingResult bindingResult,
            Model model
    ) throws IOException {


        System.out.println(message.getFilename());
        System.out.println(file.getOriginalFilename() + "HEYs " + message.getId() );
        return getString(file, user, message, bindingResult, model,null);
    }

    private String getString(@RequestParam("file") MultipartFile file, @AuthenticationPrincipal User cur_user, @Valid Message message, BindingResult bindingResult, Model model, User user) throws IOException {
        message.setAuthor(cur_user);


        if (bindingResult.hasErrors()) {
            Map<String, String> errorsMap = ControllerUtils.getErrors(bindingResult);
            model.mergeAttributes(errorsMap);
            model.addAttribute("message", message);
            System.out.println("/////////222");
        } else {


            if (file != null && !file.getOriginalFilename().isEmpty()) {
                File uploadDir = new File(uploadPath);

                if (!uploadDir.exists()) {
                    uploadDir.mkdir();
                }

                String uuidFile = UUID.randomUUID().toString();
                String resultFileName = uuidFile + "." + file.getOriginalFilename();
                System.out.println(uploadPath + "/////////");
                System.out.println(resultFileName + "/////////");

                file.transferTo(new File(uploadPath + "\\" + resultFileName));
                message.setFilename(resultFileName);
            }
            System.out.println( "/////////333");
            model.addAttribute("message", null);
            System.out.println(message.getFilename());
            messageRepo.save(message);

        }
        Iterable<Message> messages = messageRepo.findAll();
        model.addAttribute("messages", messages);
        if(user != null) return "redirect:/main/{user}"; else
         return "redirect:/main";
    }

    @GetMapping("/messages/{message}/like")
    public void like(
            @AuthenticationPrincipal User cur_user,
            @PathVariable Message message,
            RedirectAttributes redirectAttributes,
            @RequestHeader(required = false) String referer
            ) {
        Set<User> likes = message.getLikes();

        if(likes.contains(cur_user)) {
            likes.remove(cur_user);
        }else {
            likes.add(cur_user);
        }


        UriComponents uriComponents = UriComponentsBuilder.fromHttpUrl(referer).build();
        uriComponents.getQueryParams()
                .entrySet()
                .forEach(pair -> redirectAttributes.addAttribute(pair.getKey(), pair.getValue()));
//        return "redirect:" + uriComponents.getPath();
    }


}
