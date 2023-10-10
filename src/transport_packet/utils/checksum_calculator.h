#ifndef CHECKSUM_CALCULATOR_H
#define CHECKSUM_CALCULATOR_H

#include <string>
#include <bits/types.h>

class checksum_calculator
{
private:
    checksum_calculator();
public:
    static checksum_calculator instans;
    static uint16_t get_checksum(unsigned short *ptr, int nbytes);
    static bool validate(uint16_t old_checksum, uint16_t new_checksum);

};

#endif