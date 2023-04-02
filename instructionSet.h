#pragma once
#include "Library.h"


//Binary tree for 

class tree 
{
public:

	enum message
	{
		START, //ON START INITIALISE ALL TREES FOR QUES RELATIVE TO EACH STEM
		ROOT,
		TEST,



		MEMORY,

	};

	struct node {
		message msg;
		int weight;
		node* left;
		node* right;

		node(message msg, int weight)
		{
			this->msg = msg;
			this->weight = weight;
			this->left = nullptr;
			this->right = nullptr;
		}
	};

	node* root;

	tree() {
		root = nullptr;
		std::cout << "-----------------------------------\n" << "Initialising Binary Tree \n";
	}

	void sendMessage(message msg, int weight) //CATCH MESSAGE, PASS TO MESSAGE QUE
	{
		node* newNode = new node(msg, weight);

		if (root == nullptr)
		{
			root = newNode;

			setRoot(true);
		}

		else
		{
			node* focus = root;
			node* parent;

			while (true) // loops through nodes until empty slot is found.
			{

				parent = focus;

				if (newNode->weight < focus->weight) 
				{
					focus = focus->left;
					std::cout << "focus shifting left \n";
					if (focus == nullptr)
					{
						parent->left = newNode;
						std::cout << "node made left\n";
						return;
					}
				}
				else
				{
					focus = focus->right;
					std::cout << "focus shifting right \n";
					if (focus == nullptr)
					{
						parent->right = newNode;
						std::cout << "node made right\n";
						return;
					}
				}
			}

		}
	}

	message fetchPost()
	{

		node* focus = root;
		node* prevFocus = root;
		 
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
				if (focus->left == nullptr)
				{

					if (focus->right == nullptr)
					{

						std::cout << "post grabbed\n";
						message msg = focus->msg;

						switch (getFlag())
						{

						case(true):
							prevFocus->right = nullptr;
							break;
						case(false):
							prevFocus->left = nullptr;
							break;
						}
						if (prevFocus == root)
						{
							setRoot(false);
						}
						delete focus;
						std::cout << "focus cleared\n";
						return msg;
					}
					else
					{
						prevFocus = focus;
						focus = focus->right;
						setFlag(true);
						std::cout << "focus shifting right \n";
					}


				}
				else
				{

					prevFocus = focus;
					focus = focus->left;
					setFlag(false);
					std::cout << "focus shifting left \n";
				};
			}
			
			


		}

	}

	void sendMessage(message pass)
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


