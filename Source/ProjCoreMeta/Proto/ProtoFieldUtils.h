#pragma once

#include "Util/Core/Log/MyLoggingTypes.h"

class UField;
class UStruct;

UENUM(BlueprintType)
enum class EFieldIterationFlags : uint8
{
	None = 0 UMETA(DisplayName="None"),
	IncludeComposite = 1 << 0 UMETA(DisplayName="Include composite")
};
ENUM_CLASS_FLAGS(EFieldIterationFlags);

UENUM(BlueprintType)
enum class EFieldStringFlags : uint8
{
	None = 0 UMETA(DisplayName="None"),
	ExcludeOwner = 1 << 0 UMETA(DisplayName="Exclude owner")
};
ENUM_CLASS_FLAGS(EFieldStringFlags);

class FProtoFieldUtils
{
public:
	/**
	* Returns field string representation.
	*/
	static FString GetFieldString(const UField* InField, EFieldStringFlags InFlags = EFieldStringFlags::None);

	/**
	* Returns all fields recursively from the given struct;
	* @param InStruct - UStruct to iterate (cannot be nullptr);
	*/
	static TSet<UField*> GetFieldsRecursive(const UStruct* InStruct, ELogFlags InLogFlags = ELogFlags::None, EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite);

private:
};