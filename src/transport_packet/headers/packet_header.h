#ifndef PACKET_HEADER_H
#define PACKET_HEADER_H

#include "./link_header.h"
#include <netinet/ip.h>

struct packet_header
{
    struct iphdr;
    struct link_header;
};


#endif