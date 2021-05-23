# XMODEM-simple
Implementation of the XMODEM protocol for any use case. 

The motivation for coding something that was been coded over and over for the last 40 yers is that we needed a controlled evironment for teaching purposes. This library is developed and maintaned for the Natta Deambrosis ITIS school.

## Structure
For the sake of simplicity, the library is implemente just in two header files, one for the transmitter and one for the receiver. 

This avoids modifying the compile command to include also the source files. 

It is possible to have multiple instances of transmitters and receivers, each having it's own data structure. 

## Examples
The examples provided show different possible usages of the library. The developing is done using a TCP/IP socket, but a practical usage is the transfer of data between Arduino and the PC over the serial port.
