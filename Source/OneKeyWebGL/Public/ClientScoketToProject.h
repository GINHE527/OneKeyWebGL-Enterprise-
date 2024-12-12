#pragma once
#include "CoreMinimal.h"
#include<iostream>
#include<winsock.h>
#include<vector>
#include<unordered_map>
#include "HAL/Runnable.h"
#pragma comment(lib,"ws2_32.lib")
#define BUFFER_SIZE 1024

//����project��
struct ProjectList {
	//belong to ?
public:
	int belong;
	TArray<std::pair<int, FString>>list_;
	//��ʼ��
	void init(const FString &info);
	void clear();
	void add(const FString& info);
	ProjectList() {};
	~ProjectList() {};
};

class Socket_Project : public FRunnable {
public:

	virtual bool Init() override;  // ��ʼ�� runnable ����
	virtual uint32 Run() override; // ���� runnable ����
	virtual void Stop() override;  // ֹͣ runnable ����,�߳���ǰ��ֹʱ������
	virtual void Exit() override;  // �˳� runnable ����
	
};




