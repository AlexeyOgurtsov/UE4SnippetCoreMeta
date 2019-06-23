#pragma once

#include "FieldUtilsTestBase.h"
#include "Proto/ProtoFieldUtils.h"

class FPropertyValueArrayTestBase : public FFieldUtilsTestBase
{
public:
	FPropertyValueArrayTestBase(const FString& InName, bool const bComplexTask);

protected:
	TArray<FPropertyValue> PropertyValues;

	void CheckField(const UField* InExpectedField, const void* InContainer);
	void CheckFieldsIncluded(const UStruct* InStruct, const void* InContainer);

private:
};