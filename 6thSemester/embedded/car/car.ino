#include "Wheels.h"
#include "ir_remote_codes.h"

#include "LiquidCrystal_I2C.h"

#include <IRremote.h>
#include <Servo.h>

#define LCDAddress 0x27
#define MMPS 450
#define BEEPER LED_BUILTIN

#define TRIG A1
#define ECHO A2

#define IR_PIN 2
#define SERVO 9

LiquidCrystal_I2C lcd(LCDAddress, 16, 2);

Servo servo;


Wheels w;
long argIn = 0;
long dist = 100000; // in mm
long beep_delay = 250; // in milliseconds
long look_delay = 500;
long lcd_delay = 100;
unsigned long t_move_start = 0;
unsigned long t_lcd = 0;
unsigned long t_beep = 0;
unsigned long t_lookl = 0;
unsigned long t_look = look_delay / 2;
unsigned long t_lookr = look_delay;
bool blocked = false;

long angle = 90;
long distance = 0;
long dr = 0, dc = 0, dl = 0;

enum IRRemoteCode ir_code = 0;


void setup() {
    // put your setup code here, to run once:
    w.attach(7,8,5,12,4,6);

    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    servo.attach(SERVO);

    pinMode(BEEPER, OUTPUT);
    
    Serial.begin(9600);
    // Serial.setTimeout(200);

    lcd.init();
    lcd.backlight();

    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

    w.setSpeed(200);
}

void loop() {
    if (IrReceiver.decode()) {
        int new_ir_code = IrReceiver.decodedIRData.command;
        if (new_ir_code) ir_code = new_ir_code;
        Serial.println(ir_code);
        IrReceiver.resume();
    } else {
        // ir_code = 0;
    }

    // Serial.println(ir_code == IR1);
    switch (ir_code) {
    case IR1:
    {
        if (dist > 0) w.forward();
        unsigned long t = millis();
        
        // argIn = Serial.parseInt(SKIP_ALL);
        
        // if (argIn > 0) {
        //     dist = argIn * 10;
        //     t_move_start = t;
        //     w.setSpeed(200);
        //     w.forward();
        // } else if (argIn < 0) {
        //     dist = argIn * (-10);
        //     t_move_start = t;
        //     w.setSpeed(200);
        //     w.back();
        // }

        long new_dist = 0;

        if (dist > 0) {
            new_dist = dist - (long)(t - t_move_start) * MMPS / 1000;
            dist = (new_dist <= 0) ? 0 : dist;
        }

        if (dist && (dr < 30 || dc < 30 || dl < 30)) {
            blocked = true;
            dodge();
            blocked = false;
        }


        if (t >= t_lcd + lcd_delay) {
            t_lcd = t;
            lcdDisplay();
        }

        // if (t >= t_beep + beep_delay) {
        //     t_beep = t;
        //     doBeep();
        // }

        if (!blocked && t >= t_lookl + 2 * look_delay) {
            t_lookl += 2 * look_delay;
            angle = 120;
            lookAndTellDistance();
            dl = distance;
        }

        if (!blocked && t >= t_look + look_delay) {
            t_look += look_delay;
            angle = 90;
            lookAndTellDistance();
            dc = distance;
        }

        if (!blocked && t >= t_lookr + 2 * look_delay) {
            t_lookr += 2 * look_delay;
            angle = 60;
            lookAndTellDistance();
            dr = distance;
        }
        

        Serial.print(t_lookl);
        Serial.print(t_look);
        Serial.print(t_lookr);
        Serial.println("");

        if (dist == 0) w.stop();

        break;
    }
    case IR2:
        w.stop();
        break;
    
    default:
        w.stop();
        break;
    }
}

// zmienia wartość pinu BEEPER
void doBeep() {
    if (w.get_lspeed() < 0 && w.get_rspeed() < 0) {
        digitalWrite(BEEPER, digitalRead(BEEPER) ^ 1);
    }
}

void lcdDisplay() {
    t_lcd += lcd_delay;
    lcd.clear();
    // lcd.setCursor(0, 0);
    // lcd.print((new_dist > 0) ? new_dist : 0);
    lcd.setCursor(6, 0);
    lcd.print(angle);
    lcd.setCursor(10, 0);
    lcd.print(dl);
    lcd.setCursor(12, 0);
    lcd.print(dc);
    lcd.setCursor(14, 0);
    lcd.print(dr);
    lcd.setCursor(0, 1);
    lcd.print(w.get_lspeed());
    lcd.setCursor(12, 1);
    lcd.print(w.get_rspeed());
}

void lookAndTellDistance() {
    unsigned long tot;

    servo.write(angle);

    digitalWrite(TRIG, HIGH);
    delay(10);
    digitalWrite(TRIG, LOW);
    tot = pulseIn(ECHO, HIGH);

    distance = tot/59;
}

void dodge() {
    int process_delay = 200;

    w.stop();
    angle = 30;
    lookAndTellDistance();
    long rdist1 = distance;
    delay(process_delay);
    angle = 60;
    lookAndTellDistance();
    long rdist2 = distance;
    delay(process_delay);
    angle = 120;
    lookAndTellDistance();
    long ldist1 = distance;
    delay(process_delay);
    angle = 150;
    lookAndTellDistance();
    long ldist2 = distance;

    angle = 90;

    Serial.print(rdist1);
    Serial.print(" ");
    Serial.print(rdist2);
    Serial.print(" ");
    Serial.print(ldist1);
    Serial.print(" ");
    Serial.println(ldist2);

    if ((rdist1 + rdist2) > (ldist1 + ldist2)) {
        w.backRight();
    } else {
        w.backLeft();
    }

    delay(1000);
    
    w.stop();

    if (dist > 0) w.forward();
    else if (dist < 0) w.back();
}
