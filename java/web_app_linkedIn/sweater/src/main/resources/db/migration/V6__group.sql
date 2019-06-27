
create table groups (
                         id int8 not null,
                         pic bytea,
                         tag varchar(255),
                         text varchar(2048) not null,
                         name varchar(2048) not null,
                         filename varchar(255),
                         user_id int8,
                         primary key (id)
);

alter table if exists groups
    add constraint groups_user_fk
        foreign key (user_id) references usr;

create table user_group (
user_id bigint not null references usr,
group_id bigint not null references groups,
primary key (user_id, group_id)
);




