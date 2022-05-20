#include "OrgChart.hpp"

using namespace std;
namespace ariel{
    OrgChart::OrgChart(){
        // Node* n=new Node();
        // this->root=*n;
        // delete(n);
    }
    OrgChart::~OrgChart(){
        for(Node* n: this->Nodes){
            delete n;
        }
    }
    OrgChart& OrgChart::add_root(string rootName){

        this->root.name=rootName;
        return *this;
    }
    
    OrgChart& OrgChart::add_sub(string commander, string subordinate){
        if(findingFather(&this->root,commander, subordinate)==false){
            throw runtime_error("there is no such man");
        }
        return *this;
    }
    bool OrgChart::findingFather(Node* curr, string com, string sub){
        Node* temp=new Node();
        temp->name=sub;
        if(curr->name==com){
            curr->childern.push_back(temp);
            this->Nodes.push_back(temp);
            return true;
        }
        else{
            for(int i=0;i<curr->childern.size();++i){
                if(findingFather(curr->childern.at((unsigned int)i),com, sub)==true){
                    return true;
                }
            }
        }
        return false;
    }

    OrgChart::iterator::iterator(Node* ptr, int flag1)
        : pointer_to_current_node(ptr) {
            this->flag=flag1;
            if(flag1==1){
                this->Queue.push(ptr);
            }
            else if(flag1==2){
                makeRev(ptr);
                this->pointer_to_current_node=this->runrev.at((unsigned int)this->i++);
            }
            else if(flag1==3){
                this->Stack.push(ptr);
            }
    }

    string& OrgChart::iterator::operator*() const {
			return this->pointer_to_current_node->name;
	}

    string* OrgChart::iterator::operator->() const {
			return &(this->pointer_to_current_node->name);
	}

    OrgChart::iterator& OrgChart::iterator::operator++() {
        if(this->flag==1){
            Node* curr=this->Queue.front();
            for(size_t i=0;i<curr->childern.size();++i){
                this->Queue.push(curr->childern.at(i));
            }
            if(this->Queue.size()==1 && Queue.front()->childern.size()==0){
                this->pointer_to_current_node=nullptr;
            }else{
                this->Queue.pop();
                this->pointer_to_current_node=Queue.front();
            }
            
        }else if(this->flag==3){
            Node* curr=this->Stack.top();
            this->Stack.pop();
            for(int i=curr->childern.size()-1;i>=0;--i){
                Stack.push(curr->childern.at((unsigned int)i));
            }
            if(Stack.empty()){
                this->pointer_to_current_node=nullptr;
            }else{
                this->pointer_to_current_node=Stack.top();
            }
        }
        else if(this->flag==2){
            try{
                this->pointer_to_current_node=this->runrev.at((unsigned int)this->i++);
            }
            catch(const std::exception& e){
                this->pointer_to_current_node=nullptr;
            }    
        }
		return *this;
	}

    OrgChart::iterator OrgChart::iterator::operator++(int) {
            Node* curr=this->Queue.front();
            for(int i=0;i<curr->childern.size();++i){
                this->Queue.push(curr->childern.at((unsigned int)i));
            }
            this->Queue.pop();
            iterator tmp = *this;
            this->pointer_to_current_node=this->Queue.front();
            return tmp;
	}

    OrgChart::iterator OrgChart::begin() { 
        return iterator(&this->root,1);
    }

    OrgChart::iterator OrgChart::end() { 
        return iterator(nullptr,0);
    }

    OrgChart::iterator OrgChart::begin_level_order(){
        return iterator(&this->root,1);
    }

    OrgChart::iterator OrgChart::end_level_order(){
        return iterator(nullptr,0);
    }

    OrgChart::iterator OrgChart::begin_reverse_order(){
        return iterator(&this->root,2);
    }

    OrgChart::iterator OrgChart::reverse_order(){
        return iterator(nullptr,0);
    }

    void OrgChart::iterator::makeRev(Node* start){
        this->runrev.clear();
        queue<Node*> main_queue;
        main_queue.push(start);
        vector<Node*> temp;
        while (!main_queue.empty()) {
            int n = main_queue.size();
            for (int i = 0; i < n; i++) {
                Node* curr = main_queue.front();
                main_queue.pop();
                temp.insert(temp.begin(),curr);
                for(int i=0;i<curr->childern.size();i++)
                    main_queue.push(curr->childern.at((unsigned int)i));
            }
            for(Node* n: temp){
                this->runrev.insert(this->runrev.begin(),n);
            }
            temp.clear();
        }
    }

