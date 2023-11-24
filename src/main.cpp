#include <iostream>
#include "debug_gui/table.h"

#include <tinyxml2.h>

using namespace tinyxml2;

using namespace std;


int main(int argc, char* argv[])
{
    DBGui * test = new DBGui();
	
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile("SavedData.xml");

	//delete test;

	wxEntry(argc, argv);

	return 0;

}