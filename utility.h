/*
 * Utility.h
 * Copyright University of Chicago 2012
 * Author: Runnan Yang
 */

#include <iostream>
#include <vector>
#include <set>

using namespace std;

void print(set<int> v);
void print(set< set<int> > v);
void print(vector<int> v);
void print(vector< vector<int> > v);
void print(string s);

set<int> v2s(vector<int> v);
vector<int> s2v(set<int> v);

set< set<int> > combrec(set<int> prev, set<int> rest);
vector< vector<int> > combrec(vector<int> prev, vector<int> rest);

set< set<int> > powerset(set<int> s);
vector< vector<int> > powerset(vector<int> s);
