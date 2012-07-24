/*
 * Supply Chain Network - Stable Matching (based on Ostrovsky AER 2008)
 * Copyright University of Chicago 2012
 * Author: Runnan Yang
 */

#include "main.h"
#include <iostream>
#include <set>
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

// Choice function
vector<int> choice(int agent, vector<int> contracts, vector<Agent> agent_db, vector<Contract> contract_db)
{
  int maxU = 0;
  set< set<int> >::iterator maxC;

  // generate power set of contracts
  set<int> contr = v2s(contracts);
  set< set<int> > all_contract_choices = powerset(contr);

  // find max utility subset from power set
  for (set< set<int> >::iterator it = all_contract_choices.begin(); 
       it != all_contract_choices.end(); ++it){
    if (agent_db[agent].utility(*it, contract_db) > maxU){
      maxU = agent_db[agent].utility(*it, contract_db);
      maxC = it;
    }
  }
  
  vector<int> choice = s2v(*maxC);

  return choice;
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

Prenetwork T_iterate(Prenetwork prenetwork, vector<Arrow> arrow_db)
{
  // make an output set
  Prenetwork new_prenetwork(prenetwork.agents, prenetwork.arrows, prenetwork.contracts);

  // make a copy of everything because I'm lazy
  vector<int> agents = prenetwork.agents;
  vector<int> arrows = prenetwork.arrows;
  vector<int> contracts = prenetwork.contracts;

  // for each agent
  for (vector<int>::iterator agent_it = agents.begin(); agent_it != agents.end(); ++agent_it)
    {
      cout << "Adding arrows for agent " << *agent_it << endl;
      // copy the contracts corresponding to the current arrows pointing at agent a
      vector<int> curr_contracts;

      for (vector<int>::iterator arrow_it = arrows.begin(); arrow_it != arrows.end(); ++arrow_it)
	{
	  // if arrow is point at a
	  if (arrow_db[*arrow_it].target == *agent_it)
	    {
	      curr_contracts.push_back(arrow_db[*arrow_it].contract);
	    }
	}

      
      cout << "Current contracts pointing at agent " << *agent_it << " are: ";
      for (VecIt it = curr_contracts.begin(); it != curr_contracts.end(); ++it){
	cout << *it << " ";
      }
      cout << endl;
      

      // for each contract, try adding it
      for (vector<int>::iterator contract_it = contracts.begin(); contract_it != contracts.end(); ++contract_it)
	{
	  curr_contracts.push_back(*contract_it);

	  // find the choice set of the agent from curr_contracts
	  // append those arrows to new_prenetwork

	  curr_contracts.pop_back();
	}

    }
  
  // 

  return new_prenetwork;
}

// Check that arrows in Prenetwork are identical 
// (i.e. is a fixed point in iterations of T_algorithm
bool fixed_point(Prenetwork a, Prenetwork b)
{
  return (a.arrows == b.arrows);
}

Network T_algorithm(vector<int> agents, vector<int> contracts, vector<Arrow> arrow_db)
{
  // setup the min prenetwork
  Prenetwork p = minPrenetwork(agents, contracts);
  Prenetwork next = T_iterate(p, arrow_db);

  // iterate while not fixed point
  while (!fixed_point(p, next))
    {
      p = next;
      next = T_iterate(p, arrow_db);
    }
  
  // apply F_map
  Network stableNet = F_map(p, arrow_db);

  return stableNet;
}

// points to origin (favors suppliers)
Prenetwork minPrenetwork(vector<int> agents, vector<int> contracts)
{
  vector<int> arrows;
  for (VecIt contract_it = contracts.begin(); contract_it != contracts.end(); ++contract_it)
    {
      arrows.push_back(contractToArrow(*contract_it, true));
    }
  return Prenetwork(agents, arrows, contracts);
}

// points to target (favors consumers)
Prenetwork maxPrenetwork(vector<int> agents, vector<int> contracts)
{
  vector<int> arrows;
  for (VecIt contract_it = contracts.begin(); contract_it != contracts.end(); ++contract_it)
    {
      arrows.push_back(contractToArrow(*contract_it, false));
    }
  return Prenetwork(agents, arrows, contracts);
}

// map contract id's to arrow id's
// returns 2*contract if towards target, 2*contract + 1 if towards origin
int contractToArrow(int contract, bool towardsOrigin)
{
  return towardsOrigin + 2 * contract;
}

Network F_map(Prenetwork prenetwork, vector<Arrow> arrowDB)
{
  vector<int> contractsTemp(prenetwork.contracts.size(), 0);
  Network network;

  for (VecIt arrow_it = prenetwork.arrows.begin(); arrow_it != prenetwork.arrows.end(); ++arrow_it)
    {
      ++contractsTemp[arrowDB[*arrow_it].contract];
    }

  // if both arrows on the contract are included, then the contract is part of the network
  for (VecIt contract_it = contractsTemp.begin(); contract_it != contractsTemp.end(); ++contract_it)
    {
      if (*contract_it == 2)
	{
	  network.contracts.push_back(*contract_it);
	}
    }

  return network;
}

int main(int argc, char** argv)
{

  /*
  int myAgents[] = {0,1,2};
  vector<int> agents (myAgents, myAgents + sizeof(myAgents) / sizeof(int) );

  vector<Arrow> arrowDB;
  arrowDB.push_back(Arrow(0, 0, 1));
  arrowDB.push_back(Arrow(0, 1, 0));
  arrowDB.push_back(Arrow(1, 1, 2));
  arrowDB.push_back(Arrow(1, 2, 1));

  int myArrows[] = {0,1,2,3};
  vector<int> arrows (myArrows, myArrows + sizeof(myArrows) / sizeof(int) );

  vector<Contract> contractDB;
  contractDB.push_back(Contract(1, 0, 0, 1));
  contractDB.push_back(Contract(1, 0, 1, 2));

  int myContracts[] = {0,1};
  vector<int> contracts (myContracts, myContracts + sizeof(myContracts) / sizeof(int) );

  Prenetwork init(agents, arrows, contracts);
  Prenetwork it = T_iterate(init, arrowDB);
  T_iterate(init, arrowDB);

  return 0;
  */

  int myInts[] = {1,2,3,4,5};
  set<int> s (myInts, myInts+5);  
  set< set<int> > ss = powerset(s);

  print(ss);
}
