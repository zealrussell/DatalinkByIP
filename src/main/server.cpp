#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

#include "../transport_protocols/rdt_strategy.h"
#include "../transport_protocols/sr_protocol/sr_server.h"
#include "../transport_packet/utils/packet_manager.h"

#include "../transport_packet/data_packet.h"

#include "../utils/config.h"

#define SERVER_PORT 8090
#define SERVER_IP "106.15.191.2"

string readFileIntoString(char * filename)
{
    ifstream ifile(filename);
    //将文件读入到ostringstream对象buf中
    ostringstream buf;
    char ch;
    while(buf&&ifile.get(ch))
    buf.put(ch);
    //返回与流对象buf关联的字符串
    return buf.str();
}


int main () {

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SERVER_PORT);
    sin.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    // Allocate string buffer to hold incoming packet data
   
    // Open the raw socket
    int sock = socket (PF_INET, SOCK_RAW,  htons(ETH_P_IP));
    if (bind(sock, (const struct sockaddr *)& sin, sizeof(sin)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    std::vector<data_packet *> data_packets;
    string data = readFileIntoString((char *)"../../data/file.txt");
    data_packets = packet_manager::disassemble_data(data, CLIENT_IP);
    sleep(5000);
    printf("start receive\n");
    
    while(1) {
        struct sockaddr_in cliaddr;
        int n;
        socklen_t len;
        memset(&cliaddr, 0, sizeof(cliaddr));
        port_handler p(sock, &cliaddr, &len);
        std::string buffer;
        n = p.receive(buffer);

        auto *strategy = new sr_server(&p);
        strategy->init(data_packets);
        strategy->implement();
    }

    
    return 0;
}