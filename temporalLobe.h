#pragma once
#include "instructionSet.h"

//relevance : how many times this edge is traversed, algorithm prefers to traverse data points with higher relavance to object to find it.
//relevance : what the edge is actually leading towards, what is it actually relevent to.

/*
* when data is first stored edge is added to each data point traversed to find it, relevance is added in accordance to the data point originally fetched, this is done to data points hopefully related
  to the added data in some tangible way, as a human relates an elephant as an animal, data points reletad to animals should hopefully all have an edge originating from "animal"
  datacode is added, data points closer to the node will have a higher data code for that specified node, relating them to it, data points that are heavily traversed to reach a point will have a higher weight
  nodes with a lowest data code, and therefore at the edge of the data structure, are considered by deletion function, automatically deleted after so many loops if unused, conserving memory, unless considered priority by machine, flag will be given for this
  old unused nodes will also be deleted as they have not been traversed in a while.
  function will be implemented, after certain cycles every weights data code will be reduced by a set number, could be dependant on how low the data code is, larger reduction for new or old unused data e.g data with data codes < 10
   
   checks to see if relevance related to this (done through hashing) e
*/

/*
   //e.g input(find data 5)

   take data input, connect it to last fetched node on edge of grid, adds weight structure to each node traversed to reatch the newly added node, stored in stack. 





*/
class temporalLobe
{
	//FIND WAY TO DYNAMICALLY ADD WEIGHT TO NODE, MULTIPLE WEIGHTS REQUIRED
	struct node
	{
		long long int data;
		node(long long int data)
		{
			this->data = data;
		}

	};

	struct weight
	{
		int relevance{};
		long long int dataCode{};
		
		weight* in;
		weight* out;

		weight(long long int relevance, long long int dataCode, weight* in, weight* out)
		{
			this->relevance = relevance;
			this->dataCode = dataCode;
			this->in = nullptr;
			this->out = nullptr;
		}

	};


	temporalLobe()
	{
		node* newNode = new node(48384834);
		weight* newWeight = new weight(1, 8933309, )

	}
	
public:



private:

};

