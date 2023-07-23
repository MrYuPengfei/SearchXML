// @file        : server.cc
// @namespace   : KONGKONG
// @date        : 2022-05-17 06:23:57
// description : 
#include "DirScanner.hpp"
#include "PageLib.hpp"
#include "Configuration.hpp"
#include "WebPage.hpp"
#include "SplitTool.hpp"
#include "ConstValue.hpp"
#include "WebPageLib.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
using std::cout;
using std::endl;
using std::ifstream;
using std::set;
using std::stringstream;
using namespace KONGKONG;
// const char *const CONFIGURE_PATH="/home/yupengfei/YuPengFei_v4/conf/setting.conf";

Configuration *Configuration:: _pInstance
	= new Configuration( CONFIGURE_PATH);
       	//饿汉模式，线程安全

// 测试是否可以正常打开 rss 文件夹的文件
void test1(){
    cout<<"test1()"<<endl;
    DirScanner rssScanner(Configuration::getpInstance()->getConfigMap()["rss_dir"]);
    vector<string> rssFiles = rssScanner.get_absolute_file();
    for (auto &e : rssFiles)
    {
        ifstream ifs(e, ifstream::in);
        if (!ifs.good())
        {
            cout << "can't open" << endl;
        }
    }
}

//从rss语料库解析后导入 网页库 与 偏移库
void test2()
{
    cout<<"test2()"<<endl;
    DirScanner rssScanner(Configuration::getpInstance()->getConfigMap()["rss_dir"]);
    RssReader rssReader;
    vector<string>& rssFiles = rssScanner.get_absolute_file();
    for (auto &e : rssFiles)
    {
        cout<<e<<endl;
        rssReader.parseRss(e);
    }
    PageLib pageLib(rssScanner, rssReader);
    pageLib.store(
	Configuration::getpInstance()->getConfigMap()["ripePage_dir"], 
	Configuration::getpInstance()->getConfigMap()["offset_dir"]);
}


//从已经建立好的网页库 和 偏移库 中读取到
void test3(){
    cout<<"test3()"<<endl;
    cout<<"WebPageLib pageLibs"<<endl;
    WebPageLib pageLibs(
	Configuration::getpInstance()->getConfigMap()["stop_words.utf8"], 
	Configuration::getpInstance()->getConfigMap()["ripePage_dir"],
	Configuration::getpInstance()->getConfigMap()["offset_dir"]);

    cout<<"pageLibs.storeOnDisk"<<endl;
    pageLibs.storeOnDisk(
	Configuration::getpInstance()->getConfigMap()["NewRipePage_dir"],
	Configuration::getpInstance()->getConfigMap()["Newoffset_dir"], 
	Configuration::getpInstance()->getConfigMap()["invertIndex_dir"]);
}
int main(int argc,char* argv[])
{
    test1();
    test2();
    test3();
    return 0;
}
