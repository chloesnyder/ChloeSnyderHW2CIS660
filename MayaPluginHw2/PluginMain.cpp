#include <maya/MPxCommand.h>
#include <maya/MFnPlugin.h>
#include <maya/MIOStream.h>
#include <maya/MString.h>
#include <maya/MArgList.h>
#include <maya/MGlobal.h>
#include <maya/MSimple.h>
#include <maya/MDoubleArray.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MDGModifier.h>
#include <maya/MPlugArray.h>
#include <maya/MVector.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MStringArray.h>
#include <maya/MSyntax.h>
#include <list>

#include "LSystemCmd.h"

/*#define STARTX "-sx"
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
#define ENDZLONG "-endz"*/

/*static MSyntax newSyntax() {
	MSyntax syntax;
	syntax.addFlag(STARTX, STARTXLONG, MSyntax::kDouble);
	syntax.addFlag(STARTY, STARTYLONG, MSyntax::kDouble);
	syntax.addFlag(STARTZ, STARTZLONG, MSyntax::kDouble);
	syntax.addFlag(ENDX, ENDXLONG, MSyntax::kDouble);
	syntax.addFlag(ENDY, ENDYLONG, MSyntax::kDouble);
	syntax.addFlag(ENDZ, ENDZLONG, MSyntax::kDouble);
	return syntax;
}*/

MStatus initializePlugin( MObject obj )
{
    MStatus   status = MStatus::kSuccess;
    MFnPlugin plugin( obj, "MyPlugin", "1.0", "Any");

    // Register Command
    status = plugin.registerCommand( "LSystemCmd", LSystemCmd::creator, LSystemCmd::newSyntax );
    if (!status) {
        status.perror("registerCommand");
        return status;
    }

    return status;
}

MStatus uninitializePlugin( MObject obj)
{
    MStatus   status = MStatus::kSuccess;
    MFnPlugin plugin( obj );

    status = plugin.deregisterCommand( "LSystemCmd" );
    if (!status) {
	    status.perror("deregisterCommand");
	    return status;
    }

    return status;
}


