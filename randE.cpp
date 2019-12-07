/*
 *  RandE
 *  @BulbThinker
 *  2019
 *  randE.cpp
 */

#include "randE.h"

const int rand_core[10] PROGMEM = {
    0xf871887a,0x468f2917,0x9259fe14,0xd45c8b85,0x58345674,
    0x2dc48009,0x75b328a5,0x45c30745,0x10bd6c99,0xfb914f8c,
};

TrueRand::TrueRand(int analog_pin) {
    pinMode(analog_pin, INPUT);
    this->analog_pin = analog_pin;
    this->last_v = rand_core[analogRead(analog_pin)%10];
}

uint32_t TrueRand::getRandomDWORD() {
    uint32_t x = ((this->last_v ^ rand_core[x % 10]) & 0xFFFFF000)
               | ((millis()&0xFF) << 4)
               | (analogRead(this->analog_pin)&0x0F);
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