    OrgChart::iterator OrgChart::begin_preorder(){
        return iterator(&this->root,3);
    }

    OrgChart::iterator OrgChart::end_preorder(){
        return iterator(nullptr,0);
    }
    
    std::ostream& operator<<(std::ostream& output, OrgChart& org){
        for (auto it=org.begin(); it!=org.end(); ++it) {
            output << (*it);
            output <<"->";
            // if(it!=org.end()-1){
            //     output<<"->";
            // }
        }
        return output;
    }































    // vector<string>::iterator OrgChart::begin_reverse_order(){
    //     this->run.clear();
    //     makeReverseRun(this->root);
    //     return this->run.begin();
    // }
    // vector<string>::iterator OrgChart::reverse_order(){
    //     return this->run.end();;
    // }
    

    // void OrgChart::makeReverseRun(Node father){
    //     queue<Node*> main_queue;
    //     main_queue.push(&this->root);
    //     vector<string> temp;
    //     while (!main_queue.empty()) {
    //         int n = main_queue.size();
    //         for (int i = 0; i < n; i++) {
    //             Node* curr = main_queue.front();
    //             main_queue.pop();
    //             temp.insert(temp.begin(),curr->name);
    //             for(int i=0;i<curr->childern.size();i++)
    //                 main_queue.push(curr->childern.at((unsigned int)i));
    //         }
    //         for(string i: temp){
    //             this->run.insert(this->run.begin(),i);
    //         }
    //         temp.clear();
    //     }
    // }


    // vector<string>::iterator OrgChart::begin_preorder(){
    //     this->run.clear();
    //     makePreorderRun(this->root);
    //     return this->run.begin();;
    // }
    // vector<string>::iterator OrgChart::end_preorder(){
    //     return this->run.end();
    // }
    // void OrgChart::makePreorderRun(Node father){
    //     stack<Node>Stack;
    //     Stack.push(father);
    //     while (!Stack.empty()) {
    //         Node temp = Stack.top();
    //         Stack.pop();
    //         this->run.push_back(temp.name);
    //         for (int i = temp.childern.size() - 1; i >= 0; --i) {
    //             Stack.push(temp.childern.at((unsigned int) i));
    //         }
    //     }
    // }
    // vector<string>::iterator OrgChart::begin() { 
    //     this->run.clear();
    //     makeLevelRun(this->root);
    //     return this->run.begin();
    // }

    // vector<string>::iterator OrgChart::end() { 
    //     return this->run.end();
    // }
    

    // vector<string>::iterator OrgChart::begin_level_order(){
    //     this->run.clear();
    //     makeLevelRun(this->root);
    //     return this->run.begin();
    // }
    // vector<string>::iterator OrgChart::end_level_order(){
    //     return this->run.end();
    // }
    // void OrgChart::makeLevelRun(Node father){
    //     queue<Node*> main_queue;
    //     main_queue.push(&this->root);
    //     vector<string> temp;
    //     vector<Node*>t;
    //     while (!main_queue.empty()) {
    //         int n = main_queue.size();
    //         for (int i = 0; i < n; i++) {
    //             Node* curr = main_queue.front();
    //             main_queue.pop();
    //             temp.push_back(curr->name);
    //             t.push_back(curr);
    //             for(int i=0;i<curr->childern.size();i++)
    //                 main_queue.push(&(curr->childern.at((unsigned int)i)));
    //         }
    //         for(string s: temp){
    //             this->run.push_back(s);
    //         }
    //         temp.clear();
    //         for(Node* n: t){
    //             this->Nodes.push_back(n);
    //         }
    //         t.clear();
    //     }
    // }
    // // void OrgChart::vectolink(vector<Node*> &vec){
    // //     Node* temp;
    // //     for (int i=0;i<vec.size()-1;i++){
    // //         // cout<<vec.at((unsigned int)i+1)->name<<endl;
    // //         // vec.at((unsigned int)i)->next=(vec.at((unsigned int)i+1));
    // //         temp=(vec.at((unsigned int)i+1));
    // //     }
    // //     // cout<<temp->name;//
    // //     // this->last=temp;
    // //     // cout<<this->last->name<<endl;
    // // }




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