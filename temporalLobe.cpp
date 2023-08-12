#include "temporalLobe.h"

//testing ...
//when inputed

//if new problem/ category(method for finding undefined) create stack, take in data, push into stack.

//pull from stack to deposit into memory, connect first data point to the root or a related topic, pull data from stack and add to data root (from last position of stack), give new weight to each node along path from root to deposited node. This should allow the ability to locate this node.

//however flag should exist and if data inputted already exists in hashdata root should be plotted around existing data point , this creates clusters of data related to certain topics.

//(possible modification, outside edges of data should be connected to root to allow fastest data path within clusster to be found), could be changed.

temporalLobe::node* temporalLobe::initialiseMemory(bool doesStructureExist)  // initialise memory root, write to file using writeStructure file
{
    if(doesStructureExist == false)
    {
        root = createNode(0, 0);
        return root;
    }
    else
    {
        return nullptr;
    }
}

void temporalLobe::writeStructure() //write current structure to file, could possibly pull all known points from stored stack if saving whole points, or could simply write to file every time a node is created or destroyed.
{
    //write memory structure to binary file
}

void temporalLobe::readStructure() //loads current database structure from file, could load root first from beginning of file, then each individual node (consisting of dataCode and int data stored in node for translation), then connections between these nodes aka individual weights are loaded (consisting of in and out pointing connections and dataCode of weight (what node this weight points to for use by pathing algorithm).
{
    //read binary file, write from binary file to system (initialising the stored memory structure)
}

temporalLobe::node* temporalLobe::findRoot() //more memorable way to findRoot, for those who may not understand that the root private variable within tempLobe class exists to point to existing root :)
{
    return root;
}


temporalLobe::node* temporalLobe::findNode(long long int dataCode) //Find existing node to pull data from within the structure
{

    weight* topWeight{};
    node* focusNode{};
    weight* focusWeight{};
    
    

    focusNode = root;
    while (true)
    {
        if (focusNode == nullptr)
        {
            return nullptr; //datacorruption node no longer exists)
        }
        else
        {
            if (focusNode->dataCode == dataCode)
            {
                return focusNode;
            }
            else
            {
                topWeight = focusNode->outTop[dataCode].second;  //find weight pointing to path of weights towards desired node
                if (topWeight == nullptr) //precaution in case of memory corruption leading to a null weight being placed within topWeight of a node
                {
                    focusWeight = focusNode->out[dataCode][0];

                    if (focusWeight == nullptr)
                    {
                        return nullptr;
                    }
                }
                else
                {
                    focusWeight = topWeight; //find weight point with highest relevance to desired node (travelled across most frequently) refer to todo list, this algorithm only works if weights are correctly sorted within their respective vectors
                    focusNode = focusWeight->out;
                }
            }
        }
    }


}

void temporalLobe::decidePos(std::vector<long long int> data) //needs redevelopment as so to allocate data to out[] vector of addresses in node structure
{
   
    int existingIteration{};
    int vectorSize = data.size();
    std::vector <long long int> existingDataOverflow{};
    bool flag = false;

    node* stackRoot{};
    node* focusNode{};
    weight* focusWeight{};

   

    for (int i = 0; i < vectorSize; i++)
    {
        if (hashIn(data[i], true) == true)
        {
            if (flag == true)
            {
                existingDataOverflow.push_back(data[i]); //list of existing nodes that need to be connected to already found node (remember to check if connections between these nodes already exist) (connect every node to every node, all probability cases e.g blue to red red to blue etc.
                data.erase(data.begin() + i);
            }
            else
            {
                existingIteration = i;
                flag = true;
            }
        }
    }


    if (flag == true)
    {
        
        stackRoot = findNode(tempHashData(data[existingIteration]));
      

        weight* newWeight = new weight(vectorSize, stackRoot->dataCode, stackRoot, nullptr); //points in to node but not out
        focusWeight = newWeight;

        data.erase(data.begin() + existingIteration);
        --vectorSize;

      
        focusNode = createNode(9, data[0], newWeight, nullptr);
        data.erase(data.begin());

       
        while (vectorSize > 0)
        {
            weight* newWeight = new weight(vectorSize, stackRoot->dataCode, focusNode, nullptr);
            focusWeight = newWeight;
            focusNode = createNode(vectorSize, data[0],focusWeight, nullptr);
            
            data.erase(data.begin());
            --vectorSize;
        }
            
        vectorSize = existingDataOverflow.size();
        while (vectorSize > 0) //add connections between all already existing node to root node (deliberate whether to add connection from these nodes to newly created nodes too).
        {
            focusNode = findNode(tempHashData(existingDataOverflow[0]));

            weight* newWeight = new weight(5, focusNode->dataCode, stackRoot, focusNode);
            weight* newWeight = new weight(5, stackRoot->dataCode, focusNode, stackRoot);

            --vectorSize;
            existingDataOverflow.erase(existingDataOverflow.begin());
            //traversal funtion to grab existing node address as pointer (to make) need way to point to existing node, best case scenario without traversal
        }
    }
    else
    {

        stackRoot = root;

        while (vectorSize > 0)
        {
            weight* newWeight = new weight(vectorSize, stackRoot->dataCode, focusNode, nullptr);
            focusWeight = newWeight;
            focusNode = createNode(vectorSize, data[0], focusWeight, nullptr);

            data.erase(data.begin());
            --vectorSize;
        }
   
    }
}
//if connecction already exists when finding running through stack after match has been found simply connect existing data set to existing data set.


