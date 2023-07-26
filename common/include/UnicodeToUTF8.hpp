#ifndef __UnicodeToUTF8__
#define __UnicodeToUTF8__
#include <string>
#include <boost/locale/encoding.hpp>
std::string UnicodeToUTF8(const std::string & str);
std::string UnicodeToUTF8(const std::string & str){ 
    std::basic_string<wchar_t> ret;
    for(unsigned int i=0;i<str.size();) {
        if((str[i]=='\\')&&((i+1)!=str.size())&&(str[i+1]=='u')){          
            auto t = str.substr(i+2, 4);
            ret.push_back(std::stoi(t, nullptr, 16));
            i+=6;
        }else{
            ret.push_back(str[i]);
            ++i;
        }
    }
    auto r = boost::locale::conv::utf_to_utf<char>(ret);
    return r;
}





#endif