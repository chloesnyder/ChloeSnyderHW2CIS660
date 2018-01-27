#pragma once
#ifndef CreateLSystemCmd_H_
#define CreateLSystemCmd_H_

#include <maya/MPxCommand.h>
#include <string>
#include <maya/MSyntax.h>
#include <maya/MArgDatabase.h>
#include <maya/MGlobal.h>
#include <list>
#include <sstream>
#include "LSystem.h";

#define STEPSIZE "-ss"
#define STEPSIZELONG "-step"
#define ANGLE "-a"
#define ANGLELONG "-angle"
#define GRAMMAR "-g"
#define GRAMMARLONG "-grammar"
#define ITER "-i"
#define ITERLONG "-iter"

class LSystemCmd : public MPxCommand
{
public:

	static MSyntax newSyntax() {
		MSyntax syntax;
		syntax.addFlag(STEPSIZE, STEPSIZELONG, MSyntax::kDouble);
		syntax.addFlag(ANGLE, ANGLELONG, MSyntax::kDouble);
		syntax.addFlag(GRAMMAR, GRAMMARLONG, MSyntax::kString);
		syntax.addFlag(ITER, ITERLONG, MSyntax::kLong);
		return syntax;
	}


	LSystemCmd();
	virtual ~LSystemCmd();
	static void* creator() { return new LSystemCmd(); }
	MStatus doIt(const MArgList& args);
	MStatus createLSystem(double angle, double stepSize, double iter, MString grammar);
};


#endif