temporalLobe::node* temporalLobe::createNode(long long int relevance, long long int data) //initialises node, hashes new dataCode for pathing algorithm, adds weights in relation to nodes position (connects node to data structure) (referance ^^) : NOTE:: Only for data to be stored by data structure.
{
   long long int hash = hashIn(data);
   node* newNode = new node(data, hash, 1, nullptr, nullptr);
    
     return newNode;
}
temporalLobe::node* temporalLobe::createNode(long long int relevance, long long int data, weight* in, weight* out)
{
    long long int hash = hashIn(data);
    node* newNode = new node(data, hash, 1, out, in);

    out->in = newNode;
    in->out = newNode;

    return newNode;
}
temporalLobe::weight* temporalLobe::createWeight(int relevance, int dataCode, node* in, node* out)
{
    weight* newWeight = new weight(relevance, dataCode, in, out);

  //in->out[dataCode] = newWeight;
    
    compareTopWeight(dataCode, newWeight, 1);
    compareTopWeight(dataCode, newWeight);

    return newWeight;
}


void temporalLobe::pushOutWeight(long long int dataCode, node* currentNode, weight* out)
{
    currentNode->out[dataCode].push_back(out);
};
void temporalLobe::pushInWeight(long long int dataCode, node* currentNode, weight* in)
{
    currentNode->in[dataCode].push_back(in);
};

void temporalLobe::compareTopWeight(long long int dataCode, weight* currentWeight, unsigned short overload) //compare top in weight of node
{

    if (currentWeight->relevance > currentWeight->out->inTop[dataCode].first)
    {
        currentWeight->out->pushTopWeight(dataCode, currentWeight, overload);
    }
}
void temporalLobe::compareTopWeight(long long int dataCode, weight* currentWeight) //compare top out weight of node
{
    if (currentWeight->relevance > currentWeight->in->outTop[dataCode].first)
    {
        currentWeight->in->pushTopWeight(dataCode, currentWeight);
    }
}

long long int temporalLobe::hashIn(long long int data) 

{
    long long int temp{};

    temp = data * 100 % 10 - 5 / 2 + 22 * 3;

    std::cout << "DataCode ouput from hashing algorithm = " << temp << "\n";

    for (long long int i = 0; i <= temp; i++)
    {

        if (hashCodes[i] == NULL)
        {
            hashCodes.push_back(0);

            std::cout << "Push back on hashCode vector | data = 0 | " << "Current iteration = " << i << "\n";
        }
        else
        {
            std::cout << "Passing over existing data point | data = " << hashCodes[i] << " | Current iteration = " << i << "\n";
            continue;
        }
    }

    while (true)
    {
        long long int i = temp;
        if (hashCodes[i] == NULL)
        {
            std::cout << "Data input into hashCode vector | data = " << temp << " | Current iteration = " << i << "\n";
            hashCodes[i] = temp;

            return temp;
        }
        else
        {
            if (hashCodes[i] == 0)
            {
                std::cout << "Data input into hashCode vector | data = " << temp << " | Current iteration = " << i << "\n";
                hashCodes[i] = temp;
                return temp;
            }
            else
            {
                std::cout << "Passing over existing data point | data = " << hashCodes[i] << " | Current iteration = " << i << "\n";
                ++i;
            }
        }
    }

}





