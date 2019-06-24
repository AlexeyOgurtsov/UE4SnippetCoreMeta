#include "Misc/AutomationTest.h"
#include "Proto/ProtoFieldUtils.h"
#include "Test/TestClass.h"
#include "Util/Core/LogUtilLib.h"
#include "FieldUtilsArrayTestBase.h"
#include "PropertyValueArrayTestBase.h"
#include "FieldUtilsTestUtils.h"


namespace FieldUtilsTest
{
	class FTestBase_GetFieldsRecursive : public FFieldUtilsArrayTestBase
	{
	public:
		FTestBase_GetFieldsRecursive(const FString& InName, bool const bComplexTask)
		: FFieldUtilsArrayTestBase(InName, bComplexTask)
		{
		}
	};

	class FTestBase_TraverseFields : public FPropertyValueArrayTestBase
	{
	public:
		FTestBase_TraverseFields(const FString& InName, bool const bComplexTask)
		: FPropertyValueArrayTestBase(InName, bComplexTask)
		{
			PropHolder.Initialize(Cast<UObject>(GetTransientPackage()));
		} 

	protected:
		// ~Checks Begin
		/**
		* Traverse the given property field and check it's included.
		*/
		void TraverseCheckSingle(UProperty* InProperty, void* InContainer)
		{
			check(InProperty);
			TraverseTopFields(InProperty, InContainer);
			CheckIncluded(InProperty, InContainer);
		}

		void TraverseCheckRootStruct(UProperty* InProperty, void* InContainer, EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite)
		{
			check(InProperty);
			check(InContainer);

			TraverseTopFields(InProperty, InContainer, InFieldIterationFlags);
			CheckPropertiesIncluded(FProtoFieldUtils::GetStructFromField(InProperty, InContainer), InContainer);
		}
		// ~Checks End

		// ~Traverse helpers Begin
		void TraverseFieldsRecursive
		(
			UField* InRootField, void* InContainer,
			EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite
		)
		{
			TraverseFields(InRootField, InContainer, FProtoFieldUtils::TraverseFunc_TraverseSubtree, InFieldIterationFlags);
		}

		void TraverseTopFields
		(
			UField* InRootField, void* InContainer,
			EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite
		)
		{
			TraverseFields(InRootField, InContainer, FProtoFieldUtils::TraverseFunc_SkipSubtree, InFieldIterationFlags);
		}

		template<typename FuncType>
		void TraverseFields
		(
			UField* InRootField, void* InContainer, FuncType Func,
			EFieldIterationFlags InFieldIterationFlags = EFieldIterationFlags::IncludeComposite	
		)
		{
			TSet<FPropertyValue> const PropertySet = FProtoFieldUtils::TraverseFields(InRootField, InContainer, Func, ELogFlags::LogEverSuccess, InFieldIterationFlags);
			PropertyValues = PropertySet.Array();
		}
		// ~Traverse helpers End

		// ~Testee stuff Begin
		UTestClass* GetTestObject() const { return PropHolder.GetTestClass(); }
		FTestPropHolder& GetPropHolder() { return PropHolder; }
		const UClass* GetRootClass() const { return PropHolder.GetRootClass(); }
		UBoolProperty* GetProp_Bool() const { return PropHolder.GetProp_Bool(); }
		UStructProperty* GetProp_Struct() const { return PropHolder.GetProp_Struct(); }
		UObjectProperty* GetProp_Obj() const { return PropHolder.GetProp_Obj(); }
		UObject* GetObj() const { return PropHolder.GetObj(); }
		FTestStruct GetStruct() const { return PropHolder.GetStruct(); }
		// ~Testee stuff End


	private:
		// ~Testee stuff Begin
		FTestPropHolder PropHolder;
		// ~Testee stuff End
	};
} // FieldUtilsTest

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_GetFieldsRecursive_Quick, FieldUtilsTest::FTestBase_GetFieldsRecursive, "MyProtoTests.FieldUtils.Quick", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_GetFieldsRecursive_Quick2, FieldUtilsTest::FTestBase_GetFieldsRecursive, "MyProtoTests.FieldUtils.Quick2", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );

IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_TraverseFields_OnlyRootProperty, FieldUtilsTest::FTestBase_TraverseFields, "MyProto.FieldUtils.TraverseFields.OnlyRootProperty", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_TraverseFields_RootStructProperty, FieldUtilsTest::FTestBase_TraverseFields, "MyProto.FieldUtils.TraverseFields.RootStructProperty", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );
IMPLEMENT_CUSTOM_SIMPLE_AUTOMATION_TEST( FPropertyFieldUtils_TraverseFields_ClassProperty, FieldUtilsTest::FTestBase_TraverseFields, "MyProto.FieldUtils.TraverseFields.ClassProperty", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter );

bool FPropertyFieldUtils_TraverseFields_OnlyRootProperty::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	TraverseCheckSingle(GetProp_Bool(), &GetPropHolder());
	
	return true;
}

bool FPropertyFieldUtils_TraverseFields_RootStructProperty::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	TraverseCheckRootStruct(GetProp_Struct(), &GetPropHolder());
	TraverseCheckRootStruct(GetProp_Obj(), &GetPropHolder());
	
	return true;
}

bool FPropertyFieldUtils_TraverseFields_ClassProperty::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	TraverseFieldsRecursive
	(
		GetProp_Obj(), &GetPropHolder(), EFieldIterationFlags::IncludeComposite
	);

	{
		CheckObjectPropertiesIncluded(GetTestObject()->GetBaseObjectField());
		CheckObjectPropertiesIncluded(GetTestObject()->GetBaseActorField());
		CheckObjectPropertiesIncluded(GetTestObject()->GetTestObj());
		CheckObjectPropertiesIncluded(GetTestObject()->GetTestObjToObj());
		CheckObjectPropertiesIncluded(GetTestObject()->GetTestObj2());
		CheckObjectPropertiesIncluded(GetTestObject()->GetTestObjNull());
	}

	{
		const FTestStruct S = GetStruct();
		CheckStructPropertiesIncluded(&S);
	}

	{
		CheckInterfaceObjectPropertiesIncluded(GetTestObject()->GetBaseTestInterfaceField());
		CheckInterfaceObjectPropertiesIncluded(GetTestObject()->GetBaseTestInterfaceFieldToField());
		CheckInterfaceObjectPropertiesIncluded(GetTestObject()->GetBaseTestInterfaceField2());
		CheckInterfaceObjectPropertiesIncluded(GetTestObject()->GetBaseTestInterfaceFieldNull());
	}

	return true;
}

bool FPropertyFieldUtils_GetFieldsRecursive_Quick::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	const UClass* const RootClass = UTestClass::StaticClass();
	const UStruct* const TestStruct = FTestStruct::StaticStruct();
	TArray<UField*> const ResultFieldSet = FProtoFieldUtils::GetFieldsRecursive(RootClass).Array();
	Fields = ResultFieldSet;

	CheckFieldsIncluded(RootClass);
	CheckFieldsIncluded(TestStruct);
	
	return true;
}

bool FPropertyFieldUtils_GetFieldsRecursive_Quick2::RunTest(const FString& Parameters)
{
	M_LOGFUNC();

	//const UClass* const RootClass = UTestClass::StaticClass();
	//TArray<UField*> const ResultFieldSet = FProtoFieldUtils::GetFieldsRecursive(RootClass).Array();
	//Fields = ResultFieldSet;

	return true;
}