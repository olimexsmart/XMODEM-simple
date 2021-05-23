/*
    XMODEM receiver 
*/

#ifndef XM_RECEIVER
#define XM_RECEIVER

#include "XM_common.h"

#define BUFFER_LEN 1000

/*
    State of the receiver as a whole
    W_ stands for WAITING
*/
typedef enum rec_state
{
    W_SOH,
    W_PACKET,
    W_PACKET_I,
    W_DATA,
    W_CHECKSUM,
    DONE,
    ERROR
} rx_state;

/*
    List of possible errors
*/
typedef enum rec_errors
{
    E_NONE,
    E_SOH,
    E_PACKET,
    E_PACKET_I,
    E_CHECKSUM,
    E_TIMEOUT,
    E_STATE
} rx_err;

/*
    Defines an istance of receiver
*/
typedef struct XM_receiver
{
    rx_state state;
    rx_err err;
    char buffer[BUFFER_LEN];
    int index;
    int index_data;
    char packet;
    int timeout;
    int packet_size;
} XM_rx;

/*
    TODO learn to use doxygen and write decent documentation

    timeout is in ms and used in multiple types of error
    packer_size is the amount of data that each packet carries
*/
void XM_receiver_init(XM_rx *r, int timeout, int packet_size)
{
    r->state = W_SOH;
    r->err = E_NONE;
    r->packet = 1;
    r->index = 0;
    r->timeout = timeout;
    r->packet_size = packet_size;
}

/*
    when the receiver returns an ERROR state, it can be useful
    to know exactly what error we are talking about.
    The receiver goes back to a W_SOH
*/
rx_err XM_receiver_get_error(XM_rx *r)
{
    return r->err;
}

/*
    takes a bunch of chars all at once
*/
rx_state XM_receiver_new_data(XM_rx *r, char *data, int len)
{
    rx_state s;
    for (int i = 0; i < len; i++)
    {
        s = XM_receiver_new_char(r, data[i]);
    }

    return s;
}

/*
    Feeds the receiver FSM with new data

    Check return value to understand what is going on
*/
rx_state XM_receiver_new_char(XM_rx *r, char c)
{
    // If we are reusing the receiver after a complete tranfer, re-init
    if (r->state == DONE)
    {
        XM_receiver_init(r, r->timeout, r->packet_size);
    }

    // TODO implement timeout

    // Reset the error state
    if (r->err != E_NONE)
    {
        r->state = W_SOH;
        r->err = E_NONE;
    }

    // Main FSM logic
    switch (r->state)
    {
    // Waiting for SOH
    case W_SOH:
        if (c == SOH) // Correctly received SOH
        {
            r->state = W_PACKET;
        }
        else if (c == EOT) // No more stuff to receive, DONE
        {
            r->state = DONE;
        }
        else
        {
            r->state = ERROR;
            r->err = E_SOH;
        }
        break;
    // Waiting for packet number
    case W_PACKET:
        if (c == r->packet)
        {
            r->state = W_PACKET_I;
        }
        else
        {
            r->state = ERROR;
            r->err = E_PACKET;
        }
        break;
    // Waiting for inverse packet number
    case W_PACKET_I:
        if (255 - c == r->packet)
        {
            r->state = W_DATA;
        }
        else
        {
            r->state = ERROR;
            r->err = W_PACKET_I;
        }
        break;
    // Waiting to receive all the data
    case W_DATA:
        r->buffer[r->index + r->index_data] = c;
        r->index_data++;
        if (r->index_data >= r->packet_size)
        {
            r->state = W_CHECKSUM;
        }
        // No error other than timeout can be thrown from this state
        break;
    // Waiting for checksum
    case W_CHECKSUM:
        if (c == XMcommon_calculate_checksum(r->buffer[r->index], r->packet_size))
        {
            // Checksum passed, confirm data and prepare for next packet
            r->state = W_SOH;
            r->index = r->packet_size;
            r->index_data = 0;
            r->packet++;
            r->packet %= 255;
        }
        else
        {
            // Checksum error
            r->state = ERROR;
            r->err = E_CHECKSUM;
        }
        break;
    // No idea why we are here, reset to W_SOH
    default:
        r->state = ERROR;
        r->err = E_STATE;
        break;
    }

    // Update caller with what is going on
    return r->state;
}

#endif