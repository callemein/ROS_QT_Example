//
// Created by tca on 19/04/17.
//

#include "chat.h"


CppChat::CppChat(QWidget * parent)
        : QWidget(parent){
    // Initialiser

    std::cout << "Initializing CppChat ..." << std::endl;

    this->initGUI();
    this->initROS();

}

void CppChat::initGUI(){

    auto chatWindow = new QWidget();
    auto mainLayout = new QVBoxLayout();


    outputChat = new QTextEdit();
    inputMsg = new QLineEdit();
    btnSend = new QPushButton("Send");

    outputChat->setDisabled(true);

    connect(btnSend, &QPushButton::clicked , this, &CppChat::sendMsg);


    mainLayout->addWidget(outputChat);
    mainLayout->addWidget(inputMsg);
    mainLayout->addWidget(btnSend);

    chatWindow->show();
    chatWindow->setLayout(mainLayout);
}

void CppChat::initROS(){
    this->chat_pub = n.advertise<std_msgs::String>("chat", 1000);
    this->chat_sub = n.subscribe<std_msgs::String>("chat", 1000, &CppChat::recvMsg, this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CppChat::spinROS);
    timer->start(20);
}

void CppChat::spinROS(){
    ros::spinOnce();
}

void CppChat::sendMsg(){
    std::cout << "SEND: " << this->inputMsg->text().toUtf8().constData() << std::endl;

    std_msgs::String msg;
    msg.data = this->inputMsg->text().toUtf8().constData();

    this->chat_pub.publish(msg);
    this->inputMsg->clear();
    this->inputMsg->setFocus();

}

void CppChat::recvMsg(const std_msgs::String::ConstPtr& msg){
    std::cout << "RECV: " << msg->data.c_str() << std::endl;
    this->outputChat->setPlainText(this->outputChat->toPlainText() + "\n" + QString(msg->data.c_str()));

}

