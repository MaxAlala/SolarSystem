
create table skills (
                         id int8 not null,
                          tag varchar(255),
                         text varchar(2048) not null,
                         name varchar(2048) not null,
                         user_id int8,
                         primary key (id)
);

alter table if exists skills
    add constraint skills_user_fk
        foreign key (user_id) references usr;

create table user_skill (
user_id bigint not null references usr,
skill_id bigint not null references skills,
primary key (user_id, skill_id)
);




