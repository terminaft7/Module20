#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;


class Message
{

public : 
	//Message() = default;
	Message(const string & from, const string & to_whom, const string & message) : from_(from), to_whom_(to_whom), message_(message) {};
	void showlastMessage(const string& nickname, const vector <Message>& messageArray, const string& receiver);
	
protected :

	string from_;
	string to_whom_;
	string message_;
};

