#include "link_header.h"

link_header::link_header()
{
    packet_type = 0;
    seq_no = 0;
    link_protocol_type = 0;
    message_type = 0;
    message_length = 0;
}



json link_header::to_json()
{
    json j = 
    {
        {"packet_type", packet_type},
        {"seq_no", seq_no},
        {"link_protocol_type", link_protocol_type},
        {"message_type", message_type},
        {"message_length", message_length}
    };

    return j;
}

std::string link_header::to_string()
{
    auto j = to_json();
    return j.dump(4); 
}

// ------------------------------------------------------

uint8_t link_header::get_packet_type()
{
    return packet_type;
}

uint32_t link_header::get_seq_no()
{
    return seq_no;
}

uint8_t link_header::get_link_protocol_type()
{
return link_protocol_type;
}

uint16_t link_header::get_message_type()
{
return message_type;
}

uint32_t link_header::get_message_length()
{
return message_length;
}

void link_header::set_packet_type(uint8_t value)
{
    this->packet_type = value;
}

void link_header::set_seq_no(uint32_t value)
{
    seq_no = value;
}

void link_header::set_link_protocol_type(uint8_t value)
{
link_protocol_type = value;
}

void link_header::set_message_type(uint16_t value)
{
message_type = value;
}

void link_header::set_message_length(uint16_t value)
{
message_length = value;
}