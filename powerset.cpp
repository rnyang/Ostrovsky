#include <iostream>
#include <set>
 
using namespace std;

template<typename Set> std::set<Set> powerset(const Set& s, size_t n)
{
  typedef typename Set::const_iterator SetCIt;
  typedef typename std::set<Set>::const_iterator PowerSetCIt;
  std::set<Set> res;
  if(n > 0) {
    std::set<Set> ps = powerset(s, n-1);
    for(PowerSetCIt ss = ps.begin(); ss != ps.end(); ss++)
      for(SetCIt el = s.begin(); el != s.end(); el++) {
	Set subset(*ss);
	subset.insert(*el);
	res.insert(subset);
      }
    res.insert(ps.begin(), ps.end());
  } else
    res.insert(Set());
  return res;
}
template<typename Set> std::set<Set> powerset(const Set& s)
{
  return powerset(s, s.size());
}

int main()
{

  int a[] = {0,1,2,3,4};
  set<int> s (a,a+5);

  set<Set> r = powerset(s);

  for (set<Set>::iterator it = r.begin(); it != r.end(); ++it)
    {
      for (set<int>::iterator itt = (*it).begin(); itt != (*it).end(); ++itt)
	cout << *itt << " ";
    }

  cout << endl;

  return 0;
}
