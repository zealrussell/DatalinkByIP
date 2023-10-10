#include "data_packet.h"

data_packet::data_packet(std::string daddr, uint32_t seq_no, uint8_t link_protocol_type, uint16_t message_type, std::string data)
:base_packet(daddr, 1, seq_no, link_protocol_type, message_type), data(data) {
    this->lk_hdr.set_message_length(data.length());
    this->ip_hdr.tot_len = sizeof(iphdr) + sizeof(link_header) + data.length();
    this->cal_checksum();
}

std::string data_packet::to_string()
{
    return to_json().dump(4);
}

json data_packet::to_json()
{
    asc_json j = jsonfy_header();
    j["data"] = data.data();
    return j;
}

// -------------------------------------------------------------------
std::string data_packet::get_data()
{
    return data;
}

void data_packet::set_data(std::string value)
{
    this->data = value;
}
