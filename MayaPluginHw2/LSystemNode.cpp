#define MNoVersionString
#define MNoPluginEntry

#include "LSystemNode.h"
#include "cylinder.h"
#include "LSystem.h"

#include <maya/MFnPlugin.h>
#include <maya/MTime.h>
#include <maya/MFnMesh.h>
#include <maya/MPoint.h>
#include <maya/MFloatPoint.h>
#include <maya/MFloatPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MDoubleArray.h>

#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>

#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MFnMeshData.h>
#include <maya/MIOStream.h>


//virtual MStatus compute(const MPlug& plug, MDataBlock& data);
MObject LSystemNode::time;
MTypeId LSystemNode::id(0x0);
MObject LSystemNode::angle;
MObject LSystemNode::step_size;
MObject LSystemNode::grammarFile;
MObject LSystemNode::outputMesh;
MString LSystemNode::path;

void* LSystemNode::creator()
{
	return new LSystemNode;
}


// Create and add an input MFnNumericAttribute for default angle
// Create and add an input MFnNumericAttribute for default step size
// Create and add an input MFnTypedAttribute for grammar file
// Create and addd an input MFnUnitAttribute for the input time
// Create and add an MfnTypedAttribute for output geometry
MStatus LSystemNode::initialize()
{


	MFnUnitAttribute unitAttr;
	MFnTypedAttribute typedAttr;
	MFnNumericAttribute numAttr;

	MStatus returnStatus;

	LSystemNode::time = unitAttr.create("time", "tm",
		MFnUnitAttribute::kTime,
		0.0, &returnStatus);
	McheckErr(returnStatus, "ERROR creating LSystemNode time attribute\n");
	CHECK_MSTATUS(unitAttr.setKeyable(true));
	CHECK_MSTATUS(unitAttr.setStorable(true));
	CHECK_MSTATUS(unitAttr.setReadable(true));
	CHECK_MSTATUS(unitAttr.setWritable(true));

	LSystemNode::angle = numAttr.MFnNumericAttribute::create("angle",
		"a",
		MFnNumericData::kDouble,
		0.0,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating LSystemNode angle attribute\n");
	CHECK_MSTATUS(numAttr.setKeyable(true));
	CHECK_MSTATUS(numAttr.setStorable(true));
	CHECK_MSTATUS(numAttr.setReadable(true));
	CHECK_MSTATUS(numAttr.setWritable(true));

	LSystemNode::step_size = numAttr.MFnNumericAttribute::create("step",
		"ss",
		MFnNumericData::kDouble,
		0.0,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating LSystemNode step attribute\n");
	CHECK_MSTATUS(numAttr.setKeyable(true));
	CHECK_MSTATUS(numAttr.setStorable(true));
	CHECK_MSTATUS(numAttr.setReadable(true));
	CHECK_MSTATUS(numAttr.setWritable(true));


	LSystemNode::grammarFile = typedAttr.MFnTypedAttribute::create("grammar",
		"g",
		MFnData::kString,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating LSystemNode grammar attribute\n");
	CHECK_MSTATUS(typedAttr.setKeyable(true));
	CHECK_MSTATUS(typedAttr.setStorable(true));
	CHECK_MSTATUS(typedAttr.setReadable(true));
	CHECK_MSTATUS(typedAttr.setWritable(true));

	LSystemNode::outputMesh = typedAttr.create("outputMesh", "out",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating LSystemNode output attribute\n");
	CHECK_MSTATUS(typedAttr.setKeyable(false));
	CHECK_MSTATUS(typedAttr.setStorable(false));
	CHECK_MSTATUS(typedAttr.setReadable(true));
	CHECK_MSTATUS(typedAttr.setWritable(false));


	returnStatus = addAttribute(LSystemNode::time);
	McheckErr(returnStatus, "ERROR adding time attribute\n");
	returnStatus = addAttribute(LSystemNode::angle);
	McheckErr(returnStatus, "ERROR adding angle attribute\n");
	returnStatus = addAttribute(LSystemNode::step_size);
	McheckErr(returnStatus, "ERROR adding step attribute\n");
	returnStatus = addAttribute(LSystemNode::grammarFile);
	McheckErr(returnStatus, "ERROR adding grammar attribute\n");
	returnStatus = addAttribute(LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR adding output attribute\n");

	returnStatus = attributeAffects(LSystemNode::grammarFile, LSystemNode::outputMesh); 
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	returnStatus = attributeAffects(LSystemNode::angle, LSystemNode::outputMesh); 
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	returnStatus = attributeAffects(LSystemNode::step_size, LSystemNode::outputMesh); 
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	returnStatus = attributeAffects(LSystemNode::time, LSystemNode::outputMesh); 
	McheckErr(returnStatus, "ERROR in attributeAffects\n");

	return MS::kSuccess;

}

// This function should i) get called whenever an attribute, such as time, changes,
// and ii) then recompute the output mesh. We have included a utility class for creating 
// cylinders which you may use to help create the mesh geometry.
// Don’t forget to connect all the input attributes to the geometry! Test that changing every attribute from the attribute panel works correctly!

MStatus LSystemNode::compute(const MPlug& plug, MDataBlock& data)
{
	MStatus returnStatus;
	if (plug == outputMesh)
	{
		// get time
		MDataHandle timeData = data.inputValue(time, &returnStatus);
		McheckErr(returnStatus, "Error getting time data handle\n");
		MTime timeVal = timeData.asTime();

		// get angle
		MDataHandle angleData = data.inputValue(angle, &returnStatus);
		McheckErr(returnStatus, "Error getting angle data handle\n");
		double angleVal = angleData.asDouble();

		// get step size
		MDataHandle stepData = data.inputValue(step_size, &returnStatus);
		McheckErr(returnStatus, "Error getting step data handle\n");
		double stepVal = stepData.asDouble();

		// get grammar
		MDataHandle grammarData = data.inputValue(grammarFile, &returnStatus);
		McheckErr(returnStatus, "Error getting gramnar data handle\n");
		MString gramVal = grammarData.asString();

		// get output object
		MDataHandle outputHandle = data.outputValue(outputMesh, &returnStatus);
		McheckErr(returnStatus, "ERROR getting geometry data handle\n");

		MFnMeshData dataCreator;
		MObject newOutputData = dataCreator.create(&returnStatus);
		McheckErr(returnStatus, "ERROR creating outputData");

		createMesh(timeVal, angleVal, stepVal, gramVal, newOutputData, returnStatus);
		McheckErr(returnStatus, "ERROR creating mesh");

		outputHandle.set(newOutputData);
		data.setClean(plug);

	}
	else {
		return MS::kUnknownParameter;
	}
}

MObject LSystemNode::createMesh(const MTime& time, const float& angle, const float &step, const MString& grammar, MObject& outData, MStatus& stat)
{
	MFnMesh meshFS;
	MPointArray points;
	MIntArray faceCounts;
	MIntArray faceConnects;
	MPoint start;
	MPoint end;


	int t = (int)time.as(MTime::kFilm);
	MObject plugObj = MFnPlugin::findPlugin("LSystem");
	MFnPlugin plugin(plugObj);
	MString grammarFilePath = plugin.loadPath() + "/" + grammar;

	LSystem lsystem;
	// load grammar file that user selects, set default angle and step size
	lsystem.loadProgram(grammarFilePath.asChar());
	lsystem.setDefaultAngle(angle);
	lsystem.setDefaultStep(step);
	// vector to store all branches processed at each iteration of lsystem
	std::vector<LSystem::Branch> b;

	for (int i = 0; i < t; i++)
	{
		std::string currIter = lsystem.getIteration(i);
		lsystem.process(i, b);
	}

	// Create mesh after final iteration
	for (int i = 0; i < b.size(); i++)
	{
		vec3 s = b.at(i).first;
		vec3 e = b.at(i).second;
		start = MPoint(s[0], s[1], s[2]);
		end = MPoint(e[0], e[1], e[2]);
		CylinderMesh cm = CylinderMesh(start, end);
		cm.appendToMesh(points, faceCounts, faceConnects);
	}

	int numVertices = points.length();
	int numFaces = faceCounts.length();


	MObject newMesh = meshFS.create(numVertices, numFaces,
		points, faceCounts, faceConnects,
		outData, &stat);

	return newMesh;
}

