#ifndef BASE_PACKET_H
#define BASE_PACKET_H

#include <netinet/ip.h>
#include <string>
#include "./headers/link_header.h"
#include "./utils/checksum_calculator.h"

#include "../utils/config.h"
#include "../utils/json.hpp"
#include "../utils/fifo_map.hpp"

using json = nlohmann::json;

/**
 * 基础数据包
*/
class base_packet
{
private:
    std::string sz;

protected:
    iphdr ip_hdr;   // ip头
    link_header lk_hdr; // 数据链协议头

    void cal_checksum();  // 计算ip校验和
    
    std::string stringfy_header();  // 将对象转为字符串
    json jsonfy_header();  // 将对象转为json

public:
    base_packet(std::string daddr, uint8_t packet_type=0, uint32_t seq_no=0, uint8_t link_protocol_type=0, uint16_t message_type=0);
    virtual ~base_packet() = default;
    virtual std::string to_string() = 0;

    // getter
    uint32_t get_version();
    uint32_t get_ihl();
    uint8_t get_tos();
    uint16_t get_tos_len();
    uint16_t get_id();
    uint16_t get_frag_off();
    uint8_t get_ttl();
    uint8_t get_protocol();
    uint16_t get_check();
    uint32_t get_saddr();
    uint32_t get_daddr();

    uint32_t get_seq_no();
    uint16_t get_link_protocol_type();
    uint16_t get_message_type();
    uint32_t get_message_length();

    // setter
    void set_version(unsigned int value);
    void set_ihl(unsigned int value);
    void set_tos(uint8_t value);
    void set_tos_len(uint16_t value);
    void set_id(uint16_t value);
    void set_frag_off(uint16_t value);
    void set_ttl(uint8_t value);
    void set_protocol(uint8_t value);
    void set_check(uint16_t value);
    void set_saddr(uint32_t value);
    void set_daddr(uint32_t value);

    void set_seq_no(uint32_t value);
    void set_link_protocol_type(uint16_t value);
    void set_message_type(uint16_t value);
    void set_message_length(uint32_t value);
private:
    void init_ip_header();
};

#endif