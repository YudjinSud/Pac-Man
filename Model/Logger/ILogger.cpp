//
// Created by yudjin on 10/25/20.
//

#include "ILogger.h"

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
std::string ILogger::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "\n%Y-%m-%d.%X\n", &tstruct);

    return buf;
}

