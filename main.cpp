/*
 * Supply Chain Network - Stable Matching (based on Ostrovsky AER 2008)
 * Copyright University of Chicago 2012
 * Author: Runnan Yang
 */

#include<iostream>
#include<set>

#include "main.h"

using namespace std;



// Choice function

vector<int> choice(int agent, vector<int> contracts)
{
  vector<int> choice_contracts;

  // for each possible subset of contracts (i.e. power set), calculate utility
  // find max utility subset and return it

  return choice_contracts;
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

void T_algorithm()
{
  // setup the min prenetwork

  // iterate while not fixed point
  
  // apply F_map
}

// points to origin (favors suppliers)
void minPrenetwork(vector<int> agents, vector<int> contracts, vector<Contract> contractDB)
{
  vector<Arrow> arrowDB;
  for (VecIt contract_it = contracts.begin(); contract_it != contracts.end(); ++contract_it)
    {
      Contract temp = contractDB[*contract_it];
      arrowDB.push_back(Arrow(*contract_it, temp.target, temp.origin)); // arrow: target -> origin
    }

  vector<int> arrows;
  for (vector<Arrow>::iterator arrow_it = arrowDB.begin(); arrow_it != arrowDB.end(); ++arrow_it)
    {
      //arrows.push_back(
    }
  
  return Prenetwork(agents, arrows, contracts);
}

// points to target (favors consumers)
void maxPrenetwork(vector<int> agents, vector<int> contracts)
{
  
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
}
