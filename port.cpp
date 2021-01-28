
#include <stdio.h>
#include <cstdlib>
#include "port.h"

// constructor
Port::Port(String pattern) : Field(pattern, PORT), range{ 0, 0 } {
}


bool Port::set_value(String val) {
    String* sub_port;
    size_t size = 0;

    //Split by "-", the two ports to define the range
    val.split("-", &sub_port, &size);
    if (size != 2) {
        delete[] sub_port;
        return false;
    }

    int p1 = sub_port[0].trim().to_integer();
    int p2 = sub_port[1].trim().to_integer();
    delete[] sub_port;

    range[0] = (p1 < p2) ? p1 : p2;
    range[1] = (p1 < p2) ? p2 : p1;

    return true;
}


bool Port::match_value(String val) const {
    int port_int = val.trim().to_integer();
    // check if in the legal range - range[0],range[1]
    if ((range[0] <= port_int) && (port_int <= range[1])) {
        return true;
    }
    return false;
}
