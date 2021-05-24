/*
    XMODEM symbols
*/

#ifndef XM_COMMON
#define XM_COMMON

#define SOH 0x01 // Start of Header
#define EOT 0x04 // End of Transmission
#define ACK 0x06 // Acknowledge
#define NAK 0x15 // Not Acknowledge

// Function Prototypes
char XMcommon_calculate_checksum(char *data, int len);


/*
    Calculate checksum of data
*/
char XMcommon_calculate_checksum(char *data, int len)
{
    char cs = 0;
    for (int i = 0; i < len; i++)
    {
        cs += data[i];
    }

    return cs;
}

#endif