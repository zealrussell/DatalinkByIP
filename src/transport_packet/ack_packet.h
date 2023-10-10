#ifndef ACK_PACKET_H
#define ACK_PACKET_H

#include "base_packet.h"

// ACK包
class ack_packet : public base_packet
{
private:
    /* data */
public:
    ack_packet(std::string daddr, uint32_t ackno);
    
    std::string to_string();
    json to_json();
};



#endif