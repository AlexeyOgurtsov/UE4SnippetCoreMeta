#include "PropertyValueArrayTestBase.h"
#include "Util/Core/LogUtilLib.h"

FPropertyValueArrayTestBase::FPropertyValueArrayTestBase(const FString& InName, bool const bComplexTask) :
	FFieldUtilsTestBase{InName, bComplexTask}
{
}

void FPropertyValueArrayTestBase::CheckField(const UField* InExpectedField, const void* InContainer)
{
	M_NOT_IMPL();
}

void FPropertyValueArrayTestBase::CheckFieldsIncluded(const UStruct* InStruct, const void* InContainer)
{
	M_NOT_IMPL();
}