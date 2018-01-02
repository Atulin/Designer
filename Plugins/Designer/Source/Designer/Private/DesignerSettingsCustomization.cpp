//  Copyright 2017 Roel Bartstra.

//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files(the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions :

//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.

//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.

#include "DesignerSettingsCustomization.h"
#include "DesignerModule.h"

#include "DesignerEdMode.h"
#include "DesignerSettings.h"

#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "PropertyCustomizationHelpers.h"
#include "Widgets/Input/SVectorInputBox.h"
#include "PropertyHandle.h"
#include "Misc/Optional.h"
#include "Fonts/SlateFontInfo.h"

#include "EditorModeManager.h"

TSharedRef<IDetailCustomization> FDesignerSettingsCustomization::MakeInstance()
{
	//UE_LOG(LogDesigner, Error, TEXT("FDesignerSettingsCustomization::MakeInstance"));
	return MakeShareable(new FDesignerSettingsCustomization());
}

void FDesignerSettingsCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	//UE_LOG(LogDesigner, Error, TEXT("FDesignerSettingsCustomization::CustomizeDetails"));
	
	FDesignerEdMode* DesignerEdMode = (FDesignerEdMode*)GLevelEditorModeTools().GetActiveMode(FDesignerEdMode::EM_DesignerEdModeId);

	IDetailCategoryBuilder& PlacementSettingsCategory = DetailBuilder.EditCategory("PlacementSettings");

	TSharedRef<IPropertyHandle> PropertyHandle_SpawnLocationOffsetRelative = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UDesignerSettings, SpawnLocationOffsetRelative));
	TSharedRef<IPropertyHandle> PropertyHandle_SpawnLocationOffsetRelative_X = PropertyHandle_SpawnLocationOffsetRelative->GetChildHandle("X").ToSharedRef();
	TSharedRef<IPropertyHandle> PropertyHandle_SpawnLocationOffsetRelative_Y = PropertyHandle_SpawnLocationOffsetRelative->GetChildHandle("Y").ToSharedRef();
	TSharedRef<IPropertyHandle> PropertyHandle_SpawnLocationOffsetRelative_Z = PropertyHandle_SpawnLocationOffsetRelative->GetChildHandle("Z").ToSharedRef();
	
	PlacementSettingsCategory.AddProperty(PropertyHandle_SpawnLocationOffsetRelative)
	.CustomWidget()
	.NameContent()
	[
		PropertyHandle_SpawnLocationOffsetRelative->CreatePropertyNameWidget()
	]
	.ValueContent()
	.MinDesiredWidth(125.0f * 3.0f) // copied from FComponentTransformDetails
	.MaxDesiredWidth(125.0f * 3.0f)
	[
		SNew(SVectorInputBox)
		.bColorAxisLabels(true)
		.AllowSpin(false)
		.Font(DetailBuilder.GetDetailFont())
		.X_Lambda([=]() -> float { return DesignerEdMode->UISettings->SpawnLocationOffsetRelative.X; })
		.Y_Lambda([=]() -> float { return DesignerEdMode->UISettings->SpawnLocationOffsetRelative.Y; })
		.Z_Lambda([=]() -> float { return DesignerEdMode->UISettings->SpawnLocationOffsetRelative.Z; })
		.OnXChanged_Lambda([=](float Value) { DesignerEdMode->UISettings->SpawnLocationOffsetRelative.X = Value; })
		.OnYChanged_Lambda([=](float Value) { DesignerEdMode->UISettings->SpawnLocationOffsetRelative.Y = Value; })
		.OnZChanged_Lambda([=](float Value) { DesignerEdMode->UISettings->SpawnLocationOffsetRelative.Z = Value; })
	];
}

void FDesignerSettingsCustomization::OnPaintTypeChanged(IDetailLayoutBuilder* LayoutBuilder)
{
	//UE_LOG(LogDesigner, Error, TEXT("FDesignerSettingsCustomization::OnPaintTypeChanged"));
	LayoutBuilder->ForceRefreshDetails();
}

TSharedPtr<SWidget> FDesignerSettingsRootObjectCustomization::CustomizeObjectHeader(const UObject* InRootObject)
{
	//UE_LOG(LogDesigner, Error, TEXT("FDesignerSettingsRootObjectCustomization::CustomizeObjectHeader"));
	return SNullWidget::NullWidget;
}