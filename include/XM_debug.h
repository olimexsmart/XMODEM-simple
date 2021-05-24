/*
    Contains debug prints for the XM library
*/

#include <stdio.h>
#include "XM_receiver.h"

// Function Prototypes
void XM_debug__receiver_print_error(XM_rx *r);
void XM_debug__receiver_print_state(XM_rx *r);


/*
    Prints out a sho
*/
void XM_debug__receiver_print_state(XM_rx *r)
{
    switch (r->state)
    {
    case W_SOH:
        printf("Receiver is waiting for SOH.\n");
        break;
    case W_PACKET:
        printf("Receiver is waiting for packet number.\n");
        break;
    case W_PACKET_I:
        printf("Receiver is waiting for inverted packet number.\n");
        break;
    case W_DATA:
        printf("Receiver is receiving data.\n");
        break;
    case W_CHECKSUM:
        printf("Receiver is waiting for checksum.\n");
        break;
    case DONE:
        printf("Receiver is done receiving. Data is ready.\n");
        break;
    case ERROR:
        printf("Receiver is in error state: ");
        XM_debug__receiver_print_error(r);
        break;
    default:
        printf("DEBUG ERROR: state not recognized.\n");
        break;
    }
}

void XM_debug__receiver_print_error(XM_rx *r)
{
    switch (r->err)
    {
    case E_NONE:
        printf("No error present.\n");
        break;
    case E_SOH:
        printf("Expected SOH but received something else.\n");
        break;
    case E_PACKET:
        printf("Incorrect packet number.\n");
        break;
    case E_PACKET_I:
        printf("Incorrect inverse packet number.\n");
        break;
    case E_CHECKSUM:
        printf("Incorrect checksum.\n");
        break;
    case E_TIMEOUT:
        printf("Timeout exceeded.\n");       
        break; 
    default:
        printf("DEBUG ERROR: error not recognized.\n");
        break;
    }
}