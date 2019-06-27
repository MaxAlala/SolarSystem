package com.example.sweater.repos;

import com.example.sweater.domain.Group;
import com.example.sweater.domain.Skill;
import com.example.sweater.domain.User;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;


public interface SkillRepo extends CrudRepository<Skill, Long> {


    Iterable<Skill> findSkillByAuthor(User user_id);

    @Override
    Iterable<Skill> findAll();

    Skill findSkillByName(String name);
//    @Query(value = "insert into user_group (group_id, user_id) values (:group_id, :userid)", nativeQuery = true)
//     void addToUserGroups(long userid, long group_id);
//@Query(value = "insert into user_skill (skill_id,user_id) VALUES (:skill_id,:userid)", nativeQuery = true)
//void addToUserSkill(long userid, long skill_id);
//
//    @Query(value = "delete from user_skill where skill_id = :skill_id AND user_id = :userid", nativeQuery = true)
//    void deleteFromUserSkill(long userid, long skill_id);

    @Query(value = "select * from skills where id in (select skill_id from user_skill where user_id = :userid)", nativeQuery = true)
    Iterable<Skill> findUsersSkills(long userid);

    @Query(value = "select * from skills where id not in (select skill_id from user_skill where user_id = :userid)", nativeQuery = true)
    Iterable<Skill> findnotUsersSkills(long userid);

    //    @Query("select new com.example.sweater.domain.dto.MessageDto(" +
//            "   m, " +
//            "   count(ml), " +
//            "   sum(case when ml = :user then 1 else 0 end) > 0" +
//            ") " +
//            "from Message m left join m.likes ml " +
//            "where m.tag = :tag " +
//            "group by m " +
//            "order by m desc")
//
//    Page<MessageDto> findByTag(@Param("tag") String tag, Pageable pageable, @Param("user") User user);
//
//    void deleteById(Long id);
//
//    @Query("select new com.example.sweater.domain.dto.MessageDto(" +
//            "   m, " +
//            "   count(ml), " +
//            "   sum(case when ml = :user then 1 else 0 end) > 0) " +
//            "from Message m left join m.likes ml " +
//            "group by m " +
//            "order by m desc")
//    Page<MessageDto> findAllByOrderByIdDesc(Pageable pageable, @Param("user") User user);
//
//
//    @Query("select new com.example.sweater.domain.dto.MessageDto(" +
//            "   m, " +
//            "   count(ml), " +
//            "   sum(case when ml = :user then 1 else 0 end) > 0" +
//            ") " +
//            "from Message m left join m.likes ml " +
//            "where m.author = :user and m.tag = :tag " +
//            "group by m "+
//            "order by m desc")
//    Page<MessageDto> findByTagAndAuthor(@Param("tag")String tag, @Param("user") User user,Pageable pageable);
//
//    @Query("select new com.example.sweater.domain.dto.MessageDto(" +
//            "   m, " +
//            "   count(ml), " +
//            "   sum(case when ml = :user then 1 else 0 end) > 0" +
//            ") " +
//            "from Message m left join m.likes ml " +
//            "where m.author = :user " +
//            "group by m "+
//            "order by m desc")
//    Page<MessageDto> findByAuthor(@Param("user") User user, Pageable pageable);
}
