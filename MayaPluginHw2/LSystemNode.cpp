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

	return MS::kSuccess;

}