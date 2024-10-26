#pragma once
#include "Library.h"

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
public:

	struct weight;
	struct node;
	
	struct node
	{
		long long int data;
		long long int dataCode;

		int relevance;
		//simply always have the current highest weight going outwards stored in a seperate vector that can be accesed when searching, like a temp variable, when entering a new weight or updating an existing weight simply check over this temp variable, if node being compared is bigger, temp = new variable, store as a 2d vector with relevance and a pointer to the weight :)
		std::vector <std::vector<weight*>> out{}; //array of out addresses to different weights
		std::vector<std::pair<long long int , weight*>> outTop; //stored heighest relevance weight for each datacode.

		std::vector <std::vector<weight*>> in{}; //weight can be sorted based on the size of its relevance, accessed through node->relevance, this will be accessed to determine its placement within vector, aka its relevance is its iteration too, weights with the same relevance will simply be pushed back // weight will have to be updated when its relevance is changed, 
		std::vector<std::pair<long long int, weight*>> inTop{}; //stored heighest relevance weight for each datacode.

		void pushTopWeight(long long int dataCode, weight* out)
		{
			this->outTop[dataCode].first = out->relevance;
			this->outTop[dataCode].second = out;
		}
		void pushTopWeight(long long int dataCode, weight* in, unsigned short overload)
		{
			this->inTop[dataCode].first = in->relevance;
			this->inTop[dataCode].second = in;
		}
		node(long long int data, long long int dataCode,long long int relevance, weight* out, weight* in)
		{
			this->data = data;
			this->dataCode = dataCode;
			this->relevance = relevance;

			this->out[dataCode].push_back(in);
			pushTopWeight(dataCode, out);
			this->in[dataCode].push_back(out);
			pushTopWeight(dataCode, in, 1);
			
		}


	};

	struct weight
	{
		int relevance{};
		long long int dataCode{};
		
		node* in;
		node* out;

		weight(long long int relevance, long long int dataCode, node* in, node* out)
		{
			this->relevance = relevance;
			this->dataCode = dataCode;
			this->in = in;
			this->out = out;
		}

	};


	//temporalLobe()
	//{
	//	node* newNode = new node(48384834, 8933309, nullptr, 0);
	//	node* newWeight = new node(); //e.g for use of weight and node in creation of new weight and node

	//}

	//todo create function that uses hashIn to initialise a node from input int data adding returned hash from dataCode input into hashCodes Vector (vectors purpose is to store datacodes of all nodes as to check for node availability before treversal of structure).
	// future referance, deciding function needs to be made to determine wether data needs to be stored fully with weights (dataIn()) if data needs to be retrieved (dataOut) or if a weight has to be added to the data due to relevant data being stored within.
	node* initialiseMemory(bool doesStructureExist);
	void writeStructure();
	void readStructure();

	void decidePos(std::vector<long long int> data);
	node* createNode(long long int relevance, long long int data);
	node* createNode(long long int relevance, long long int data, weight* in, weight* out);
	weight* createWeight(int relevance, int datacode, node* in, node* out);

	void deleteNode(node* nodePointer);
	void deleteWeight(weight* weightPointer);


	void pushOutWeight(long long int datacode, node* currentNode, weight* out);
	void pushInWeight(long long int datacode, node* currentNode, weight* in);
	void compareTopWeight(long long int dataCode, weight* currentWeight, unsigned short overload);
	void compareTopWeight(long long int dataCode, weight* currentWeight);

	long long int hashIn(long long int data);
	bool hashIn(long long int data, bool overload);
	long long int tempHashData(long long int data);
	std::vector<long long int> hashCodes{};

	node* findNode(long long int dataCode);
	node* findRoot();

	void relevanceReduction();

	bool translateStructure(node* root);
	bool readStructure(std::string fileName);

	void writeNode(std::ofstream& file, node* readingNode);
	void writeWeight(std::ofstream& file, weight* readingWeight);
	void writeDupeNode(std::ofstream& file, long long int dataCode);

	std::string readNode(std::vector<node*> *que, std::string contents, weight* in, temporalLobe::weight* out);
	std::string readDupeNode(std::string contents);
	std::string readWeight(std::vector<weight*>* que, std::string contents, node* in, node* out); 

private:
	node* root;
};

