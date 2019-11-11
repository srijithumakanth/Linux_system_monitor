#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "format.h"
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() {
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid_) +
                       LinuxParser::kCmdlineFilename);

  string line;
  if (stream.is_open()) {
    getline(stream, line);

    return line;
  }
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid_) +
                       LinuxParser::kStatusFilename);

  string line, key, value;
  int ramKb, ramMb;
  if (stream.is_open())
  {
    while(getline(stream, line))
    {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if(key == "VmSize:")
      {
        ramKb = stoi(value);
      }
    }
  }
  ramMb = ramKb / 1000;

  return to_string(ramMb);
}

// TODO: Return the user (name) that generated this process
string Process::User() {
  string line, uid, userLine;
  string key, value, username, uservalue;

  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid_) +
                       LinuxParser::kStatusFilename);
  if (stream.is_open()) {
    while (getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid:") {
        uid = value;
      }
    }
  }

  std::ifstream filestream(LinuxParser::kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, userLine)) {
      std::replace(userLine.begin(), userLine.end(), ':', ' ');
      std::istringstream linestream(userLine);
      while (linestream >> username >> uservalue >> uservalue) {
        if (uservalue == uid) {
          return username;
        }
      }
    }
  }
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid_) +
                       LinuxParser::kStatFilename);

  if (stream.is_open()) {
    std::string line;
    getline(stream, line);
    std::istringstream buf(line);
    std::istream_iterator<string> beg(buf), end;
    std::vector<string> values(beg, end);

    long int uptime = stol(values[21]);
    long int uptime_in_sec = uptime / sysconf(_SC_CLK_TCK);

    return uptime_in_sec;
  }
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }