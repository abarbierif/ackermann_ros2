import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/angelo/Documents/repos/ackermann_ros2/ackermann_robot/install/ackermann_robot'
