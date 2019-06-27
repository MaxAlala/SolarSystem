package com.example.sweater.repos;

import com.example.sweater.domain.Group;
import com.example.sweater.domain.User;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;
import org.springframework.stereotype.Repository;

import java.util.List;


@Repository
public interface UserRepo extends JpaRepository<User, Long> {
    User findByUsername(String username);
    User findByIdOath(Long idoath);
    User findByActivationCode(String code);
    List<User> findAllByUsernameContaining(String str);
@Query(value = "select * from usr where id in (select user_id from user_skill where skill_id = :skill_id)", nativeQuery = true)
List<User> findUserBySkill(long skill_id);
}
