#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include <vector>
#include <string>

#include "../headers/packet_header.h"
#include "../base_packet.h"
#include "../data_packet.h"
#include "../ack_packet.h"

/**
 * 数据包解析器
*/
class packet_parser
{
private:
    // 检查数据包是否合法
    static bool validate_packet (std::string buffer);

public:
    static packet_header parse_packet_header(std::string buffer);
    static data_packet *parse_datapacket(std::string buffer);
    static ack_packet *parse_ackpacket(std::string buffer);
    static int get_packet_length(std::string buffer);

};

#endif