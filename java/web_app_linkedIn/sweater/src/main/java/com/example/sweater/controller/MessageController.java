package com.example.sweater.controller;

import com.example.sweater.domain.ChatMessage;
import com.example.sweater.domain.Views;
import com.example.sweater.domain.dto.EventType;
import com.example.sweater.domain.dto.ObjectType;
import com.example.sweater.repos.ChatMessageRepo;
import com.example.sweater.repos.MessageRepo;
import com.example.sweater.util.WsSender;
import com.fasterxml.jackson.annotation.JsonView;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.handler.annotation.MessageMapping;
import org.springframework.messaging.handler.annotation.SendTo;
import org.springframework.web.bind.annotation.*;

import java.time.LocalDateTime;
import java.util.List;
import java.util.function.BiConsumer;

@RestController
@RequestMapping("message")
public class MessageController {
    private final ChatMessageRepo messageRepo;
    private final BiConsumer<EventType, ChatMessage> wsSender;

    @Autowired
    public MessageController(ChatMessageRepo messageRepo, WsSender wsSender) {
        this.messageRepo = messageRepo;
        this.wsSender = wsSender.getSender(ObjectType.MESSAGE, Views.IdName.class);
    }

    @GetMapping
    @JsonView(Views.IdName.class)
    public List<ChatMessage> list() {
        return messageRepo.findAll();
    }

    @GetMapping("{id}")
    @JsonView(Views.FullMessage.class)
    public ChatMessage getOne(@PathVariable("id") ChatMessage chatMessage) {
        return chatMessage;
    }

    @PostMapping
    public ChatMessage create(@RequestBody ChatMessage message) {
        message.setCreationDate(LocalDateTime.now());
        ChatMessage updatedMessage = messageRepo.save(message);
        wsSender.accept(EventType.CREATE, updatedMessage);
        return updatedMessage;
    }

    @PutMapping("{id}")
    public ChatMessage update(
            @PathVariable("id") ChatMessage messageFromDb,
            @RequestBody ChatMessage message
    ) {
        BeanUtils.copyProperties(message, messageFromDb, "id");

        ChatMessage updatedMessage = messageRepo.save(messageFromDb);

        wsSender.accept(EventType.UPDATE, updatedMessage);

        return updatedMessage;
    }

    @DeleteMapping("{id}")
    public void delete(@PathVariable("id") ChatMessage message) {
        messageRepo.delete(message);
        wsSender.accept(EventType.REMOVE, message);
    }
}
