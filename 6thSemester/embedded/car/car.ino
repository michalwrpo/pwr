#include "Wheels.h"
#include "LiquidCrystal_I2C.h"
#include "TimerOne.h"

#define LCDAddress 0x27
#define MMPS 450
#define BEEPER LED_BUILTIN

LiquidCrystal_I2C lcd(LCDAddress, 16, 2);


Wheels w;
long argIn = 0;
long dist = 0; // in mm
long beepPeriod = 250000; // in microseconds
unsigned long t1 = 0;
unsigned long t2 = 0;
int delay2 = 100;


void setup() {
    // put your setup code here, to run once:
    w.attach(7,8,5,12,11,6);

    pinMode(BEEPER, OUTPUT);
    
    Serial.begin(9600);
    Serial.setTimeout(200);

    Timer1.initialize();
    TimerUpdate();

    lcd.init();
    lcd.backlight();
}

void loop() {
    unsigned long t = millis();
    
    argIn = Serial.parseInt(SKIP_ALL);
    
    if (argIn > 0) {
        dist = argIn * 10;
        t1 = t;
        w.setSpeed(200);
        w.forward();
    } else if (argIn < 0) {
        dist = argIn * (-10);
        t1 = t;
        w.setSpeed(200);
        w.back();
    }

    long new_dist = 0;

    if (dist > 0) {
        new_dist = dist - (long)(t - t1) * MMPS / 1000;
        dist = (new_dist <= 0) ? 0 : dist;
    }


    if (t >= t2 + delay2) {
        t2 += delay2;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print((new_dist > 0) ? new_dist : 0);
        lcd.setCursor(0, 1);
        lcd.print(w.get_lspeed());
        lcd.setCursor(12, 1);
        lcd.print(w.get_rspeed());
    }

    if (dist == 0) {
        w.stop();
    }
}

void TimerUpdate() {
    Timer1.detachInterrupt();
    Timer1.attachInterrupt(doBeep, beepPeriod);
}

// zmienia wartość pinu BEEPER
void doBeep() {
    if (w.get_lspeed() < 0 && w.get_rspeed() < 0) {
        digitalWrite(BEEPER, digitalRead(BEEPER) ^ 1);
    }
}
