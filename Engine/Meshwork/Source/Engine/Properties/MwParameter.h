#pragma once

#include "..\..\MwGlobals.h"

#include "MwParameterType.h"

#include "..\Primitive\MwVector4.h"

class MWDLLCLASS MwParameter
{
private:
	static MwParameter *GetEffectiveParameter(MwParameter *parameter);

	void DisposeValue();

public:
	void *value;
	MwParameterType type;

	MwParameter(void);
	MwParameter(int value);
	MwParameter(float value);
	MwParameter(bool value);
	MwParameter(const MwVector4 &value);
	MwParameter(MwParameterType type, void *value);
	virtual ~MwParameter(void);

	// Gets the effective value of the parameter.
	MwParameter *GetEffectiveParameter();
	// Recalls the effective value of the parameter and sets it. If the parameter was a reference before calling this method, after that it will hold the referenced value
	void RecallEffectiveParameter();

	// Sets the type of the parameter and reallocates memory if required
	void SetType(MwParameterType type);

	// Sets a reference value of the given type. If necessary, previous memory is deallocated and no new memory is allocated. Only a reference is saved.
	void SetReference(MwParameterType type, void *value);
	// Sets a value of the given type. If necessary, memory is reallocated. Depending on the type, a copy of the referenced value or a reference is saved.
	void SetValue(MwParameterType type, void *value);
	// Returns the effective value of the parameter. Traces to a non-mechanism value
	void *GetEffectiveValue();

	// Sets an integer value
	void SetInt(int value);
	// Gets the effective value as an integer.
	int GetInt();

	// Sets a float value
	void SetFloat(float value);
	// Gets the effective value as a float.
	float GetFloat();

	// Sets an bool value
	void SetBool(bool value);
	// Gets the effective value as a bool.
	bool GetBool();	

	// Sets a color value
	void SetColor(const MwVector4 &value);
	// Gets the effective value as a color.
	MwVector4 GetColor();
};

