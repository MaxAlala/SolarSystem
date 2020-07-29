/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   InteractiveMarkerRos.cpp
 * Author: northlight
 * 
 * Created on July 16, 2020, 3:10 PM
 */

#include "InteractiveMarkerRos.h"
// for tcp server
#include<stdio.h>
#include<string.h> //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h> //write
#include <string>

extern Eigen::Vector3d g_position_of_the_first_match;
extern Eigen::Quaterniond g_r_quat;

int createServerAndSendCoordinates() {
    /*
        C socket server example
     */
    using namespace std;
    std::string coordinates = "<Server><Pos2><X>" + to_string(g_position_of_the_first_match[0]) + "</X><Y>" + to_string(g_position_of_the_first_match[1]) + "</Y><Z>" + to_string(g_position_of_the_first_match[2]) + "</Z><A>" + to_string(g_r_quat.z()) + "</A><B>" + to_string(g_r_quat.y()) + "</B><C>" + to_string(g_r_quat.x()) + "</C></Pos2></Server>";
    int socket_desc, client_sock, c, read_size;
    struct sockaddr_in server, client;
    char client_message[2000];

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    //Bind
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof (server)) < 0) {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Listen
    listen(socket_desc, 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof (struct sockaddr_in);

    //accept connection from an incoming client
    client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t*) & c);
    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
    puts("Connection accepted");

    //Receive a message from client
    while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
        //Send the message back to client
        write(client_sock, client_message, strlen(client_message));
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }
    return 0;

}

void graspObject(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback) {
    interactiveMarkerRos::shouldISendDetectedObject = 1;
    shouldISendDetectedObject2 = 34;
    createServerAndSendCoordinates();

    ROS_INFO("You chose 'yes'.");

}

void dontGraspObject(const visualization_msgs::InteractiveMarkerFeedbackConstPtr &feedback) {
    interactiveMarkerRos::shouldISendDetectedObject = 0;
    ROS_INFO("You chose 'no'.");
}

Marker InteractiveMarkerRos::makeBox(InteractiveMarker &msg) {
    Marker marker;
    float scale = 0.10;
    marker.type = visualization_msgs::Marker::MESH_RESOURCE;
    marker.mesh_resource = "package://using_markers/src/AX-01b_bearing_box.stl";
    marker.scale.x = scale;
    marker.scale.y = scale;
    marker.scale.z = scale;
    marker.pose.position.x = position_of_the_first_match[0];
    marker.pose.position.y = position_of_the_first_match[1];
    marker.pose.position.z = position_of_the_first_match[2];
    marker.pose.orientation.x = r_quat.x();
    marker.pose.orientation.y = r_quat.y();
    marker.pose.orientation.z = r_quat.z();
    marker.pose.orientation.w = r_quat.w();
    marker.color.r = 153.0f;
    marker.color.g = 0.0f;
    marker.color.b = 153.0f;
    marker.color.a = 0.7;

    return marker;
}

InteractiveMarkerControl& InteractiveMarkerRos::makeBoxControl(InteractiveMarker &msg) {
    InteractiveMarkerControl control;
    control.always_visible = true;
    control.markers.push_back(makeBox(msg));
    msg.controls.push_back(control);

    return msg.controls.back();
}

InteractiveMarker InteractiveMarkerRos::makeEmptyMarker(bool dummyBox) {
    InteractiveMarker int_marker;
    int_marker.header.frame_id = "camera";
    int_marker.pose.position.y = -3.0 * marker_pos++;
    ;
    int_marker.scale = 1;

    return int_marker;
}

void InteractiveMarkerRos::makeMenuMarker(std::string name) {
    InteractiveMarker int_marker = makeEmptyMarker();
    int_marker.name = name;

    InteractiveMarkerControl control;

    control.interaction_mode = InteractiveMarkerControl::BUTTON;
    control.always_visible = true;

    control.markers.push_back(makeBox(int_marker));
    int_marker.controls.push_back(control);

    server->insert(int_marker);
}

void InteractiveMarkerRos::initMenu() {
    h_first_entry = menu_handler.insert("should i pick detected object up?");
    MenuHandler::EntryHandle entry = menu_handler.insert(h_first_entry, "yes", &graspObject);
    entry = menu_handler.insert(h_first_entry, "no", &dontGraspObject);
}

InteractiveMarkerRos::InteractiveMarkerRos(Eigen::Vector3d& position_of_the_first_match, Eigen::Quaterniond& r_quat) {
    for (int i = 0; i < 3; i++)
        this->position_of_the_first_match[i] = position_of_the_first_match[i];

    this->r_quat.x() = r_quat.x();
    this->r_quat.y() = r_quat.y();
    this->r_quat.w() = r_quat.w();
    this->r_quat.z() = r_quat.z();

}

InteractiveMarkerRos::~InteractiveMarkerRos() {
}
