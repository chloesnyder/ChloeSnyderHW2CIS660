#pragma once
#include <maya/MPxNode.h>



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
	static MObject angle;
	static MObject step_size;
	static MObject grammarFile;
	static MObject outputMesh;

	
protected:
	MObject createMesh(const MTime& time, const float& angle, const float &step, const MString& grammar, MObject& outData, MStatus& stat);


};


