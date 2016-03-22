// ListenSocket.cpp: implementation of the CListenSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KernelMonitorv1.h"
#include "ListenSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListenSocket::CListenSocket()
{
	//m_pAcceptedSocket = NULL;
	m_pDlgPointer = NULL;
	// --- jwj ---
	for (int i = 0; i < 1000; i++) {
		m_pAcceptedSocket_0[i] = NULL;
	}
	m_acceptCnt = 0;
	m_acceptIndex = 0;
	// --- jwj ---
}

CListenSocket::~CListenSocket()
{

}

void CListenSocket::OnAccept(int nErrorCode)
{
	// 连接整理
	if (m_acceptCnt < m_acceptIndex) // 下标与总连接数不匹配时整理
	{
		for(int i = 0; i < m_acceptIndex; i++)
		{
			if ((m_pAcceptedSocket_0[i] != NULL)
					&&(m_pAcceptedSocket_0[i]->m_hSocket == INVALID_SOCKET)) // 该连接已关闭
			{
				delete m_pAcceptedSocket_0[i];
				m_pAcceptedSocket_0[i] = NULL;
				for (int j = m_acceptIndex - 1; j > i; j--)
				{
					if ((m_pAcceptedSocket_0[j] != NULL)
						&&(m_pAcceptedSocket_0[j]->m_hSocket != INVALID_SOCKET)) // 该连接可用
					{
						m_pAcceptedSocket_0[i] = m_pAcceptedSocket_0[j];
						m_pAcceptedSocket_0[j] = NULL;
						m_acceptIndex--;
						break;
					}
				}
			}
		}
	}
	
	m_pAcceptedSocket_0[m_acceptIndex] = new CMonitorReceiveSocket(); // --- jwj ---
	
	if (!m_pAcceptedSocket_0[m_acceptIndex])
	{
		AfxMessageBox("There is a error when alloc memory for accepted socket!\n");
		return;
	}
	struct sockaddr_in _sa_tmp;
	int _len_tmp = sizeof(_sa_tmp);
	SOCKET hTemp = accept(m_hSocket, (struct sockaddr *)&_sa_tmp, &_len_tmp); // hTemp是重新生成的一个socket，来传输数据

	if(((CKernelMonitorv1Dlg*)m_pDlgPointer)->whiteList.size()>0&&inStringArray(((CKernelMonitorv1Dlg*)m_pDlgPointer)->whiteList,inet_ntoa(_sa_tmp.sin_addr))==false )
	{
		closesocket(hTemp);
		CString tmp=inet_ntoa(_sa_tmp.sin_addr);
		((CKernelMonitorv1Dlg*)m_pDlgPointer)->SendAndStoreMessage("Can't connect!"+(tmp));
		return;
	}
	if (hTemp != INVALID_SOCKET)
	{
		m_pAcceptedSocket_0[m_acceptIndex]->m_hSocket = hTemp;
		m_pAcceptedSocket_0[m_acceptIndex]->m_pDlgPointer = m_pDlgPointer;
		m_pAcceptedSocket_0[m_acceptIndex]->m_pListenSocket = this;	// 用于在CMonitorReceiveSocket中客户端连接计数
		if (SOCKET_ERROR == WSAEventSelect(m_pAcceptedSocket_0[m_acceptIndex]->m_hSocket, 
									m_pAcceptedSocket_0[m_acceptIndex]->m_hSocketEvent,
									FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE))
		{
			//delete m_pAcceptedSocket;
			//m_pAcceptedSocket = NULL;
			delete m_pAcceptedSocket_0[m_acceptIndex];
			m_pAcceptedSocket_0[m_acceptIndex] = NULL;
		}
		else
		{
			//m_pAcceptedSocket->Start(TRUE);
			//m_pAcceptedSocket->OnConnect(0);
			m_pAcceptedSocket_0[m_acceptIndex]->Start(TRUE);
			m_acceptCnt++;

			struct sockaddr_in _sa;
			int _len = sizeof(_sa);
			CString _ip, _port, _num;
			char _s[32];
			if(!getpeername(m_pAcceptedSocket_0[m_acceptIndex]->m_hSocket, (struct sockaddr *)&_sa, &_len))
			{
				//m_pAcceptedSocket_0[m_acceptIndex]->m_hSocket.close();
				_ip = inet_ntoa(_sa.sin_addr);
				_itoa_s(ntohs(_sa.sin_port), _s, 10);
				_port = _s;
				_itoa_s(m_acceptCnt, _s, 10);
				_num = _s;
				CString _msg = "Add New Client Ip:" + _ip + ", Port:" + _port + ", Num of Clients:" + _num;
				((CKernelMonitorv1Dlg*)m_pDlgPointer)->SendAndStoreMessage(_msg);
			}

			m_acceptIndex++;
			if (m_acceptCnt == 1000) {
				((CKernelMonitorv1Dlg*)m_pDlgPointer)->SendAndStoreMessage("Accepted sockets buffer is full!");
				return;
			}
		}
	}
	else
	{
		//delete m_pAcceptedSocket;
		//m_pAcceptedSocket = NULL;
		delete m_pAcceptedSocket_0[m_acceptIndex];
		m_pAcceptedSocket_0[m_acceptIndex] = NULL;
	}
}

void CListenSocket::OnClose(int nErrorCode)
{
	CloseConnection();
}

void CListenSocket::CloseConnection()
{
	for (int i = 0; i < m_acceptIndex; i++) {	// 1000
		if (m_pAcceptedSocket_0[i]) {
			if (m_pAcceptedSocket_0[i]->m_hSocket != INVALID_SOCKET)	// 否则说明连接已经提前关闭
			{
				m_pAcceptedSocket_0[i]->Stop(FALSE);	// ?
				m_acceptCnt = (m_acceptCnt > 0)? m_acceptCnt - 1 : 0;
				// 客户信息输出
				struct sockaddr_in _sa;
				int _len = sizeof(_sa);
				CString _ip, _port, _num;
				char _s[32];
				if(!getpeername(m_pAcceptedSocket_0[i]->m_hSocket, (struct sockaddr *)&_sa, &_len))
				{
					_ip = inet_ntoa(_sa.sin_addr);
					_itoa_s(ntohs(_sa.sin_port), _s, 10);_port = _s;
					_itoa_s(m_acceptCnt, _s, 10);_num = _s;
					CString _msg = "Delete Client Ip:" + _ip + ", Port:" + _port + ", Num of Clients:" + _num;
					((CKernelMonitorv1Dlg*)m_pDlgPointer)->SendAndStoreMessage(_msg);
				}
				m_pAcceptedSocket_0[i]->Close();// 关闭当前的接收socket，此时m_hSocket == INVALID_SOCKET
			}

			delete m_pAcceptedSocket_0[i];
			m_pAcceptedSocket_0[i] = NULL;
		}
	}
	m_acceptIndex = 0;
	m_acceptCnt = 0;
}
