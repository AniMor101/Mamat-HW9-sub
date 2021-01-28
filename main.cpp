
#include <iostream>
#include <stdlib.h>
#include "string.h"
#include "field.h"
#include "ip.h"
#include "port.h"
#include "input.h"

using namespace std;

int main(int argc, char** argv) {
    // Check args validity
    if ((check_args(argc, argv)) != 0) {
        exit(1);
    }

    String* rule_sub;
    size_t rule_size = 0;
    String rule(argv[1]);

    // Split rule to "pattern" and "val"
    rule.split("=", &rule_sub, &rule_size);
    String pattern = (rule_sub[0]);
    String val = (rule_sub[1]);
    pattern = pattern.trim();
    val = val.trim();

    // Reference class according to pattern
    if ((pattern.equals("src-ip")) || (pattern.equals("dst-ip"))) {
        Ip ip_rule(pattern);
        ip_rule.set_value(val);
        parse_input(ip_rule);
    }
    else if ((pattern.equals("src-port")) || (pattern.equals("dst-port"))) {
        Port port_rule(pattern);
        port_rule.set_value(val);
        parse_input(port_rule);
    }

    delete[] rule_sub;
    return 0;
}