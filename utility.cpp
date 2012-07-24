/*
 * Utility Functions
 * Copyright University of Chicago 2012
 * Author: Runnan Yang
 *
 */

#include <set>
#include <iostream>
#include <vector>

using namespace std;

void print(set<int> v)
{
  for (set<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
      cout << *it << " ";
    }
  cout << endl;
}

void print(set< set<int> > v)
{
  for (set< set<int> >::iterator it = v.begin(); it != v.end(); ++it)
    {
      print(*it);
    }
  cout << endl;
}

void print(vector<int> v)
{
  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    {
      cout << *it << " ";
    }
  cout << endl;
}

void print(vector< vector<int> > v)
{
  for (vector< vector<int> >::iterator it = v.begin(); it != v.end(); ++it)
    {
      print(*it);
    }
  cout << endl;
}

void print(string s)
{
  cout << s << endl;
}

set<int> v2s(vector<int> v){
  set<int> out;
  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
    out.insert(*it);
  return out;
}

vector<int> s2v(set<int> v){
  vector<int> out;
  for (set<int>::iterator it = v.begin(); it != v.end(); ++it)
    out.push_back(*it);
  return out;
}

set< set<int> > combrec(set<int> prev, set<int> rest)
{
  set< set<int> > out;
  if (rest.size() <=1)
    {
      out.insert(prev);
      prev.insert(*rest.begin());
      out.insert(prev);
    }
  else
    {
      out.insert(prev);
      for (set<int>::iterator it = rest.begin(); it != rest.end(); ++it)
	{
	  set<int> prevtemp(prev);
	  set<int> resttemp;

	  prevtemp.insert(*it);

	  for (set<int>::iterator itt = rest.begin(); itt != rest.end(); ++itt)
	    {
	      if (*itt != *it)
		resttemp.insert(*itt);
	    }

	  set< set<int> > combs = combrec(prevtemp, resttemp);

	  for (set< set<int> >::iterator cit = combs.begin(); cit != combs.end(); ++cit)
	    {
	      out.insert(*cit);
	    }
	  
	}
    }

  return out;
}

std::vector< std::vector<int> > combrec(std::vector<int> prev, 
					std::vector<int> rest){
  std::vector< std::vector<int> > out;

  if (rest.size() <= 1){
    out.push_back(prev);
    prev.insert(prev.end(), rest.begin(), rest.end());
    out.push_back(prev);
  }
  else{
    out.push_back(prev);
    for( std::vector<int>::size_type it = 0; it < rest.size(); ++it){
      std::vector<int> prevtemp (prev);
      std::vector<int> resttemp;
      prevtemp.push_back(rest[it]);

      for (vector<int>::size_type itt = 0; itt < rest.size(); ++itt){
	if (it != itt){
	  resttemp.push_back(rest[itt]);
	}
      }

      std::vector< std::vector<int> > combs = combrec(prevtemp, resttemp);

      for (std::vector< std::vector<int> >::iterator cit = combs.begin(); cit != combs.end(); ++cit){
	out.push_back(*cit);
      }
    }
  }
  return out;
}

// Wrapper for combrec
std::set< std::set<int> > powerset(std::set<int> values){
  std::set<int> init;
  return combrec(init, values);
}

std::vector< std::vector<int> > powerset(std::vector<int> values){
  std::vector<int> init;
  return combrec(init, values);
}
