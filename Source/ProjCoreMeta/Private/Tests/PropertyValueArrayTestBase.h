#pragma once

#include "FieldUtilsTestBase.h"
#include "Proto/ProtoFieldUtils.h"

class FPropertyValueArrayTestBase : public FFieldUtilsTestBase
{
public:
	FPropertyValueArrayTestBase(const FString& InName, bool const bComplexTask);

protected:
	TArray<FPropertyValue> PropertyValues;

	// ~Checks Begin
	void CheckIncluded(const UProperty* InExpectedProperty, const void* InContainer);

	/**
	* Checks that all properties for the given container are included in the result set of properties.
	* @note: If container is nullptr, the test is passed.
	* @param InStruct: structure of the container (maybe nullptr if container is nullptr).
	*/
	void CheckPropertiesIncluded(const UStruct* InStruct, const void* InContainer, EFieldIterationFlags InFlags = EFieldIterationFlags::None);

	void CheckInterfaceObjectPropertiesIncluded(const FScriptInterface& InScriptInterface, EFieldIterationFlags InFlags = EFieldIterationFlags::None)
	{
		check(InScriptInterface.GetObject());
		const UObject* const Container = InScriptInterface.GetObject();
		CheckObjectPropertiesIncluded(Container, InFlags);
	}

	template<class ObjectType>
	void CheckObjectPropertiesIncluded(const ObjectType* InContainer, EFieldIterationFlags InFlags = EFieldIterationFlags::None)
	{
		CheckPropertiesIncluded(ObjectType::StaticClass(), InContainer, InFlags);
	}

	template<class StructType>
	void CheckStructPropertiesIncluded(const StructType* InContainer, EFieldIterationFlags InFlags = EFieldIterationFlags::None)
	{
		CheckPropertiesIncluded(StructType::StaticStruct(), InContainer, InFlags);		
	}
	// ~Checks End

private:
};