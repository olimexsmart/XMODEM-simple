/*
    Sample application receiving a file with XMODEM over IP
*/

#include <stdio.h>
#include "../../include/XM_receiver.h"
#include "../../include/XM_common.h"
#include "../../include/XM_debug.h"

int main()
{
    XM_rx r;

    XM_receiver_init(&r, 1000, 16);
    XM_debug__receiver_print_state(&r);

    XM_receiver_new_char(&r, SOH);
    XM_debug__receiver_print_state(&r);

    XM_receiver_new_char(&r, 23);
    XM_debug__receiver_print_state(&r);

    XM_receiver_new_char(&r, 1);
    XM_debug__receiver_print_state(&r);

    return 0;
}