#ifndef SR_SERVER_H
#define SR_SERVER_H

#include "selective_repeat.h"
#include "../../utils/constants.h"
#include "../../utils/port_handler.h"
#include "../../utils/pkt_send_status.h"
#include "../../transport_packet/data_packet.h"
#include "../../transport_packet/ack_packet.h"

#include <pthread.h>
#include <vector>

/**
 * 发送端，发送数据包
*/
class sr_server : public selective_repeat
{
private:
    // 存放待发送的包
    std::vector<data_packet *> data_packets;
    // 所有发送包的状态
    std::vector<struct pkt_in> pkts_status;
    // 发送、接收线程
    pthread_t send_id, recv_id;
    pthread_mutex_t lock;

    void send_packet(int index);
    // 发送功能的工作线程
    static void * run_sender_thread(void * tmp);
    // 接收功能的工作线程
    static void * run_receiver_thread(void * tmp);
    
    // 发送功能的具体实现函数
    void send_handler();
    // 接收功能的具体实现函数
    void recv_handler();

public:
    sr_server(port_handler *p);

    void init(std::vector<data_packet *> &data_packets);
    void implement();
};

#endif