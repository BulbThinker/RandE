/*
 *  RandE
 *  @BulbThinker
 *  2019
 *  randE.h
 */
#ifndef RAND_E_H
#define RAND_E_H

#include <stdint.h>
#include <Arduino.h>


class ARand {
    private:
        virtual uint32_t getRandomDWORD(void) = 0;
    public:
        virtual int next_int(void);
        virtual int next_int(int min_v, int max_v);
        virtual float next_float(void);
        virtual double next_double(void);
		virtual double next_unit_interval(void);
		virtual double next_normal(void);
		virtual double next_normal(double mean, double std);
};


class TrueRand : public ARand{
    private:
        int analog_pin;
        uint32_t last_v;
        uint32_t getRandomDWORD(void);
    public:
        TrueRand(int analog_pin);
};


class XorShift : public ARand {
    private:
        uint32_t seed;
        uint32_t getRandomDWORD(void);
    public:
        XorShift(uint32_t seed);
};

class LCG : public ARand {
	private:
        uint32_t seed;
        uint32_t getRandomDWORD(void);
		uint32_t A, C, M;
    public:
        LCG(uint32_t seed);
};

#endif
