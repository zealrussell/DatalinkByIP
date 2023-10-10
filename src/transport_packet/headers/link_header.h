#ifndef DATALINKHDR_H
#define DATALINKHDR_H

#include <stdint.h>
#include "../../utils/json.hpp"

using json = nlohmann::json;

class link_header
{
private:
    uint8_t packet_type; // 包类型，0表示空包，1表示数据包，2表示ack包
    uint32_t seq_no; // 包序号
    uint8_t link_protocol_type; // 数据链协议类型，0表示空，1表示link11协议, 2表示link16协议, 3标识link22协议
    uint16_t message_type; // 消息类型
    uint32_t message_length; // 

public:
    link_header();
    json to_json();
    std::string to_string();
    
    // getter
    uint8_t get_packet_type();
    uint32_t get_seq_no();
    uint8_t get_link_protocol_type();
    uint16_t get_message_type();
    uint32_t get_message_length();

    // setter
    void set_packet_type(uint8_t value);
    void set_seq_no(uint32_t value);
    void set_link_protocol_type(uint8_t value);
    void set_message_type(uint16_t value);
    void set_message_length(uint16_t value);
};


#endif