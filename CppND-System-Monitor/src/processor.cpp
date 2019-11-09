#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() 
{
    double currentIdle, currentTotal;
    double cpuFreq = sysconf(_SC_CLK_TCK);
    
    currentIdle = LinuxParser::IdleJiffies();
    currentTotal = LinuxParser::Jiffies();

    float utilization = 1.0 - (currentIdle - lastIdleJiffes_) / (currentTotal - lastTotalJiffes_);

    lastIdleJiffes_ = currentIdle;
    lastTotalJiffes_ = currentTotal;

    return utilization;
}
