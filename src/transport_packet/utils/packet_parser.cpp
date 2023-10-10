#include "packet_parser.h"

bool packet_parser::validate_packet(std::string  buffer)
{
    return true;
}

data_packet * packet_parser::parse_datapacket(std::string buffer)
{
    if (!validate_packet(buffer)){
        return nullptr;
    }
    int len = get_packet_length(buffer);
    return (struct data_packet *)(buffer.c_str() + len);
}

ack_packet * packet_parser::parse_ackpacket(std::string buffer)
{
    if (!validate_packet(buffer))
        return nullptr;
    int len = get_packet_length(buffer);
    return (struct ack_packet *)(buffer.c_str() + len);
}

int packet_parser::get_packet_length(std::string buffer)
{
    if (!validate_packet(buffer))
        return -1;
    struct iphdr *ip = (struct iphdr *)(buffer.c_str() + sizeof(struct iphdr));
    return ip->tot_len;
}
