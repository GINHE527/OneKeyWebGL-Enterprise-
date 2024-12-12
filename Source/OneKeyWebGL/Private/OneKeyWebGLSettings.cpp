#include "OneKeyWebGLSettings.h"
#include "IElImagePickerModule.h"
#include "SElImagePicker.h"
// 构造函数，初始化默认值
FString imagePaths  = "100";
UOneKeyWebGLSettings::UOneKeyWebGLSettings()
{
    //PreviewImage = nullptr;
    Custom_Project_Name = "Project-Basic-Name";
    Account_ = "";
    Password_ = "";
    Eula_Confirm = false;
    ImagePath= FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() + "OneKeyWebGL/Resources/Pictrue_prievew.png");
    IcoPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() + "OneKeyWebGL/Resources/Baisc_ico.ico");
    
    //if(Custom_Loading_pi)
}
void UOneKeyWebGLSettings::RegeneratePreview() {
    return;
}



static FElImagePickerConfiguration* Ficonfig = new FElImagePickerConfiguration;
static FElImagePickerConfiguration* Ficoconfig = new FElImagePickerConfiguration;
static FIntPoint* NeedSizePicture = new FIntPoint;

void UOneKeyWebGLSettings::UpdateImagePaths() {
	// 将 ImagePath 赋值给 Ficonfig->TargetImagePath
	Ficonfig->TargetImagePath = ImagePath;
}

class NewModel :public IElImagePickerModule {
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

class NewIconModel : public IElImagePickerModule {
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

static NewModel* newmodel = new NewModel;
static NewIconModel* newiconmodel = new NewIconModel;
TSharedRef<SWidget>UOneKeyWebGLSettings::CreateImageWidget(UOneKeyWebGLSettings* Settings) {
    FString DefaultImagePaths = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() + "OneKeyWebGL/Resources/Pictrue_prievew.png");
    Ficonfig->TargetImagePath = Settings->ImagePath;
    TArray<FString>pathss;
    pathss.Add("png");
    Ficonfig->FileExtensions = pathss;
    NeedSizePicture->X = 1920;
    NeedSizePicture->Y = 1080;
    Ficonfig->bRequiresSpecificSize = true;
    FVector2D sizesize = FVector2D(480.0f, 360.0f);
    Ficonfig->MaxDisplayedImageDimensions = sizesize;
    Ficonfig->RequiredImageDimensions = *NeedSizePicture;
    return newmodel->MakeEditorWidget(*Ficonfig);
}

TSharedRef<SWidget>UOneKeyWebGLSettings::CreateIcoImageWidget(UOneKeyWebGLSettings* Settings) {
    FString DefaultImagePaths = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() + "OneKeyWebGL/Resources/Basic_ico.ico");
	Ficoconfig->TargetImagePath = Settings->IcoPath;
	TArray<FString>pathss;
	pathss.Add("ico");
    Ficoconfig->FileExtensions = pathss;
	NeedSizePicture->X = 64;
	NeedSizePicture->Y = 64;
	Ficoconfig->bRequiresSpecificSize = true;
	FVector2D sizesize = FVector2D(64.0f, 64.0f);
	Ficoconfig->MaxDisplayedImageDimensions = sizesize;
	Ficoconfig->RequiredImageDimensions = *NeedSizePicture;
	return newiconmodel->MakeEditorWidget(*Ficoconfig);
}