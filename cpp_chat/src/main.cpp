//
// Created by tca on 19/04/17.
//
#include "chat.h"


#include "ros/ros.h"
#include <QApplication>



int main(int argc, char* argv[]){

    ros::init(argc, argv, "cpp_chat");

    QApplication app(argc, argv);

    auto chatTool = new CppChat(nullptr);

    return app.exec();
}