// @file        : DirScanner.hpp
// @namespace   : KONGKONG
// @date        : 2022-05-17 06:20:31
// description : 
#ifndef __DIRSCANNER_HPP__
#define __DIRSCANNER_HPP__
#include "prepair.hpp"

namespace KONGKONG
{
class DirScanner
{
public:
    DirScanner(const string &dir);
    const vector<string>& get_absolute_file()const;
private:
    void traverse();   //获取语料库目录下的所有语料文件
private:
    string _dir;            //语料库目录
    vector<string> _files;  //语料库文件的绝对路径
};
}

#endif
