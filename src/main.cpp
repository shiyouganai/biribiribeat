/**
 * \file
 * \author shiyouganai
 * \copyright 2019-2020 shiyouganai
 * 
 * \brief Entry point of C++ program after runtime init.
 */
#include <Arduino.h>
#include "game.h"

int main(void)
{
    /* arduino specific init */
    init();
    Serial.begin(9600);

    /* atmega32u4 usb device init */
    #if defined(USBCON)
    USBDevice.attach();
    #endif

    /* init game */
    game main_game;

    /* main game loop, will not return unless error */
    #ifdef DEBUG_SERIAL
    Serial.print("Entering main game loop");
    #endif
    main_game.loop();

    /* we should never get here in normal operation */
    for (;;) {
        #ifdef SERIAL_EVENTS
        if (serialEventRun) serialEventRun();
        #endif
	}

    return 0;
}