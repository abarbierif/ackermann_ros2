## uROS
Se implementa un microcontrolador (ESP32) con un sensor ultrasónico (HC-SR04) que se comunica con ros2 iron por puerto serial.
El objetivo es agregar un sensor ultrasónico de forma física al robot ackermann y visualizarlo de forma virtual en RVIZ.
> [!NOTE]
> Se necesita la instalación del agente que permite la comunicación con uROS

# Creación de nodo
Se crea un nodo publicador en el microcontrolador utilizando Arduino IDE, este nodo envía un mensaje tipo range periodicamente.
El mensaje depende de la captura del sensor ultrasónico. Se utiliza el Arduino IDE para subir el [archivo .ino]([link](https://github.com/abarbierif/ackermann_ros2/blob/main/uros_ws/src/node_sensor.ino)) al microcontrolador.
> [!NOTE]
> Es necesario instalar la librería de microROS en el Arduino IDE, en este proyecto se utiliza la distribución iron.

# Modificación URDF
Se modifica el URDF previamente diseñado para agregar un link y joint para el sensor.
> [!IMPORTANT]
> El nombre del link creado debe coincidir con el marco de referencia definido en la creación del nodo. (En este caso "sensor_link")

# Ejecución
> [!IMPORTANT]
> Para utlizar ROS2, siempre hacer source ROS2 en cada nueva terminal ```source /opt/ros/iron/setup.bash```

Primero se debe iniciar el agente de uROS que permite la comunicación.

comandos de ejecución:
```
ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyUSB0
```

> [!NOTE] 
> Se asume que ya existe la build del agente

> [!NOTE]
> El puerto ttyUSB0 depende de la conexión con el puerto serial

> [!IMPORTANT]
> El puerto puede necesitar permisos para la ejecución del agente, estos se pueden modificar con el comando chmod ```sudo chmod 777 /ttyUSB0```.

Una vez ejecutado el nodo en el microcontrolador, se pueden visualizar los tópicos activos.

comandos de ejecución:

```
ros2 topic list
```

Donde debería estar el nodo creado con el nombre que se le asignó, en nuestro caso **micro_ros_arduino_node_publisher**

# Visualización en RVIZ
Una vez esté el tópico disponible, visualizamos el [URDF](link) modificado.
Para esto:
- Primero se crea el nodo que publica los estados del URDF.
- Luego se crea el nodo que publica los joints y transformaciones.
- Y finalmente se abre RVIZ para visualizar el modelo.

comandos de ejecución:
```
ros2 run robot_state_publisher robot_state_publisher <path absoluto URDF>
ros2 run joint_state_publisher joint_state_publisher
ros2 run joint_state_publisher_gui joint_state_publisher_gui
ros2 run rviz2 rviz2
```

> [!NOTE]
> Si no se guarda un archivo de configuración de RVIZ, es necesario configurar el entorno para la visualización
Dejando como referencia **base_link**, añadir modelo con el tópico **robot state publisher** y añadir range con el tópico **micro_ros_arduino_node_publisher**

>[!NOTE]
> De forma alternativa se puede utilizar el lanzamiento de paquete por defecto **urdf_tutorial** con ```ros2 launch urdf_tutorial display.launch.py model:={DIRECTORIO}/{MODELO}.urdf``` y en RVIZ solo añadir el **range**.
> Para utilizar esta forma alternativa es necesario tener instalado el paquete urdf_tutorial ```sudo apt install ros-iron-urdf-tutorial```.

Una vez configurado se visualiza el modelo del robot con sus articulaciones y el range representando el sensor ultrasónico que cambia dependiendo del estado del sensor.

Finalmente se puede mostrar la unión de los nodos con ```rqt_graph```.
