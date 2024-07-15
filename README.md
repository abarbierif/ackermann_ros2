# ackermann_ros2

- ROS2 [ROS2 Documentation](https://docs.ros.org/en/iron/Installation/Ubuntu-Install-Debians.html) (Seguir Desktop Install)
- Gazebo ```sudo apt install ros-<version_ros>-gazebo-ros-pkgs```
- Xacro ```sudo apt install ros-<version_ros>-xacro```
- <version_ros>: Actualmente se esta empleando **iron**

> [!IMPORTANT]
> Para utlizar ROS2, siempre hacer source ROS2 en cada nueva terminal ```source /opt/ros/iron/setup.bash```

### URDF

  - [ackermann xacro](https://github.com/abarbierif/ackermann_ros2/blob/main/ackermann_robot/urdf/ackermann.xacro)

### XACRO

  - [ackermann.xacro](https://github.com/abarbierif/ackermann_ros2/blob/main/ackermann_robot/urdf/ackermann.xacro) Archivo que modela la estructura del robot
  - [params.xacro](https://github.com/abarbierif/ackermann_ros2/blob/main/ackermann_robot/urdf/params.xacro) Archivo que contiene parámetros del robot

### RVIZ
  - El archivo de lanzamiento en ***python*** es creado en un **paquete** de ROS. Para más información sobre la creación de paquetes y su compilación ver [creating a package](https://docs.ros.org/en/iron/Tutorials/Beginner-Client-Libraries/Creating-Your-First-ROS2-Package.html)
  
  - Para la visualización mediante los ***nodos*** ```robot_state_publisher```, ```joint_state_publisher``` y ```rviz2``` se realizó el siguiente launch file [visualization.launch.py](https://github.com/abarbierif/ackermann_ros2/blob/main/ackermann_robot/launch/visualization.launch.py)
    >**Nota**: La variable ```urdf_path``` en la línea 8 debe ser modificado a la ruta del archivo ```.xacro```\
    >**Nota**: La ruta al archivo ```config.rviz``` debe ser modificada por la ruta de un archivo de ocnfiguración de **RVIZ** previamente creado o en su defecto eliminar la opción del comando, en ese caso la configuración debe realizarse de forma manual una vez abierto **RVIZ**

  comandos de ejecución:
    
    ```
    cd <workspace>
    source install/local_setup.bash
    ros2 launch ackermann_robot visualization.launch.py
    ```
  La visualización del robot es:
  Utilizando ```rqt_graph``` se visualiza el siguiente grafo:
    
### GAZEBO

- Para añadir un **nodo** de control se utliza el driver ```libgazebo_ros_ackermann_drive.so```, este es vinculado al robot con el siguiente archivo [gazebo.xacro](https://github.com/abarbierif/ackermann_ros2/blob/main/ackermann_robot/urdf/gazebo.xacro). Para modularizar los componentes del robot se utliza el archivo [robot.xacro](https://github.com/abarbierif/ackermann_ros2/blob/main/ackermann_robot/urdf/robot.xacro) (archivo principal que integra los componentes del robot)

- Para la visualización mediante los ***nodos*** ```robot_state_publisher```, ```spawn_entity``` y ```gazebo``` se realizó el siguiente launch file [visualization.launch.py](https://github.com/abarbierif/ackermann_ros2/blob/main/ackermann_robot/launch/gazebo.launch.py). Adicionalmente, también se agregó el nodo ```rviz2```
    >**Nota**: La variable ```urdf_path``` en la línea 12 debe ser modificado a la ruta del archivo ```.xacro```\
    >**Nota**: La ruta al archivo ```config_lidar.rviz``` debe ser modificada por la ruta de un archivo de ocnfiguración de **RVIZ** previamente creado o en su defecto eliminar la opción del comando, en ese caso la configuración debe realizarse de forma manual una vez abierto **RVIZ**
  

#### Sensor LIDAR

- Para agregar un sensor tipo **LIDAR** se utiliza el driver ```libgazebo_ros_ray_sensor.so```, vinculado al robot en el archivo [lidar.xacro](https://github.com/abarbierif/ackermann_ros2/blob/main/ackermann_robot/urdf/lidar.xacro). El driver envía mensajes del tipo ```LaserScan``` a través del tópico ```scan```.

  comandos de ejecución:
    
    ```
    cd <workspace>
    source install/local_setup.bash
    ros2 launch ackermann_robot gazebo.launch.py
    ```
    > [!WARNING] Para visualizar el sensor en RVIZ es necesario añadir la visualización manualmente con el mensaje tipo ```LaserScan``` y luego vincularlo al tópico ```scan```. 
    
  La visualización del robot en GAZEBO es:
  
  Utilizando ```rqt_graph``` se visualiza el siguiente grafo: 
  
