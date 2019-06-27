create sequence hibernate_sequence start 1 increment 1;

create table message (
    id int8 not null,
    filename varchar(255),
    pic bytea,
    tag varchar(255),
    text varchar(2048) not null,
    user_id int8,
    primary key (id)
);


create table user_role (
    user_id int8 not null,
    roles varchar(255)
);

create table usr (
    id int8 not null,
    activation_code varchar(255),
    active boolean not null,
    email varchar(255),
    aboutme varchar(255),
    password varchar(255),
    username varchar(255) not null,
    primary key (id),
        gender     varchar(255),
    last_visit timestamp,
    locale     varchar(255),
    userpic    varchar(255),
    id_oath int8
);

create table chat_message (
    id bigint primary key,
    text varchar(255),
    creation_date timestamp

);



alter table if exists message
    add constraint message_user_fk
    foreign key (user_id) references usr;

alter table if exists user_role
    add constraint user_role_user_fk
    foreign key (user_id) references usr;
