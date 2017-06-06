//
// Created by ljh on 2017/6/5.
//

#include "TextQuery.h"
using std::cin;
using std::cout;
using std::istringstream; // split line to word with space \n \t etc

TextQuery::TextQuery(ifstream &is): input(new vector<string>)
{
    string line;
    while(getline(is, line)){
        input->push_back(line);
        istringstream line_stream(line);
        auto&& lineno = input->size() - 1;
        string word, tmp;
        while(line_stream >> tmp){
            word.clear();
            std::remove_copy_if(tmp.begin(), tmp.end(),
                                std::back_inserter(word), ispunct);
            auto& nos = wm[word];
            if(!nos) nos.reset(new set<LineNo>);
            nos->insert(lineno);
        }
    }
}

QueryResult TextQuery::query(const string &qs)
{
    static shared_ptr<set<LineNo>> nodata(new set<LineNo>);
    auto found = wm.find(qs);
    if(found == wm.end()) // not find
        return QueryResult(qs, nodata, input);
    else
        return QueryResult(qs, found->second, input);
}

std::ostream& print(std::ostream &out, const QueryResult &qr)
{
    out << qr.word << " occurs: " << qr.lptr->size()
         << (qr.lptr->size() > 1  ? " times" : " time") << std::endl;
    for(const auto &i : *qr.lptr)
        out << "\t(line " << i + 1 << ") \t" << qr.text->at(i) << std::endl;

    return out;
}

