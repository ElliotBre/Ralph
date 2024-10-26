#pragma once
#include "connectionMain.h"

//Binary tree for 

class tree : public temporalLobe
{
public:
	enum message
	{
		START, //ON START INITIALISE ALL TREES FOR QUES RELATIVE TO EACH STEM
		ROOT,
		TEST,



		MEMORY,
		INIT,
		WRITESTRUCT,
		READSTRUCT,
		DECIDEPOS,
		CREATENODE,
		CREATENODEFULL,
		CREATEWEIGHT,
		DELETENODE,
		DELETEWEIGHT,
		PUSHOUTWEIGHTADRESS,
		PUSHINWEIGHTADRESS,
	    HASHIN,
		HASHINOVERLOAD,
		TEMPHASHDATA,
		FINDNODE,
		FINDROOT,
		RELEVANCEREDUCTION,
		TRANSLATESTRUCTURE,
		READSTRUCTURE,
		WRITENODE,
		WRITEWEIGHT,
		WRITEDUPENODE,
		READNODE,
		READDUPENODE,
		READWEIGHT

	};

	struct messageNode {
		message msg;
		int messageWeight;
		messageNode* left;
		messageNode* right;

		messageNode(message msg, int messageWeight)
		{
			this->msg = msg;
			this->messageWeight = messageWeight;
			this->left = nullptr;
			this->right = nullptr;
		}
	};

	messageNode* queRoot;

	tree() {
		queRoot = nullptr;
		std::cout << "-----------------------------------\n" << "Initialising Binary Tree \n";
	}

	void sendMessage(message msg, int messageWeight) //CATCH MESSAGE, PASS TO MESSAGE QUE
	{
		messageNode* newMessageNode = new messageNode(msg, messageWeight);

		if (queRoot == nullptr)
		{
			queRoot = newMessageNode;

			setRoot(true);
		}

		else
		{
			messageNode* queFocus = queRoot;
			messageNode* parent;

			while (true) // loops through nodes until empty slot is found.
			{

				parent = queFocus;

				if (newMessageNode->messageWeight < queFocus->messageWeight) 
				{
					queFocus = queFocus->left;
					std::cout << "focus shifting left \n";
					if (queFocus == nullptr)
					{
						parent->left = newMessageNode;
						std::cout << "node made left\n";
						return;
					}
				}
				else
				{
					queFocus = queFocus->right;
					std::cout << "focus shifting right \n";
					if (queFocus == nullptr)
					{
						parent->right = newMessageNode;
						std::cout << "node made right\n";
						return;
					}
				}
			}

		}
	}

	message fetchPost()
	{

		messageNode* queFocus = queRoot;
		messageNode* prevQueFocus = queRoot;
		 
		while (true)
		{ 
			//program runs into null ptr when it should not, tries to read empty memory from nullptr->left, throws read access violation (of course) || NOTE FOR BUGFIXING
			//I believe the memory for focus is not being cleared correctly.
			//Possible fix, set pointer to (deleted focus) as nullptr (I hope) :)
			// It worked.
			//Im leaving this here as a memorial to the many hours spent fixing this bug...

			if (getRoot() == false)
			{
				std::cout << "root reached \n";

				return ROOT;
			}
			else
			{
				if (queFocus->left == nullptr)
				{

					if (queFocus->right == nullptr)
					{

						std::cout << "post grabbed\n";
						message msg = queFocus->msg;

						switch (getFlag())
						{

						case(true):
							prevQueFocus->right = nullptr;
							break;
						case(false):
							prevQueFocus->left = nullptr;
							break;
						}
						if (prevQueFocus == queRoot)
						{
							setRoot(false);
						}
						delete queFocus;
						std::cout << "focus cleared\n";
						return msg;
					}
					else
					{
						prevQueFocus = queFocus;
						queFocus = queFocus->right;
						setFlag(true);
						std::cout << "focus shifting right \n";
					}


				}
				else
				{

					prevQueFocus = queFocus;
					queFocus = queFocus->left;
					setFlag(false);
					std::cout << "focus shifting left \n";
				};
			}
			
			


		}

	}

	void sendMessage(message pass, tree instance)
	{
		switch (pass)
		{
		case(START):
			std::cout << " initializing RALPH \n";

			break;
		case(TEST):
			std::cout << " FIRST \n";

			break;
		case(ROOT):
			std::cout << "do something \n";


			break;
		case(MEMORY):
			std::cout << "Accesing memory";

			break;
		case(WRITESTRUCT):

			break;

		case(READSTRUCT):

			break;
		case(DECIDEPOS):

			break;
		case(CREATENODE):

			break;
		case(CREATENODEFULL):

			break;
		case(CREATEWEIGHT):

			break;
		case(DELETENODE):

			break;
		case(DELETEWEIGHT):

			break;
		case(PUSHOUTWEIGHTADRESS):

			break;
		case(PUSHINWEIGHTADRESS):

			break;
		case(HASHIN):

			break;
		case(HASHINOVERLOAD):

			break;
		case(TEMPHASHDATA):

			break;
		case(FINDNODE):

			break;
		case(FINDROOT):

			break;
		case(RELEVANCEREDUCTION):

			break;
		case(TRANSLATESTRUCTURE):

			break;
		case(READSTRUCTURE):

			break;
		case(WRITENODE):

			break;
		case(WRITEWEIGHT):

			break;
		case(WRITEDUPENODE):

			break;
		case(READNODE):

			break;
		case(READDUPENODE):

			break;
		case(READWEIGHT):

			break;
		default:
			break;
		}
	}
private:
	
	bool shiftFlag = false; //false = left, true = right

	bool getFlag()
	{
		return shiftFlag;
	}
	void setFlag(bool set)
	{
		shiftFlag = set;
	}



	bool rootFlag = false;

	bool getRoot()
	{
		return rootFlag;
	}
	void setRoot(bool set)
	{
		rootFlag = set;
	}

};


