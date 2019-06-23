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