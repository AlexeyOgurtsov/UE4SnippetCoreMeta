#include "PropertyValueArrayTestBase.h"
#include "Proto/ProtoFieldUtils.h"
#include "Util/Core/LogUtilLib.h"

FPropertyValueArrayTestBase::FPropertyValueArrayTestBase(const FString& InName, bool const bComplexTask) :
	FFieldUtilsTestBase{InName, bComplexTask}
{
}

void FPropertyValueArrayTestBase::CheckIncluded(const UProperty* InExpectedProperty, const void* InContainer)
{
	int32 Index;
	bool const bPropFound = FProtoFieldUtils::FindPropertyValue(PropertyValues, InExpectedProperty, InContainer, Index);
	TestTrue(FString::Printf(TEXT("Property {%s} is expected"), *FProtoFieldUtils::GetFieldString(InExpectedProperty)), bPropFound);
}

void FPropertyValueArrayTestBase::CheckPropertiesIncluded(const UStruct* InStruct, const void* InContainer, EFieldIterationFlags InFlags)
{
	if(InContainer == nullptr)
	{
		M_LOG(TEXT("{%s}: Test is passed: container is nullptr"), *FProtoFieldUtils::GetFieldStringSafe(InStruct));
		return;
	}	

	for(UProperty* ExpectedProperty : TFieldRange<UProperty>(InStruct))
	{
		if(FProtoFieldUtils::IsRelevantField(ExpectedProperty, InFlags, ELogFlags::LogEverSuccess))	
		{
			CheckIncluded(ExpectedProperty, InContainer);
		}
	}
}