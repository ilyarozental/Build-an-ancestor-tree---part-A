#pragma once
#include <iostream>
#include <string>


using namespace std;
namespace family{

    class Tree{
        string _name;
        int _type;

        Tree *findNode( string &);
    public:
        Tree(string name, int type = 0): 
            _name(name), 
            _type(type) { };
        Tree &addFather(const string &,const string &);
	    Tree &addMother(const string &,const string &);  
        void display(int depth = 1) ;
        string relation(const string &) ;
        string find(const string &) ;
        bool remove(const string &);
    };
};