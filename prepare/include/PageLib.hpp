#ifndef __PAGELIB_HPP__
#define __PAGELIB_HPP__
#include "prepair.hpp"

namespace KONGKONG
{
class PageLib
{
public:
    PageLib(DirScanner &dirScanner,RssReader& rssReader)
        :_dirscanner(dirScanner),_rssReader(rssReader){}
    void store(const string&pagelib_dir,const string&offsetLib_dir){
        _rssReader.dump(pagelib_dir,offsetLib_dir,_pagelibs,_offsetLib);
    }//存储网页库与偏移库  

private:
    DirScanner &_dirscanner;
    RssReader &_rssReader;
    vector<string> _pagelibs;  //存放rss格式化后的string
    map<int,pair<int,int>> _offsetLib; //<网页编号，<起始偏移，结束偏移>>


};


}

#endif
