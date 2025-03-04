# Practica1 Marc Grau
Objetivos: 
  1. Generar el programa y subir el codigo al github de cada uno
  2. Modificar el programa para que incluya el envio de datos (ON y OFF) al puerto serie. Añadir la
  iunicialización del puerto serie y el envio cada vez que cambia el estado del led.
  Iniciar pin de led como salida
  Iniciar el terminal serie
  Bucle infinito:
    Encender led
    Sacar por puerto serie mensaje ON
    Espera de 1000 milisegundos
    Apagar led
    Sacar por puesto serie mensaje OFF
    Espera de 1000 milisegundos

Código:
#include <Arduino.h>

unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = false;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }
}


  3. Medición de frecuencia d'encendido y apagado sin delays
Eliminar los delay modificar el pin de salida a uno cualquiera de los que estan disponibles i medir con el osciloscopio cual es la màxima frecuencia de apagado encendido que     permite el microcontrolador.
  3.1 Medir la frecuencia en estos cuatro casos:
  3.2 Con el envio por el puerto série del mensaje i utilizando las funciones de Arduino
  3.3 Con el envio por el puerto série y accedirendo directamente a los registros
  3.4 Sin el envio por el puerto série del mensaje i utilizando las funciones de Arduino
  3.5 Sin el envio por el puerto série y accedirendo directamente a los registros

  3.1 Con envío por puerto serie utilizando funciones de arduino:
    void loop() {
     digitalWrite(led, HIGH);   // turn the LED on
     Serial.println("ON"); //puerto serie sacar ON
     digitalWrite(led, LOW);    // turn the LED off
     Serial.println("OFF"); //puerto serie sacar OFF
    }
digitalwrite y println (delay: 0,5ms) --> 930Hz

  3.2 Con envío por puerto serie accediendo directamente a los registros
  uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;
  void loop() {
     Serial.println("ON");
     *gpio_out |= (1 << led);
     Serial.println("OFF");      
     *gpio_out ^= (1 << led);
    }
reg y println (delay: 0,5ms) --> 930Hz

  3.3 Con el envio por el puerto série y accedirendo directamente a los registros
  void loop() {
     digitalWrite(led, HIGH);   // turn the LED on
     digitalWrite(led, LOW);    // turn the LED off
    }
  digitalwrite sin println (delay: 0,5ms) --> 992Hz

  3.4 Sin el envio por el puerto série del mensaje i utilizando las funciones de Arduino
  uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;
  void loop() {
     *gpio_out |= (1 << led);
     *gpio_out ^= (1 << led);
    }
con reg sin println (delay: 0,5ms) --> 992Hz


DIAGRAMA DE FLUJO
graph TD;
    inicio[Iniciar pin 23 como salida del MP] --> Encender;
    Encender --> Esperar[Esperar 1 segundo];
    Esperar --> Apagar;
    Apagar --> Esperar[Esperar 1 segundo];
    Esperar --> Encender;
