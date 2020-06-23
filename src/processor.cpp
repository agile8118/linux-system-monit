#include <string>
#include <map>
#include <chrono>
#include <thread>

#include "processor.h"
#include "linux_parser.h"

using std::string;
using std::map;


// Return the aggregate CPU utilization
float Processor::Utilization() {
  map<string, long> prevCpuData = LinuxParser::CpuUtilization();
  // Wait for 100 milliseconds and then get then cpu data again
  std::this_thread::sleep_for (std::chrono::milliseconds(100));
  map<string, long> cpuData = LinuxParser::CpuUtilization();
  
  float PrevIdle = prevCpuData["idle"] + prevCpuData["iowait"];
  float Idle = cpuData["idle"] + cpuData["iowait"];

  float PrevNonIdle = prevCpuData["user"] + prevCpuData["nice"] + prevCpuData["system"] + prevCpuData["irq"] + prevCpuData["softirq"] + prevCpuData["steal"];
  float NonIdle = cpuData["user"] + cpuData["nice"] + cpuData["system"] + cpuData["irq"] + cpuData["softirq"] + cpuData["steal"];

  float PrevTotal = PrevIdle + PrevNonIdle;
  float Total = Idle + NonIdle;

  float totald = Total - PrevTotal;
  float idled = Idle - PrevIdle;

  return (totald - idled)/totald; 
}