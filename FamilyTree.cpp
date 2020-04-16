#include "FamilyTree.hpp"

using namespace std;
using namespace family;

Tree *Tree::findNode( string &name){

    return this;               
}

Tree &Tree::addFather(const string &son,const string &father){
 
    return *this;
}

Tree &Tree::addMother(const string &son,const string &mom){
    return *this;
}

string Tree::relation(const string &str) {
  
    return "";
}

string Tree::find(const string &str) {
  return "";
}

bool Tree::remove(const string &ancestor){

    return true;
}

void Tree::display(int){
    
}