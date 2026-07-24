#include <Arduino.h>

#define PIN_LED    2
#define PIN_BUTTON 13

TaskHandle_t buttonTaskHandle = nullptr;

void IRAM_ATTR buttonISR();
void buttonTask(void *parameter);

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  // The button is active-low. The internal pull-up keeps the input from floating.
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  xTaskCreatePinnedToCore(
    buttonTask,
    "Button task",
    2048,
    nullptr,
    1,
    &buttonTaskHandle,
    ARDUINO_RUNNING_CORE
  );

  // Trigger on both edges so the task can track debounced press/release state.
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), buttonISR, CHANGE);
}

void loop() {
  // All application work is event-driven, so the Arduino loop task is unused.
  vTaskDelete(nullptr);
}

void IRAM_ATTR buttonISR() {
  BaseType_t higherPriorityTaskWoken = pdFALSE;

  vTaskNotifyGiveFromISR(buttonTaskHandle, &higherPriorityTaskWoken);

  if (higherPriorityTaskWoken == pdTRUE) {
    portYIELD_FROM_ISR();
  }
}

void buttonTask(void *parameter) {
  bool previousButtonState = HIGH;
  bool ledState = LOW;

  for (;;) {
    // Sleep without consuming CPU until an edge interrupt wakes this task.
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

    // Allow mechanical switch bounce to settle, then sample once.
    vTaskDelay(pdMS_TO_TICKS(20));
    bool currentButtonState = digitalRead(PIN_BUTTON);

    // Toggle only on a confirmed HIGH-to-LOW transition (a button press).
    if (previousButtonState == HIGH && currentButtonState == LOW) {
      ledState = !ledState;
      digitalWrite(PIN_LED, ledState);
    }

    previousButtonState = currentButtonState;

    // Discard notifications produced by bounce during the debounce interval.
    ulTaskNotifyTake(pdTRUE, 0);
  }
}



/* 
This is the superloop version
#include <Arduino.h>

#define PIN_LED    2
#define PIN_BUTTON 13
void reverseGPIO(int pin);

void setup() {
  // initialize digital pin PIN_LED as an output.
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  if (digitalRead(PIN_BUTTON) == LOW) {
    delay(20);
    if (digitalRead(PIN_BUTTON) == LOW) {
      reverseGPIO(PIN_LED);
  }
    while (digitalRead(PIN_BUTTON) == LOW);
    delay(20);
    while (digitalRead(PIN_BUTTON) == LOW);
  }
}

void reverseGPIO(int pin){
  digitalWrite(pin, !digitalRead(pin));
}
*/