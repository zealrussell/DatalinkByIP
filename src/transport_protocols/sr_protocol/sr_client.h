#ifndef SR_CLIENT_H
#define SR_CLIENT_H

#include "./selective_repeat.h"
#include "../transport_packet/data_packet.h"
#include "../transport_packet/ack_packet.h"

/**
 * 接收端，接收数据包，并发送ack
*/
class sr_client : public selective_repeat
{
private:

    // 将接收到的数据包总数
    int expected_packets_count;
    // 接收到的数据包队列
    std::vector<data_packet *> *received_packets;

public:
    sr_client(port_handler *p);

    void init(int expected_packets_count, vector<data_packet *> *received_packets);
    void implement();
};


#endif