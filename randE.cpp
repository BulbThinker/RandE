/*
 *  RandE
 *  @BulbThinker
 *  2019
 *  randE.cpp
 */

#include "randE.h"


TrueRand::TrueRand(int analog_pin) {
    this->analog_pin = analog_pin;
    this->last_v = analogRead(analog_pin);
}

uint32_t TrueRand::getRandomDWORD() {
    uint32_t x = (this->last_v & 0xFFFFF00F)
               | (analogRead(this->analog_pin)&0xFF << 4);
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return (this->last_v = x);
}

int TrueRand::next_int() {
    return ((int)this->getRandomDWORD());
}

int TrueRand::next_int(int min_v, int max_v) {
    return ((max_v - min_v)*this->next_double() + min_v);
}

float TrueRand::next_float() {
    return ((float)this->getRandomDWORD()/4294967296.0f);
}

double TrueRand::next_double() {
    return ((double)this->getRandomDWORD()/4294967296.0);
}


XorShift::XorShift(uint32_t seed) {
    this->seed = seed;
}

uint32_t XorShift::getRandomDWORD() {
    uint32_t x = this->seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return this->seed = x;
}

int XorShift::next_int() {
    return ((int)this->getRandomDWORD());
}

int XorShift::next_int(int min_v, int max_v) {
    return ((max_v - min_v)*this->next_double() + min_v);
}

float XorShift::next_float() {
    return ((float)this->getRandomDWORD()/4294967296.0f);
}

double XorShift::next_double() {
    return ((double)this->getRandomDWORD()/4294967296.0);
}

