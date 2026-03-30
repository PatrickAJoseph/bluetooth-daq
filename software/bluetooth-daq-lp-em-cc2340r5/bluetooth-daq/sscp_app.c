
#include "sscp.h"
#include "sscp_app.h"

void gpioWriteRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        
    }
}

void gpioToggleRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        
    }
}

void gpioReadRegCallback(void* reg, int operation)
{
    (void)reg;
    (void)operation;

    if( operation == SSCP_REGISTER_OPERATION_READ )
    {

    }
    else if( operation == SSCP_REGISTER_OPERATION_WRITE )
    {
        
    }
}
