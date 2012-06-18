#include "LevelSet.h"
#include "ReadImage.h"
#include "WriteImage.h"
#include "Segmentation.h"

using namespace std;

LevelSet::LevelSet()
{
	//Initialize to default
	m_iterations = 0;
	m_propagation = 0;
	m_curvature = 0;
	m_advection = 0;
}

LevelSet::~LevelSet()
{

}

void LevelSet::PrintCommandListing()
{
	cout << "LevelSet Tool 1.0 (Jun 2012) - Command Listing" << endl;
	cout << "-------------------------------" << endl;
	cout << "usage LevelSet speed.img initial.img <options>" << endl;
	cout << " " << endl;
	cout << "speed.img - The speed image inside of the object you want to segment should be negative (between -1 and 0) and the outside of the object should be positive (0 to +1)" << endl;
	cout << "initial.img - The initialization image should be -1 inside the object that seeds the segmentation and +1 outside the seed object" << endl;
	cout << "-levelset n_iter - Perform level set segmentation for n_iter iterations" << endl;
	cout << "-levelset-advection value - Set the advection parameter of the snake to given value" << endl;
	cout << "-levelset-curvature value - Set the curvature parameter of the snake to given value" << endl;
	cout << "-levelset-propagation value - Set the propagation parameter of the snake to given value" << endl;
	cout << "-o | --output - Write the output image" << endl;
	cout << "-h | --help - Display this command listing" << endl;
}

int LevelSet::ProcessCommand(char *argv[])
{
	//Get command
	string cmd = argv[0];

	//Commands in alphabetical order
	if(cmd == "-h" || cmd == "--help")	//Print the command listing
	{
		PrintCommandListing();
		return 0;
	}
	else if(cmd == "-levelset")
	{
		int nb_iter = atoi(argv[1]);
		Segmentation segment(this);
		segment(nb_iter);
		return 1;
	}
	else if(cmd == "-levelset-advection")
	{
		m_advection = atof(argv[1]);
		return 1;
	}
	else if(cmd == "-levelset-curvature")
	{
		m_curvature = atof(argv[1]);
		return 1;
	}
	else if(cmd == "-levelset-propagation")
	{
		m_propagation = atof(argv[1]);
		return 1;
	}
	else if(cmd == "-o" || "--output")
	{
		WriteImage write(this);
		write(argv[1]);
		return 1;
	}
	else
	{
		cout << "Error, command " << cmd << "is unknown. Please type -h or --help to see the command listing." << endl;	//Unknown command
		return 0;
	}
}

int LevelSet::ProcessCommandLine(int argc, char *argv[])
{
	//Check the number of arguments
	if(argc == 1)
	{
		cout << "LevelSet tool" << endl;
		cout << "For usage examples and help, call --help or -h" << endl;
		return 0;
	}

	//Process command line
	for(int i = 1; i < argc; i++)
	{
		string cmd = argv[i];
		if(cmd[0] == '-')
		{
			//A command has been supplied
			i = i + ProcessCommand(argv+i);
		}
		else
		{
			//An image file name has been provided. If this image is followed by commands
			//read it and push in the pipeline.
			if(i != argc-1)
			{
				ReadImage read(this);
				read(argv[i]);
			}
			else
			{
				WriteImage write(this);
				write(argv[i]);
			}
		}
	}
	return 0;
}
