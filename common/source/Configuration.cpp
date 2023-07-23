// @file        : Configuration.cpp
// @namespace   : KONGKONG
// @date        : 2022-05-17 07:39:21
// description : 
#include "Configuration.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;
namespace KONGKONG
{
    //Configuration* Configuration::_pInstance=nullptr;
    Configuration* Configuration::getpInstance()
    {
        return _pInstance;
    }

    void Configuration::destroy()
    {
        if (_pInstance)
        {
            delete _pInstance;
            _pInstance = NULL;
        }
    }

    map<string, string> &Configuration::getConfigMap()
    { 
        return _configMap;
    }

    Configuration::Configuration(const string &filepath)
        : _filepath(filepath)
    {
        cout<<"读取配置文件:"<<filepath<<endl;
        readConf();
    }

    Configuration::~Configuration()
    {
        destroy();
    }

    void Configuration::readConf()
    {
        ifstream ifs(_filepath, ifstream::in);
        if (!ifs.good())
        {
            cout << __FILE__ << ":" << __LINE__ << " "  << "ifstream openERROR" << endl;
            exit(-1);
        }

        string lines;
        string first, second;
        while (getline(ifs, lines))
        {
            stringstream ss(lines);
            ss >> first >> second;
            _configMap[first] = second;
        }
        ifs.close();
    }
} // namespace KONGKONG
