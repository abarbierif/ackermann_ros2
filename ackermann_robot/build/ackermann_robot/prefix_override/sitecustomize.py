import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/angelo/Documents/2024-1/ros/ackermann_robot/install/ackermann_robot'
