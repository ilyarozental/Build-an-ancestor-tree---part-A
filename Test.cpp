#include "doctest.h"
#include "FamilyTree.hpp"
#include <string>

using namespace family;
Tree *buildtestT();

TEST_CASE("add funcs") {
   Tree t("AA");
   CHECK_NOTHROW(t.addFather("AA", "AF"));
   CHECK_NOTHROW(t.addFather("AF", "AFF"));
   CHECK_NOTHROW(t.addFather("AFF", "AFFF"));
   CHECK_NOTHROW(t.addMother("AA", "AM"));
   CHECK_NOTHROW(t.addMother("AM", "AMM"));
   CHECK_NOTHROW(t.addMother("AMM", "AMMM"));
   CHECK_THROWS(t.addMother("AA", "AM")); 
   CHECK_THROWS(t.addMother("AM", "asd")); 
   CHECK_THROWS(t.addMother("NOTEXIST", "asd")); 
   CHECK_THROWS(t.addFather("AA", "AF")); 
   CHECK_THROWS(t.addFather("AF", "something")); 
   CHECK_THROWS(t.addFather("NOTEXIST", "something")); 
   CHECK(t.find("father") == "AF");
   CHECK(t.find("grandfather") == "AFF");
   CHECK(t.find("great-grandfather") == "AFFF");
   CHECK(t.find("mother") == "AM");
   CHECK(t.find("grandmother") == "AMM");
   CHECK(t.find("great-grandmother") == "AMMM");
   Tree t1("AA");
   CHECK_NOTHROW(t1.addMother("AA", "qwee").addFather("AA", "asdasd").addMother("qwee","zxczxc").addFather("asdasd", "asdasdasd"));
}
TEST_CASE("relation func") {
    Tree *T;
    CHECK_NOTHROW(T = buildtestT());
    CHECK(T->relation("yossi") == "me");
    CHECK(T->relation("avi") == "father");
    CHECK(T->relation("timur") == "grandfather");
    CHECK(T->relation("ronen") == "great-grandfather");
    CHECK(T->relation("rubi") == "great-great-grandfather");
    CHECK(T->relation("anit") == "great-grandmother");
    CHECK(T->relation("shimrit") == "grandmother");
    CHECK(T->relation("amir") == "great-grandfather");
    CHECK(T->relation("rahel") == "mother");
    CHECK(T->relation("zahi") == "grandfather");
    CHECK(T->relation("shlomi") == "great-great-grandfather");
    CHECK(T->relation("eyal") == "great-great-grandfather");
    CHECK(T->relation("hofit") == "great-great-grandmother"); 
    delete T;
}
TEST_CASE("test show") {
    Tree *tree;
    CHECK_NOTHROW(tree = buildtestT());
    CHECK_NOTHROW(tree->display()); 
    delete tree;
}

TEST_CASE("find") {
    Tree *T;
    CHECK_NOTHROW(T = buildtestT());
    CHECK(T->find("me") == "yossi"); 
    CHECK(T->find("father") == "avi"); 
    CHECK(T->find("mother") == "rahel"); 
    CHECK_THROWS(T->find("asd"));
    CHECK_NOTHROW(string("grandfather") = T->find("grandfather"));
    CHECK((string("grandfather") == "timur" || string("grandfather") == "zahi")); 
    CHECK(T->find("grandmother") == "shimrit");   
    CHECK_NOTHROW(string("great_grandfather") = T->find("great-grandfather")); 
    CHECK((string("great_grandfather") == "ronen" || string("great_grandfather") == "amir")); 
    CHECK(T->find("great-grandmother") == "anit"); 
    CHECK_NOTHROW(string("great_great_grandfather") = T->find("great-great-grandfather")); 
    CHECK((string("great_great_grandfather") == "rubi" || string("great_great_grandfather") == "shlomi" || string("great_great_grandfather") == "eyal")); 
    CHECK(T->find("great-great-grandmother") == "hofit"); 
    CHECK_THROWS(T->find("brother"));
    CHECK_THROWS(T->find("great-great-great-grandfather"));
    CHECK_THROWS(T->find("great-great-great-great-grandfather"));
    CHECK_THROWS(T->find("anit"));
    delete T;
}

