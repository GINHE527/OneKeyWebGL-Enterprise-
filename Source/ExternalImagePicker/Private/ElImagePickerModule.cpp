

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWidget.h"
#include "IElImagePickerModule.h"
#include "SElImagePicker.h"

/**
 * Public interface for splash screen editor module
 */
class FExternalImagePickerModule : public IElImagePickerModule
{
public:
	virtual TSharedRef<SWidget> MakeEditorWidget(const FElImagePickerConfiguration& InConfiguration) override
	{
		return SNew(SElImagePicker)
			.TargetImagePath(InConfiguration.TargetImagePath)
			.DefaultImagePath(InConfiguration.DefaultImagePath)
			.OnExternalImagePicked(InConfiguration.OnExternalImagePicked)
			.OnGetPickerPath(InConfiguration.OnGetPickerPath)
			.MaxDisplayedImageDimensions(InConfiguration.MaxDisplayedImageDimensions)
			.RequiresSpecificSize(InConfiguration.bRequiresSpecificSize)
			.RequiredImageDimensions(InConfiguration.RequiredImageDimensions)
			.Extensions(InConfiguration.FileExtensions);
	}
	
};

IMPLEMENT_MODULE(FExternalImagePickerModule, ExternalImagePicker)
