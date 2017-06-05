//
//  main.cpp
//  TextQuery
//
//  Created by pezy on 6/4/14.
//  Copyright (c) 2017 lfys. All rights reserved.
//
//  The TextQuery and QueryResult classes use only capabilities that we have
//  already covered.
//  use class

#include "TextQuery.h"

void runQueries(std::ifstream& infile)
{
    TextQuery tq(infile);
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
    }
}

int main()
{
    ifstream file("../data/bible.txt");
    runQueries(file);
}