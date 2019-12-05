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


class IRand {
    private:
        virtual uint32_t getRandomDWORD(void) = 0;
    public:
        virtual int next_int(void) = 0;
        virtual int next_int(int min_v, int max_v) = 0;
        virtual float next_float(void) = 0;
        virtual double next_double(void) = 0;
};


class TrueRand : public IRand{
    private:
        int analog_pin;
        uint32_t last_v;
        uint32_t getRandomDWORD(void);
    public:
        TrueRand(int analog_pin);
        int next_int(void);
        int next_int(int min_v, int max_v);
        float next_float(void);
        double next_double(void);
};


class XorShift : public IRand {
    private:
        uint32_t seed;
        uint32_t getRandomDWORD(void);
    public:
        XorShift(uint32_t seed);
        int next_int(void);
        int next_int(int min_v, int max_v);
        float next_float(void);
        double next_double(void);
};

#endif
