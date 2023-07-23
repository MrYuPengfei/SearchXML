#include "WebPageLib.hpp"
#include<cmath>
using namespace std;
namespace KONGKONG
{
WebPageLib::WebPageLib(const string &stopword_dir, const string &ripepage_dir,const string &offset_dir)
:_stopWords_dir(stopword_dir)
,_ripePage_dir(ripepage_dir)
,_offset_dir(offset_dir)
{
    readInfoFromFile();
}
    //将去重后的内容写到网页库 偏移库 倒排索引表中
void WebPageLib::storeOnDisk(const string &str1,const string &str2,const string &str3)
{
    cout<<"storeOnDisk"<<endl;
    ofstream papefile(str1,ofstream::in);
    ofstream offsetfile(str2,ofstream::in);
    ofstream invertIndexfile(str3,ofstream::in);
    // if(!papefile.good()||!offsetfile.good()||!invertIndexfile.good())
    // {
    //     cout<<__FILE__<<":"<<__LINE__<<":"<<__FILE__<<"file is open error "<<endl;
    //     exit(-1);
    // }
    for(size_t i=0;i<_webPages.size();++i)
    {
        string doc=_webPages[i].getDoc();
        off_t beg=papefile.tellp();
        papefile<<doc;
        off_t end=papefile.tellp();
        offsetfile<<i<<" "<<beg<<" "<<end<<endl;
    }

    //创建TF_IDF算法复制hash表
    //
    createDF_hashmap();


    //
    //建立倒排索引文件
    //
    createInvertIndexTable();


    //写入倒排索引文件
    for(auto &elem:_invertIndexTable)
    {
        invertIndexfile<<elem.first<<"  ";
        for(auto &elem2:elem.second)
        {
            invertIndexfile<<elem2.first<<"  "<<elem2.second<<"  ";

        }
        invertIndexfile<<endl;
    }
    papefile.close();
    offsetfile.close();
    invertIndexfile.close();
    cout<<"新的网页库，偏移库  倒排索引库建立成功  ！！！"<<endl;

}


void WebPageLib::readInfoFromFile()    //从停词库，网页库，偏移库中读取数据
{
    cout<<"readInfoFromFile  "<<_stopWords_dir<<endl;
    ifstream stop_word_file(_stopWords_dir);
    // if(!stop_word_file.good())
    // {
    //     cout<<__FILE__<<":"<<__LINE__<<": file  open error "<<endl;
    //     exit(-1);
    // }
    string words;
    while(getline(stop_word_file,words))
    {
        _stopWords.insert(words);
    }
    ifstream papefile(_ripePage_dir);
    ifstream offsetfile(_offset_dir);
    // if(!papefile.good()||!offsetfile.good())
    // {
    //     cout<<__FILE__<<" :"<<__LINE__<<":"<<__FILE__<<"file is open error "<<endl;
    //     exit(-1);
    // }
    string str("");
    int docid=0;
    off_t beg=0,end=0;
    // cout<<"WebPageLib.cc 88"<<endl;
    char buff[65536]={0};
    while(getline(offsetfile,str))
    { 
        bzero(buff,sizeof(buff));
        stringstream oss(str);
        oss>>docid>>beg>>end;
        //根据偏移量读取<doc>.. </doc>
        papefile.read(buff,end-beg+1);
        string doc(buff);
        // cout<<"doc"<<doc<<endl;
        // cout<<"docid:"<<docid<<" beg:"<<beg<<" end:"<<end<<endl;
        //cout<<"doc"<<docid<<endl;
        WebPage page(doc,_spilt,_stopWords);
        
        //cout<<"doc"<<endl;
        //如果是相同的网页不必再次读入
        if(find(_webPages.begin(),_webPages.end(),page)==_webPages.end())
        {
            _webPages.push_back(std::move(page));
        }else{
            cout<<"发现了一个重复的网页"<<endl;
        }
    }
    cout<<"WebPageLib.cc 110 ------------------"<<endl;
    // stop_word_file.close();
    // offsetfile.close();
    // papefile.close();
}
void WebPageLib::createInvertIndexTable()   //建立倒排索引表
{        
    cout<<"createInvertIndexTable"<<endl;
    ifstream stop_word_file(_stopWords_dir);
    vector<vector<pair<string, double>>> weights(_webPages.size()); //<单词，未归一化权重> temp下标代表文章id

        for (size_t i = 0; i < _webPages.size(); i++)
        {
            map<string, int> &wordsMap = _webPages[i].getWordMap();
            for (auto &e : wordsMap) // <单词，词频>
            {
                string word = e.first;
                double TF = (double)e.second / _webPages[i].getTotalwords();
                int DF = _DF_hashmap[word];
                int N = _webPages.size();
                double IDF = log10((double)N / (DF + 1));
                double w = TF * IDF;
                weights[i].push_back(make_pair(word, w));
            }
        }

        //将单词的权重进行归一化处理 W = w /sqrt(w1^2 + w2^2 +...+ wn^2)
        for (size_t i = 0; i < weights.size(); i++)
        {
            vector<pair<string, double>> &wordsVec = weights[i]; //i号文档的 <单词，未处理权重>
            double sum = 0;
            for (auto &e : wordsVec)
            {
                sum += e.second * e.second;
            }
            sum = sqrt(sum);
            for (auto &e : wordsVec)
            {
                e.second /= sum;
            }
        }

        //插入结果到倒排索引表
        for (size_t i = 0; i < weights.size(); i++)
        {
            vector<pair<string, double>> &wordsVec = weights[i]; //i号文档的 <单词，归一化权重>
            for (auto &e : wordsVec)
            {
                _invertIndexTable[e.first].push_back(make_pair(i, e.second));
            }
        }

}
void WebPageLib::createDF_hashmap()    //TF_DF算法的辅助哈希表
{
    cout<<"creatDF_hashmap"<<endl;
    for(size_t i=0;i<_webPages.size();i++)
    {
        map<string,int> &wordsMap=_webPages[i].getWordMap();
        for(auto &elem:wordsMap)
        {
            _DF_hashmap[elem.first]++;
        }
    }
}

}//namespace KONGKONG
