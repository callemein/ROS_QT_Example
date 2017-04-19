#!/usr/bin/env python3
# encoding: utf-8
import sys

import rospy
from std_msgs.msg import String

from PyQt5.QtCore import *
from qtpy.QtWidgets import *
from qtpy.QtGui import *

class PythonChat(QWidget):

    received_data = pyqtSignal(['QString'])

    def __init__(self):
        super(PythonChat, self).__init__()
        #Initialiser
        print("Initializing PythonChat ...")
        self.init_GUI()
        self.init_ROS()

    def init_GUI(self):
        mainLayout =  QVBoxLayout()

        self.outputChat = QTextEdit()
        self.inputMsg = QLineEdit()
        self.btnSend = QPushButton("Send")

        self.outputChat.setDisabled(True);

        self.btnSend.clicked.connect(self.send_message);

        mainLayout.addWidget(self.outputChat);
        mainLayout.addWidget(self.inputMsg);
        mainLayout.addWidget(self.btnSend);

        self.received_data.connect(self.update_chatbox)

        self.show();
        self.setLayout(mainLayout);

    def init_ROS(self):
        self.pub = rospy.Publisher('chat', String, queue_size=1)
        self.sub = rospy.Subscriber("chat", String, self.recv_message)

    def send_message(self):
        print("SEND: ", self.inputMsg.text())

        self.pub.publish(String(self.inputMsg.text()))

        self.inputMsg.clear()
        self.inputMsg.setFocus()

    def recv_message(self, data):
        print("RECV: ", data.data)
        self.received_data.emit(str(data.data)) #Use signal to handle thread communication automatically

    def update_chatbox(self, data):
        self.outputChat.setPlainText(self.outputChat.toPlainText() + "\n" + data)


