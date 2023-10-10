#ifndef PACKET_MANAGER_H
#define PACKET_MANAGER_H

#include <vector>
#include <string>
#include "../base_packet.h"
#include "../data_packet.h"
#include "../../utils/constants.h"

/**
 * 数据包的封装与拆解
*/
class packet_manager
{
public:
    // 将对象格式的数据合并成字符串
    static std::string assemble_data(std::vector<data_packet*> packet_queue);
    // 将字符串格式的数据
    static std::vector<data_packet*> disassemble_data(std::string data, char* daddr, uint32_t seq_no=0, uint8_t link_protocol_type=0, uint16_t message_type=0);

private:
    packet_manager(/* args */) = default;
    // 按包序号从小到大排序
    static bool comp(data_packet *p1, data_packet *p2);
};


#endif