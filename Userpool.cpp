#include "User.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
#include "Userpool.h"

void Userpool::addUser(const User& username) {
	Userpool_vect.push_back(username);
}

bool Userpool::checkUser(const string& nickname, const string& password) {
	if (!Userpool_vect.empty()) {
		for (auto& u : Userpool_vect) {

			if ((u.getnickname() == nickname) && (u.getpassword() == password)) {
				cout << "Login successful. " << endl;
				return true;
			}
		}
	}
	cout << "Login failed. Try again." << endl;
	return false;
}

void Userpool::showUsers() {
	string usernickname;
	for (int i(0); i < Userpool_vect.size(); i++) {
		usernickname = Userpool_vect[i].getnickname();
		cout << usernickname << endl;
	}
}
