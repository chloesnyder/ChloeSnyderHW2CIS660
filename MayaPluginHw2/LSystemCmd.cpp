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

	MString branchStartX;
	MString branchStartY;
	MString branchStartZ;
	MString branchEndX;
	MString branchEndY;
	MString branchEndZ;

	double stepSize;
	double angle;
	MString grammar;
	int numIter;


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
	if (parser.isFlagSet(STARTY))
	{
		parser.getFlagArgument(STARTY, 0, branchStartY);
	}
	if (parser.isFlagSet(STARTZ))
	{
		parser.getFlagArgument(STARTZ, 0, branchStartZ);
	}
	if (parser.isFlagSet(ENDX))
	{
		parser.getFlagArgument(ENDX, 0, branchEndX);
	}
	if (parser.isFlagSet(ENDY))
	{
		parser.getFlagArgument(ENDY, 0, branchEndY);
	}
	if (parser.isFlagSet(ENDZ))
	{
		parser.getFlagArgument(ENDZ, 0, branchEndZ);
	}

	MString command = "circle - centerX 0 - centerY 0 - centerZ 0 - name nurbsCircle1 - radius 2; \ncurve -d 1 -p " + branchStartX + " " + branchStartY + " " + branchStartZ + " - p "
		+ branchEndX + " " + branchEndY + " " + branchEndZ + " -k 0 - k 1 - name curve1;" 
		+ "\nselect - r nurbsCircle1 curve1 ;" 
		+ "\nextrude - ch true - rn false - po 1 - et 2 - ucp 1 - fpt 1 - upn 1 - rotation 0 - scale 1 - rsp 1 \"nurbsCircle1\" \"curve1\";";

	status = MGlobal::executeCommand(command);
	MGlobal::displayInfo("LSystemCmd\n");
	setResult("LSystemCmd was executed\n");

	return status;
}

