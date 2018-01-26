#pragma once
#include <maya/MPxNode.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnMeshData.h>
#include <maya/MFnMesh.h>
#include <maya/MTime.h>
#include "cylinder.h"


#define McheckErr(stat,msg)             \
        if ( MS::kSuccess != stat ) {   \
                cerr << msg;            \
                return MS::kFailure;    \
        }

class LSystemNode :
	public MPxNode
{
public:
	LSystemNode() {};
	virtual ~LSystemNode() {};
	virtual MStatus compute(const MPlug& plug, MDataBlock& data);
	static void* creator();
	static MStatus initialize();

	static MTypeId id;
	static MObject time;
	static MObject defaultAngle;
	static MObject defaultStepSize;
	static MObject grammarFile;
	static MObject outputGeometry;

	static MString path;

protected:
	MObject createMesh(const MTime& time, MObject& outData, MStatus& stat);


};


