/*
    Sample application receiving a file with XMODEM over IP
*/

#include <stdio.h>
#include "../../include/XM_receiver.h"

int main() {
    XM_rx r;

    XM_receiver_init(&r, 1000, 16);

    return 0;
}