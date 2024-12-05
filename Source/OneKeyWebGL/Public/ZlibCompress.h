
#pragma once
#define ZLIB_WINAPI
#include "CoreMinimal.h"
#include <string>
#include <Shlwapi.h> 
#include "zip.h"
#include "unzip.h"
#include "zlib.h"

#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "zlibstat.lib")
// bool CompressDirectory(const FString& DirectoryPath, const FString& OutputPath)
// {
//     // Get the platform file system
//     IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
// 
//     // Check if the directory exists
//     if (!PlatformFile.DirectoryExists(*DirectoryPath))
//     {
//         UE_LOG(LogTemp, Error, TEXT("Directory does not exist: %s"), *DirectoryPath);
//         return false;
//     }
// 
//     // Buffer to store data
//     FBufferArchive Archive;
// 
//     // Gather all files in the directory
//     TArray<FString> FileNames;
//     PlatformFile.FindFilesRecursively(FileNames, *DirectoryPath, nullptr);
// 
//     for (const FString& FilePath : FileNames)
//     {
//         // Load file contents
//         TArray<uint8> FileData;
//         if (FFileHelper::LoadFileToArray(FileData, *FilePath))
//         {
//             // 写入文件名长度和文件名
//             FString FFFPath = FilePath;
//             FString RelativeFilePath = FPaths::MakePathRelativeTo(FFFPath, *DirectoryPath);
//             int32 FileNameLength = RelativeFilePath.Len();
//             Archive << FileNameLength;
//             Archive.Serialize((void*)*RelativeFilePath, FileNameLength * sizeof(TCHAR));
// 
//             // Write file data length and file data
//             int32 FileDataSize = FileData.Num();
//             Archive << FileDataSize;
//             Archive.Serialize(FileData.GetData(), FileDataSize);
//         }
//         else
//         {
//             UE_LOG(LogTemp, Warning, TEXT("Failed to load file: %s"), *FilePath);
//         }
//     }
// 
//     // Compress the archive
//     TArray<uint8> CompressedData;
//     FArchiveSaveCompressedProxy Compressor(CompressedData, ECompressionFlags::COMPRESS_ZLIB);
//     Compressor << Archive;
//     Compressor.Flush();
// 
//     // Save compressed data to disk
//     return FFileHelper::SaveArrayToFile(CompressedData, *OutputPath);
// }

#define PTRLOG(contentlog) UE_LOG(LogTemp,Warning,TEXT(contentlog)) 

bool nyAddfiletoZip(zipFile zfile, const std::string& fileNameinZip, const std::string& srcfile)
{
    // 目录如果为空则直接返回
    if (NULL == zfile || fileNameinZip.empty())
    {
        return 0;
    }

    int nErr = 0;
    zip_fileinfo zinfo = { 0 };
    tm_zip tmz = { 0 };
    zinfo.tmz_date = tmz;
    zinfo.dosDate = 0;
    zinfo.internal_fa = 0;
    zinfo.external_fa = 0;

    char sznewfileName[MAX_PATH] = { 0 };
    memset(sznewfileName, 0x00, sizeof(sznewfileName));
    strcat_s(sznewfileName, fileNameinZip.c_str());
    if (srcfile.empty())
    {
        strcat_s(sznewfileName, "\\");
    }

    nErr = zipOpenNewFileInZip(zfile, sznewfileName, &zinfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED, Z_DEFAULT_COMPRESSION);
    if (nErr != ZIP_OK)
    {
        return false;
    }
    if (!srcfile.empty())
    {
        // 打开源文件
        FILE* srcfp = _fsopen(srcfile.c_str(), "rb", _SH_DENYNO);
        if (NULL == srcfp)
        {
            PTRLOG("Cant open source file(ignore when compressing document )");
            return false;
        }

        // 读入源文件写入zip文件
        int numBytes = 0;
        char* pBuf = new char[1024 * 100];
        if (NULL == pBuf)
        {
            PTRLOG("cant create temp zone");
            return 0;
        }
        while (!feof(srcfp))
        {
            memset(pBuf, 0x00, sizeof(pBuf));
            numBytes = fread(pBuf, 1, sizeof(pBuf), srcfp);
            nErr = zipWriteInFileInZip(zfile, pBuf, numBytes);
            if (ferror(srcfp))
            {
                break;
            }
        }
        delete[] pBuf;
        fclose(srcfp);
    }
    zipCloseFileInZip(zfile);

    return true;
}

