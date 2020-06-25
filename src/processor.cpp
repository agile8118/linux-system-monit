#include "processor.h"

#include <map>
#include <string>
#include <thread>

#include "linux_parser.h"

using std::map;
using std::string;

// Return the aggregate CPU utilization
float Processor::Utilization() {
  map<string, long> cpuData = LinuxParser::CpuUtilization();
  float fraction;
  long active = cpuData["user"] + cpuData["nice"] + cpuData["system"] +
                cpuData["irq"] + cpuData["softirq"] + cpuData["steal"];
  long total = active + cpuData["iowait"] + cpuData["idle"];

  fraction = float(active - previous_active) / float(total - previous_total);
  previous_active = active;
  previous_total = total;

  return fraction;
}