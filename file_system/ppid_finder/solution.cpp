#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sstream>

using namespace std;

int main() {
	pid_t pid = getpid();
	string line, ppid, word, pids;
	ifstream infile("/proc/" + to_string(pid) + "/status");
	while ( getline (infile,line) ) {
	        istringstream iss(line);
		iss >> word;
		if (word == "PPid:") {
			iss >> ppid;
			break;
		}
	}
	infile.close();
	cout << ppid << '\n';
	return 0;
}

