#include "ftptcpclient.h"
#include <iostream>
#include <fstream>
#include <cstring>
FtpTcpClient::FtpTcpClient()
{

}

FtpTcpClient::~FtpTcpClient()
{

}

bool FtpTcpClient::openSession(const string& serverName, int port)
{
    string response;
    connected = open(serverName, port);
    if(!connected)
    {
        return false;
    }
    char respBuffer[256];
    try
    {
        int byte_recv = recvGetLine(respBuffer, 256);

        if (byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("220")!=string::npos)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    catch(SocketException& e)
    {
        return false;
    }
    return false;
}

bool FtpTcpClient::login()
{
    if(!connected)
    {
        print("Not connected!");
        return false;
    }
    else
    {
        string request;
        string response;
        char respBuffer[256];
        int byte_recv;
        try
        {
            request = "USER "+username+"\r\n";
            sendStringRequest(request);
            byte_recv = recvGetLine(respBuffer,256);
            if(byte_recv>0)
            {
                response = respBuffer;
                print(response);
                if(response.find("220")!=string::npos)
                {
                    byte_recv=recvGetLine(respBuffer,256);
                    if(byte_recv>0)
                    {
                        response = respBuffer;
                        print(response);
                    }
                    else
                    {
                        return false;
                    }
                }
                else if (response.find("331")!=string::npos)
                {

                }
                else
                {
                    return false;
                }

                if(response.find("331")!=string::npos)
                {
                    request = "PASS "+password+"\r\n";
                    sendStringRequest(request);
                    byte_recv = recvGetLine(respBuffer,256);
                    if(byte_recv>0)
                    {
                        response = respBuffer;
                        print(response);
                        if(response.find("230")!=string::npos)
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }

        }
        catch(SocketException& e)
        {
            return false;
        }
    }
}
void FtpTcpClient::setUsername(const string& username)
{
    this->username = username;
}

void FtpTcpClient::setPassword(const string& password)
{
    this->password = password;
}

bool FtpTcpClient::cwd(const string& directory)
{
    string request;
    string response;
    char respBuffer[256];
    int byte_recv;
    try
    {
        sendStringRequest("CWD "+directory+"\r\n");
        byte_recv = recvGetLine(respBuffer,256);
        if(byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("250")!=string::npos)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    catch(SocketException& e)
    {
        return false;
    }
    return false;
}

bool FtpTcpClient::pwd()
{
    string request;
    string response;
    char respBuffer[256];
    int byte_recv;
    try
    {
        sendStringRequest("PWD\r\n");
        byte_recv = recvGetLine(respBuffer,256);
        if(byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("257")!=string::npos)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    catch(SocketException& e)
    {
        return false;
    }
    return false;
}

bool FtpTcpClient::List(const string& directory)
{
    string request;
    string response;
    char respBuffer[256];
    int byte_recv;
    try
    {
        sendStringRequest("PASV\r\n");
        byte_recv = recvGetLine(respBuffer,256);
        if(byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("227")!=string::npos)
            {
                string host = getHost(response);
                response = respBuffer;
                string port = getPort(response);
                sendStringRequest("LIST "+directory+"\r\n");
                byte_recv = recvGetLine(respBuffer,256);
                if(byte_recv>0)
                {
                    response = respBuffer;
                    print(response);
                    if(response.find("150")!=string::npos)
                    {
                        openData(host,port);
                        byte_recv = recvGetLineData(respBuffer,256);
                        while (byte_recv>0)
                        {
                            response= respBuffer;
                            print(response);
                            byte_recv = recvGetLineData(respBuffer,256);
                        }
                        byte_recv = recvGetLine(respBuffer,256);
                        response = respBuffer;
                        print(response);
                        if(response.find("226")!=string::npos)
                        {
                            datasocket.close();
                            return true;
                        }
                        else
                        {
                            datasocket.close();
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
        }
    }
    catch(SocketException& e)
    {
        return false;
    }
    return false;
}

bool FtpTcpClient::mkd(const string& directory)
{
    string request;
    string response;
    char respBuffer[256];
    int byte_recv;
    try
    {
        sendStringRequest("MKD "+directory+"\r\n");
        byte_recv = recvGetLine(respBuffer,256);
        if(byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("257")!=string::npos)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    catch(SocketException& e)
    {
        return false;
    }
    return false;
}

bool FtpTcpClient::rmd(const string& directory)
{
    string request;
    string response;
    char respBuffer[256];
    int byte_recv;
    try
    {
        sendStringRequest("RMD "+directory+"\r\n");
        byte_recv = recvGetLine(respBuffer,256);
        if(byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("250")!=string::npos)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    catch(SocketException& e)
    {
        return false;
    }
    return false;
}

bool FtpTcpClient::rename(const string& old_directory, const string& new_directory)
{
    string request;
    string response;
    char respBuffer[256];
    int byte_recv;
    try
    {
        sendStringRequest("RNFR "+old_directory+"\r\n");
        byte_recv = recvGetLine(respBuffer,256);
        if(byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("350")!=string::npos)
            {
                sendStringRequest("RNTO "+new_directory+"\r\n");
                byte_recv = recvGetLine(respBuffer,256);
                if(byte_recv>0)
                {
                    response = respBuffer;
                    print(response);
                    if(response.find("250")!=string::npos)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }

        }
        else
        {
            return false;
        }
    }
    catch(SocketException& e)
    {
        return false;
    }
}

bool FtpTcpClient::dele(const string& directory)
{
    string request;
    string response;
    char respBuffer[256];
    int byte_recv;
    try
    {
        sendStringRequest("DELE "+directory+"\r\n");
        byte_recv = recvGetLine(respBuffer,256);
        if(byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("250")!=string::npos)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    catch(SocketException& e)
    {
        return false;
    }
    return false;
}

bool FtpTcpClient::upload(const string& directory)
{
    string request;
    string response;
    char respBuffer[256];
    int byte_recv;
    try
    {
        FILE* fp;
        fp = fopen(directory.c_str(),"rb");
        if (fp)
        {
            sendStringRequest("PASV\r\n");
            byte_recv = recvGetLine(respBuffer,256);
            if(byte_recv>0)
            {
                response = respBuffer;
                print(response);
                if(response.find("227")!=string::npos)
                {
                    string host = getHost(response);
                    response = respBuffer;
                    string port = getPort(response);
                    string filename = directory.substr(directory.find_last_of("/\\") + 1);

                    sendStringRequest("STOR "+filename+"\r\n");
                    byte_recv = recvGetLine(respBuffer,256);
                    if (byte_recv>0)
                    {
                        response = respBuffer;
                        print(response);
                        if (response.find("150")!=string::npos)
                        {
                            int i=0;
                            openData(host,port);
                            while(feof(fp)==0)
                            {
                                int c = getc(fp);
                                if (c == EOF)
                                {
                                    sendDataBufferData(respBuffer,i);
                                    break;
                                }
                                respBuffer[i]=c;
                                i++;
                                if (i==256){
                                    sendDataBufferData(respBuffer,256);
                                    i=0;
                                }
                            }
                            fclose(fp);
                            datasocket.close();
                            byte_recv = recvGetLine(respBuffer,256);
                            if (byte_recv>0)
                            {
                                response = respBuffer;
                                print(response);
                                if (response.find("226")!=string::npos)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                datasocket.close();
                                return false;
                            }
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            print("Khong tim thay tep!");
            return false;
        }
    }
    catch(SocketException& e)
    {
        return false;
    }
    return false;
}

bool FtpTcpClient::download(const string& directory)
{
    string request;
    string response;
    char respBuffer[256];
    int byte_recv;
    try
    {
        sendStringRequest("PASV\r\n");
        byte_recv = recvGetLine(respBuffer, 256);
        if (byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("227")!=string::npos)
            {
                string host = getHost(response);
                response = respBuffer;
                string port = getPort(response);
                sendStringRequest("RETR "+directory+"\r\n");
                byte_recv=recvGetLine(respBuffer, 256);
                if (byte_recv>0)
                {
                    response = respBuffer;
                    print(response);
                    if(response.find("150")!=string::npos)
                    {
                        openData(host,port);
                        string filename = directory.substr(directory.find_last_of("/\\") + 1);
                        FILE *fp;
                        string path = "E:\\Client\\"+filename;
                        fp = fopen(path.c_str(),"wb");
                        if (fp)
                        {
                            byte_recv = recvDataBufferData(respBuffer,256);
                            while(byte_recv>0)
                            {
                                for (int i=0; i<byte_recv; i++)
                                {
                                    putc(respBuffer[i],fp);
                                }
                                byte_recv = recvDataBufferData(respBuffer,256);
                            }
                            fclose(fp);
                            datasocket.close();
                            byte_recv = recvGetLine(respBuffer,256);
                            if (byte_recv>0)
                            {
                                response = respBuffer;
                                print(response);
                                if (response.find("226")!=string::npos)
                                {
                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }
                            else
                            {
                                datasocket.close();
                                return false;
                            }
                        }
                        else
                        {
                            print("Loi tao tep!");
                            datasocket.close();
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    catch (SocketException& e)
    {
        return false;
    }
}
bool FtpTcpClient::quit()
{
    bool sessionClose;
    string response;
    try
    {
        sendStringRequest("QUIT\r\n");
        char respBuffer[256];
        int byte_recv = recvGetLine(respBuffer, 256);
        if(byte_recv>0)
        {
            response = respBuffer;
            print(response);
            if(response.find("221")==0)
            {
                sessionClose = true;
                loginStatus = false;
            }
            else
            {
                sessionClose = false;
            }
        }
        else
        {
            sessionClose = false;
        }
    }
    catch (SocketException& e)
    {

        return false;
    }
    return sessionClose;
}

string FtpTcpClient::getHost(const string& response)
{
    string port_host="";
    string s = response;
    int n = s.length();
    char char_array[n+1];
    strcpy(char_array,s.c_str());
    for (int i=27; i<n-1; i++)
    {
        port_host+=char_array[i];
    }
    int n2=port_host.length();
    char char_array2[n2+1];
    strcpy(char_array2,port_host.c_str());
    char *h1=strtok(char_array2,",");
    string h1_str(h1);
    char *h2=strtok(NULL,",");
    string h2_str(h2);
    char *h3=strtok(NULL,",");
    string h3_str(h3);
    char *h4=strtok(NULL,",");
    string h4_str(h4);
    char *p1=strtok(NULL,",");
    string p1_str(p1);
    char *p2=strtok(NULL,",");
    string p2_str(p2);
    string host = h1_str+"."+h2_str+"."+h3_str+"."+h4_str;
    return host;
}

string FtpTcpClient::getPort(const string& response)
{
    string port_host="";
    string s = response;
    int n = s.length();
    char char_array[n+1];
    strcpy(char_array,s.c_str());
    for (int i=27; i<n-1; i++)
    {
        port_host+=char_array[i];
    }
    int n2=port_host.length();
    char char_array2[n2+1];
    strcpy(char_array2,port_host.c_str());
    char *h1=strtok(char_array2,",");
    string h1_str(h1);
    char *h2=strtok(NULL,",");
    string h2_str(h2);
    char *h3=strtok(NULL,",");
    string h3_str(h3);
    char *h4=strtok(NULL,",");
    string h4_str(h4);
    char *p1=strtok(NULL,",");
    string p1_str(p1);
    char *p2=strtok(NULL,",");
    string p2_str(p2);
    int port=stoi(p1_str)*256+stoi(p2_str);
    return to_string(port);
}
