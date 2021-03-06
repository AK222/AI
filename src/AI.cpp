#include "ALU/utils/debugfuncs.h"
#include "ALU/utils/tests.h"
#include "AIU/Verbal Response Unit/SentimentAnalysis/SA.h"

void RunTests()
{
	std::cout << "tokenizeSentenceTEST()\n";
	Test::tokenizeSentenceTEST();
	std::cout << "getWordInfoTEST()\n";
	Test::getWordInfoTEST();
	std::cout << "createWIPTEST()\n";
	Test::createWIPTEST();
	std::cout << "WIPtoANDfromStrvectorTEST()\n";
	Test::WIPtoANDfromStrvectorTEST();
	std::cout << "getWordWIPTEST()\n";
	Test::getWordWIPTEST();
	// The above tests take around 10 secs
}

int main()
{
	std::cout << "Starting Bootup . . . \n";
	Dictionary::BOOTUP();
	std::cout << "Bootup complete!\n";

	/////////////////////////////////////////////

	//RunTests();
	std::cout << "Passage: Not the best shogi board, but does its job for its price. The pieces are attached to plastic frame, and you would have to take each piece apart from the frame. I didn't have any tools, so I just used my hands to snap it off and smooth each piece using sandpaper.\nThe pieces are magnetic, but not too strong so you can move pieces on the board by either pushing it or picking it up, just like how you would with regular wooden shogi board and pieces.\nThe letters printed are a little faded...not sure if this is by design or just cheap ink quality.But I don't think it has faded after the use, it was like that already when I opened the package. Still legible after a month of use.\nVery nice traveling size.I play it with my father and for some reason he loves shaking the pieces to feel the magnets inside..." << std::endl;
	
	std::string sa = performSentimentAnalysis("Not the best shogi board, but does its job for its price. The pieces are attached to plastic frame, and you would have to take each piece apart from the frame. I didn't have any tools, so I just used my hands to snap it off and smooth each piece using sandpaper. The pieces are magnetic, but not too strong so you can move pieces on the board by either pushing it or picking it up, just like how you would with regular wooden shogi board and pieces.The letters printed are a little faded...not sure if this is by design or just cheap ink quality.But I don't think it has faded after the use, it was like that already when I opened the package. Still legible after a month of use. Very nice traveling size.I play it with my father and for some reason he loves shaking the pieces to feel the magnets inside...");
	//^---- ERROR READING CHARACTERS OF STRING!
	std::cout << "Sentiment Analysis returned:" << std::endl;
	std::cout << sa << std::endl;

	/////////////////////////////////////////////

	WaitforEnter
}