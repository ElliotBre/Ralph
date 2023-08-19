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

void temporalLobe::deleteNode(node* nodePointer) //Deletes weights pointing directly into and out of node before deleting the node structure itself. Note: look at todo for further development of this function (and or deleteWeight function depending on direction taken).
{


    while (0 < nodePointer->out.size())
    {
        if (nodePointer->out[0].size() == 0)
        {
            nodePointer->out.erase(nodePointer->out.begin());
        }
        else
        {

            while (0 < nodePointer->out[0].size())
            {
                deleteWeight(nodePointer->out[0][0]);
               // nodePointer->out[0].erase(nodePointer->out[0].begin()); Note: not needed (neeeds to be tested) as removal covered in deleteWeight Function
            }

            nodePointer->out.erase(nodePointer->out.begin());
        }

    }

    while (0 < nodePointer->in.size())
    {
        if (nodePointer->in[0].size() == 0)
        {
            nodePointer->in.erase(nodePointer->in.begin());
        }
        else
        {

            while (0 < nodePointer->in[0].size())
            {
                deleteWeight(nodePointer->in[0][0]);
                //nodePointer->in[0].erase(nodePointer->in[0].begin()); As stated above.
            }

            nodePointer->in.erase(nodePointer->in.begin());
        }

    }

    delete nodePointer;
}

   

