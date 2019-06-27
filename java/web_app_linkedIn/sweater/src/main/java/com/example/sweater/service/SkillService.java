package com.example.sweater.service;

import com.example.sweater.repos.SkillRepo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.jpa.repository.Query;

public class SkillService {
    @Autowired
    public SkillRepo skillRepo;



}
