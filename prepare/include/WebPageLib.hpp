// @file        : WebPageLib.hpp
// @namespace   : KONGKONG
// @date        : 2022-05-17 06:26:27
// description : 
#ifndef __WEBPAGELIB_HPP__
#define __WEBPAGELIB_HPP__
#include "SplitTool.hpp"
#include "WebPage.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_map>
using namespace std;
namespace KONGKONG
{
class WebPageLib
{
public:
    WebPageLib(const string &stopword_dir, const string &ripepage_dir,const string &offset_dir);
    //将去重后的内容写到网页库 偏移库 倒排索引表中
    void storeOnDisk(const string &str1,const string &str2,const string &str3);


private:
    void readInfoFromFile();    //从停词库，网页库，偏移库中读取数据
    void createInvertIndexTable();   //建立倒排索引表
    void createDF_hashmap();    //TF_DF算法的辅助哈希表
private:
    string _stopWords_dir;
    string _ripePage_dir;
    string _offset_dir;
    vector<WebPage> _webPages; // 网页
    unordered_map<string,int> _DF_hashmap;   //文档频率hash表  <单词，文档频率>
    unordered_map<string,vector<pair<int ,double>>> _invertIndexTable; //倒排索引  <单词 ， <所在文档ID,单词权重>>
    set<string > _stopWords;   // 停词库
    SplitTool _spilt;          // cppjieba分词工具
};
}//namespace KONGKONG

#endif
