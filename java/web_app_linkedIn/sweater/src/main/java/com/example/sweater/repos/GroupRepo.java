package com.example.sweater.repos;

import com.example.sweater.domain.Group;
import com.example.sweater.domain.Message;
import com.example.sweater.domain.User;
import com.example.sweater.domain.dto.MessageDto;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;


public interface GroupRepo extends CrudRepository<Group, Long> {


    Iterable<Group> findGroupsByAuthor(User user_id);

    @Override
    Iterable<Group> findAll();

//    @Query(value = "insert into user_group (group_id, user_id) values (:group_id, :userid)", nativeQuery = true)
//     void addToUserGroups(long userid, long group_id);
@Query(value = "insert into user_group (group_id,user_id) VALUES (:group_id,:userid)", nativeQuery = true)
void addToUserGroups(long userid, long group_id);
    @Query(value = "delete from user_group where group_id = :group_id AND user_id = :userid)", nativeQuery = true)
    void deleteFromUserGroups(long userid, long group_id);

    @Query(value = "select * from groups where id  not in (select group_id from user_group where user_id = :userid)", nativeQuery = true)
    Iterable<Group> findnotUsersGroup(long userid);

    @Query(value = "select * from groups where id in (select group_id from user_group where user_id = :userid)", nativeQuery = true)
    Iterable<Group> findUsersGroup(long userid);



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
