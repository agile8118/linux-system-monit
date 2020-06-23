#include <string>

#include "format.h"


// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
std::string Format::ElapsedTime(long seconds) {
    long hours;
    long mins;
    std::string d_hours;
    std::string d_mins;
    std::string d_secs;

    hours = seconds / 3600;
    seconds = seconds - hours * 3600;
    mins = seconds / 60;
    seconds = seconds - mins * 60;

    if (hours < 10) {
        d_hours = "0" + std::to_string(hours);
    } else {
        d_hours = std::to_string(hours);
    }

    if (mins < 10) {
        d_mins = "0" + std::to_string(mins);
    } else {
        d_mins = std::to_string(mins);
    }

    if (seconds < 10) {
        d_secs = "0" + std::to_string(seconds);
    } else {
        d_secs = std::to_string(seconds);
    }
    
    return d_hours + ":" + d_mins + ":" + d_secs;
}