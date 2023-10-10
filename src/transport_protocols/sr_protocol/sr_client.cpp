#include "./sr_client.h"
#include "../../transport_packet/utils/checksum_calculator.h"
#include "../../transport_packet/utils/packet_parser.h"

sr_client::sr_client(port_handler *p) : selective_repeat(p) { }

/**
 * expected_packets_count: 将要接收的数据包总数
 * recevied_packets: 将接收到的数据包存入数组中
*/
void sr_client::init(int expected_packets_count, std::vector<data_packet *> *recevied_packets) {
    this->expected_packets_count = expected_packets_count;
    this->received_packets = received_packets;
}

/**
 * 
*/
void sr_client::implement() {
    
    std::set<int> received_seq_no; // 接收序号的窗口

    int received_pkt_count = 0;
    while (received_pkt_count < expected_packets_count) {
        // 1. 接收数据包
        std::string buffer;
        p_handler->receive(buffer);
        // 2. 将接收的包反序列化为对象
        data_packet *curr_pkt = packet_parser::parse_datapacket(buffer);

        int pkt_seq_no = curr_pkt->get_seq_no();
        printf("packet %d have been recevied. \n", pkt_seq_no);
        // 3. 发送ack数据包
        ack_packet ack(CLIENT_IP, pkt_seq_no);
        if (checksum_calculator::validate(1,3)) {
            p_handler->send(ack.to_string());
            
            // 当前接收的包序号是否收到过
            // 0：在，重复包
            // 1：不在，新包
            int exists = (received_seq_no.find(pkt_seq_no) != received_seq_no.end());
            
            if (exists == 1) continue; // 已收到的重复包，不继续
            // 4. 新包，存入接收队列
            received_packets->push_back(curr_pkt);
            received_seq_no.insert(pkt_seq_no);
            received_pkt_count++;
        }
    }

}