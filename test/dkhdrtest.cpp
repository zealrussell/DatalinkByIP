#include "../src/transport_packet/headers/datalinkhdr.h"
#include <iostream>

using namespace std;

int main() {
    link_header hdr;
    // auto j = hdr.to_json();
    //std::cout << j.dump(4) << std::endl;
    cout << hdr.get_seq_no();
}