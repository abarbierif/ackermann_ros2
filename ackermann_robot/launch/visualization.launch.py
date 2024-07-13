from launch import LaunchDescription
from launch.actions import ExecuteProcess
from launch.substitutions import Command
from launch_ros.actions import Node

def generate_launch_description():

    urdf_path = '/home/minicaos/project/ackermann_robot/ackermann_robot/urdf/robot.xacro'

    with open(urdf_path,'r') as i:
        robot_desc = i.read()

    pub = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        output='screen',
        parameters=[{
            'robot_description': Command(['xacro ', urdf_path])
        }]
    )

    joint = Node(
        package="joint_state_publisher_gui",
        executable="joint_state_publisher_gui",
        name="joint_state_publisher_gui",
        output='screen'
    )

    rviz = ExecuteProcess(
        cmd=['rviz2', '-d', '/home/minicaos/project/ackermann_robot/ackermann_robot/rviz/config.rviz'],
        output='screen'
    )

    return LaunchDescription([
        pub,
        joint,
        rviz
    ])