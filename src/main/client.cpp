#include <iostream>
#include "../transport_packet/ack_packet.h"
#include "../transport_packet/data_packet.h"
#include "../transport_packet/utils/packet_manager.h"
#include "../transport_packet/utils/packet_parser.h"

#include "../transport_protocols/sr_protocol/sr_client.h"
#include "../transport_protocols/rdt_strategy.h"
#include "../utils/config.h"


using namespace std;

int main() {
    int socket_fd = socket(AF_INET, SOCK_RAW, htons(ETH_P_IP));
    if (socket_fd < 0) {
        perror("socket create error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8080);
    sin.sin_addr.s_addr = inet_addr(CLIENT_IP);

    socklen_t sin_len = sizeof(sin);

    port_handler *p = new port_handler(socket_fd, &sin, &sin_len);


    string buffer;
    p->receive(buffer);
    ack_packet *response = packet_parser::parse_ackpacket(buffer);
    int expected_packets_count = response->get_seq_no();
    delete response;

    vector<data_packet *> received_packets;
    auto *strategy = new sr_client(p);
    strategy->init(expected_packets_count, &received_packets);
    strategy->implement();
    std::string data = packet_manager::assemble_data(received_packets);
    cout << "data:  " << data << endl;
    return 0;   

}