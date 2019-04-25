#ifndef PKT_H
#define PKT_H
#include <stdint.h>
#include <cstdio>
//#pragma execution_character_set("utf-8")

const int  data_size0=800;
struct packet {
    uint16_t len;//64K
    uint32_t seqnum;
    char data[data_size0];
};
struct ack_packet {
    uint16_t len;
    uint32_t acknum;
};

class pkt
{
public:
    pkt();
};

#endif // PKT_H
