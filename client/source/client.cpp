#include "client.h"
// using namespace std;
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);if (sockfd == -1){perror("socket");exit(errno);}
    {// 连接网络
        struct sockaddr_in sockinfo;
        {// initi socket information
            bzero(&sockinfo, sizeof(sockinfo));
            sockinfo.sin_addr.s_addr = inet_addr("127.0.0.1");
            sockinfo.sin_port = htons(8888);
            sockinfo.sin_family = AF_INET;
        }
        {// TCP connect 
            int connect_ret = connect(sockfd, (sockaddr *)&sockinfo, sizeof(sockinfo));
            if(-1 == connect_ret){perror("connect");exit(-1);}
        }
    }
    {// 业务逻辑
        char buf[1000000];
        while (1)
        {
            bzero(buf, sizeof(buf));
            read(0, buf, sizeof(buf));
            send(sockfd, buf, strlen(buf)-1, 0);
            
            bzero(buf, sizeof(buf));
            recv(sockfd, buf, sizeof(buf), 0);
            write(STDOUT_FILENO,buf,strlen(buf));
            // cout<<buf<<endl;
            // cout<<UnicodeToUTF8(buf)<<endl;
        }
    }
    close(sockfd);
    return EXIT_SUCCESS;
}
