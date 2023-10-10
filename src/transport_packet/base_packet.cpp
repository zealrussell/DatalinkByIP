#include "base_packet.h"
#include <arpa/inet.h>

base_packet::base_packet(std::string daddr, uint8_t packet_type, uint32_t seq_no, 
    uint8_t link_protocol_type, uint16_t message_type) {
    init_ip_header();
    this->ip_hdr.daddr = inet_addr(daddr.data());
    this->lk_hdr.set_seq_no(seq_no);
}

std::string base_packet::stringfy_header()
{
    return jsonfy_header().dump(4);
}

json base_packet::jsonfy_header()
{
    json j = 
    {
        {"ip_hdr", {
            {"version", get_version()},
            {"ihl", get_ihl()},
            {"tos", get_tos()},
            {"tos_len", get_tos_len()},
            {"id", get_id()},
            {"frag_off", get_frag_off()},
            {"ttl", get_ttl()},
            {"protocol", get_protocol()},
            {"check", get_check()},
            {"saddr", get_saddr()},
            {"daddr", get_daddr()},
        }}
    };
    j["lk_hdr"] = lk_hdr.to_json();
    return j;
}

void base_packet::cal_checksum()
{
    this->set_check(checksum_calculator::get_checksum((unsigned short *)(&this->ip_hdr), this->ip_hdr.ihl));
}

void base_packet::init_ip_header()
{
    ip_hdr.version = 4;
    ip_hdr.ihl = 5;
    ip_hdr.tos = 0;
    ip_hdr.tot_len = 0;
    ip_hdr.id = 0;
    ip_hdr.frag_off = 0;
    ip_hdr.ttl = 255;
    ip_hdr.protocol = 140;
    ip_hdr.check = 0;
    ip_hdr.saddr = inet_addr(LOCAL_IP);
    ip_hdr.daddr = 0;
}


// -------------------------------------------------------------------

uint32_t base_packet::get_seq_no()
{
    return lk_hdr.get_seq_no();
}

uint16_t base_packet::get_link_protocol_type()
{
    return lk_hdr.get_link_protocol_type();
}

uint16_t base_packet::get_message_type()
{
    return lk_hdr.get_message_type();
}

uint32_t base_packet::get_message_length()
{
    return lk_hdr.get_message_length();
}

uint32_t base_packet::get_version()
{
    return ip_hdr.version;
}

uint32_t base_packet::get_ihl()
{
    return ip_hdr.ihl;
}

uint8_t base_packet::get_tos()
{
    return ip_hdr.tos; 
}

uint16_t base_packet::get_tos_len()
{
    return ip_hdr.tot_len;
}

uint16_t base_packet::get_id()
{
    return ip_hdr.id;
}

uint16_t base_packet::get_frag_off()
{
    return ip_hdr.frag_off;
}

uint8_t base_packet::get_ttl()
{
    return ip_hdr.ttl;
}

uint8_t base_packet::get_protocol()
{
    return ip_hdr.protocol;
}

uint16_t base_packet::get_check()
{
    return ip_hdr.check;
}

uint32_t base_packet::get_saddr()
{
    return ip_hdr.saddr;
}

uint32_t base_packet::get_daddr()
{
    return ip_hdr.daddr;
}


void base_packet::set_version(unsigned int value)
{
    this->ip_hdr.version = value;
}

void base_packet::set_ihl(unsigned int value)
{
    this->ip_hdr.ihl = value;
}

void base_packet::set_tos(uint8_t value)
{
    this->ip_hdr.tos = value;
}

void base_packet::set_tos_len(uint16_t value)
{
    this->ip_hdr.tot_len = value;
}

void base_packet::set_id(uint16_t value)
{
    this->ip_hdr.id = value;
}

void base_packet::set_frag_off(uint16_t value)
{
    this->ip_hdr.frag_off = value;
}

void base_packet::set_ttl(uint8_t value)
{
    this->ip_hdr.ttl = value;
}

void base_packet::set_protocol(uint8_t value)
{
    this->ip_hdr.protocol = value;
}

void base_packet::set_check(uint16_t value)
{
    this->ip_hdr.check = value;
}

void base_packet::set_saddr(uint32_t value)
{
    this->ip_hdr.saddr = value;
}

void base_packet::set_daddr(uint32_t value)
{
    this->ip_hdr.daddr = value;
}

void base_packet::set_seq_no(uint32_t value)
{
    this->lk_hdr.set_seq_no(value);
}

void base_packet::set_link_protocol_type(uint16_t value)
{
    this->lk_hdr.set_link_protocol_type(value);
}

void base_packet::set_message_type(uint16_t value)
{
    this->lk_hdr.set_message_type(value);
}

void base_packet::set_message_length(uint32_t value)
{
    this->lk_hdr.set_message_length(value);
}

// -------------------------------------------------------------------
