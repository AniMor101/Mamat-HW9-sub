
#include <iostream>
#include <cstring>
#include "field.h"
#include "ip.h"
#include "port.h"


// constructor
Field::Field(String pattern, field_type type) : pattern(pattern), type(type) {
}

// constructor
Field::Field(String pattern) : pattern(pattern), type(GENERIC) {
}

// destructor
Field::~Field() {
}

// get type 
field_type Field::get_type() const {
    return type;
}


bool Field::set_value(String val) {
    if (type == IP) {
        return ((Ip*)this)->set_value(val);
    }

    if (type == PORT) {
        return ((Port*)this)->set_value(val);
    }

    return false;
}


bool Field::match_value(String val) const {
    if (type == IP) {
        return ((Ip*)this)->match_value(val);
    }

    if (type == PORT) {
        return ((Port*)this)->match_value(val);
    }

    return false;
}


bool Field::match(String packet) {
    String* packet_parts;
    size_t part_num = 0;
    // split packets according to , into rule
    packet.split(",", &packet_parts, &part_num);
    for (int i = 0; i < (int)part_num; i++) {
        String* sub_packet;
        size_t sub_num;
        // split the rule according to = into pattern (ip/port) and value
        packet_parts[i].trim().split("=", &sub_packet, &sub_num);
        if (sub_num == 0) {
            continue;
        }
        if (sub_num != 2) {
            delete[] sub_packet;
            continue;
        }

        String ip_or_port = sub_packet[0].trim();
        String value = sub_packet[1].trim();
        // compare pattern and value
        if (ip_or_port.equals(pattern) && match_value(value)) {
            delete[] sub_packet;
            delete[] packet_parts;
            return true;
        }
        delete[] sub_packet;
    }

    if (part_num != 0) {
        delete[] packet_parts;
    }
    return false;
}

