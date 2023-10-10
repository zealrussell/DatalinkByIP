#ifndef PORT_HANDLER_H
#define PORT_HANDLER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <string>
#include <string.h>

class port_handler {
    private:
        int socket_fd;
        struct sockaddr_in *addr;
        socklen_t *addr_len;
    public:

        port_handler();
        port_handler(int &socket_fd, struct sockaddr_in *addr, socklen_t *addr_len);
        
        int send(std::string data);
        int receive(std::string &buffer);

    private:
        int write(char *buffer, int sz);
        int writeExact(char *buffer, int sz);
        int read(char *buffer, int sz);
        int tryRead(char *total, int sz);
        int readExact(char *total, int sz);
        int closeConnection();
};

#endif