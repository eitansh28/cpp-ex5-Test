#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>

#pragma once
using namespace std;


namespace ariel{
    class iterator;
    struct Node {
		string name;
        Node* next;
        vector<Node>childern;
    };
    
    class OrgChart
    {
    private:
        
    Node root;
    Node* last;
    vector<string>run;
    vector<Node>runNodes;
    int start=0;

    public:
        OrgChart();
        // ~OrgChart();
        OrgChart& add_root(string root);
        OrgChart& add_sub(string commander, string subordinate);
        bool findingFather(Node &root, string com, string sub);
        vector<string> getrun();
        Node getroot(){return this->root;}
        // vector<string>::iterator begin();
        // vector<string>::iterator end();
        vector<string>::iterator begin_level_order();
        vector<string>::iterator end_level_order();
        vector<string>::iterator begin_reverse_order();
        vector<string>::iterator reverse_order();
        vector<string>::iterator begin_preorder();
        vector<string>::iterator end_preorder();
        void makeLevelRun(Node father);
        void makeReverseRun(Node father);
        void makePreorderRun(Node father);
        void vectolink(vector<Node> &vec);
        friend std::ostream& operator<<(std::ostream& output, OrgChart& org);
     
    class iterator {
        
	private:
        Node* pointer_to_current_node;
        // vector<string>::iterator it;

	public:

		iterator(Node* ptr)
			: pointer_to_current_node(ptr) {}
        // iterator(vector<string>::iterator it)
		// 	: it(it) {}

		string& operator*() const {
			return pointer_to_current_node->name;
		}
        // string& operator*() const {
		// 	return *it;
		// }

		string* operator->() const {
			return &(this->pointer_to_current_node->name);
		}
        // string* operator->() const {
		// 	return &(*it);
		// }

		iterator& operator++() {
			pointer_to_current_node=pointer_to_current_node->next;
			return *this;
		}
        // iterator& operator++() {
		// 	++it;  //mistake!!!!!!
		// 	return *this;
		// }

		iterator operator++(int) {
			iterator tmp = *this;
            pointer_to_current_node=pointer_to_current_node->next;
            return tmp;
		}

		friend bool operator== (const iterator& a, const iterator& b) {
            return a.pointer_to_current_node == b.pointer_to_current_node;
        }
        friend bool operator!= (const iterator& a, const iterator& b) {
            return a.pointer_to_current_node != b.pointer_to_current_node; 
        }  

	};  // END OF CLASS ITERATOR
    iterator begin();
    iterator end();
    };
}