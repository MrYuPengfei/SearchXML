// @file        : WebPage.hpp
// @namespace   : KONGKONG
// @date        : 2022-05-17 06:15:48
// description : 
#ifndef  __WEBPAGE_HPP__
#define  __WEBPAGE_HPP__
#include "SplitTool.hpp"
#include <map>
#include <vector>
#include <set>
#include <string>
using std::map;
using std::vector;
using std::set;
using std::string;
namespace KONGKONG
{
const static size_t TOPK_NUMBER = 20;
//存储一篇文章, 也就是<doc>..</doc>
class WebPage
{
friend bool operator==(const WebPage &lhs, const WebPage &rhs);
friend bool operator<(const WebPage &lhs,const WebPage&rhs);

public:
    WebPage(const string &doc, SplitTool &splitTool, set<string>& stopWords);
    void makeSummary(const map<string,int>& wordsMap); //根据查询词生成摘要 
    int getTotalwords(){return _totalWords;}   //过去单词总数
    map<string, int> &getWordMap() { return _wordMap;}
    string getDoc() const {return _doc;}
    string getTitle() const { return _title;}
    string getLink() const { return _link; }
    string getSummary() const { return _summary;}
    void showPage() const { cout<<" >>> "<<_title<<" <<< "<<endl<<"link:  "<<_link<<endl<<"  "<<_content<<endl;};
    //判断两篇文章是否相等

private:
    void processDoc();                   //使用cppjieba，对格式化文档进行处理
    void calcTopK(size_t k);             //topK算法计算频率最高的k个单词
    void storeWordsMap(const string &s); //进行词频统计

private:
    int _totalWords;    //单词总数
    string _doc; //整个<doc> .. </doc>， 也就是整篇文章xml
    string _title;
    string _link; //url
    string _description;//描述
    string _content; //整篇文章  <doc> .. </doc>
    string _summary; //摘要，自行生成
    map<string,int> _wordMap;  //保存文章的所有词语和词频，不包括停用词  <单词，词频>
    vector<string> _topWords;   //该篇文章频率最高的前k个词
    SplitTool &_splitTool;      //cppjieba中文分词库
    set<string> &_stopWords;    //停词库
};

}// namespace KONGKONG


#endif
