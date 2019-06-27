
create table personalmessage (
                         id int8 not null,
                          tag varchar(255),
                         text varchar(2048) not null,
                         user_id int8,
                         receiver_id int8,
                         primary key (id)
);

alter table if exists personalmessage
    add constraint personalmessage_user_fk
        foreign key (user_id) references usr;

alter table if exists personalmessage
    add constraint personalmessage_receiver_fk
        foreign key (receiver_id) references usr;




