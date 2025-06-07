#include "Buzzer.h"
#include <Arduino.h> // For pinMode, digitalWrite, delay

void buzzer_init() {
    pinMode(WIO_BUZZER, OUTPUT);
}

void beep_success() {
    analogWrite(WIO_BUZZER, 255);
    delay(200);
    analogWrite(WIO_BUZZER, 0);
}

void beep_fail() {
    for (int i=0; i<2; i++) {
        analogWrite(WIO_BUZZER, 255);
        delay(200);
        analogWrite(WIO_BUZZER, 0);
        delay(200);
    }
}

void beep_short(int count) {
    for (int i=0; i<count; i++) {
        analogWrite(WIO_BUZZER, 128);
        delay(150);
        analogWrite(WIO_BUZZER, 0);
        delay(150);
    }
}