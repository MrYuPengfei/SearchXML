// @file        : SplitTool.hpp
// @namespace   : KONGKONG
// @date        : 2022-05-17 06:29:04
// description : 
#ifndef __SPLITTOOL_HPP__
#define __SPLITTOOL_HPP__
#include "cppjieba/Jieba.hpp"
#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;
#include "ConstValue.hpp"
namespace KONGKONG
{
class SplitTool     //使用结巴分词库进行分词
{
public:
    SplitTool()
        :_jieba(DICT_PATH,HMM_PATH,USER_DICT_PATH,IDF_PATH,STOP_WORD_PATH)
    {
        cout<<"CPPJIEBA  init"<<endl;
    }
    vector<string> cut(const string str)    //返回str的分词结果
    {
        vector<string> words;
        _jieba.CutForSearch(str,words);   //
        return words;
    }
private:
    cppjieba::Jieba _jieba;
};

}//namespace KONGKONG
#endif
