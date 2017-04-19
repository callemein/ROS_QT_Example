#!/usr/bin/env python3
# encoding: utf-8

from python_chat import PythonChat

import sys

import rospy
from std_msgs.msg import String

from PyQt5.QtCore import *
from qtpy.QtWidgets import *
from qtpy.QtGui import *

def main(argv=None):
    rospy.init_node('python_chat', anonymous=True)
    app = QApplication(argv)

    chat_app = PythonChat()

    return app.exec_()


if __name__ == '__main__':
    status = main(sys.argv)
    sys.exit(status)
