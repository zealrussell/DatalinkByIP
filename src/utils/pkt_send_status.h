#ifndef PKT_SEND_STATUS_H
#define PKT_SEND_STATUS_H

#include "constants.h"
#include <bits/stdc++.h>

/**
 * 
*/
struct pkt_in
{
    pkt_in() : status(NOT_SEND), start_time(clock()) {}
    PKT_STATUS status;
    clock_t start_time;
};


#endif