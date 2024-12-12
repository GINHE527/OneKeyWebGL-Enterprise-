#include "ClientSocket.h"
#include "ClientScoketToProject.h"

#define PORT 8080
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1024
#endif
#define SERVER_IP "192.168.64.131"
int Socket_Client::state = -1;
Socket_Client* Socket_Client::Instance = nullptr;
int Socket_Client::uid = -1;
bool Socket_Client::Init() { 
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed" << std::endl;
		return false;
	}

	if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		std::cerr << "Socket creation failed" << std::endl;
		WSACleanup();
		return false;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // Use inet_pton if preferred

	if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "Connection failed" << std::endl;
		closesocket(client_socket);
		WSACleanup();
		return false;
	}
	return true; 
}


uint32 Socket_Client::Run() {
	if (toLogin(usr, pwd)) {
		Socket_Client::state = 1;
		UE_LOG(LogTemp, Log, TEXT("LoginCompletely"));
	}
	else {
		Socket_Client::state = 0;
		UE_LOG(LogTemp, Log, TEXT("LoginError"));
	}
	return 1;
}
void Socket_Client::Stop() {}
void Socket_Client::Exit() {}

Socket_Client* Socket_Client::GetSocketIns(FString &username ,FString &password) {
	if (Socket_Client::Instance == nullptr) {
		Socket_Client* new_ins = new Socket_Client(username,password);
		Socket_Client::Instance = new_ins;
		return new_ins;
	}
	else {
		return Socket_Client::Instance;
	}
}

bool Socket_Client::BeginToConnect() {
	


	return true;
}

bool Socket_Client::toLogin(FString &username, FString &passwrod) {
	
	FString send_message = "LOGIN " + username + " " + passwrod;
	std::string command = TCHAR_TO_UTF8(*send_message);
	send(client_socket, command.c_str(), command.length(), 0);
	memset(buffer, 0, BUFFER_SIZE);
	int valread = recv(client_socket, buffer, BUFFER_SIZE, 0);
	if (valread <= 0) {
		return false;
	}
	FString DebugSentence = UTF8_TO_TCHAR(buffer);
	UE_LOG(LogTemp, Log, TEXT("Login Buffer: %s"),*DebugSentence);
	
	return true;
}

//仅支持正整数
int32 IntPower(int32 index, int32 power) {
	if (power > 0)return index * IntPower(index, power - 1);
		return 1;
}

//解析info: 111 projectname1 + 3212 projectname2 + 36666 projectname3;
//双指针解锁 初始化
void ProjectList::init(const FString& info) {
	clear();
	ProjectList::add(info);
	return;
}

//列表添加， 意义和初始化一样 只不过不需要归零
void ProjectList::add(const FString& info) {
	int32 start = 0;
	int32 left = 0;
	int32 right = 0;
	int32 end = 0;
	int32 len = info.Len();
	while (end < len) {
		if (info[end] == '+' || end == len - 1) {
			int32 tempint = 0;
			FString tempstring;
			//先读取数字
			left = start;
			right = left;

			while (info[right] < '9' || info[right]> '0') {
				right++;
			}
			int32 mid = right - 1;
			//向后迭代
			for (right--; right >= left; right--) {
				int32 inter = info[right] - '0';
				tempint += inter * IntPower(10, mid - right);
			}

			//现在提取字符
			left = mid + 2;
			right = end - 2;
			//向前迭代
			for (left; left <= right; left++) {
				tempstring += info[left];
			}
			//赋值:
			this->list_.Add(std::make_pair(tempint,tempstring));
			//指针偏移
			start = end + 2;
			end = end + 2;
		}
		else end++;
	}
	return;
}
//清理
void ProjectList::clear() {
	this->list_.Empty();
	return;
}
