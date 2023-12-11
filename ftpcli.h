#ifndef FTPCLI_H_INCLUDED
#define FTPCLI_H_INCLUDED

#include "cli.h"
#include "ftptcpclient.h"

class FtpClientCLI : public CmdLineInterface
{
private:
    FtpTcpClient* client;
public:
    FtpClientCLI();
    ~FtpClientCLI();

private:
    void initCmd();
    void doOpen(string cmd_argv[], int cmd_argc);
    void doHelp(string cmd_argv[], int cmd_argc);
    void doLogin(string cmd_argv[], int cmd_argc);
    void doCwd(string cmd_argv[], int cmd_argc);
    void doPwd(string cmd_argv[], int cmd_argc);
    void doList(string cmd_argv[], int cmd_argc);
    void doMkd(string cmd_argv[], int cmd_argc);
    void doRmd(string cmd_argv[], int cmd_argc);
    void doRename(string cmd_argv[], int cmd_argc);
    void doDele(string cmd_argv[], int cmd_argc);
    void doUpload(string cmd_argv[], int cmd_argc);
    void doDownload(string cmd_argv[], int cmd_argc);
    void doQuit(string cmd_argv[], int cmd_argc);
};
#endif // FTPCLI_H_INCLUDED
