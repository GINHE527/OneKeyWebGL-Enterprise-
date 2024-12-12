#pragma once
#include "CoreMinimal.h"
#include<iostream>
#include<winsock.h>
#include<vector>
#include<unordered_map>
#include "HAL/Runnable.h"
#pragma comment(lib,"ws2_32.lib")
#define BUFFER_SIZE 1024

//承载project表
struct ProjectList {
	//belong to ?
public:
	int belong;
	TArray<std::pair<int, FString>>list_;
	//初始化
	void init(const FString &info);
	void clear();
	void add(const FString& info);
	ProjectList() {};
	~ProjectList() {};
};

class Socket_Project : public FRunnable {
public:

	virtual bool Init() override;  // 初始化 runnable 对象
	virtual uint32 Run() override; // 运行 runnable 对象
	virtual void Stop() override;  // 停止 runnable 对象,线程提前终止时被调用
	virtual void Exit() override;  // 退出 runnable 对象
	
};




