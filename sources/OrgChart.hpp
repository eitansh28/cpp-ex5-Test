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
        vector<Node*>childern;
    };
    
    class OrgChart
    {
    private:
        
    Node root;
    vector<Node*>Nodes;
    int start=0;

    public:
        OrgChart();
        ~OrgChart();
        OrgChart(OrgChart &other);
        OrgChart(OrgChart &&other)noexcept;
        OrgChart& operator=(OrgChart &&other)noexcept;
        OrgChart& operator=(const OrgChart &other);
        OrgChart& add_root(string root);
        OrgChart& add_sub(string commander, string subordinate);
        bool findingFather(Node* root, string com, string sub);
        Node getroot(){return this->root;}
        friend std::ostream& operator<<(std::ostream& output, OrgChart& org);
     
    
    class iterator {
        
	private:
        Node* pointer_to_current_node;
        queue<Node*>Queue;
        stack<Node*>Stack;
        vector<Node*>runrev;
        int flag=0;
        int i=0;

	public:
		iterator(Node* ptr,int flag);
        string& operator*() const;
		string* operator->() const;
        iterator& operator++();
		iterator operator++(int);
        void makeRev(Node* start);

		friend bool operator==(const iterator& a, const iterator& b) {
            return a.pointer_to_current_node == b.pointer_to_current_node;
        }
        friend bool operator!=(const iterator& a, const iterator& b) {
            return a.pointer_to_current_node != b.pointer_to_current_node; 
        }  

	};  // END OF CLASS ITERATOR
    iterator begin();
    iterator end();
    iterator begin_level_order();
    iterator end_level_order();
    iterator begin_reverse_order();
    iterator reverse_order();
    iterator begin_preorder();
    iterator end_preorder();
    };
}













// vector<string>::iterator begin();
        // vector<string>::iterator end();
        // vector<string>::iterator begin_level_order();
        // vector<string>::iterator end_level_order();
        // vector<string>::iterator begin_reverse_order();
        // vector<string>::iterator reverse_order();
        // vector<string>::iterator begin_preorder();
        // vector<string>::iterator end_preorder();
        // void makeLevelRun(Node father);
        // void makeReverseRun(Node father);
        // void makePreorderRun(Node father);
        // void vectolink(vector<Node*> &vec);