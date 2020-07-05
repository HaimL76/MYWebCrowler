#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <Windows.h>
#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "OpenWebPage.h"
#include "ResolveHostName.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

const int DefaultPort = 80;

void OpenWebPage::OpenPage(string& url)
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
        return;

    SOCKET socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socketfd == INVALID_SOCKET)
    {
        WSACleanup();
        return;
    }

    RegularResolveHostName resolve;

    string& strIp = resolve.Resolve(url);

    int ip;

    inet_pton(AF_INET, strIp.c_str(), &ip);

    int port = DefaultPort;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ip;
    addr.sin_port = htons(port);

    result = connect(socketfd, (SOCKADDR*)&addr, sizeof(addr));

    if (result == SOCKET_ERROR) {
        int err = errno;
        WSACleanup();
        Sleep(2000);
    }

    cout << "connected!" << endl;

    //HTTP GET
    string get_http = "GET / HTTP/1.1\r\nHost: " + url + "\r\nConnection: close\r\n\r\n";

    const char* str = get_http.c_str();

    result = send(socketfd, str, strlen(str), 0);

    char buff[1000];

    string response;

    while (result > 0)
    {
        int size = sizeof(buff);

        result = recv(socketfd, buff, size, 0);

        if (result > 0) 
        {
            if (result < size)
                buff[result] = '\0';

            response.append(buff);
        }
    }

    cout << response;
}