TEST_CASE("remove function") {
    Tree *T;
    CHECK_NOTHROW(T = buildtestT());
    CHECK_THROWS(T->remove("yossi")); 
    CHECK_THROWS(T->remove("Dani"));  
    CHECK_NOTHROW(T->remove("amir"));
    CHECK(T->relation("amir") == "unrelated");
    CHECK(T->relation("eyal") == "unrelated");
    CHECK(T->relation("hofit") == "unrelated");
    CHECK_THROWS(T->remove("amir")); 
    CHECK_THROWS(T->remove("eyal")); 
    CHECK_THROWS(T->remove("hofit"));  
    CHECK_NOTHROW(T->remove("shlomi"));
    CHECK(T->relation("shlomi") == "unrelated");
    CHECK_THROWS(T->remove("shlomi")); 
    CHECK_NOTHROW(T->remove("zahi"));
    CHECK(T->relation("zahi") == "unrelated");
    CHECK_THROWS(T->remove("zahi")); 
    CHECK_NOTHROW(T->remove("rubi"));
    CHECK(T->relation("rubi") == "unrelated");
    CHECK_THROWS(T->remove("rubi")); 
    CHECK_NOTHROW(T->remove("anit"));
    CHECK(T->relation("anit") == "unrelated");
    CHECK_THROWS(T->remove("anit"));   
    CHECK_NOTHROW(T->remove("ronen"));
    CHECK(T->relation("ronen") == "unrelated");
    CHECK_THROWS(T->remove("ronen"));   
    CHECK_NOTHROW(T->remove("shimrit"));
    CHECK(T->relation("shimrit") == "unrelated");
    CHECK_THROWS(T->remove("shimrit"));   
    CHECK_NOTHROW(T->remove("timur"));
    CHECK(T->relation("timur") == "unrelated");
    CHECK_THROWS(T->remove("timur"));   
    CHECK_NOTHROW(T->remove("rahel"));
    CHECK(T->relation("rahel") == "unrelated");
    CHECK_THROWS(T->remove("rahel"));   
    CHECK_NOTHROW(T->remove("avi"));
    CHECK(T->relation("avi") == "unrelated");
    CHECK_THROWS(T->remove("avi"));   
    
    CHECK_NOTHROW(T = buildtestT());
    CHECK_THROWS(T->remove("yossi ")); 
    CHECK((T->find("grandfather") == string("zahi") || T->find("grandfather") == string("timur")));
    CHECK(T->find("father") == string("avi"));
    T->remove("avi"); 
    CHECK_THROWS(T->find("father"));
    CHECK(T->find("grandfather") == string("timur"));
    CHECK(T->find("great-grandmother") == string("shimrit")); 
    CHECK(T->find("great-grandfather") == string("ronen")); 
    T->remove("shimrit");
    CHECK_THROWS(T->find("great-grandmother"));
    T->remove("timur");
    CHECK_THROWS(T->find("great-grandfather"));
    CHECK_THROWS(T->find(T->find("grandfather")));
    T->addFather("shimrit", "gabi"); 
    CHECK(T->find("grandfather") == string("gabi")); 
    CHECK(T->find("grandmother") == string("hofit"));
    T->remove("hofit"); 
    CHECK_THROWS(T->find("grandmother")); 
    T->remove("shimrit"); 
    CHECK_THROWS(T->find("grandfather")); 
    CHECK_THROWS(T->find("mother"));
}

Tree *buildtestT(){ 
    Tree *T  = new Tree("yossi"); 
	CHECK_NOTHROW(T->addFather("yossi", "avi"));   
	CHECK_NOTHROW(T->addMother("yossi", "rahel"));  
    CHECK_NOTHROW(T->addFather("rahel", "zahi"));
	CHECK_NOTHROW(T->addFather("avi", "timur"));
	CHECK_NOTHROW(T->addMother("avi", "shimrit"));
	CHECK_NOTHROW(T->addFather("shimrit", "amir"));
	CHECK_NOTHROW(T->addFather("timur", "ronen"));
	CHECK_NOTHROW(T->addMother("timur", "anit"));
    CHECK_NOTHROW(T->addFather("anit", "shlomi"));
	CHECK_NOTHROW(T->addFather("ronen", "rubi"));
    CHECK_NOTHROW(T->addFather("amir", "eyal"));
    CHECK_NOTHROW(T->addMother("amir", "hofit")); 
    return T;
}