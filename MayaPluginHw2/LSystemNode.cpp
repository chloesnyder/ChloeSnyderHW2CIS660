#include "LSystemNode.h"

//virtual MStatus compute(const MPlug& plug, MDataBlock& data);
MObject LSystemNode::time;
MTypeId LSystemNode::id(0x80000);
MObject LSystemNode::defaultAngle;
MObject LSystemNode::defaultStepSize;
MObject LSystemNode::grammarFile;
MObject LSystemNode::outputGeometry;
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

	LSystemNode::defaultAngle = numAttr.MFnNumericAttribute::create("angle",
		"a",
		MFnNumericData::kFloat,
		0.0,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating LSystemNode angle attribute\n");

	LSystemNode::defaultStepSize = numAttr.MFnNumericAttribute::create("step",
		"ss",
		MFnNumericData::kFloat,
		0.0,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating LSystemNode step attribute\n");

	LSystemNode::grammarFile = typedAttr.MFnTypedAttribute::create("grammar",
		"g",
		MFnData::kString,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating LSystemNode grammar attribute\n");

	LSystemNode::outputGeometry = typedAttr.create("outputGeometry", "out",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating LSystemNode output attribute\n");

	typedAttr.setStorable(false);
	//numAttr.setStorable(true); // do I need this?

	returnStatus = addAttribute(LSystemNode::time);
	McheckErr(returnStatus, "ERROR adding time attribute\n");
	returnStatus = addAttribute(LSystemNode::defaultAngle);
	McheckErr(returnStatus, "ERROR adding angle attribute\n");
	returnStatus = addAttribute(LSystemNode::defaultStepSize);
	McheckErr(returnStatus, "ERROR adding step attribute\n");
	returnStatus = addAttribute(LSystemNode::grammarFile);
	McheckErr(returnStatus, "ERROR adding grammar attribute\n");
	returnStatus = addAttribute(LSystemNode::outputGeometry);
	McheckErr(returnStatus, "ERROR adding output attribute\n");

	returnStatus = attributeAffects(LSystemNode::grammarFile, LSystemNode::outputGeometry); // do I need this?
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	returnStatus = attributeAffects(LSystemNode::defaultAngle, LSystemNode::outputGeometry); // do I need this?
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	returnStatus = attributeAffects(LSystemNode::defaultStepSize, LSystemNode::outputGeometry); // do I need this?
	McheckErr(returnStatus, "ERROR in attributeAffects\n");
	returnStatus = attributeAffects(LSystemNode::time, LSystemNode::outputGeometry); // do I need this?
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
	if (plug == outputGeometry)
	{
		// get time
		MDataHandle timeData = data.inputValue(time, &returnStatus);
		McheckErr(returnStatus, "Error getting time data handle\n");
		MTime time = timeData.asTime();

		// get angle
		MDataHandle angleData = data.inputValue(defaultAngle, &returnStatus);
		McheckErr(returnStatus, "Error getting angle data handle\n");
		float angle = angleData.asFloat();

		// get angle
		MDataHandle stepData = data.inputValue(defaultStepSize, &returnStatus);
		McheckErr(returnStatus, "Error getting step data handle\n");
		float step = stepData.asFloat();

		// get grammar
		MDataHandle grammarData = data.inputValue(grammarFile, &returnStatus);
		McheckErr(returnStatus, "Error getting gramnar data handle\n");
		MString gram = grammarData.asString();

		
		// get output object
		MDataHandle outputHandle = data.outputValue(outputGeometry, &returnStatus);
		McheckErr(returnStatus, "ERROR getting geometry data handle\n");

		MFnMeshData dataCreator;
		MObject newOutputData = dataCreator.create(&returnStatus);
		McheckErr(returnStatus, "ERROR creating outputData");

	}
}

MObject LSystemNode::createMesh(const MTime& time, MObject& outData, MStatus& stat)
{
	MFnMesh meshFS;
	MPoint start = MPoint();
	MPoint end = MPoint(0, 1, 0);
	CylinderMesh cm = CylinderMesh(start, end);

	MPointArray points;
	MIntArray faceCounts;
	MIntArray faceConnects;

	 cm.getMesh(points, faceCounts, faceConnects);

	 int numVertices = points.length();
	 int numFaces = faceCounts.length();


	MObject newMesh = meshFS.create(numVertices, numFaces,
		points, faceCounts, faceConnects,
		outData, &stat);

	return newMesh;
}