void temporalLobe::deleteWeight(weight* weightPointer) //finds and removes weight from in->out and out->in lists for corresponding nodes before deleting the weight structure itself.
{

    std::vector<weight*> focusVector {};
    std::vector<weight*> focusVectorIn{};
    weight* focusWeight {};
    weight* focusWeightIn{};
    long long int targetWeightIteration {};
    long long int targetWeightIterationIn{};
    long long int tempTargetWeightIterationFront = 0;
    long long int tempTargetWeightIterationFrontIn = 0;
  
    focusVector = weightPointer->out->in[weightPointer->dataCode];
    focusVectorIn = weightPointer->in->out[weightPointer->dataCode];

        //erase correspondent weight in node connected out->in vector
        //erase correspondent weight in node connected in->out vector
        //messing around with simultaneous loop to make the process of searching for weight pointer in both vectors more efficient than having two loops through basic login (I wish, I was way too tired for this). Note: do change this to two seperate loops if this fails spectacularly, I have confidence that it will work as intended though, just here for future troubleshooting
        while (focusWeight != weightPointer || focusWeightIn != weightPointer)
        {
            if(focusWeight != weightPointer)
            { 
            focusWeight = focusVector[0];
            }
       
            if (focusWeightIn != weightPointer)
            {
                focusWeightIn = focusVectorIn[0];
            }

            if (focusWeight == weightPointer && focusWeightIn == weightPointer)
            {
                targetWeightIteration = tempTargetWeightIterationFront;
                targetWeightIterationIn = tempTargetWeightIterationFrontIn;
            }
            else {
                if (focusWeight == weightPointer && focusWeightIn != weightPointer)
                {
                    targetWeightIteration = tempTargetWeightIterationFront;
                    tempTargetWeightIterationFrontIn += 1;

                    focusWeightIn = focusVectorIn[focusVectorIn.size()];
                    if (focusWeightIn == weightPointer)
                    {
                        targetWeightIterationIn = focusVectorIn.size();
                    }
                    else
                    {
                        focusVectorIn.pop_back();
                        focusVectorIn.erase(focusVectorIn.begin());
                    }
                }
                else {
                    if (focusWeight != weightPointer && focusWeightIn == weightPointer)
                    {
                        targetWeightIterationIn = tempTargetWeightIterationFrontIn;
                        tempTargetWeightIterationFront += 1;
                       

                        focusWeight = focusVector[focusVector.size()];
                        if (focusWeight == weightPointer)
                        {
                            targetWeightIteration = focusVector.size();
                        }
                        else
                        {
                            focusVector.pop_back();
                            focusVector.erase(focusVector.begin());
                        }
                    }
                    else {
                        tempTargetWeightIterationFront += 1;
                        tempTargetWeightIterationFrontIn += 1;

                        focusWeight = focusVector[focusVector.size()];
                        focusWeightIn = focusVectorIn[focusVectorIn.size()];

                        if (focusWeight == weightPointer)
                        {
                            targetWeightIteration = focusVector.size();
                        }
                        else
                        {
                            focusVector.pop_back();
                            focusVector.erase(focusVector.begin());
                        }
                        if (focusWeightIn == weightPointer)
                        {
                            targetWeightIterationIn = focusVectorIn.size();
                        }
                        else
                        {
                            focusVectorIn.pop_back();
                            focusVectorIn.erase(focusVectorIn.begin());
                        }
                    }
                }
            }
        
        }



 /*erase from out->in vector*/weightPointer->out->in[weightPointer->dataCode].erase(weightPointer->out->in[weightPointer->dataCode].begin() + targetWeightIteration);
 /*erase from in->out vector*/weightPointer->in->out[weightPointer->dataCode].erase(weightPointer->in->out[weightPointer->dataCode].begin() + targetWeightIterationIn);
        
        delete weightPointer;
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

//Note modifications such as a list of all low relevance vectors (as to speed up process of deletion), can be added. Modification for a more efficient function is also probably needed.
void temporalLobe::relevanceReduction() //runs through every node, if(node->relevance !> 10) --node->relevance, does same for in weight list for each visited node.
{
    node* focusNode{};
    weight* focusWeight{};

    std::vector<long long int> tempCodes = hashCodes;
    std::vector<weight*> tempWeights{};
    


    focusNode = root;

    while (tempCodes.size() > 0)
    {
        focusNode = findNode(tempCodes[0]);

        if (focusNode->relevance < 10)
        {
            if (focusNode->relevance <= 0)
            {
                //delete node (placeholder)
            }
            else
            {
                --focusNode->relevance;

                for (int i = 0; i < focusNode->in.size(); i++)
                {

                    while (tempWeights[0] == nullptr)
                    {
                        tempWeights = focusNode->in[i];
                        if (tempWeights[0] == nullptr)
                        {
                            ++i;
                        }
                    }

                    while (tempWeights.size() > 0)
                    {
                        focusWeight = tempWeights[0];
                        if (focusWeight->relevance < 10)
                        {
                            if (focusWeight->relevance <= 0)
                            {
                                //delete weight (placeholder)
                            }
                            else
                            {
                                --focusWeight->relevance;
                            }

                        }

                        tempWeights.erase(tempWeights.begin());
                    }
                }
            }
        }

        tempCodes.erase(tempCodes.begin());
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
// Debating Add: Function before deletion of found weight in nodeDelete function: function within nodeDelete function to replace cut threads, aka weight -inWeight- /DeletedNode/ -outwWeight- |TargetNode|  ||||||  -inWeight-----|targetNode| ||||||| as shown in diagram should be connected to its target node (node relating to its dataCode) or closest node with an outgoing weight(with same dataCode as targetNode) to targetNode. If no outgoing weight / node exists or dataCode == deletedNode dataCode, then delete weight. May be slightly out of scope for the function group though.
//Add translation function that is able to write entire structure to a binary file, works off of a translation ruleset, e.g five 0s in conjunction for a new weight /  node etc (needs to be developed theoretically). De initialise structure (delete) after this has been finished.
//Add reverse to the above function as so you can read from a binary file and initialise the structure. Using the same translation function makes sense, should be coded as so it can work in reverse too.
//Note: using the c++ binary read / write function library should be useful for the above two ADDs. Aswell as the bitset function to store data points for writing and reading translation.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


                                   //TO DO LIST
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Write function to be placed into the STEM loop, link all functions to ENUMS as so they can be called individually by the que.
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
