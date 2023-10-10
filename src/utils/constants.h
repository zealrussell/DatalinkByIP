#ifndef CONSTANTS_H
#define CONSTANTS_H

// 定义常量

#define MAX_REQ_SZ 1024
#define HEADER_SZ 36
#define DELM "\r\n"

#define CS_IDX 0
#define LEN_IDX 1
#define SEQ_IDX 2


// 数据包的长度
#define DATA_SZ 500

/* event types for congestion control */
enum EVENT_TYPE {ACK, TIMEOUT, DupACK};

// 数据包的状态: 已确认，未发送， 已发送
enum PKT_STATUS {ACKED, NOT_SEND, SENT};

#define MSS 512
#define INITIAL_THRESHOLD MSS
#define MAX_WINDOW_SZ 1024

// 超时重传时间
#define PKT_LOSS_TIME 100000


#endif