#include "ProtoFieldUtils.h"
#include "Util/Core/LogUtilLib.h"

FString FProtoFieldUtils::GetFieldString(const UField* InField, EFieldStringFlags InFlags)
{
	FString Result;

	if((InFlags & EFieldStringFlags::ExcludeOwner) == EFieldStringFlags::None)
	{
		Result.Append(TEXT("OwnerStruct={"));		
		Result.Append(ULogUtilLib::GetNameAndClassSafe(InField->GetOwnerStruct()));	
		Result.Append(TEXT("}; "));		
	}

	Result.Append(ULogUtilLib::GetNameAndClassSafe(InField));
	
	return Result;
}

FString FProtoFieldUtils::GetPropertyValueString(const UProperty* InProperty, const void* InValue, EPropertyValueStringFlags InFlags)
{
	if(const UNumericProperty* PropAsNumeric = Cast<const UNumericProperty>(InProperty))
	{
		return PropAsNumeric->GetNumericPropertyValueToString(InValue);
	}
	else if(const UBoolProperty* PropAsBool = Cast<const UBoolProperty>(InProperty))
	{
		return PropAsBool->GetPropertyValue(&InValue) ? FString(TEXT("TRUE")) : FString(TEXT("false"));
	}
	else if(const UObjectPropertyBase* PropAsObj = Cast<const UObjectPropertyBase>(InProperty))
	{
		return PropAsObj->GetObjectPropertyValue(InValue) ? FString(TEXT("SET")) : FString(TEXT("nullptr"));
	}
	else if(const UClassProperty* PropAsClass = Cast<const UClassProperty>(InProperty))
	{
		return PropAsClass->MetaClass ? PropAsClass->MetaClass->GetName() : FString(TEXT("nullptr"));
	}
	else if(const UInterfaceProperty* PropAsInterface = Cast<const UInterfaceProperty>(InProperty))
	{
		return PropAsInterface->InterfaceClass ? PropAsInterface->InterfaceClass->GetName() : FString(TEXT("nullptr"));
	}
	else if(const UNameProperty* PropAsName = Cast<const UNameProperty>(InProperty))
	{
		return UNameProperty::GetPropertyValue(InValue).ToString();
	}
	else if(const UStrProperty* PropAsString = Cast<const UStrProperty>(InProperty))
	{
		return UStrProperty::GetPropertyValue(InValue);
	}
	else if(const UArrayProperty* PropAsArray = Cast<const UArrayProperty>(InProperty))
	{
		return GetArrayPropertyValueString(PropAsArray, InValue, InFlags);
	}
	else if(const UMapProperty* PropAsMap = Cast<const UMapProperty>(InProperty))
	{
		return GetMapPropertyValueString(PropAsMap, InValue, InFlags);
	}
	else if(const USetProperty* PropAsSet = Cast<const USetProperty>(InProperty))
	{
		return GetSetPropertyValueString(PropAsSet, InValue, InFlags);
	}
	else if(const UStructProperty* PropAsStruct = Cast<UStructProperty>(InProperty))
	{
		return FString(TEXT("{STRUCT}"));
	}
	else if(const UDelegateProperty* PropAsDelegate = Cast<const UDelegateProperty>(InProperty))
	{
		return PropAsDelegate->SignatureFunction ? FString(TEXT("SET")) : FString(TEXT("nullptr"));
	}
	else if(const UMulticastDelegateProperty* PropAsMultiDelegate = Cast<const UMulticastDelegateProperty>(InProperty))
	{
		return PropAsMultiDelegate->SignatureFunction ? FString(TEXT("SET")) : FString(TEXT("nullptr"));
	}
	else
	{
		return FString(TEXT("{UNKNOWN_PROP_TYPE}"));
	}
}

FString FProtoFieldUtils::GetArrayPropertyValueString(const UArrayProperty* InProperty, const void* InValue, EPropertyValueStringFlags InFlags)
{
	M_NOT_IMPL_RET(FString{TEXT("{IMPL:ARRAY_AS_STRING}")});
}

FString FProtoFieldUtils::GetSetPropertyValueString(const USetProperty* InProperty, const void* InValue, EPropertyValueStringFlags InFlags)
{
	M_NOT_IMPL_RET(FString{TEXT("{IMPL:SET_AS_STRING}")});
}

FString FProtoFieldUtils::GetMapPropertyValueString(const UMapProperty* InProperty, const void* InValue, EPropertyValueStringFlags InFlags)
{
	M_NOT_IMPL_RET(FString{TEXT("{IMPL:MAP_AS_STRING}")});
}

FString FProtoFieldUtils::GetFieldStringSafe(const UField* InField, EFieldStringFlags InFlags)
{
	if(InField == nullptr)
	{
		return FString(TEXT("{nullptr}"));
	}
	return GetFieldString(InField, InFlags);
}
bool FProtoFieldUtils::FindPropertyValue(const TArray<FPropertyValue>& InArray, const UProperty* InProperty, const void *InContainer, int32& OutPropertyValueIndex)
{
	check(InProperty);
	check(InContainer);
	bool const bFound = InArray.Find(FPropertyValue{const_cast<UProperty*>(InProperty), const_cast<void*>(InContainer)}, OutPropertyValueIndex);
	return bFound;
}

UStruct* FProtoFieldUtils::GetStructFromField(UField* InField, const void* InContainer)
{
	if(UStruct* Struct = Cast<UStruct>(InField))
	{
		return Struct;	
	}

	if(UStructProperty* StructProperty = Cast<UStructProperty>(InField))
	{
		return StructProperty->Struct;
	}

	if(UObjectPropertyBase* ObjectProperty = Cast<UObjectPropertyBase>(InField))
	{
		return GetPropertyValueRuntimeClass(ObjectProperty, InContainer);

	}

	if(UInterfaceProperty* InterfaceProperty = Cast<UInterfaceProperty>(InField))
	{
		return GetPropertyValueRuntimeClass(InterfaceProperty, InContainer);
	}

	return nullptr;
}

bool FProtoFieldUtils::IsRelevantField(UField* InField, EFieldIterationFlags InFlags, ELogFlags InLogFlags)
{
	bool const bIncludeComposite = ((InFlags & EFieldIterationFlags::IncludeComposite) != EFieldIterationFlags::None);
	if(UFunction* FuncField = Cast<UFunction>(InField))
	{
		if((InFlags & EFieldIterationFlags::IncludeFunction) == EFieldIterationFlags::None)
		{
			M_LOG_IF_FLAGS(InLogFlags, TEXT("{%s}: Skipping ufunction (include function flag is NOT set)"), *GetFieldString(InField));	
			return false;
		}
	}
	else if(UStructProperty* StructProperty = Cast<UStructProperty>(InField))
	{
		if(bIncludeComposite)
		{
			M_LOG_IF_FLAGS(InLogFlags, TEXT("{%s}: Skipping struct property (include composite flag is NOT set)"), *GetFieldString(InField));	
			return false;
		}
	}

	return true;
}

TSet<UField*> FProtoFieldUtils::GetFieldsRecursive(const UStruct* const InStruct, ELogFlags InLogFlags, EFieldIterationFlags InFieldIterationFlags)
{
	M_LOGFUNC_IF_FLAGS(InLogFlags);
	check(InStruct);

	TSet<UField*> Fields;

	TArray<const UStruct*> StructsToVisit;
	StructsToVisit.Add(InStruct);

	for(int32 StructIndex = 0; StructIndex < StructsToVisit.Num(); StructIndex++)
	{
		const UStruct* S  = StructsToVisit[StructIndex];
		M_LOG_IF_FLAGS(InLogFlags, TEXT("UStruct {%s}: "), *GetFieldString(S));
		for(UField* F : TFieldRange<UField>(S))
		{
			if( Fields.Contains(F) )
			{
				M_LOG_IF_FLAGS(InLogFlags, TEXT("Skipping UStruct - Field already visited"), *GetFieldString(S));
				continue;
			}

			if(UStructProperty* StructProperty = Cast<UStructProperty>(F))
			{
				UStruct* StructField = StructProperty->Struct;

				StructsToVisit.Add(StructField);

			}

			if(IsRelevantField(F, InFieldIterationFlags, InLogFlags))
			{
				M_LOG_IF_FLAGS(InLogFlags, TEXT("Adding field {%s}"), *GetFieldString(F));
				Fields.Add(F);
			}
		}
	}
	M_LOG_IF_FLAGS(InLogFlags, TEXT("%d structs visited"), StructsToVisit.Num());

	return Fields;
}
