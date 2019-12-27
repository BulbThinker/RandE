/*
 *  RandE
 *  @BulbThinker
 *  2019
 *  randE.cpp
 */

#include <randE.h>

#define RAND_CORE_SIZE 10

const uint32_t rand_core[RAND_CORE_SIZE] PROGMEM = {
    0xf871887a,0x468f2917,0x9259fe14,0xd45c8b85,0x58345674,
    0x2dc48009,0x75b328a5,0x45c30745,0x10bd6c99,0xfb914f8c,
};

int ARand::next_int() {
    return ((int)(this->getRandomDWORD() & 0x00007FFF));
}

int ARand::next_int(int min_v, int max_v) {
    return ((int)((max_v - min_v)*this->next_double() + min_v));
}

float ARand::next_float() {
    return ((float)this->getRandomDWORD()/4294967296.0f);
}

double ARand::next_double() {
    return ((double)this->getRandomDWORD()/4294967296.0);
}

double ARand::next_unit_interval() {
	return ((double)this->getRandomDWORD()/4294967295.0);
}

double ARand::next_normal(void) {
	double u1 = this->next_unit_interval();
	double u2 = this->next_unit_interval();
	return (sqrt(-2.0 * log(u1)) * cos(6.28318530718*u2));
}

double ARand::next_normal(double mean, double std) {
	return ((this->next_normal() * std) + mean);
}

/*=================================================================*/

TrueRand::TrueRand(int analog_pin) {
    pinMode(analog_pin, INPUT);
    this->analog_pin = analog_pin;
    this->last_v = rand_core[analogRead(analog_pin) % RAND_CORE_SIZE];
}

uint32_t TrueRand::getRandomDWORD() {
    uint32_t x = ((this->last_v ^ rand_core[x % RAND_CORE_SIZE]) & 0xFFFFF000)
               | ((millis()&0xFF) << 4)
               | (analogRead(this->analog_pin)&0xF);
    x = (((1103515245 * x) + 12345) & 0x7FFFFFFF);
    return (this->last_v = x);
}

/*=================================================================*/

XorShift::XorShift(uint32_t seed = 1) {
    this->seed = seed;
}

uint32_t XorShift::getRandomDWORD() {
    uint32_t x = this->seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return this->seed = x;
}

/*=================================================================*/

LCG::LCG(uint32_t seed = 1) {
	this->seed = seed;
}

uint32_t LCG::getRandomDWORD() {
	this->seed = (((1103515245 * this->seed) + 12345) & 0x7FFFFFFF);
	return this->seed;
}

/*=================================================================*/
