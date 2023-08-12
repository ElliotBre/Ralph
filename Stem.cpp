#include "connectionMain.h"
#include "Library.h"

//NOTE: to link program files each file can consist of a class, each class can be called by its various functions through object creation (when START message is fetched) each class is capable of sending messages into main loop through their own messaging procedures
//These messages can then be handled through the main loop, when a message is passed it will call its relevant function /  functions from its source file to execute the required procedure.

//Basic messages for all classes :
/*
   PULL MESSAGE (PULLS first priority message from a given source files que, sends it into mainMessage loop to be executed) (This should be done for every file (in priority order) at the end of a message FDE cycle)
	   relevant function:
						 queMessage(MSG) internal messaging procedure for source file, ques parameter message into relavent que, ready to be fetched by the main messaging cycle.

   INITIALIZEOBJ (Initialises object for all source file instances, pulling them into scope within the main file procedures.

   */
int main()
{

	tree mainLoop;

	mainLoop.sendMessage(mainLoop.START, 10);
	mainLoop.sendMessage(mainLoop.TEST, 4);
	mainLoop.sendMessage(mainLoop.START, 3);
	mainLoop.sendMessage(mainLoop.TEST, 6);

	std::cout << "Binary Tree Populated\n" << "-----------------------------------\n";

	while (true) //LOOP
	{

		bool flag = false;
		int num{};
		mainLoop.sendMessage(mainLoop.fetchPost()); //CHECK MESSAGE QUE PRIORITY, TAKE PRIORITY MESSAGE

		while (flag == false) // loop implemented to pause system at runtime as to see console outputs of main message loop.
		{
			while (std::cout << "|please enter 1 to continue|\n" && !(std::cin >> num))
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << " |Incorrect data input| \n";
			}
			if (num == 1)
			{
				flag = true;
			}
		}


		/*

		LOOP

	CATCH MESSAGE _/

	PASS TO MESSAGE QUE _/

	CHECK MESSAGE QUE PRIORITY _/

	TAKE PRIORITY MESSAGE _/

	DO FUNC FROM MESSAGE _/

	RECIEVE MESSAGE FROM FUNC

	RECIEVE MESSAGE FROM PARIETAL

	DO BACKGROUND FUNC FROM SECOND MESSAGE SET (IF IN HIBERNATION, OR A SET AMOUNT OF TIME HAS PASSED)

	SET MESSAGE PRIORITIES (IF REACTORY FUNCTIONS RETURN THAT A FUNCTION NEEDS COMPLETING IMMEDIATELY)

		LOOP

		*/

		//POSSIBLE TO HAVE MULTIPLE PRIORITY QUES CALLED IN PRIORITY ORDER, MIMICKING BACKGROUND FUNCTIONS OF BRAIN
		//POSSIBLE MESSAGE LOOP FOR EACH SECTION OF THE BRAIN IF REQUIRED, may be out of limitations however.
	}
















	return 0;
}

//need to set enum message before passing into function


//In not to creating ralph I have defined a set structure in which each part of Ralphs brain will form. In which each part will originate from a root node, as seen in the temporal lobe program, data processed by each respective part of the brain will store data in its respective root sector; howeveer, these sectors will not be independant, but instead will be connected through relations in the data processed (aka each sector will be connected by weight) these weights will act as direct connections in how ralphs brain communicates, for instance connecting the logical solution of what and a previously processed solution of kangaroo to the kangaroo data node, which will be connected to the data cluster of the data of a processed image of a kangaroo. 
// an example of how  this may be used within programmative thinking within ralph is here: ralph takes in data via a question, "what is a kangaroo", he checks his processing centre to see if the answer or data regarding this answer is stored within its respective cluster, pulling nodes related to this and displaying the data in the desired language and format, he simultaneously looks for this data within other clusters, if one is found in a cluster it checks to see if a connection exists to a different cluster , if it does it follows it and pulls its respective data. If it is found that related data is not connected to each cluster then new connections will be formed, this may be as abstract as connecting the picture of a kangaroo to the data point within long term memory of the sahara or sarengheti in response to a positive response or "dopamine" being released on the correct answer of "what is a sarengheti animal" and kangaroo being the response
//this will give ralph the ability to cross referance between different sections and pieces of his brain to form ideas, connections and referances to different matters as to answer matters more efficiently, as we are all learning machines after all.

// process diagram

//data input --> processing centre / find answer / try answer / store solution if correct --> if not pull data from seperate cluster and try and format answer from current data, according to the data provided / if simallar answer exists to current question, format in a simalar way --> check how output is reecieved, if good add respective connections, store solution in processing cluster (next to / in relation to similar answer if used) / connect data points in different cluster e.g what is a kangaroo to kangaroo imagery cluster, kangaroo long term memory data point, sahara data point etc
