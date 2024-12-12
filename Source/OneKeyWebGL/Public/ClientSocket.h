#pragma once
#include "CoreMinimal.h"
#include<iostream>
#include<winsock.h>
#include "HAL/Runnable.h"
#pragma comment(lib,"ws2_32.lib")
#define BUFFER_SIZE 1024

class Socket_Client : public FRunnable{
public :
	//��ȡ��ǰʵ��
	static Socket_Client* GetSocketIns(FString& username, FString& password);
	virtual bool Init() override;  // ��ʼ�� runnable ����
	virtual uint32 Run() override; // ���� runnable ����
	virtual void Stop() override;  // ֹͣ runnable ����,�߳���ǰ��ֹʱ������
	virtual void Exit() override;  // �˳� runnable ����

	virtual bool BeginToConnect();
	virtual bool toLogin(FString& username, FString& password);
	static int state;
private:
	
	Socket_Client(FString &username,FString password) {
		pwd = password;
		usr = username;
	};
	~Socket_Client() {
		Instance = nullptr;
		closesocket(client_socket);
		WSACleanup();
	};
	static Socket_Client* Instance;
	WSADATA wsaData;
	SOCKET client_socket;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];
	FString pwd;
	FString usr;
	static int uid;
};



