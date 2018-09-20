/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Ang Zhi Yuan
 *
 * Created on 19 September, 2018, 12:42 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <thread>
#include <unistd.h>			//Used for UART
#include <fcntl.h>			//Used for UART
#include <termios.h>

using namespace std;

int setupUart() {
    //-------------------------
    //----- SETUP USART 0 -----
    //-------------------------
    //At bootup, pins 8 and 10 are already set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively
    int uart0_filestream = -1;

    //OPEN THE UART
    //The flags (defined in fcntl.h):
    //	Access modes (use 1 of these):
    //		O_RDONLY - Open for reading only.
    //		O_RDWR - Open for reading and writing.
    //		O_WRONLY - Open for writing only.
    //
    //	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
    //											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
    //											immediately with a failure status if the output can't be written immediately.
    //
    //	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
    uart0_filestream = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY );		//Open in blocking read/write mode
    if (uart0_filestream == -1) {
            //ERROR - CAN'T OPEN SERIAL PORT
            printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
    }

    //CONFIGURE THE UART
    //The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
    //	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
    //	CSIZE:- CS5, CS6, CS7, CS8
    //	CLOCAL - Ignore modem status lines
    //	CREAD - Enable receiver
    //	IGNPAR = Ignore characters with parity errors
    //	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
    //	PARENB - Parity enable
    //	PARODD - Odd parity (else even)
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;		//<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);
    return uart0_filestream;
}

int uartFilestream  = -1;

void receiver() {
    if (uartFilestream == -1)
        return;
    //----- CHECK FOR ANY RX BYTES -----
    // Read up to 255 characters from the port if they are there
    unsigned char rx_buffer[256];
    while (1) {
        int rx_length = read(uartFilestream, (void*)rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max)
        if (rx_length > 0) {
            //Bytes received
            rx_buffer[rx_length] = '\0';
            printf("%s\n", rx_buffer);
        }
    }
}

void sender() {
    if (uartFilestream == -1) {
        return;
    }
    char tx_buffer[256] = "Hello World\n";
    printf("Sent hello world\n");
    while (1) {
        write(uartFilestream, tx_buffer, strlen(tx_buffer));
    }
    while(fgets(tx_buffer, 256 , stdin) != NULL)
    {
        int count = write(uartFilestream, tx_buffer, strlen(tx_buffer));		//Filestream, bytes to write, number of bytes to write
        if (count < 0) {
                printf("UART TX error\n");
        }
    }
    return;
}

/*
 * 
 */
int main(int argc, char** argv) {
    uartFilestream = setupUart();
    printf("Set up UART filestream\n");
    thread first (receiver);     // spawn new thread that calls foo()
    thread second (sender);  // spawn new thread that calls bar(0)
    
    // synchronize threads:
    first.join();                // pauses until first finishes
    second.join();               // pauses until second finishes
    return 0;
}

