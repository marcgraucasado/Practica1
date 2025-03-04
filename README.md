# Práctica 1 - Marc Grau

## Objetivos

- Generar el programa y subir el código al GitHub de cada uno.
- Modificar el programa para que incluya el envío de datos (ON y OFF) al puerto serie.
- Añadir la inicialización del puerto serie y el envío cada vez que cambia el estado del LED.
- Iniciar pin de LED como salida.
- Iniciar el terminal serie.
- Bucle infinito:
  - Encender LED.
  - Sacar por puerto serie mensaje ON.
  - Espera de 1000 milisegundos.
  - Apagar LED.
  - Sacar por puerto serie mensaje OFF.
  - Espera de 1000 milisegundos.

## Código

```cpp
#include <Arduino.h>

#define LED_BUILTIN 21

unsigned long previousMillis = 0;
const long interval = 1000;
bool ledState = false;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
        Serial.println(ledState ? "ON" : "OFF");
    }
}
```

## Medición de frecuencia de encendido y apagado sin `delay`

Se elimina el `delay`, se modifica el pin de salida a uno cualquiera de los disponibles y se mide con el osciloscopio cuál es la máxima frecuencia de apagado/encendido que permite el microcontrolador.

### Casos de medición

#### 1. Con envío por puerto serie utilizando funciones de Arduino

```cpp
void loop() {
    digitalWrite(led, HIGH);
    Serial.println("ON");
    digitalWrite(led, LOW);
    Serial.println("OFF");
}
```

- **Frecuencia medida**: 930Hz

#### 2. Con envío por puerto serie accediendo directamente a los registros

```cpp
uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;
void loop() {
    Serial.println("ON");
    *gpio_out |= (1 << led);
    Serial.println("OFF");
    *gpio_out ^= (1 << led);
}
```

- **Frecuencia medida**: 930Hz

#### 3. Sin envío por el puerto serie utilizando funciones de Arduino

```cpp
void loop() {
    digitalWrite(led, HIGH);
    digitalWrite(led, LOW);
}
```

- **Frecuencia medida**: 992Hz

#### 4. Sin envío por el puerto serie accediendo directamente a los registros

```cpp
uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;
void loop() {
    *gpio_out |= (1 << led);
    *gpio_out ^= (1 << led);
}
```

- **Frecuencia medida**: 992Hz

## Diagrama de Flujo

```mermaid
graph TD;
inicio[Iniciar pin 23 como salida del MP] --> Encender;
Encender --> Esperar1[Esperar 1 segundo];
Esperar1 --> Apagar;
Apagar --> Esperar1;
Esperar1 --> Encender;
