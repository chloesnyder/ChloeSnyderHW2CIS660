#ifndef CreateLSystemCmd_H_
#define CreateLSystemCmd_H_

#include <maya/MPxCommand.h>
#include <string>
#include <maya/MSyntax.h>
#include <maya/MArgDatabase.h>

#define STARTX "-sx"
#define STARTY "-sy"
#define STARTZ "-sz"
#define STARTXLONG "-startx"
#define STARTYLONG "-starty"
#define STARTZLONG "-startz"
#define ENDX "-ex"
#define ENDY "-ey"
#define ENDZ "-ez"
#define ENDXLONG "-endx"
#define ENDYLONG "-endy"
#define ENDZLONG "-endz"

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
		syntax.addFlag(STARTX, STARTXLONG, MSyntax::kString);
		syntax.addFlag(STARTY, STARTYLONG, MSyntax::kString);
		syntax.addFlag(STARTZ, STARTZLONG, MSyntax::kString);
		syntax.addFlag(ENDX, ENDXLONG, MSyntax::kString);
		syntax.addFlag(ENDY, ENDYLONG, MSyntax::kString);
		syntax.addFlag(ENDZ, ENDZLONG, MSyntax::kString);
		syntax.addFlag(STEPSIZE, STEPSIZELONG, MSyntax::kDouble);
		syntax.addFlag(ANGLE, ANGLELONG, MSyntax::kDouble);
		syntax.addFlag(GRAMMAR, GRAMMARLONG, MSyntax::kString);
		syntax.addFlag(ITER, ITERLONG, MSyntax::kLong);
		return syntax;
	}


    LSystemCmd();
    virtual ~LSystemCmd();
    static void* creator() { return new LSystemCmd(); }
    MStatus doIt( const MArgList& args );
};

#endif