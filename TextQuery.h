//
// Created by ljh on 2017/6/5.
//

#ifndef TEXTQUERY_TEXTQUERY_H
#define TEXTQUERY_TEXTQUERY_H

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

class QueryResult;

class TextQuery
{
public:
    using LineNo = std::vector<string>::size_type;
    TextQuery(ifstream&);
    QueryResult query(const string&);

private:
    shared_ptr<vector<string>> input;
    map<string, shared_ptr<set<LineNo>>> wm;
};


class QueryResult
{
public:
    friend std::ostream& print(std::ostream&, const QueryResult&);
public:
    QueryResult(const string& s, shared_ptr<set<TextQuery::LineNo>> l,
                      shared_ptr<vector<string>> t)
            : word(s), lptr(l), text(t)
    {

    }

private:
    string word;
    shared_ptr<set<TextQuery::LineNo>> lptr;
    shared_ptr<vector<string>> text;
};

std::ostream& print(std::ostream&, const QueryResult&);
#endif //TEXTQUERY_TEXTQUERY_H
