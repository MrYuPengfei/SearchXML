#include "prepair.hpp"
using namespace KONGKONG;
Configuration *Configuration:: _pInstance= new Configuration( CONFIGURE_PATH);
void test1();//测试是否可以正常打开 rss 文件夹的文件 (DirScanner)
void test2();//从rss语料库解析后导入 网页库 与 偏移库
void test3();//从已经建立好的网页库 和 偏移库 中读取到
int main(int argc,char* argv[])
{
    // test1();    
    test2();
    // test3();  
    return 0;
}
void test1(){
    cout<<"test1()"<<endl;
    DirScanner rssScanner(Configuration::getpInstance()->getConfigMap()["rss_dir"]);
    const vector<string>& rssFiles = rssScanner.get_absolute_file();
    for (auto &e : rssFiles) {
        ifstream ifs(e, ifstream::in);
        if (!ifs.good()){cout << "can't open" << endl;}
        else{cout<<"get xml file path:"<<e<<endl; ifs.close();}
    }
}

void test2()
{
    cout<<"test2()"<<endl;
    RssReader rssReader;
    DirScanner rssScanner(Configuration::getpInstance()->getConfigMap()["rss_dir"]);
    for (const auto &e : rssScanner.get_absolute_file()) rssReader.parseRss(e);
    PageLib pageLib(rssScanner, rssReader);
    pageLib.store(
	Configuration::getpInstance()->getConfigMap()["ripePage_dir"], 
	Configuration::getpInstance()->getConfigMap()["offset_dir"]);
}


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
