#include "ftpcli.h"
#include <iostream>
FtpClientCLI::FtpClientCLI():CmdLineInterface("ftp>")
{
    cout<<"FTP Client v1.0"<<endl;
    initCmd();
    client = new FtpTcpClient();
}

FtpClientCLI::~FtpClientCLI()
{
    delete client;
}


void FtpClientCLI::initCmd()
{
    addCmd("open",CLI_CAST(&FtpClientCLI::doOpen));
    addCmd("login",CLI_CAST(&FtpClientCLI::doLogin));
    addCmd("cwd",CLI_CAST(&FtpClientCLI::doCwd));
    addCmd("pwd",CLI_CAST(&FtpClientCLI::doPwd));
    addCmd("list",CLI_CAST(&FtpClientCLI::doList));
    addCmd("mkd",CLI_CAST(&FtpClientCLI::doMkd));
    addCmd("rmd",CLI_CAST(&FtpClientCLI::doRmd));
    addCmd("rename",CLI_CAST(&FtpClientCLI::doRename));
    addCmd("dele",CLI_CAST(&FtpClientCLI::doDele));
    addCmd("upload",CLI_CAST(&FtpClientCLI::doUpload));
    addCmd("download",CLI_CAST(&FtpClientCLI::doDownload));
    addCmd("help",CLI_CAST(&FtpClientCLI::doHelp));
}

void FtpClientCLI::doOpen(string cmd_argv[], int cmd_argc)
{
    /*
     - client mo ket noi den server
     - client nhan chuoi ki tu chua thoi gian
     - Neu server dong ket noi thi client ket thuc phien
     - In ra thoi gian
    */
    if(cmd_argc==3)
    {
        int port = stoi(cmd_argv[2]);
        bool ok = client->openSession(cmd_argv[1],port);
        if(ok)
            cout << "Ket noi thanh cong" << endl;
        else
            cout << "Ket noi khong thanh cong hoac server khong san sang" << endl;

    }
    else if(cmd_argc==2)
    {
        bool ok = client->openSession(cmd_argv[1]);
        if(ok)
            cout << "Ket noi thanh cong" << endl;
        else
            cout << "Ket noi khong thanh cong hoac server khong san sang" << endl;
    }
    else
    {
        cout << "Lenh khong dung tham so" << endl;
    }
}


void FtpClientCLI::doLogin(string cmd_argv[], int cmd_argc)
{
    if(cmd_argc==1)
    {
        string username;
        string password;
        cout<<"Username:";
        getline(cin,username);
        client->setUsername(username);
        cout<<"Password:";
        getline(cin,password);
        client->setPassword(password);
        bool ok = client->login();
        if(ok)
        {
            cout<<"Da dang nhap thanh cong!"<<endl;
            client->loginStatus=true;
        }
        else
        {
            if(!client->loginStatus)
                cout<<"Dang nhap that bai!"<<endl;
            else
                cout<<"Da Dang Nhap!"<<endl;
        }
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}

void FtpClientCLI::doCwd(string cmd_argv[], int cmd_argc)
{
    if (cmd_argc>=2)
    {
        string path="";
        for (int i=1;i<cmd_argc;i++)
        {
            if (i==cmd_argc-1)
            path+=cmd_argv[i];
            else
            {
                path+=cmd_argv[i];
                path+=" ";
            }

        }
        client->cwd(path);
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}

void FtpClientCLI::doPwd(string cmd_argv[], int cmd_argc)
{
    if (cmd_argc==1)
    {
        client->pwd();
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}

void FtpClientCLI::doList(string cmd_argv[], int cmd_argc)
{
    if (cmd_argc==1)
    {
        client->List("");
    }
    else if (cmd_argc>=2)
    {
        string path="";
        for (int i=1;i<cmd_argc;i++)
        {
            if (i==cmd_argc-1)
            path+=cmd_argv[i];
            else
            {
                path+=cmd_argv[i];
                path+=" ";
            }

        }
        client->List(path);
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}


void FtpClientCLI::doMkd(string cmd_argv[], int cmd_argc)
{
    if (cmd_argc>=2)
    {
        string path="";
        for (int i=1;i<cmd_argc;i++)
        {
            if (i==cmd_argc-1)
            path+=cmd_argv[i];
            else
            {
                path+=cmd_argv[i];
                path+=" ";
            }

        }
        client->mkd(path);
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}

void FtpClientCLI::doRmd(string cmd_argv[], int cmd_argc)
{
    if (cmd_argc>=2)
    {
        string path="";
        for (int i=1;i<cmd_argc;i++)
        {
            if (i==cmd_argc-1)
            path+=cmd_argv[i];
            else
            {
                path+=cmd_argv[i];
                path+=" ";
            }

        }
        client->rmd(path);
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}

void FtpClientCLI::doRename(string cmd_argv[], int cmd_argc)
{
    if (cmd_argc==1)
    {
        string old_directory;
        string new_directory;
        cout<<"From:";
        getline(cin,old_directory);
        cout<<"To:";
        getline(cin,new_directory);
        client->rename(old_directory,new_directory);
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}

void FtpClientCLI::doDele(string cmd_argv[], int cmd_argc)
{
    if (cmd_argc>=2)
    {
        string path="";
        for (int i=1;i<cmd_argc;i++)
        {
            if (i==cmd_argc-1)
            path+=cmd_argv[i];
            else
            {
                path+=cmd_argv[i];
                path+=" ";
            }

        }
        client->dele(path);
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}

void FtpClientCLI::doUpload(string cmd_argv[], int cmd_argc)
{
    if (cmd_argc>=2)
    {
        string path="";
        for (int i=1;i<cmd_argc;i++)
        {
            if (i==cmd_argc-1)
            path+=cmd_argv[i];
            else
            {
                path+=cmd_argv[i];
                path+=" ";
            }

        }
        client->upload(path);
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}

void FtpClientCLI::doDownload(string cmd_argv[], int cmd_argc)
{
    if (cmd_argc>=2)
    {
        string path="";
        for (int i=1;i<cmd_argc;i++)
        {
            if (i==cmd_argc-1)
            path+=cmd_argv[i];
            else
            {
                path+=cmd_argv[i];
                path+=" ";
            }

        }
        client->download(path);
    }
    else
    {
        cout<<"Lenh khong dung tham so"<<endl;
    }
}

void FtpClientCLI::doHelp(string cmd_argv[], int cmd_argc)
{
    cout <<"Cac lenh chuong trinh ho tro"<<endl;
    cout<<"- open <server> [port]             Mo Ket Noi Den FTP Server"<<endl;
    cout<<"- login                            Dang Nhap"<<endl;
    cout<<"- cwd <dir>                        Chuyen Thu Muc Hien Hanh"<<endl;
    cout<<"- list [dir]                       In Danh Sach Tep, Thu Muc"<<endl;
    cout<<"- mkd <dir>                        Tao Thu Muc"<<endl;
    cout<<"- rmd <dir>                        Xoa Thu Muc"<<endl;
    cout<<"- rename                           Doi Ten Tep, Thu Muc"<<endl;
    cout<<"- dele <filename>                  Xoa File"<<endl;
    cout<<"- download <filename>              Tai Ve"<<endl;
    cout<<"- upload <filename>                Tai Len"<<endl;
    cout<<"- help                             Tro giup"<<endl;
    cout<<"- quit                             Ket thuc chuong trinh"<<endl;
}

