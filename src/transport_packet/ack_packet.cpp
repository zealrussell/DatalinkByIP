#include "ack_packet.h"

ack_packet::ack_packet(std::string daddr, uint32_t ack_no)
: base_packet(daddr, 2, ack_no){
    this->ip_hdr.tot_len = sizeof(iphdr) + sizeof(link_header);
    this->cal_checksum();
}

std::string ack_packet::to_string(){
   return stringfy_header(); 
}

json ack_packet::to_json()
{
    return jsonfy_header();
}
