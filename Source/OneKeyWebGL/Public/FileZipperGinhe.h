//Copyright Ginhe.cn, Inc.All Rights Reserved.

//create by :     (until 2024/11/5 )
//**********************************************************************************************//
//																								//
//		00		00				00															    //
//		00		00				00														        //
//		00		00				00																//
//		0000000000	  0000000	00000000	00 000000	 0000000	  0000000	  0000000		//
//		00		00	00	    00	00	   00	000		00	00	    00	 00		 	 00		    	//
//		00		00	0000000000	00	   00	00		00	0000000000	  0000000	  0000000		//
//		00		00	00	  		00	   00	00		00	00			 		00	        00		//
//		00	  	00	  0000000	00000000	00		00	  0000000	  0000000	  0000000		//
//																								//
//**********************************************************************************************//

#pragma once

#include "CoreMinimal.h"
#include "Editor/UnrealEd/Public/Editor.h"
#include "FileHelpers.h"
#include "Runtime\Core\Public\HAL\FileManager.h"
#include "Runtime\Core\Public\HAL\PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "ZlibCompress.h"
#include "Winsock.h"
#include <fstream>
#include <iostream>
//#include "windows.h"
#include "string"
#include <cstddef>
#include"HAL/Runnable.h"
#include "Windows/WindowsPlatformProcess.h"


#pragma comment(lib, "wsock32.lib")	
//FString 的修改操作文档
//这个头文件负责对文件的复制及压缩

#define DebugLog(msg) UE_LOG(LogTemp, Warning ,TEXT(msg))
#define OKYLOG(ms,msg)   UE_LOG(LogTemp, Warning ,TEXT(ms),*msg)

#undef CopyFile

class Zipper_ginhe {
public:
	//赋予zipper_ginehe_thread为友类，避免复用
	friend class Zipper_ginhe_thread;
	//得到项目文件
	const FString Project_path = FPaths::ProjectDir();
	//绝对地址
	const FString Project_ab_path = FPaths::ConvertRelativePathToFull(Project_path);
	//复制时间
	const FString Start_time = FDateTime::Now().ToString();
	//得到 mac 地址 FGenericPlatformMisc::GetHashedMacAddressString(),存档为目标地址
	const FString ZipName = FGenericPlatformMisc::GetHashedMacAddressString() + "_" + Start_time + ".zip";
	const FString FtpZipName = FGenericPlatformMisc::GetHashedMacAddressString() + "_" + Start_time;
	//输出地址
	const FString Projectname = FPaths::GetBaseFilename(FPaths::GetProjectFilePath());
	const FString OutPut_path = Project_path + "OneKey/" + FGenericPlatformMisc::GetHashedMacAddressString() + "_" + Start_time;
	//构造初始化
	const FString pyPlugin_path_ab = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir() + "OneKeyWebGL/Source/OneKeyWebGL/pan123upload/thread_upload.exe");
	FString Name;
	FString DebugString;
	bool ItCanBeRun;

	void copydir() {
		//copyFunction();
		if (CheckContentFile(Project_path + "Content")) {
			DebugString = "ContentExists";
			ItCanBeRun = true;

			//copy list 
			FString CopyPath = OutPut_path + "/Content";
			if (!CopyDirectory(FPaths::ProjectContentDir(), CopyPath))
				DebugLog("Content copy failed");
			CopyPath = OutPut_path + "/Plugins";
			if (!CopyDirectory(FPaths::ProjectPluginsDir(), CopyPath))
				DebugLog("Plugins copy failed");
			CopyPath = OutPut_path + "/Config";
			if (!CopyDirectory(FPaths::ProjectConfigDir(), CopyPath))
				DebugLog("Config copy failed");
			CopyPath = OutPut_path + "/Source";
			if (!CopyDirectory(FPaths::GameSourceDir(), CopyPath))
				DebugLog("Source copy failed");
			CopyPath = OutPut_path + "/Intermediate";
			if (!CopyDirectory(FPaths::GameSourceDir(), CopyPath))
				// 			DebugLog("Intermediate copy failed");
				// 			CopyPath = OutPut_path + "/ThirdParty";
				if (!CopyDirectory(FPaths::GameSourceDir(), CopyPath))
					DebugLog("ThirdParty copy failed");
			CopyPath = OutPut_path + "/.vs";
			// 			if (!CopyDirectory(FPaths::GameSourceDir(), CopyPath))
			// 			DebugLog(".vs copy failed");

			FString DestinationPath_Copy = OutPut_path + "/" + FPaths::GetBaseFilename(FPaths::GetProjectFilePath()) + ".uproject";
			if (!CopyFilef(FPaths::GetProjectFilePath(), DestinationPath_Copy))
			{
				DebugLog("error ! not find .uproject !!! ");
				ItCanBeRun = false;
			}
			//sln不需要复制
// 			DestinationPath_Copy = OutPut_path+"/"+FPaths::GetBaseFilename(FPaths::GetProjectFilePath())+".sln";
// 			CopyPath = Project_path + FPaths::GetBaseFilename(FPaths::GetProjectFilePath()) + ".sln";
// 			CopyFilef(CopyPath, DestinationPath_Copy);
		}
		else {
			DebugString = "ContentNotExists";
			ItCanBeRun = false;
		}
	}

	Zipper_ginhe(){
		ItCanBeRun = true;
	};
	~Zipper_ginhe() {
	};

