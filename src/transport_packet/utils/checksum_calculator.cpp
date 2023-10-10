#include "./checksum_calculator.h"
#include <vector>
#include <bitset>
#include "checksum_calculator.h"

checksum_calculator::checksum_calculator() {}


uint16_t checksum_calculator::get_checksum(unsigned short * ptr, int nbytes)
{
    register long sum;
    unsigned short oddbyte;
    register short answer;
    sum=0;
    while(nbytes>1) {
        sum+=*ptr++;
        nbytes-=2;
    }
    if(nbytes==1) {
        oddbyte=0;
        *((u_char*)&oddbyte)=*(u_char*)ptr;
        sum+=oddbyte;
    }
 
    sum = (sum>>16)+(sum & 0xffff);
    sum = sum + (sum>>16);
    answer=(short)~sum;
    
    return(answer);
}

bool checksum_calculator::validate(uint16_t old_checksum, uint16_t new_checksum) {

    std::bitset<16> sum = std::bitset<16>(old_checksum + new_checksum);
    for(int i = 0 ; i < sum.size() ; i++){
        if(sum[i])
        return true;
    }
    return false;
}