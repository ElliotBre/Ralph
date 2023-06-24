#include "temporalLobe.h"


//when inputed

//if new problem/ category(method for finding undefined) create stack, take in data, push into stack.

//pull from stack to deposit into memory, connect first data point to the root or a related topic, pull data from stack and add to data root (from last position of stack), give new weight to each node along path from root to deposited node. This should allow the ability to locate this node.

//however flag should exist and if data inputted already exists in hashdata root should be plotted around existing data point , this creates clusters of data related to certain topics.

//(possible modification, outside edges of data should be connected to root to allow fastest data path within clusster to be found), could be changed.

temporalLobe::node* temporalLobe::initialiseMemory(bool doesStructureExist)  // initialise memory root, write to file using writeStructure file
{
    if(doesStructureExist == false)
    {
        return createNode(0, 0);
    }
    else
    {
        return nullptr;
    }
}

void temporalLobe::writeStructure() //write current structure to file, could possibly pull all known points from stored stack if saving whole points, or could simply write to file every time a node is created or destroyed.
{
    
}

void temporalLobe::readStructure() //loads current database structure from file, could load root first from beginning of file, then each individual node (consisting of dataCode and int data stored in node for translation), then connections between these nodes aka individual weights are loaded (consisting of in and out pointing connections and dataCode of weight (what node this weight points to for use by pathing algorithm).
{

}



temporalLobe::node* temporalLobe::findNode(long long int dataCode)
{
    return nullptr;
}
void temporalLobe::decidePos(std::vector<long long int> data) //needs redevelopment as so to allocate data to out[] vector of addresses in node structure
{
    long long int stackRoot{};
    int existingIteration{};
    int vectorSize = data.size();
    int relevance{};
    std::vector <long long int> existingDataOverflow{};
    bool flag = false;
 

    for (int i = 0; i < vectorSize; i++)
    {
        if (hashIn(data[i], true) == true)
        {
            if (flag == true)
            {
                existingDataOverflow.push_back(data[i]);
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

        
        stackRoot = data[existingIteration];
        weight* newWeight = new weight(vectorSize, /*pointerToExistingNode->dataCode*/, /*pointer to existing node, traversal function or list of node addresses needed*/, nullptr);

        data.erase(data.begin() + existingIteration);
        --vectorSize;

        while (true)
        {
            
        }
        
        
        //traversal funtion to grab existing node address as pointer (to make) need way to point to existing node, best case scenario without traversal

    }
    else
    {
        stackRoot = data[0];
    }

    while (true)
    {
        
    }

}
//if connecction already exists when finding running through stack after match has been found simply connect existing data set to existing data set.


temporalLobe::node* temporalLobe::createNode(long long int relevance, long long int data) //initialises node, hashes new dataCode for pathing algorithm, adds weights in relation to nodes position (connects node to data structure) (referance ^^) : NOTE:: Only for data to be stored by data structure.
{
   long long int hash = hashIn(data);
     node* newNode = new node(data, hash, nullptr, nullptr);

     return newNode;
}
temporalLobe::weight* temporalLobe::createWeight(int relevance, int datacode, node* in, node* out)
{
    weight* newWeight = new weight(relevance, datacode, in, nullptr);

    return newWeight;
}

/*void temporalLobe::Root()
{
    node*newNode = new node(0,0,nullptr, 1)
}
*/


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
// Create treversal function to specific node as precourser to node creation functions, nescassary as to grab node address if it already exists in existing memory structure. Follow memory structure in referance

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


                                   //TO DO LIST
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//TODO ADD FUNCTION TO SAVE CURRENT DATA STRUCTURE TO DEVICE STORAGE, NOTE :: AFTER STRUCTURAL FUNCTIONS HAVE BEEN DESIGNED AND IMPLEMENTED
//to do update to give weight connection to root or position from root in referance to data inputed along with data. other update referance ^^ , this is going to take a while :) (develop decidePos in conjunction with dataIn func)
// TODO CONFIGURE IN AND OUT ADRRESSES OF EACH NODE TO BE AN ARRAY OF ADDRESSES, THE POSITIONS OF WHICH ARE DETERMINED BY THE DATACODE OF THE NODE BEING POINTED TO
// NOTE: POSSIBLY ONLY NEED OUT ADDRESSES IF ALGORITHM IS GOING TO BE ONE WAY, AS ADDRESSES OF ALREADY TRAVERSED NODES WILL BE STORED IN A STACK.
//     // Edit hash function as so hashcodes are stored with an in pointer to relative node.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
