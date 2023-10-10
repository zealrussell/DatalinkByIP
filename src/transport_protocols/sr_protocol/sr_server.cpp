#include "./sr_server.h"
#include "../transport_packet/utils/packet_parser.h"

sr_server::sr_server(port_handler *p) : selective_repeat(p) {
    pthread_mutex_init(&lock, NULL);
}

void sr_server::init(std::vector<data_packet *> &data_packets) {
    this->data_packets = data_packets;
    ack_packet ak(CLIENT_IP, data_packets.size());
    // 向接收端发送数据包总数
    p_handler->send(ak.to_string());
    pkts_status.resize(data_packets.size());
}

void sr_server::implement() {
    pthread_create(&recv_id, NULL, run_receiver_thread, this);
    pthread_create(&send_id, NULL, run_sender_thread, this);

    pthread_join(recv_id, NULL);
    pthread_join(send_id, NULL);
}

void * sr_server::run_sender_thread(void * tmp) {
    ((sr_server *)tmp)->send_handler();
    pthread_exit(NULL);
}

void * sr_server::run_receiver_thread(void * tmp) {
    ((sr_server *)tmp)->recv_handler();
    pthread_exit(NULL);
}

// 发送功能的具体实现函数
void sr_server::send_handler() {
    int base = 0;   // 当前需要发送的包序号
    int number_pkts = data_packets.size();  // 需要发送的总数
    clock_t curr_time;

    while (base < number_pkts) {
        
        int remaining = number_pkts - base;
        for (int i = base; ((i - base) < remaining); i++) {
            switch (pkts_status[i].status)
            {
            case ACKED:
                break;
            case NOT_SEND:
                send_packet(i);
                break;
            case SENT: 
                curr_time = clock();
                if ((curr_time - pkts_status[i].start_time) > PKT_LOSS_TIME) {
                    send_packet(i);
                }
                break;
            default:
                break;
            }
        }

        // 滑动窗口
        while (pkts_status[base].status == ACKED && base < number_pkts) base++;
        
    }

}

// 接收ACK功能的具体实现函数
void sr_server::recv_handler() {
    int ack_pkts_counter = 0;   // 接收包计数器
    std::set<int> recevied_seq_no;  // 接收序号的队列

    while(ack_pkts_counter < data_packets.size()) {
        // 1. 接收ack序号
        std::string buffer;
        p_handler->receive(buffer);
        ack_packet *pkt = packet_parser::parse_ackpacket(buffer); // 序列化得到ack包

        uint32_t pkt_seq_no = pkt->get_seq_no(); // 当前ack包的序号
        ack_packet ack(CLIENT_IP, pkt_seq_no);

        // 2. 校验ack
        if(true) {
            int exists = (recevied_seq_no.find(pkt_seq_no) != recevied_seq_no.end());
            if (exists == 1) {
                delete pkt;
                continue;
            }

            // 将发送的包标记为确认
            pthread_mutex_lock(&lock);
            pkts_status[pkt_seq_no].status = ACKED;
            successful_sent++;
            pthread_mutex_unlock(&lock);

            recevied_seq_no.insert(pkt_seq_no);
            ack_pkts_counter++;
        }
        delete pkt;
    }
}
void sr_server::send_packet(int seq_no) {
    // 从发送队列中获取要发送的数据包
    data_packet *curr_pkt = data_packets[seq_no];
    
    pkts_status[seq_no].status = SENT;
    pkts_status[seq_no].start_time = clock();
    if (true){
        p_handler->send(curr_pkt->to_string());
        printf("Packet with seqno %d will be send\n", seq_no);
    }
    total_sent++;
}