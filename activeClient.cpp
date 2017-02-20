#include <iostream>
// Stuff for AJAX
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "pstream.h"
#include <string>
#include <iostream>

using namespace std;
using namespace cgicc; // Needed for AJAX functions.

// routine to run a shell command and get the results.
string runCommand(string command);

int main() {
  Cgicc cgi;    // Ajax object

  // Create AJAX objects to recieve information from web page.
  form_iterator uname = cgi.getElement("uname");

  // output required message for AJAX
  cout << "Content-Type: text/plain\n\n";

  // Call runCommand to get results
  string stuname = **uname;
  cout << stuname;
  string command = "ps -aef | grep " + stuname; 
  string results = runCommand(command);
  cout << results;
  
return 0;
}


string runCommand(string command) {

  // run a process and create a streambuf that reads its stdout and stderr
  redi::ipstream proc(command, redi::pstreams::pstdout | redi::pstreams::pstderr);
  string line,lines;
  // read child's stdout
  while (getline(proc.out(), line)) {
    lines = lines + line + "<br />";
  }

  // read child's stderr
  while (getline(proc.err(), line)) {
    lines = lines + line + "<br />";
  }
  return lines;
}
