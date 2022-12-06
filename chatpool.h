#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "User.h"
using namespace std;

class chatpool {
public:
	vector<map<int, string> > chatpool_vect;
	int checkmap(string receiver, string nickname);
	void showmap(string receiver, string nickname);
	void sendmessage(string receiver, string nickname, string message);
	void processRequest(string receiver, string nickname);

protected:

}; 
