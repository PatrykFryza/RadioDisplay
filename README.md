RadioDisplay is a firmware for STM32F4 discovery development kit with nRF24L01+.

The code contains LCD and touchscreen implementation and SPI functionality for wireless module.
When program starts it generates two buttons on the display, clicking each of them is sending other message via nRF module.
Rest of the LCD is showing received messages that comes from other nRF modules (this project was made physically in 2 copies).

Both touchscreen and nRF receiving are working on interrupt.
