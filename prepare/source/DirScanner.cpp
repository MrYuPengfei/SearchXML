// @file        : DirScanner.cc
// @namespace   : KONGKONG
// @date        : 2022-05-17 06:20:06
// description : 
#include "DirScanner.hpp"
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
using std::cout;
using std::endl;
namespace KONGKONG
{
DirScanner::DirScanner(const string &dir):_dir(dir){this->traverse();}

const vector<string>& DirScanner::get_absolute_file()const { return _files;}

void DirScanner::traverse(){
   //获取语料库目录下的所有语料文件
    DIR *dir=opendir(_dir.c_str());
    if(!dir){cout<<"open dir is error"<<endl;exit(-1);}
    struct dirent *dir_info;
    while((dir_info=readdir(dir))!=nullptr){
        string filename(dir_info->d_name);
        if(("."==filename)||".."==filename)  continue;
        string str=_dir+"/"+dir_info->d_name;
        _files.push_back(move(str));
    }
    closedir(dir);
}

}


