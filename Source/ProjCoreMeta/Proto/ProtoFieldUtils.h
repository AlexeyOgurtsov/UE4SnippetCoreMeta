#pragma once

#include "Util/Core/Log/MyLoggingTypes.h"
#include "Util/Core/LogUtilLib.h"

class UField;
class UStruct;

UENUM(BlueprintType)
enum class EFieldIterationFlags : uint8
{
	None = 0 UMETA(DisplayName="None"),
	IncludeComposite = 1 << 0 UMETA(DisplayName="Include composite"),
	IncludeFunction = 1 << 1 UMETA(DisplayName="Include function")
};
ENUM_CLASS_FLAGS(EFieldIterationFlags);

UENUM(BlueprintType)
enum class EFieldStringFlags : uint8
{
	None = 0 UMETA(DisplayName="None"),
	ExcludeOwner = 1 << 0 UMETA(DisplayName="Exclude owner")
};
ENUM_CLASS_FLAGS(EFieldStringFlags);

UENUM(BlueprintType)
enum class EFieldTraverseFunctionResult : uint8
{
	StopTraverse = 0 UMETA(DisplayName="Stop search"), // Should we stop traverse completely
	TraverseSubtree = 1 UMETA(DisplayName="Traverse subtree"), // We should traverse the subtree rooted from this field
	SkipSubtree = 2 UMETA(DisplayName="Skip subtree"), // We should skip this subtree but continue the traverse
};

class FProtoFieldUtils
{
public:
	/**
	* Returns field string representation.
	*/
	static FString GetFieldString(const UField* InField, EFieldStringFlags InFlags = EFieldStringFlags::None);

	/**
	* Returns most-actual dynamic pointer to UStruct.
	*
	* @returns:
	* For UStruct:                 this
	* For UObjectBaseProperty:     GetPropertyValue_InContainer(InContainer)->GetClass()
	* For UStructProperty:         Struct
	* For UInterfaceProperty:      GetPropertyValue_InContainer(InContainer)->GetClass()
	* For Other:                   nullptr;
	*/
	static UStruct* GetStructFromField(UField* InField, const void* InContainer);

	/**
	* @Returns: 
	* Runtime class of object property value in the field; 
	* nullptr - if property value is nullptr;
	* nullptr - if property value is not inherited from UObject.
	*/
	template<class PropT> 
	static UClass* GetPropertyValueRuntimeClass(const PropT* InProp, const void* InContainer)
	{
		check(InProp);
		check(InContainer);

		const UObject* const PropertyValue = *InProp->ContainerPtrToValuePtr<const UObject*>(InContainer);
	
		if( nullptr == PropertyValue )
		{
			return nullptr;
		}

		return PropertyValue->GetClass();
	}

	/**
	* Returns all fields recursively from the given struct;
	* @param InStruct - UStruct to iterate (cannot be nullptr);
	*/
	static TSet<UField*> GetFieldsRecursive(const UStruct* InStruct, ELogFlags InLogFlags = ELogFlags::None, EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite);

	/**
	* Traverses hierarchy of fields. 
	* Concrete (Runtime) classes of UObjectBaseProperty, UInterfaceProperty, UStructProperty are traversed recursively.
	*
	* @param   Func          Func taking UField* and returning EFieldTraverseFunctionResult
	*/
	template<typename FuncType>
	static TSet<UField*> TraverseFields
	(
		const UField* InRootField, void* InContainer, FuncType Func,
		ELogFlags InLogFlags = ELogFlags::None, EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite	
	)
	{
		TSet<UField*> ResultFields;
		M_NOT_IMPL();
		return ResultFields;
	}

	static EFieldTraverseFunctionResult TraverseFunc_SkipSubtree(const UField* InField) { return EFieldTraverseFunctionResult::SkipSubtree; }
	static EFieldTraverseFunctionResult TraverseFunc_TraverseSubtree(const UField* InField) { return EFieldTraverseFunctionResult::TraverseSubtree; }

private:
};