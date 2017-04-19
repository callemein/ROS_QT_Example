//
// Created by tca on 19/04/17.
//

#include <iostream>
#include <string>

// ROS INCLUDES
#include "ros/ros.h"
#include "std_msgs/String.h"

//QT INCLUDES
#include <QApplication>
#include <QObject>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QTimer>



#ifndef CPP_CHAT_CHAT_H
#define CPP_CHAT_CHAT_H

class CppChat : public QWidget{
public:
    CppChat(QWidget * parent);

public slots:
    void sendMsg();
    void recvMsg(const std_msgs::String::ConstPtr& msg);

private:
    void initGUI();
    void initROS();
    void spinROS();

    ros::NodeHandle n;

//Variables
    QTextEdit * outputChat;
    QLineEdit * inputMsg;
    QPushButton * btnSend;
    QTimer * timer;

    ros::Publisher chat_pub;
    ros::Subscriber chat_sub;




};

#endif //CPP_CHAT_CHAT_H
