#ifndef DATA_PACKET_H
#define DATA_PACKET_H

#include "base_packet.h"

template<class K, class V, class dummy_compare, class A>
using my_workaround_fifo_map = nlohmann::fifo_map<K, V, nlohmann::fifo_map_compare<K>, A>;
using asc_json = nlohmann::basic_json<my_workaround_fifo_map>;


// 数据包
class data_packet : public base_packet
{
private:
    std::string data;  // 数据链消息数据

public:
    data_packet(std::string daddr, uint32_t seq_no, uint8_t link_protocol_type, uint16_t message_type, std::string data);
    std::string to_string();
    json to_json();

    // getter
    std::string get_data();

    // setter
    void set_data(std::string);
};


#endif