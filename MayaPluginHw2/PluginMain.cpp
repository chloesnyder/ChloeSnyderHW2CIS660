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

	char buffer[2048];
	//sprintf_s(buffer, 2048, "source \"%s/MyPluginDialog\";", plugin.loadPath());
	//sprintf_s(buffer, 2048, "..\"%s/MyPluginDialog\";", plugin.loadPath());
	MGlobal::executeCommand(buffer, true);

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


