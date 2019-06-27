package com.example.sweater.config;

import com.example.sweater.domain.Role;
import com.example.sweater.domain.User;
import com.example.sweater.repos.UserRepo;
import com.example.sweater.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.autoconfigure.security.oauth2.client.EnableOAuth2Sso;
import org.springframework.boot.autoconfigure.security.oauth2.resource.PrincipalExtractor;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.security.config.annotation.authentication.builders.AuthenticationManagerBuilder;
import org.springframework.security.config.annotation.method.configuration.EnableGlobalMethodSecurity;
import org.springframework.security.config.annotation.web.builders.HttpSecurity;
import org.springframework.security.config.annotation.web.configuration.EnableWebSecurity;
import org.springframework.security.config.annotation.web.configuration.WebSecurityConfigurerAdapter;
import org.springframework.security.crypto.bcrypt.BCryptPasswordEncoder;
import org.springframework.security.crypto.password.PasswordEncoder;

import java.time.LocalDateTime;
import java.util.Collections;
import java.util.UUID;

@Configuration
@EnableWebSecurity
//@EnableGlobalMethodSecurity(prePostEnabled = true) // for PreAuthorize
@EnableOAuth2Sso
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Autowired
    private UserService userService;


    public WebSecurityConfig(){

    }




    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder(8);
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http
                .authorizeRequests()
                .antMatchers( "/logout","/registration", "/static/**", "/activate/*", "/message", "/message/*","/", "/login**", "/js/**", "/error**").permitAll()
                .anyRequest().authenticated()

//                .formLogin()
//                .loginPage("/login")
//                .permitAll()
//                .and()
                .and().csrf().ignoringAntMatchers("/message/*","/message","/logout")
            .and().logout().logoutSuccessUrl("/").permitAll()
                .and().rememberMe();
    }

    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception {
        auth.userDetailsService(userService)
                .passwordEncoder(userService.getPasswordEncoder());
    }

    @Bean
    public PrincipalExtractor principalExtractor(UserRepo UserRepo) {
        return map -> {
            String strId = (String) map.get("sub");
            strId = strId.substring(0,strId.length()-10);
            long id = Long.parseLong(strId);
            User user = UserRepo.findByIdOath(id);
            if(user == null)
             {
                User newUser = new User();
                newUser.setIdOath(id);
                newUser.setUsername((String) map.get("name"));
                newUser.setEmail((String) map.get("email"));
                newUser.setGender((String) map.get("gender"));
                newUser.setLocale((String) map.get("locale"));
                newUser.setUserpic((String) map.get("picture"));
                newUser.setRoles(Collections.singleton(Role.USER));
                newUser.setActive(true);
                newUser.setActivationCode(UUID.randomUUID().toString());
                return UserRepo.save(newUser);
            }

            user.setLastVisit(LocalDateTime.now());
            return UserRepo.save(user);
        };
    }
}
