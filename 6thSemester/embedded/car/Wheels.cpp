#include <Arduino.h>

#include "Wheels.h"

#define SET_MOVEMENT(side,f,b) digitalWrite( side[0], f);\
                               digitalWrite( side[1], b)

Wheels::Wheels() { 
    this->lspeed = 0;
    this->rspeed = 0;
}

void Wheels::attachRight(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsRight[0] = pF;
    this->pinsRight[1] = pB;
    this->pinsRight[2] = pS;
}


void Wheels::attachLeft(int pF, int pB, int pS)
{
    pinMode(pF, OUTPUT);
    pinMode(pB, OUTPUT);
    pinMode(pS, OUTPUT);
    this->pinsLeft[0] = pF;
    this->pinsLeft[1] = pB;
    this->pinsLeft[2] = pS;
}

void Wheels::setSpeedRight(uint8_t s)
{
    analogWrite(this->pinsRight[2], s);
    this->rspeed = (this->rdir != 0) ? s * this->rdir : s;
}

void Wheels::setSpeedLeft(uint8_t s)
{
    analogWrite(this->pinsLeft[2], s);
    this->lspeed = (this->ldir != 0) ? s * this->ldir : s;
}

void Wheels::setSpeed(uint8_t s)
{
    setSpeedLeft(s);
    setSpeedRight(s);
}

void Wheels::attach(int pRF, int pRB, int pRS, int pLF, int pLB, int pLS)
{
    this->attachRight(pRF, pRB, pRS);
    this->attachLeft(pLF, pLB, pLS);
}

void Wheels::forwardLeft() 
{
    SET_MOVEMENT(pinsLeft, HIGH, LOW);
    this->ldir = 1;
    if (this->lspeed < 0) this->lspeed *= -1;
}

void Wheels::forwardRight() 
{
    SET_MOVEMENT(pinsRight, HIGH, LOW);
    this->rdir = 1;
    if (this->rspeed < 0) this->rspeed *= -1;
}

void Wheels::backLeft()
{
    SET_MOVEMENT(pinsLeft, LOW, HIGH);
    this->ldir = -1;
    if (this->lspeed > 0) this->lspeed *= -1;
}

void Wheels::backRight()
{
    SET_MOVEMENT(pinsRight, LOW, HIGH);
    this->rdir = -1;
    if (this->rspeed > 0) this->rspeed *= -1;    
}

void Wheels::forward()
{
    this->forwardLeft();
    this->forwardRight();
}

void Wheels::back()
{
    this->backLeft();
    this->backRight();
}

void Wheels::stopLeft()
{
    SET_MOVEMENT(pinsLeft, LOW, LOW);
    this->lspeed = 0;
}

void Wheels::stopRight()
{
    SET_MOVEMENT(pinsRight, LOW, LOW);
    this->rspeed = 0;
}

void Wheels::stop()
{
    this->stopLeft();
    this->stopRight();
}

int Wheels::get_lspeed() {
    return this->lspeed;
}

int Wheels::get_rspeed() {
    return this->rspeed;
}

// void Wheels::goForward(int cm) {
//     this->forward();
//     // this->setSpeed(200);
//     delay(cm * 27);
//     this->stop();
// }

// void Wheels::goBack(int cm) {
//     this->back();
//     // this->setSpeed(200);
//     delay(cm * 27);
//     this->stop();
// }