bool temporalLobe::hashIn(long long int data, bool overload)
{
    long long int temp{};

    temp = data * 100 % 10 - 5 / 2 + 22 * 3;

    std::cout << "DataCode ouput from hashing algorithm = " << temp << "\n";

    if (hashCodes[temp] != NULL)
    {
        if (hashCodes[temp] != 0)
        {
            if (hashCodes[temp] == temp)
            {
                std::cout << "DataCode found in hashTable. Returning true. \n";
                return true;
            }
            else
            {
                while (true)
                {
                    
                    long long int i = temp;
                    std::cout << "Existing DataCode not equal to input found, incrementing index. Index = " << i << "\n";

                    if (hashCodes[i] <= temp)
                    {
                        if (hashCodes[i] != temp)
                        {
                            ++i;
                        }
                        else
                        {
                            std::cout << "DataCode found in hash table, index = " << i << "\n";
                            return true;
                        }
                    }
                    else
                    {
                        std::cout << "DataCode not found in hash table, last index = " << i << " Data stored in index = " << hashCodes[i] << "\n";
                        return false;
                    }
                }
            }
        }
        else
        {
            std::cout << "DataCode not found in hash table, last index = " << temp << " Data stored in index = " << hashCodes[temp] << "\n";
            return false;
        }
    }
    else
    {
        std::cout << "DataCode not found in hash table, last index = " << temp << " Data stored in index = NULL | End of table reached. \n";
        return false;
    }

}


long long int temporalLobe::tempHashData(long long int data) //quickly hash data for comparison
{
    return data * 100 % 10 - 5 / 2 + 22 * 3;
}





// Model brains memory off of weighted graph and A star algorithm.
    /*

    TAKE DATA INPUT
    RELATE DATA INPUT TO EXISTING MEMORY THROUGH A STAR (USING WEIGHT SPECIFIC MEMORY, IF MEMORY WEIGHT DOESNT EXIST RETURN !MEMORY EXISTS)
    IF ( MEMORY EXISTS )
    {
      RETURN MEMORY ALONG WITH EXISTING DATA WITH SIGNIFICANT WEIGHT
      ADD WEIGHT TO CONNECTION TO THAT MEMORY CLUSTER
    }
    ELSE
    }
      STORE MEMORY
      WEIGHT = 1;
    }
    END

    */

    //IF DATA IS USED FREUENTLY WITH OTHER DATA ADD CONNECTIONS TO RELAVENT DATA


//NOTE:: TO REMEMBER:: IMPLEMENTATION OF THIS MEMORY STORAGE TYPE AND NOT A HASHED DATA BASE IS SO RELATIONAL DATA CAN BE PULLED ALONG WITH REQUIRED DATA BY PROBLEM SOLVING ALGORITHMS TO FORM COHERENT RESPONSES AND ACTIONS TO INPUTTED DATA
//NOTE FOR FURTHER DEVELOPMENT: FOCUS ON BASIC FEATURES AS OF RIGHT NOW, FEATURES FOR ADDED EFFICIENCY / USER EXPERIENCE CAN COME IN LATER :)
                                   //PRIORITY TO DO LIST
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Add function that runs through entire memory structure, --relevance from all nodes and weights etc unless they have permanance in the system (a relevance over 10 (subject to change after experimentation)) function then deletes all nodes and weights with a relevance of 0, this saves storage space
//Add translation function that is able to write entire structure to a binary file, works off of a translation ruleset, e.g five 0s in conjunction for a new weight /  node etc (needs to be developed theoretically). De initialise structure (delete) after this has been finished.
//Add reverse to the above function as so you can read from a binary file and initialise the structure. Using the same translation function makes sense, should be coded as so it can work in reverse too.
//Note: using the c++ bitmap function library should be useful for the above two ADDs.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


                                   //TO DO LIST
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Write function to be placed into the STEM loop, link all functions to ENUMS as so they can be called individually by the que.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
