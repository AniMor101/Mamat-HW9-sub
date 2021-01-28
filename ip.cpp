#include <stdio.h>
#include <cstring>
#include <iostream>
#include "ip.h"

// Constructor, initialization list
Ip::Ip(String pattern) : Field(pattern, IP), low(0), high(0) {
}


bool Ip::set_value(String val) {
    String* sub_ip;
    size_t size = 0;
    unsigned int ip_int = 0;

    // splitting with delimiter / and . into 5,
    val.split("/.", &sub_ip, &size);
    if (size != 5) {
        delete[] sub_ip;
        return false;
    }
    // the four ones : IP
    ip_int =
        (sub_ip[0].trim().to_integer() << 24) |
        (sub_ip[1].trim().to_integer() << 16) |
        (sub_ip[2].trim().to_integer() << 8) |
        (sub_ip[3].trim().to_integer());

    // the last one : mask length
    int mask_length = sub_ip[4].trim().to_integer();
    delete[] sub_ip;
    // mask
    unsigned int bitmask = 0xFFFFFFFF;
    bitmask = (mask_length != 0) ? bitmask << (32 - mask_length) : 0;
    // adding the mask: the lower bits are ones (high) and zeros (low)
    low = ip_int & bitmask;
    high = ip_int | (~bitmask);

    return true;
}


bool Ip::match_value(String val) const {
    String* sub_ip;
    size_t size = 0;
    unsigned int ip_int = 0;
    // split according to . into 4: the IP
    val.split(".", &sub_ip, &size);
    if (size != 4)
    {
        delete[] sub_ip;
        return false;
    }

    ip_int =
        (sub_ip[0].trim().to_integer() << 24) |
        (sub_ip[1].trim().to_integer() << 16) |
        (sub_ip[2].trim().to_integer() << 8) |
        (sub_ip[3].trim().to_integer());

    delete[] sub_ip;
    // check if in the legal range - low, high
    if ((low <= ip_int) && (ip_int <= high)) {
        return true;
    }
    return false;
}
