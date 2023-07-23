// @file        : PageLib.cc
// @namespace   : KONGKONG
// @date        : 2022-05-17 06:12:55
// description : 
#include "PageLib.hpp"
#include "Configuration.hpp"
namespace KONGKONG
{
PageLib::PageLib(DirScanner &dirS,RssReader& rssReader)
:_dirscanner(dirS),_rssReader(rssReader)
{
}

void PageLib::store(const string &pagelib_dir,const string &offsetLib_dir)
{
    _rssReader.dump(pagelib_dir,offsetLib_dir,_pagelibs,_offsetLib);
}
    
}//namespace KONGKONG
