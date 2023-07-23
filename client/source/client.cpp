#include "client.h"
using namespace std;
int main()
{
    int ret;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in sockinfo;
    bzero(&sockinfo, sizeof(sockinfo));
    sockinfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockinfo.sin_port = htons(8888);
    sockinfo.sin_family = AF_INET;
    ret = connect(sockfd, (sockaddr *)&sockinfo, sizeof(sockinfo));
    if (-1 == ret)
    {
        perror("connect");
        exit(-1);
    }

    char buf[1000000];

    while (1)
    {
        bzero(buf, sizeof(buf));
        read(0, buf, sizeof(buf));
        send(sockfd, buf, strlen(buf)-1, 0);

        bzero(buf, sizeof(buf));
        recv(sockfd, buf, sizeof(buf), 0);
        // cout << buf<< endl;

        cout<<UnicodeToUTF8(buf)<<endl;

    // //    // 在使用jsoncpp解析含有中文的字符串的时候，
    // //    // 使用toStyledString()函数生成的字符串中的中文部分将变成\u加4个16进制数字
    // //    // 会出现解析乱码的情况。https://www.freesion.com/article/84561434539/
    //      // 接收到json格式的数据,解析
    //     const std::string rawJson(buf);
    //     cout<<rawJson<<endl;
    //     const auto rawJsonLength = static_cast<int>(rawJson.length());
    //     constexpr bool shouldUseOldWay = false;
    //     JSONCPP_STRING err;
    //     Json::Value value;
    //     // if (shouldUseOldWay) {
    //     //     Json::Reader reader;
    //     //     reader.parse(rawJson, value);
    //     // } else {
    //     //     Json::CharReaderBuilder builder;
    //     //     const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());
    //     //     if (!reader->parse(rawJson.c_str(), rawJson.c_str() + rawJsonLength, &value,
    //     //                     &err)) {
    //     //     std::cout << "error" << std::endl;
    //     //     return EXIT_FAILURE;
    //     //     }
    //     // }

    //     // {
    //     // "files" : [
    //     //     {
    //     //         "summary" : "nk> http://www.iteye.com/news/31902 </link>\n\t <description> ,,,,,,,,,,,\u5f15\u7528,\u539f\u6587\uff1a,5,algorithms",
    //     //         "title" : "Facebook,\u7528,Rust,\u91cd\u5199,Mercurial,\ufffd\ufffd",
    //     //         "url" : "http://www.iteye.com/news/31902"
    //     //     }
    //     // ]
    //     // }




    //     cout<<"size"<<value["files"].size()<<"\n\n\n"<<endl;
    //     for (unsigned int i = 0; i < value["files"].size(); ++i) 
    //     { 
    //         string title = value["files"][i]["title"].asString(); 
    //         string url= value["files"][i]["url"].asString(); 
    //         string summary = value["files"][i]["summary"].asString(); 
    //         cout << "-------------------------------------------------" << endl; 
    //         cout << "标题:" << endl; 
    //         cout << title << endl; 
    //         cout << "链接:" << endl; 
    //         cout << url << endl; 
    //         cout << "摘要:" << endl; 
    //         cout << summary << endl; 
    //     } 


    }

    close(sockfd);
    return EXIT_SUCCESS;
}
