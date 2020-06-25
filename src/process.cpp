#include "process.h"

#include <time.h>
#include <unistd.h>

#include <cctype>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::map;
using std::string;
using std::to_string;
using std::vector;

Process::Process(int id) { pid_ = id; }

// Return this process's ID
int Process::Pid() { return pid_; }

// Return this process's CPU utilization
float Process::CpuUtilization() const {
  vector<string> cpuData = LinuxParser::CpuUtilization(pid_);
  long total_time = std::stol(cpuData[13]) + std::stol(cpuData[14]) +
                    std::stol(cpuData[15]) + std::stol(cpuData[16]);

  return ((total_time / sysconf(_SC_CLK_TCK)) / float(UpTime()));
}

// Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid_); }

// Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid_); }

// Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// Return the age of this process (in seconds)
long int Process::UpTime() const { return LinuxParser::UpTime(pid_); }

// Overload the "less than" comparison operator for Process objects
bool Process::operator<(const Process& a) const {
  return (this->CpuUtilization() > a.CpuUtilization());
}