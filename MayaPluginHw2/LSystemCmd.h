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

class LSystemCmd : public MPxCommand
{
public:

	static MSyntax newSyntax() {
		MSyntax syntax;
		syntax.addFlag(STARTX, STARTXLONG, MSyntax::kDouble);
		syntax.addFlag(STARTY, STARTYLONG, MSyntax::kDouble);
		syntax.addFlag(STARTZ, STARTZLONG, MSyntax::kDouble);
		syntax.addFlag(ENDX, ENDXLONG, MSyntax::kDouble);
		syntax.addFlag(ENDY, ENDYLONG, MSyntax::kDouble);
		syntax.addFlag(ENDZ, ENDZLONG, MSyntax::kDouble);
		return syntax;
	}


    LSystemCmd();
    virtual ~LSystemCmd();
    static void* creator() { return new LSystemCmd(); }
    MStatus doIt( const MArgList& args );
};

#endif