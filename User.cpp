#include "User.h"
#include <string>
#include <iostream>
using namespace std;

string User::getnickname() {
	return nickname_;
}

string User::getpassword() {
	return password_;
}
