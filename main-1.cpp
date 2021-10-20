#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32")

// g++ main.cpp -lwsock32 -o net
// ./net.exe

using namespace  std;

int main() {
    WSADATA  wsa;
    if(WSAStartup(MAKEWORD(2,2),&wsa)!= 0) {
        cout << "Blad: "<< WSAGetLastError();
        return 1;
    }
    SOCKET  s;
    if ((s = socket(AF_INET,SOCK_STREAM,IPPROTO_IP)) == INVALID_SOCKET) {
        cout <<"Blad tworzenia gniazda: "<<WSAGetLastError();
    }
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr("69.164.223.208");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    if(connect(s,(sockaddr*)&server,sizeof (server)) < 0) {
        cout << "Blad polaczenia";
    }
    char out[] = "GET/HTTP/1.1\r\n\r\n\r\n\r\n";
    int  send_size;
    if((send_size == send(s,out, sizeof (out), 0)) < 0) {
        cout << "Blad wysylki ";
    }
    cout << "[send]"<<send_size<<endl;
    char *in = new char[2000];
    int recv_size;
    for(int i = 0; i < 100; i++){
        if((recv_size = recv(s,in,2000,0))== SOCKET_ERROR) {
            cout << "Blad odbioru";
        }
        if (recv_size > 0) {
            cout << "[recv]"<<recv_size <<endl;
            cout << in;
        }
    }
    closesocket(s);
    return 0;
}
