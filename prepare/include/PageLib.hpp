#ifndef __PAGELIB_HPP__
#define __PAGELIB_HPP__
#include "Configuration.hpp"
#include "DirScanner.hpp"
#include "RssReader.hpp"
using namespace std;

namespace KONGKONG
{
class PageLib
{
public:
    PageLib(DirScanner &,RssReader&);
    void store(const string&,const string&);  //存储网页库与偏移库  

private:
    DirScanner &_dirscanner;
    RssReader &_rssReader;
    vector<string> _pagelibs;  //存放rss格式化后的string
    map<int,pair<int,int>> _offsetLib; //<网页编号，<起始偏移，结束偏移>>


};


}

#endif
