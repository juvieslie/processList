#include "pstream.h"
#include <string>
#include <iostream>

using namespace std;

string runCommand(string command);


int main()
{
  string username;
  cout << "Enter a username:";
  cin >> username;

  string command = "ps -aef | grep " + username;

  cout << runCommand(command);

  return 0;

}


string runCommand(string command) {
  
// run a process and create a streambuf that reads its stdout and stderr
  redi::ipstream proc(command, redi::pstreams::pstdout | redi::pstreams::pstderr);
  string line,lines;
  // read child's stdout
  while (getline(proc.out(), line)) {
    lines = lines + line + "<p>\n";;
  }

  // read child's stderr
  while (getline(proc.err(), line)) {
    lines = lines + line + "<p>\n";
  }
  return lines;
} 
