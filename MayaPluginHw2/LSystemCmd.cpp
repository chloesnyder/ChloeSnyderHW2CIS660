#pragma once
#include "LSystemCmd.h"


LSystemCmd::LSystemCmd() : MPxCommand()
{
}

LSystemCmd::~LSystemCmd()
{
}

MStatus LSystemCmd::createLSystem(double angle, double step, double iter, MString grammar)
{
	LSystem lsystem;
	lsystem.loadProgramFromString(grammar.asChar());
	lsystem.setDefaultAngle(angle);
	lsystem.setDefaultStep(step);
	std::vector<LSystem::Branch> b;

	for (int i = 0; i < iter; i++)
	{
		std::string currIter = lsystem.getIteration(i);
		lsystem.process(i, b);
	}

	for (int i = 0; i < b.size(); i++)
	{
		vec3 start = b.at(i).first;
		vec3 end = b.at(i).second;

		std::string c;
		std::stringstream stringStream;
		stringStream << "$myCurve = `curve -d 1 -p " << start[0] << " " << start[2] << " " << start[1] << " -p " << end[0] << " " << end[2] << " " << end[1] << "-k 0 -k 1`";
		c = stringStream.str();

		MString command1 = "global string $myCurve";
		MString command2 = c.c_str();
		MString command3 = "circle -r 0.2 -name nurbsCircle1";
		MString command4 = "select -r nurbsCircle1 curve1";
		MString command5 = "extrude -ch true -rn false -po 1 -et 2 -ucp 1 -fpt 1 -upn 1 -rotation 0 -scale 1 -rsp 1 nurbsCircle1 $myCurve";

		MGlobal::executeCommand(command1);
		MGlobal::executeCommand(command2);
		MGlobal::executeCommand(command3);
		MGlobal::executeCommand(command4);
		MGlobal::executeCommand(command5);
	}

	return MS::kSuccess;
}

MStatus LSystemCmd::doIt(const MArgList& args)
{

	double stepSize = 0;
	double angle = 0;
	MString grammar = "";
	int numIter = 0;


	MStatus status;

	MArgDatabase parser(syntax(), args, &status);
	if (status != MS::kSuccess)
	{
		return status;
	}

	if (parser.isFlagSet(ANGLE))
	{
		parser.getFlagArgument(ANGLE, 0, angle);
	}
	if (parser.isFlagSet(STEPSIZE))
	{
		parser.getFlagArgument(STEPSIZE, 0, stepSize);
	}
	if (parser.isFlagSet(GRAMMAR))
	{
		parser.getFlagArgument(GRAMMAR, 0, grammar);
	}
	if (parser.isFlagSet(ITER))
	{
		parser.getFlagArgument(ITER, 0, numIter);
	}

	status = createLSystem(angle, stepSize, numIter, grammar);

	MGlobal::displayInfo("LSystemCmd\n");
	setResult("LSystemCmd was executed\n");

	return status;
}
