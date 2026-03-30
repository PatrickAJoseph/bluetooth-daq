#ifndef SSCP_APP_H
#define SSCP_APP_H

/* Application function definitions. */

extern void gpioWriteRegCallback(void* reg, int operation);
extern void gpioToggleRegCallback(void* reg, int operation);
extern void gpioReadRegCallback(void* reg, int operation);

#endif /* SSCP_APP */