#include "chatpool.h"
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MESSAGE_BUFFER 4096 // Максимальный размер буфера для приема и передачи
#define PORT 7777 // Номер порта, который будем использовать для приема и передачи


char buffer[MESSAGE_BUFFER];
char send_buffer[MESSAGE_BUFFER];

//char message[MESSAGE_BUFFER];
int socket_file_descriptor, message_size;
socklen_t length;
const char* end_string = "end";
struct sockaddr_in serveraddress, client;

using namespace std;

int chatpool::checkmap(string receiver, string nickname) {
	
	int counter = 0;
 
	if (!this->chatpool_vect.empty()) {
		for (auto& u : this->chatpool_vect) {
	
				if (u.begin()->second == receiver + "_" + nickname || u.begin()->second == nickname + "_" + receiver) {
				   
                    return counter;
				}
            counter++;
			}
		}
	return -1;
	}

void chatpool::showmap(string receiver, string nickname) {
    int ind(0);
	for (auto& u : this->chatpool_vect) {

        if (u.begin()->second == receiver + "_" + nickname || u.begin()->second == nickname + "_" + receiver) {

            for (map<int, string>::iterator it = u.begin(); it != u.end(); ++it)
            {
                cout << it->second << endl;
                ind++;
            }
        }
	}
    if (ind == 0) { cout << "You did not chat with " << receiver << " yet! Start a conversation!" << endl; }
}

void chatpool::sendmessage(string receiver, string nickname, string message) {
    string complete_message = "from " + nickname + ": " + message;
    if (receiver == "all") {
        for (auto& u : this->chatpool_vect) {
            int x = u.size();
            u.insert({ x+1, complete_message });
            break;
        }
    }

  
    int y = this->checkmap(receiver, nickname);
    if (y == -1) {

        map <int, string> mapname;
        string ident = receiver + "_" + nickname;
        mapname.insert({ 0,ident });
        mapname.insert({ 1, complete_message });
        this->chatpool_vect.push_back(mapname);
        
    }
    else if (y > -1) {
        int size_map = this->chatpool_vect[y].size();
        this->chatpool_vect[y].insert({ size_map +1, complete_message });
    }
}


void chatpool::processRequest(string receiver, string nickname) {
    // Создадим UDP сокет
    socket_file_descriptor = socket(AF_INET, SOCK_DGRAM, 0);
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    // Зададим порт для соединения
    serveraddress.sin_port = htons(PORT);
    // Используем IPv4
    serveraddress.sin_family = AF_INET;
    // Привяжем сокет
    bind(socket_file_descriptor, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
    cout << "SERVER IS LISTENING THROUGH THE PORT: " << PORT << " WITHIN A LOCAL SYSTEM" << endl;
    message_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &length);
    buffer[message_size] = '\0';
    cout << "check1" << endl;
 	int n = receiver.length();
    char receiver_char[n+1];
    strcpy(receiver_char, receiver.c_str());
        
    if (strcmp(receiver_char, buffer) == 0) {
        cout << "check2" << endl;
        
        char answer[2]="1";
      //WHY CLIENT IS NOT RECEIVING THE ANSWER??????
        sendto(socket_file_descriptor, answer, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));   
       
           
    while (1) {
        // Длина сообщения от клиента
        length = sizeof(client);
        message_size = recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &length);
        buffer[message_size] = '\0';
        if (strcmp(buffer, end_string) == 0) {
            cout << "Server is Quitting" << endl;
            close(socket_file_descriptor);
        break;            
            //exit(0);
        }
    cout << "check"<<endl;
   // recvfrom(socket_file_descriptor, buffer, sizeof(buffer), 0, nullptr, nullptr);
    cout << "Message Received from Client: " << buffer << endl;
    cout << "check2"<<endl;
    int b;
    string s = "";
    for (b = 0; b < message_size; b++) {
        s = s + buffer[b];}
        
        this->sendmessage(nickname, receiver, s);


        // ответим клиенту
        cout << "Enter reply message to the client: " << endl;
        cin >> send_buffer;

        int c;
        string xx = "";
        for (c = 0; c < message_size; c++) {
        xx = xx + send_buffer[c];}
  
         this->sendmessage(receiver, nickname, xx);

       // strncpy(send_buffer, message.c_str(), MESSAGE_BUFFER);
        sendto(socket_file_descriptor, send_buffer, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));
  
        cout << "Waiting for the Reply from Client..!" << endl;
    }

    // закрываем сокет, завершаем соединение
    close(socket_file_descriptor);
    
}
    else {cout << "Sorry, the user you want to talk to is not online. Please try later." << endl;
    strcpy(send_buffer, "0");
    sendto(socket_file_descriptor, send_buffer, MESSAGE_BUFFER, 0, (struct sockaddr*)&client, sizeof(client));  
    }
}