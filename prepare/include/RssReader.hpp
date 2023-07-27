#ifndef __RSSREADER_H__
#define __RSSREADER_H__
#include "prepair.hpp"
namespace KONGKONG
{
    struct RssItem
    {
        string title;
        string link;
        string description;
        string content;
    };

    class RssReader
    {
    public:
        void DFS(XMLElement *);
        bool parseRss(const string &filename);                                                 //解析
        void dump(const string &ripePage_dir, const string& offset_dir, vector<string> &pageLibs, map<int, pair<int,int>> &offsetLib); //输出
    private:
        vector<RssItem> _rss;
    };

} // namespace KONGKONG

#endif
