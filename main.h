/*
 * Supply Chain Network - Stable Matching (based on Ostrovsky AER 2008)
 * Copyright University of Chicago 2012
 * Author: Runnan Yang
 */

#include<vector>

using namespace std;

typedef vector<int>::iterator VecIt;

struct Network
{
  Network();
  vector<int> contracts;
};

struct Prenetwork
{
  Prenetwork();
  Prenetwork(vector<int> agents, vector<int> arrows, vector<int> contracts);
  vector<int> agents;
  vector<int> arrows;
  vector<int> contracts;
};

struct Agent
{
  Agent();
  // function ptr to utility function
  int level; // only lower level agents can sell to higher level agents
};

struct Arrow
{
  Arrow();
  Arrow(int contract, int origin, int target);
  int contract;
  int origin;
  int target;
};

struct Contract
{
  Contract();
  Contract(int qty, double price, int origin, int target);
  int qty;
  double price;
  int origin;
  int target;
};

// Constructors

Network::Network() {};

Prenetwork::Prenetwork() {};
Prenetwork::Prenetwork(vector<int> agents_, vector<int> arrows_, vector<int> contracts_)
{
  agents = agents_;
  arrows = arrows_;
  contracts = contracts_;
}

Agent::Agent() {};


Arrow::Arrow() {};
Arrow::Arrow(int contract_, int origin_, int target_)
{
  contract = contract_;
  origin = origin_;
  target = target_;
}

Contract::Contract() {};
Contract::Contract(int qty_, double price_, int origin_, int target_)
{
  qty = qty_;
  price = price_;
  origin = origin_;
  target = target_;
}
