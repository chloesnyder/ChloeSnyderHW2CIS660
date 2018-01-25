#include "LSystemCmd.h"


#include <maya/MGlobal.h>
#include <list>
LSystemCmd::LSystemCmd() : MPxCommand()
{
}

LSystemCmd::~LSystemCmd() 
{
}

MStatus LSystemCmd::doIt( const MArgList& args )
{

	double branchStartX;
	// message in Maya output window
    cout<<"Implement Me!"<<endl;
	std::cout.flush();

	MStatus status;

	MArgDatabase parser(syntax(), args, &status);
	if (status != MS::kSuccess)
	{
		return status;
	}

	if (parser.isFlagSet(STARTX))
	{
		parser.getFlagArgument(STARTX, 0, branchStartX);
	}

	// message in scriptor editor
	MGlobal::displayInfo("Implement Me!");

    return MStatus::kSuccess;
}

