//
//  main.cpp
//  TextQuery
//
//  Created by pezy on 6/4/14.
//  Copyright (c) 2017 lfys. All rights reserved.
//
//  The TextQuery and QueryResult classes use only capabilities that we have
//  already covered.
//  don;t use class
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <sstream>
#include <algorithm>
#include <iterator>

using std::set;
using std::map;
using std::vector;
using std::string;
using std::ifstream;
using std::shared_ptr;
using std::cout;
using std::endl;

using LineNo = std::vector<string>::size_type;

// 建立单词到行的对应map关系，行号只保存一遍，故使用set来保存
map<string, shared_ptr<set<LineNo>>> wm;
void readfile(vector<string>& filev, ifstream &is);
shared_ptr<set<LineNo>> query(const string&);
void print(const vector<string> filev, const string & str, shared_ptr<set<LineNo>> ptr);
void runqueries(ifstream &is, vector<string> &filev);


int main() {

    ifstream file("../data/bible.txt");
    vector<string> filev;
    readfile(filev, file);
    runqueries(file, filev);

//    int l = 0;
//    for(auto &&line : filev){
//        cout << "\t(line " << l+1 <<") " << line << endl;
//        l++;
//        if(l > 100) break;
//    }

    return 0;
}

void readfile(vector<string>& filev, ifstream &is){

    string text;
    while(std::getline(is, text)){
        filev.push_back(text);
        int &&n = filev.size() - 1; // 当前行号
        std::istringstream line(text); // 将当前文本分解为单词
        string word, tmp;
        while(line >> tmp){
            word.clear();
            std::remove_copy_if(tmp.begin(), tmp.end(),
                                std::back_inserter(word), ispunct);
            auto &lines = wm[word];
            if(!lines) // 在我们第一次遇见这个单词的时候，此指针为空
                lines.reset(new set<LineNo>);
            lines->insert(n);
        }
    }
}

shared_ptr<set<LineNo>> query(const string &str){

    static shared_ptr<set<LineNo>> nodata(new set<LineNo>);
    auto loc = wm.find(str);
    if(loc == wm.end())
        return nodata;
    else
        return loc->second;
}

void print(const vector<string> filev, const string & str, shared_ptr<set<LineNo>> ptr){

    cout << str << " occurs " << ptr->size() << " "
         << (ptr->size() > 1 ? "times" : "time") << endl;
    for(auto &&i : *ptr)
        cout << "\t(line" << i + 1 << ") " << filev[i] << endl;
}

void runqueries(ifstream &is, vector<string> &filev){

    while(true){
        std::cout << "enter word to look for, or q to quit: ";
        string str;
        if(!(std::cin >> str) || str == "q") break;
        auto ptr = query(str);
        print(filev, str, ptr);
    }
}