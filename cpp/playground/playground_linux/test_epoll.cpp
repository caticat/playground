#include "test_epoll.h"
#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace test_epoll
{
	using namespace std;

	void test()
	{
		// epoll初始化
		cout << "epoll初始化" << endl;
		int maxConn = 10;
		int fdEpoll = epoll_create(maxConn);
		epoll_event arrEvent[maxConn];

		// 监听socket初始化
		cout << "监听socket初始化" << endl;
		int fdListen = socket(AF_INET, SOCK_STREAM, 0);
		if (fdListen < 0)
		{
			cout << "创建socket失败" << endl;
			return;
		}
		int reuseaddr = 1;
		if (setsockopt(fdListen, SOL_SOCKET, SO_REUSEADDR, (char*)&reuseaddr, sizeof(reuseaddr)) != 0)
		{
			cout << "设置socket可重用失败" << endl;
			return;
		}
		epoll_event event;
		event.data.fd = fdListen;
		event.events = EPOLLIN;
		epoll_ctl(fdEpoll, EPOLL_CTL_ADD, event.data.fd, &event);
		sockaddr_in addrListen;
		memset(&addrListen, 0, sizeof(sockaddr_in));
		addrListen.sin_family = AF_INET;
		addrListen.sin_addr.s_addr = inet_addr("0.0.0.0");
		addrListen.sin_port = htons(2223);
		if (bind(fdListen, (sockaddr*)&addrListen, sizeof(addrListen)) != 0)
		{
			cout << "绑定监听地址端口失败" << endl;
			return;
		}
		if (listen(fdListen, 5) != 0)
		{
			cout << "开启监听失败" << endl;
			return;
		}

		// 循环处理
		cout << "开启监听与协议收发循环" << endl;
		int eventNum = 0;
		int bufferLen = 1024;
		char buffer[bufferLen];
		bool isRunning = true;
		while (isRunning)
		{
			eventNum = epoll_wait(fdEpoll, arrEvent, maxConn, 1000);
			if (eventNum < 0)
			{
				isRunning = false;
				cout << "网络错误,错误号:" << errno << endl;
			}
			else
			{
				for (int i = 0; i < eventNum; i++)
				{
					if (arrEvent[i].events & EPOLLIN)
					{
						if (arrEvent[i].data.fd == fdListen)
						{
							sockaddr_in addrClient;
							socklen_t addrClientLen = sizeof(sockaddr_in);
							int fdClient = accept(fdListen, (sockaddr*)&addrClient, &addrClientLen);
							if (fdClient < 0)
							{
								if ((errno != EAGAIN) && (errno != EINTR))
								{
									cout << "accept失败,错误号:" << errno << endl;
									isRunning = false;
								}
							}
							else
							{
								cout << "客户端[" << inet_ntoa(addrClient.sin_addr) << "]连接,sock[" << fdClient << "]" << endl;
								epoll_event event;
								event.data.fd = fdClient;
								event.events = EPOLLIN;
								epoll_ctl(fdEpoll, EPOLL_CTL_ADD, event.data.fd, &event);
							}
						}
						else
						{
							ssize_t readLen = recv(arrEvent[i].data.fd, buffer, bufferLen, 0);
							if (readLen < 0)
							{
								if ((errno != EAGAIN) && (errno != EINPROGRESS))
								{
									cout << "读取socket数据出错:" << errno << endl;
									epoll_ctl(fdEpoll, EPOLL_CTL_DEL, arrEvent[i].data.fd, &arrEvent[i]);
									close(arrEvent[i].data.fd);
								}
							}
							else if (readLen == 0)
							{
								cout << "正常关闭socket" << endl;
								epoll_ctl(fdEpoll, EPOLL_CTL_DEL, arrEvent[i].data.fd, &arrEvent[i]);
								close(arrEvent[i].data.fd);
							}
							else
							{
								buffer[readLen] = '\0';
								cout << "sock[" << arrEvent[i].data.fd << "]收到数据:" << buffer << endl;
								sprintf(buffer, "server return");
								int lenSend = send(arrEvent[i].data.fd, buffer, strlen(buffer), 0); // 这里的逻辑检测就不处理了
								cout << "发送数据长度:" << lenSend << endl;
							}
						}
					}
				}
			}
		}

		cout << "main结束" << endl;
	}
}
