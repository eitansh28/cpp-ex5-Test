#include"OrgChart.hpp"
#include "doctest.h"

using namespace ariel;

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

TEST_CASE("good cases"){
   OrgChart Myorg;
   CHECK_NOTHROW(Myorg.add_root("first"));
   CHECK_NOTHROW(cout<<Myorg<<endl);
   CHECK_NOTHROW(Myorg.add_root("second"));
   CHECK_NOTHROW(cout<<Myorg<<endl);
   CHECK_NOTHROW(Myorg.add_sub("second","s1"));
   CHECK_NOTHROW(Myorg.add_sub("second","s2"));
   CHECK_NOTHROW(Myorg.add_sub("second","s3"));
   CHECK_NOTHROW(Myorg.add_sub("s1","s4"));
   CHECK_NOTHROW(Myorg.add_sub("s2","s5"));
   CHECK_NOTHROW(Myorg.add_sub("s2","s6"));
   CHECK_NOTHROW(Myorg.add_sub("s3","s7"));
   CHECK_THROWS(Myorg.add_sub("vv","ww"));
   CHECK_THROWS(Myorg.add_sub("?","!"));
   
   int first = 0;
   char temp='1';
    for (auto it = Myorg.begin_level_order(); it != Myorg.end_level_order(); ++it){
        if(first==0){
            CHECK(*it=="second");
            first+=2;
        }
        // else if(first==2) {
        //     CHECK(*it=="first");
        //     first=1;
        // }
        else{
            string s="s";
            s+=temp;
            CHECK(*it==s);
            temp++;
        }
    }


}