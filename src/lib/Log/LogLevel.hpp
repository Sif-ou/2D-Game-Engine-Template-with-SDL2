#pragma once
#include <iostream>

namespace LOG 
{
    enum LOG_LEVEL  
    {
        DEBUG_INFO , /* debug output away from console */
        INFO ,  /* milestones */
        WARN ,  /* something is off but still working */
        ERROR , /* something brake but the system is still running */
        FATAL   /* system can't recover */
    } ;
 }