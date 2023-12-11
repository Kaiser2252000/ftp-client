#include "tcpclient.h"
#include <iostream>
#include <fstream>

TcpClient::TcpClient()
{
    connected = false;

}

TcpClient::~TcpClient()
{

}


bool TcpClient::open(const string& serverHost, unsigned short port)
{
    try
    {
        this->localsocket.connect(serverHost,port);
        this->connected = true;
        return true;

    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

bool TcpClient::open(const string& serverHost, const string& port)
{
    try
    {
        this->localsocket.connect(serverHost,port);
        this->connected = true;
        return true;

    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}


int TcpClient::sendStringRequest(const string& request)
{
    try
    {
        return this->localsocket.send(request);
    }
    catch(SocketException& e)
    {
        cerr << e.what();
        return -1;
    }
}
int TcpClient::sendDataBuffer(const char* buffer, unsigned int bufLen)
{
    try
    {
       return this->localsocket.send(buffer, bufLen);
    }
    catch(SocketException& e)
    {
        cerr << e.what();
        return -1;
    }
}
int TcpClient::recvGetLine(char* buffer, unsigned int maxLen)
{
    int bytes;
    try
    {
        bytes = localsocket.recvLine(buffer, maxLen-1);
        if(bytes>2)
        {
            buffer[bytes-2] = 0;
        }
        else
        {
            *buffer =0;
        }
        return bytes;
    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
}

int TcpClient::recvDataBuffer(char* buffer, unsigned int bufLen)
{
    int bytes;
    try
    {
        bytes = localsocket.recv(buffer, bufLen-1);
        return bytes;
    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
}

int TcpClient::recvStringBuffer(char* buffer, unsigned int bufLen)
{
    int bytes;
    try
    {
        bytes = localsocket.recv(buffer, bufLen-1);
        if(bytes>0)
        {
            buffer[bytes]=0;
        }
        else
        {
            *buffer = 0;
        }
        return bytes;
    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        *buffer = 0;
        return -1;
    }
}


void TcpClient::close()
{
    try
    {
        localsocket.shutdown(SHUTDOWN_BOTH);
        localsocket.close();
    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
    }
    connected = false;
}

void TcpClient::printLn(const string& msg)
{
    cout << msg << endl << endl;

}

void TcpClient::print(const string& msg)
{
    cout << msg << endl;

}

bool TcpClient::openData(const string& serverHost, unsigned short port)
{
    try
    {
        this->datasocket.connect(serverHost,port);
        this->connectedData = true;
        return true;

    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

bool TcpClient::openData(const string& serverHost, const string& port)
{
    try
    {
        this->datasocket.connect(serverHost,port);
        this->connectedData = true;
        return true;

    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return false;
    }
}

int TcpClient::recvDataBufferData(char* buffer, unsigned int bufLen)
{
    int bytes;
    try
    {
        bytes = datasocket.recv(buffer, bufLen-1);
        return bytes;
    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
}

int TcpClient::recvStringBufferData(char* buffer, unsigned int bufLen)
{
    int bytes;
    try
    {
        bytes = datasocket.recv(buffer, bufLen-1);
        if(bytes>0)
        {
            buffer[bytes]=0;
        }
        else
        {
            *buffer = 0;
        }
        return bytes;
    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        *buffer = 0;
        return -1;
    }
}

int TcpClient::recvGetLineData(char* buffer, unsigned int maxLen)
{
    int bytes;
    try
    {
        bytes = datasocket.recvLine(buffer, maxLen-1);
        if(bytes>2)
        {
            buffer[bytes-2] = 0;
        }
        else
        {
            *buffer =0;
        }
        return bytes;
    }
    catch(SocketException& e)
    {
        cerr << e.what() << endl;
        return -1;
    }
}

int TcpClient::sendDataBufferData(const char* buffer, unsigned int bufLen)
{
    try
    {
       return this->datasocket.send(buffer, bufLen);
    }
    catch(SocketException& e)
    {
        cerr << e.what();
        return -1;
    }
}

int TcpClient::sendStringRequestData(const string& request)
{
    try
    {
        return this->datasocket.send(request);
    }
    catch(SocketException& e)
    {
        cerr << e.what();
        return -1;
    }
}
