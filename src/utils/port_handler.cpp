#include "port_handler.h"
#include "constants.h"

port_handler::port_handler() {

}

port_handler::port_handler(int &socket_fd, struct sockaddr_in *addr, socklen_t *addr_len) 
    : socket_fd(socket_fd), addr(addr), addr_len(addr_len)  {

}

int port_handler::send(std::string data) {
    char *buff = (char *)data.data();
    int len = data.size();
    return writeExact(buff, len);
}

int port_handler::receive(std::string &buffer) {
    char buf[MAX_REQ_SZ] = {0};
    tryRead(buf, HEADER_SZ);
    std::string pkg(buf);
    int len;
    int n = readExact(buf, len);
    buffer = std::string(buf, n);

    return n;
}

/**
 * 分段发送数据
*/
int port_handler::writeExact(char * buffer, int sz)
{
    char * ptr = buffer;
    int len = sz;
    while (len > 0) {
        int status = write(ptr, len);
        if (status == -1) {
            printf("%s \n", strerror(errno));
            return status;
        }
        if (status == 0) break;
        ptr += status;
        len -= status;
    }
    return sz;
}


int port_handler::tryRead(char * total, int sz)
{
    return recvfrom(socket_fd, total, sz, 0, (struct sockaddr *) addr, addr_len);
}

int port_handler::readExact(char * total, int sz)
{
    int len = sz;
    char *buffer = total;
    while (sz > 0) {
        // 有效读取到的数据长度
        int valread = read(buffer, sz);
        // 读取错误
        if (valread < 0) {
            return -1;
        }
        if (valread == 0) {
            break;
        }
        sz -= valread;
        buffer += valread;

    }
    return len - sz;
}

/**
 * 调用 recv 接收
*/
int port_handler::read(char * buffer, int sz)
{
    return recvfrom(socket_fd, buffer, sz, 0, (struct sockaddr *) addr, addr_len);
}

/**
 * 调用sendto发送
*/
int port_handler::write(char * buffer, int sz)
{
    return sendto(socket_fd, buffer, sz, 0, (struct sockaddr *) addr, *addr_len);
}


int port_handler::closeConnection()
{
    return close(socket_fd);
}