#include "packet_manager.h"



std::string packet_manager::assemble_data(std::vector<data_packet*> packet_queue)
{
    std::sort(packet_queue.begin(), packet_queue.end(), comp);
    std::string data= "";
    // 从数据包中取出数据并拼接
    for (data_packet *p : packet_queue) {
        data += p->get_data();
        delete p;
    }
    return data;
}

std::vector<data_packet*> packet_manager::disassemble_data(std::string data, char* daddr, 
    uint32_t seq_no, uint8_t link_protocol_type, uint16_t message_type)
{
    // 切分字符串
    std::vector<std::string> chunks;
    for (int i = 0; i < data.size(); i += DATA_SZ) {
        std::string chunk = data.substr(i, DATA_SZ);
        chunks.push_back(chunk);
    }

    // 封装数据包
    std::vector<data_packet*> packets;
    for(std::string chunk : chunks) {
        data_packet *pkt = new data_packet(daddr, seq_no, link_protocol_type, message_type, chunk);
        packets.push_back(pkt);
        seq_no++;
    }
    return packets;
}

bool packet_manager::comp(data_packet * p1, data_packet * p2)
{
    return p1->get_seq_no() < p2->get_seq_no();
}
