#pragma once
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
#include "LSystemNode.h"


MStatus initializePlugin(MObject obj)
{
	MStatus   status = MStatus::kSuccess;
	MFnPlugin plugin(obj, "MyPlugin", "1.0", "Any");

	// Register Command
	status = plugin.registerCommand("LSystemCmd", LSystemCmd::creator, LSystemCmd::newSyntax);
	if (!status) {
		status.perror("registerCommand LSystemCmd");
		return status;
	}

	plugin.setName("LSystem");

	status = plugin.registerNode("LSystemNode", LSystemNode::id, LSystemNode::creator, LSystemNode::initialize);
	if (!status) {
		CHECK_MSTATUS_AND_RETURN_IT(status);
	}

	char buffer[2048];
	MString s = plugin.loadPath();
	LSystemNode::path = plugin.loadPath();
	sprintf_s(buffer, 2048, "source \"%s/LSystemCmd.mel\";", s.asChar());
	MGlobal::executeCommand(buffer, true);

	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus   status = MStatus::kSuccess;
	MFnPlugin plugin(obj);

	status = plugin.deregisterCommand("LSystemCmd");
	if (!status) {
		status.perror("deregisterCommand LSystemCmd");
		return status;
	}

	status = plugin.deregisterNode(LSystemNode::id);
	if (!status) {
		CHECK_MSTATUS_AND_RETURN_IT(status);
	}

	return status;
}