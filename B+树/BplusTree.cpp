#include<bits/stdc++.h>
using namespace std;

struct Node{
    bool is_leaf;
    vector<int> keys;
    vector<Node*> children;
    vector<string> vals;
}