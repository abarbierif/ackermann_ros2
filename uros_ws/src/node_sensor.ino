#include <micro_ros_arduino.h>
#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rosidl_runtime_c/string.h>
#include <std_msgs/msg/header.h>
#include <sensor_msgs/msg/range.h>

// publicador
rcl_publisher_t publisher;

// definir el tipo de mensaje
rosidl_runtime_c__String frame_id;
std_msgs__msg__Header header;
sensor_msgs__msg__Range msgRange;

// estructuras de datos de uROS
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

// pines de hardware
#define TRIGGER 22  // pin digital 2 para el trigger del sensor
#define ECHO 23     // pin digital 3 para el echo del sensor

// variable globales del programa
long t; // tiempo que demora en llegar el eco
long d; // distancia en centimetros

void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
  RCLC_UNUSED(last_call_time);
  if (timer != NULL) {
    rcl_publish(&publisher, &msgRange, NULL);

    digitalWrite(TRIGGER, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER, LOW); // la secuencia envía un pulso de 10us

    t = pulseIn(ECHO, HIGH);  // ancho de pulso
    d = t / 58.5;               // distancia = 2/t[us](ida y vuelta)*velocidad sonido(0.0343[cm/us]) aprox t[us]/58.5

    if (d > 201) {
      d = 200;  // se define distancia máxima
    }

    msgRange.range = d * 0.01;  // de cm a m (range espera distancia en metros)
  }
}

void setup() {
  set_microros_transports();  // configurar transportes de uROS

  pinMode(TRIGGER, OUTPUT); // pin como salida
  pinMode(ECHO, INPUT);     // pin como entrada
  digitalWrite(TRIGGER, LOW); // pin trigger 0

  delay(2000);

  allocator = rcl_get_default_allocator();  // obtener asignador de memoria predeterminado

  // iniciar opciones (puntero soporte, sin argumentos en linea de comandos, no se utilizan argumentos, asignador de memoria)
  rclc_support_init(&support,
    0,
    NULL,
    &allocator);

  // crear nodo (inicializacion del nodo con nombre del nodo, asignacion en el espacio y puntero que contiene la estructura)
  rclc_node_init_default(&node,
    "micro_ros_arduino_node",
    "",
    &support);

  // crear publicador (inicia publicador en el nodo con el tipo de mensaje range con el nombre de micro_ros_arduino_node_publisher)
  rclc_publisher_init_default(
    &publisher,
    &node,
    ROSIDL_GET_MSG_TYPE_SUPPORT(sensor_msgs, msg, Range),
    "micro_ros_arduino_node_publisher");

  // crear timer (configura temporizador que llama a funcion timer_callback en intervalos definidos)
  const unsigned int timer_timeout = 1000;
  rclc_timer_init_default(
    &timer,
    &support,
    RCL_MS_TO_NS(timer_timeout),
    timer_callback);
  
  // crear executor (administra la ejecucion del temporizador)
  rclc_executor_init(&executor,
    &support.context,
    1,
    &allocator);
  rclc_executor_add_timer(&executor, &timer);

  frame_id.data = "sensor_link";  // se define el marco de referencia
  header.frame_id = frame_id;

  msgRange.header = header;
  msgRange.min_range = 0.01;
  msgRange.max_range = 2.0;
  msgRange.range = 0.05;
  msgRange.field_of_view = 25 * 3.14 / 180 ;  //15 a 30 grados según datasheet, se escoge 25

}

void loop() {
  delay(100); // acumula tareas para ser ejecutadas
  rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100));  //ejecuta tareas listas para ser ejecutadas
}