bool nyCollectfileInDirtoZip(zipFile zfile, const std::string& filepath, const std::string& parentdirName)
{
    if (NULL == zfile || filepath.empty())
    {
        return false;
    }
    bool bFile = false;
    std::string relativepath = "";
    WIN32_FIND_DATAA findFileData;

    char szpath[MAX_PATH] = { 0 };
    if (::PathIsDirectoryA(filepath.c_str()))
    {
        strcpy_s(szpath, sizeof(szpath) / sizeof(szpath[0]), filepath.c_str());
        int len = strlen(szpath) + strlen("\\*.*") + 1;
        strcat_s(szpath, len, "\\*.*");
    }
    else
    {
        bFile = true;
        strcpy_s(szpath, sizeof(szpath) / sizeof(szpath[0]), filepath.c_str());
    }

    HANDLE hFile = ::FindFirstFileA(szpath, &findFileData);
    if (NULL == hFile)
    {
        return false;
    }
    do
    {
        if (parentdirName.empty())
            relativepath = findFileData.cFileName;
        else
            // 生成zip文件中的相对路径
            relativepath = parentdirName + "\\" + findFileData.cFileName;

        // 如果是目录
        if (findFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
        {
            // 去掉目录中的.当前目录和..前一个目录
            if (strcmp(findFileData.cFileName, ".") != 0 && strcmp(findFileData.cFileName, "..") != 0)
            {
                nyAddfiletoZip(zfile, relativepath, "");

                char szTemp[MAX_PATH] = { 0 };
                strcpy_s(szTemp, filepath.c_str());
                strcat_s(szTemp, "\\");
                strcat_s(szTemp, findFileData.cFileName);
                nyCollectfileInDirtoZip(zfile, szTemp, relativepath);
            }
            continue;
        }
        char szTemp[MAX_PATH] = { 0 };
        if (bFile)
        {
            //注意：处理单独文件的压缩
            strcpy_s(szTemp, filepath.c_str());
        }
        else
        {
            //注意：处理目录文件的压缩
            strcpy_s(szTemp, filepath.c_str());
            strcat_s(szTemp, "\\");
            strcat_s(szTemp, findFileData.cFileName);
        }

        nyAddfiletoZip(zfile, relativepath, szTemp);

    } while (::FindNextFileA(hFile, &findFileData));
    FindClose(hFile);

    return true;
}

/*
* 函数功能 : 压缩文件夹到目录
* 备    注 : dirpathName 源文件/文件夹
*      zipFileName 目的压缩包
*      parentdirName 压缩包内名字(文件夹名)
*/
bool nyCreateZipfromDir(const std::string& dirpathName, const std::string& zipfileName, const std::string& parentdirName)
{
    bool bRet = false;

    /*
    APPEND_STATUS_CREATE    创建追加
    APPEND_STATUS_CREATEAFTER 创建后追加（覆盖方式）
    APPEND_STATUS_ADDINZIP    直接追加
    */
    zipFile zFile = NULL;
    if (!::PathFileExistsA(zipfileName.c_str()))
    {
        zFile = zipOpen(zipfileName.c_str(), APPEND_STATUS_CREATE);
    }
    else
    {
        zFile = zipOpen(zipfileName.c_str(), APPEND_STATUS_ADDINZIP);
    }
    if (NULL == zFile)
    {
        PTRLOG("cant create zip");
        return bRet;
    }

    if (nyCollectfileInDirtoZip(zFile, dirpathName, parentdirName))
    {
        bRet = true;
    }

    zipClose(zFile, NULL);

    return bRet;
}

bool ToZippedd(const FString& InFolderPath, const FString& OutFolderPath , const FString& ProjectName)
{
    std::string dirpath = TCHAR_TO_UTF8(*InFolderPath);                   // 源文件/文件夹
    std::string zipfileName = TCHAR_TO_UTF8(*OutFolderPath);           // 目的压缩包
    static const std::string  projectname = TCHAR_TO_UTF8(*ProjectName);
    bool ref = nyCreateZipfromDir(dirpath, zipfileName, projectname);          // 包内文件名<如果为空则压缩时不指定目录>
    return ref;

}

#undef PTRLOG