private:
	//查找Content文件夹是否存在
	bool CheckContentFile(FString Path) {
		return FPaths::DirectoryExists(Path);
	}
	//复制文件
	bool CopyFilef(const FString &SourcePath ,const FString &DestinationPath) {
//Debug INFO
// 		OKYLOG("text 1 %s", FPaths::GetProjectFilePath());
// 		OKYLOG("text 3 %s", FPaths::GetBaseFilename(FPaths::GetProjectFilePath()));
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		if (!PlatformFile.FileExists(*SourcePath)) {
			OKYLOG("%s is exist ! copy failed", FPaths::GetBaseFilename(SourcePath));
		}
		
		if (!PlatformFile.CopyFile(*DestinationPath,*SourcePath)) {
			UE_LOG(LogTemp,Warning,TEXT("Copy %s to %s failed"), *SourcePath, *DestinationPath);
			return false;
		}
		else {
			OKYLOG("%s copy complete", FPaths::GetBaseFilename(SourcePath));
		}
		
		return true;

	}
	//复制文件夹
	bool CopyDirectory(const FString& SourceDirPath, const FString& DestinationDirPath)
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		// 如果目标目录不存在，则创建它
		if (!PlatformFile.DirectoryExists(*DestinationDirPath))
		{
			PlatformFile.CreateDirectoryTree(*DestinationDirPath);
		}
		if (PlatformFile.CopyDirectoryTree(*DestinationDirPath, *SourceDirPath, true)) {
			UE_LOG(LogTemp, Warning, TEXT("Copy %s complete"), *SourceDirPath);
			return true;
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Copy failled"));
			return false;
		}
		return true;
	}

public:
	void PrintTxtFileContents(const FString& FilePath)
	{
		FString needprint = Project_ab_path + +"OneKey/" + ZipName;
		// 要创建或覆盖的文件名
		std::string fileName = TCHAR_TO_UTF8(*FilePath);
		// 要写入文件的内容
		std::string fileContent = TCHAR_TO_UTF8(*needprint);

		// 以输出模式打开文件，如果文件已存在则覆盖
		std::ofstream outputFile(fileName, std::ios::out);
		if (outputFile.is_open()) {
			// 将内容写入文件
			outputFile << fileContent;
			outputFile.close();
			DebugLog("output completely");
		}
		else {
			DebugLog("txt output erorr.");
		}

		return ;
	}

private:
	static int listall;
	int ID;
};

//获取文件夹大小的方法
uint64 GetDirectorySize(const FString& DirectoryPath)
{
	// Check if the directory exists
	if (!FPaths::DirectoryExists(DirectoryPath))
	{
		return 0;
	}

	// Get the file manager instance
	IFileManager& FileManager = IFileManager::Get();

	// Use a recursive function to calculate the size
	uint64 TotalSize = 0;
	bool bHasFiles = false;

	// Iterator for files in the directory
	TArray<FString> FileArray;
	FileManager.FindFilesRecursive(FileArray, *DirectoryPath, TEXT("*.*"), true, false);

	// Iterate through the found files
	for (const FString& File : FileArray)
	{
		// Get the size of the file
		TotalSize += FileManager.FileSize(*File);
		bHasFiles = true; // We found at least one file
	}

	// If no files were found, return 0
	return bHasFiles ? TotalSize : 0;
}

//多线程ZipPtr的实现，将保证zipper只能使用一次
//多线程实现最多1个线程保持此实现 (懒汉式实现)

class Zipper_ginhe_thread : public FRunnable {
public:
	virtual bool Init() override;  // 初始化 runnable 对象
	virtual uint32 Run() override; // 运行 runnable 对象
	virtual void Stop() override;  // 停止 runnable 对象,线程提前终止时被调用
 	virtual void Exit() override;  // 退出 runnable 对象
	Zipper_ginhe_thread(Zipper_ginhe* ppp) {
		ptr = ppp;
	}
	Zipper_ginhe* ptr;
};

bool Zipper_ginhe_thread::Init() { return true; }
uint32 Zipper_ginhe_thread::Run() { 
	ptr->copydir();
	DebugLog("Begin to zip and upload!");
	const FString OutPath_zip = ptr->Project_path + "OneKey/" + ptr->ZipName;
	if (ToZippedd(FPaths::ConvertRelativePathToFull(ptr->OutPut_path), FPaths::ConvertRelativePathToFull(OutPath_zip), ptr->Projectname)) {
		//ftp传输
		//ZipPtr->FtpBegin();
		DebugLog("Begin to upload !");
		FString needPrintpath = FPaths::ProjectPluginsDir() + "OneKeyWebGL/Source/OneKeyWebGL/pan123upload/_internal/path.txt";
		needPrintpath = FPaths::ConvertRelativePathToFull(needPrintpath);
		ptr->PrintTxtFileContents(needPrintpath);
		//跨平台需要修改
		UE_LOG(LogTemp, Warning, TEXT("Begin run %s"), *ptr->pyPlugin_path_ab);
		//类外运行
		system(TCHAR_TO_UTF8(*ptr->pyPlugin_path_ab));
	}
	
	return 0; }
void Zipper_ginhe_thread::Stop() {}
void Zipper_ginhe_thread::Exit(){}


#define ZipperRob Zipper_ginhe

/*
相关文章参考 ：
	//参考文章 https://blog.csdn.net/zhengliuguo/article/details/81370156
	//https://dawnarc.com/2016/03/ue4fstring%E5%B8%B8%E7%94%A8api/
	//https://zhuanlan.zhihu.com/p/375046731
*/