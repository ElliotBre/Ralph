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
		
		
		mainLoop.sendMessage(mainLoop.fetchPost()); //CHECK MESSAGE QUE PRIORITY, TAKE PRIORITY MESSAGE
		
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
