#include "OrgChart.hpp"

using namespace std;
namespace ariel{
    OrgChart::OrgChart(){
        vector<string>temp;
        this->run=temp;
        Node n;
        this->root=n;
    }
    // OrgChart::~OrgChart(){

    // }
    OrgChart& OrgChart::add_root(string rootName){
        if(this->start==0){
            this->root.name=rootName;
            this->start=1;
        }else{
            Node temp=this->root;
            Node newroot;
            newroot.name=rootName;
            this->root=newroot;
            this->root.childern.push_back(temp);
        }
        return *this;
    }
    vector<string> OrgChart::getrun(){
        return this->run;
    }
    OrgChart& OrgChart::add_sub(string commander, string subordinate){
        if(findingFather(this->root,commander, subordinate)==false){
            throw runtime_error("there is no such man");
        }
        return *this;
    }
    bool OrgChart::findingFather(Node &curr, string com, string sub){
        Node temp;
        temp.name=sub;
        if(curr.name==com){
            curr.childern.push_back(temp);
            return true;
        }
        else{
            for(int i=0;i<curr.childern.size();++i){
                if(findingFather(curr.childern.at((unsigned int)i),com, sub)==true){
                    return true;
                }
            }
        }
        return false;
    }

    // vector<string>::iterator OrgChart::begin() { 
    //     this->run.clear();
    //     this->first=0;
    //     makeLevelRun(this->root);
    //     return this->run.begin();
    // }

    // vector<string>::iterator OrgChart::end() { 
    //     return this->run.end();
    // }
    OrgChart::iterator OrgChart::begin() { 
        this->run.clear();
        this->runNodes.clear();
        makeLevelRun(this->root);
        vectolink(this->runNodes);
        return iterator(&this->root);
    }

    OrgChart::iterator OrgChart::end() { 
        // return iterator(this->root.next);
        return iterator(this->last);
    }
    vector<string>::iterator OrgChart::begin_level_order(){
        this->run.clear();
        makeLevelRun(this->root);
        return this->run.begin();
    }
    vector<string>::iterator OrgChart::end_level_order(){
        return this->run.end();
    }
    vector<string>::iterator OrgChart::begin_reverse_order(){
        this->run.clear();
        makeReverseRun(this->root);
        return this->run.begin();
    }
    vector<string>::iterator OrgChart::reverse_order(){
        return this->run.end();;
    }
    vector<string>::iterator OrgChart::begin_preorder(){
        this->run.clear();
        makePreorderRun(this->root);
        return this->run.begin();;
    }
    vector<string>::iterator OrgChart::end_preorder(){
        return this->run.end();
    }

    void OrgChart::makeLevelRun(Node father){
        Node ta;
        ta.name="bvbvb";
        this->root.next=&ta;
        // cout<<this->root.next->name<<endl;
        this->last=&ta;
        // cout<<this->last.name<<endl;
        queue<Node*> main_queue;
        main_queue.push(&this->root);
        vector<string> temp;
        vector<Node>t;
        while (!main_queue.empty()) {
            int n = main_queue.size();
            for (int i = 0; i < n; i++) {
                Node* curr = main_queue.front();
                main_queue.pop();
                temp.push_back(curr->name);
                t.push_back(*curr);
                for(int i=0;i<curr->childern.size();i++)
                    main_queue.push(&(curr->childern.at((unsigned int)i)));
            }
            for(string s: temp){
                this->run.push_back(s);
            }
            temp.clear();
            for(Node n: t){
                this->runNodes.push_back(n);
            }
            t.clear();
        }
    }

    void OrgChart::makeReverseRun(Node father){
        queue<Node*> main_queue;
        main_queue.push(&this->root);
        vector<string> temp;
        while (!main_queue.empty()) {
            int n = main_queue.size();
            for (int i = 0; i < n; i++) {
                Node* curr = main_queue.front();
                main_queue.pop();
                temp.insert(temp.begin(),curr->name);
                for(int i=0;i<curr->childern.size();i++)
                    main_queue.push(&(curr->childern.at((unsigned int)i)));
            }
            for(string i: temp){
                this->run.insert(this->run.begin(),i);
            }
            temp.clear();
        }
    }

    void OrgChart::makePreorderRun(Node father){
        stack<Node>Stack;
        Stack.push(father);
        while (!Stack.empty()) {
            Node temp = Stack.top();
            Stack.pop();
            this->run.push_back(temp.name);
            for (int i = temp.childern.size() - 1; i >= 0; --i) {
                Stack.push(temp.childern.at((unsigned int) i));
            }
        }
    }
    std::ostream& operator<<(std::ostream& output, OrgChart& org){
        for (auto it=org.begin_level_order(); it!=org.end_level_order(); ++it) {
            output << (*it);
            if(it!=org.end_level_order()-1){
                output<<"->";
            }
        }
        return output;
    }

    void OrgChart::vectolink(vector<Node> &vec){
        Node* temp;
        for (unsigned int i=0;i<vec.size()-1;i++){
            vec.at(i).next=&(vec.at(i+1));
            temp=&(vec.at(i+1));
        }
        // cout<<temp->name;//
        // this->last=temp;
        // cout<<this->last->name<<endl;
    }
    // void OrgChart::makeLevelRun(Node father){
        // if(this->first==0){
        //     this->run.push_back(father.name);
        //     if(father.childern.size()>0){
        //         father.next=&(father.childern.at(0));
        //     }
        //     this->first=1;
        // }
        // for(int i=0;i<father.childern.size();i++){
        //     this->run.push_back(father.childern.at((unsigned int)i).name);
        //     if(i<father.childern.size()-1){
        //         father.childern.at((unsigned int)i).next=&(father.childern.at((unsigned int)i+1));
        //         this->last=(father.childern.at((unsigned int)i+1));
        //     } 
        // }for(int i=0;i<father.childern.size();i++){
        //     makeLevelRun(father.childern.at((unsigned int) i));
        // }
    // }
    // void OrgChart::makeReverseRun(Node father){
        // if(this->first==0){
        //     this->run.insert(this->run.begin(),father.name);
        //     this->first=1;
        // }
        // for(int i=father.childern.size()-1;i>=0;--i){
        //     this->run.insert(this->run.begin(),father.childern.at((unsigned int)i).name);
        // }for(int i=father.childern.size()-1;i>=0;--i){
        //     makeReverseRun(father.childern.at((unsigned int)i));
        // }
    // }
}