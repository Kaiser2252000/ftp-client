#ifndef FTPTCPCLIENT_H_INCLUDED
#define FTPTCPCLIENT_H_INCLUDED
#include "tcpclient.h"

class FtpTcpClient: public TcpClient
{
private:
    string username;
    string password;

public:
    bool loginStatus=false;
    FtpTcpClient();
    ~FtpTcpClient();
    bool openSession(const string& serverName, int port=21);
    bool login();
    bool pwd();
    void setUsername(const string&username);
    void setPassword(const string&password);
    bool cwd(const string& directory);
    bool List(const string& directory);
    bool mkd(const string& directory);
    bool rmd(const string& directory);
    bool rename(const string& old_directory, const string& new_directory);
    bool dele(const string& directory);
    bool upload(const string& directory);
    bool download(const string& directory);
    bool quit();
    string getPort(const string& response);
    string getHost(const string& response);
};

#endif //FTPTCPCLIENT_H_INCLUDED
