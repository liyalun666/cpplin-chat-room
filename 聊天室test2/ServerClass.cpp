#include "ServerClass.h"

using namespace std;

HANDLE HMute = CreateMutex(NULL, FALSE, NULL);//������

const int MaxNum = 100;//�ͻ����������

int CountNum = 0;//ͳ�Ƶ�ǰ�Ŀͻ�������

set<string> RoomIDs;//������з����

class ClntObject {//��ſͻ��˵�socket������ţ��ǳ�
private:

	SOCKET m_Socket;//�ͻ��˵�socket

	string m_RoomID;//���������

	string m_Name;//�ǳ�

public:

	ClntObject() {

	}
	ClntObject(SOCKET Socket) {
		m_Socket = Socket;
	}

	~ClntObject() {

	}

	SOCKET GetSocket() {//��ȡsocket
		return m_Socket;
	}

	void SetRoomID(string id) {//���ÿͻ������������
		m_RoomID = id;
	}

	string GetRoomID() {//��ȡ�ͻ������������
		return m_RoomID;
	}

	void SetName(string name) {//���ÿͻ����ǳ�
		m_Name = name;
	}

	string GetName() {//��ȡ�ͻ����ǳ�
		return m_Name;
	}
};

ClntObject Clnts[MaxNum];//����������ſͻ��˶��������

//��ȡ��ǰʱ�䣬����string����
string TimeNow() {
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	//תΪ�ַ���
	stringstream ss;

	//ss << std::put_time(std::localtime(&t), "%Y��%m��%d��%Hʱ%M��%S��");
	ss << std::put_time(std::localtime(&t), "%Y��%m��%d��%Hʱ%M��%S��");

	string time = ss.str() + '\n';

	return time;
}

/*�д�����Ҫд�������ˣ�������*/
void ShowRoom(ClntObject &Clnt, MsgType* msg) {
	string IDs;
	/*
		�����ˣ�
		���ܣ����յ�ShowRoom��Ϣ�����ͻ��˷������з����
	*/
	
	//������MsgTypeָ��תΪMsgShow����ָ��
	// 
	//�����з���ķ������Ϊ��Ϣ�����ÿͻ���
	for (set<string>::iterator it = RoomIDs.begin(); it != RoomIDs.end(); it++)
	{
		IDs += *it;
	}
	char ch[256];
	strcpy(ch, IDs.c_str());
	send(Clnt.GetSocket(), ch, strlen(ch), NULL);
}

/*�д�����Ҫд�������ˣ�������*/
void CreateRoom(ClntObject& Clnt, MsgType* msg) {

	char temp[256];//��ʱ���飬��Ÿÿͻ������ɹ���ʧ�ܵ���Ϣ

	MsgCreate* create = (MsgCreate*)msg;//������MsgTypeָ��תΪ����ָ��

	/*
		�����ˣ�������
		���ܣ����յ�CreateRoom��Ϣ�����ͻ��˷������ɹ���ʧ�ܵ���Ϣ
		������create���д������ķ���ź��ǳ�����
	*/

	//�ж��Ƿ��и÷��䣬��û�����½������ұ�����RoomIDs���¼�ǳƵ�Clnt��RoomID�����У�
	//���Ѵ��ڷ��䣬�򷢸��ÿͻ����½�����������Ϣ

	//�����ͬһ����&&�ǳ����ظ�����ȡ�ǳƳɹ�������¼�ǳƵ�Clnt��Name�����У�
	//�ǳ��ظ��򷢸��ÿͻ���ȡ��ʧ�ܵ���Ϣ
}

/*�д�����Ҫд�������ˣ����*/
void JoinRoom(ClntObject& Clnt, MsgType* msg) {

	char temp[256];//��ʱ���飬��Ÿÿͻ�����ɹ���ʧ�ܵ���Ϣ

	MsgJoin* join = (MsgJoin*)msg;//������MsgTypeָ��תΪ����ָ��

	/*
		�����ˣ�
		���ܣ����յ�JoinRoom��Ϣ�����ͻ��˷�����ɹ���ʧ�ܵ���Ϣ
		������join���д������ķ���ź��ǳ�����
	*/

	//������MsgTypeָ��תΪMsgCreate����ָ��

	//�ж��Ƿ��и÷��䣬���оͼ��룬��¼�ǳƵ�ClntObject��RoomID�����У�
	//��û�д˷��䣬�򷢸��ÿͻ����½�����������Ϣ

	//�����ͬһ����&&�ǳ����ظ�����ȡ�ǳƳɹ�������¼�ǳƵ�ClntObject��Name�����У�
	//�ǳ��ظ��򷢸��ÿͻ���ȡ��ʧ�ܵ���Ϣ
}

/*�д�����Ҫд�������ˣ�ũ�ֳ�*/
void LeaveRoom(ClntObject& Clnt, MsgType* msg) {

	char temp[256];//��ʱ���飬��Ÿÿͻ��뿪����Ϣ

	MsgLeave* leave = (MsgLeave*)msg;//������MsgTypeָ��תΪ����ָ��

	/*
		�����ˣ�
		���ܣ����յ�leave��Ϣ����ͬ����������ͻ��˷��ÿͻ����뿪����Ϣ
	*/

	//������MsgTypeָ��תΪMsgLeave����ָ��

	//���ÿͻ����뿪����Ϣ�����÷�������г�Ա

	//���ÿͻ��˵ķ���ź��ǳ��ÿ�
}

/*�д�����Ҫд�������ˣ����Ѿ�*/
void Talk(ClntObject& Clnt, char* temp1) {

	char temp[256] = { 0 };//��ʱ���飬��ŷ��������ͻ��˵���Ϣ

	memset(temp, 0, 256);//���

	WaitForSingleObject(HMute, INFINITE);
	/*
		�����ˣ�
		���ܣ����������Ϣ���͸�ͬ����������ͻ���
		����Ҫ���ǳƣ���Ϣ   ���� �����������ɶ��
	*/

	ReleaseMutex(HMute);
	}

unsigned WINAPI HandleClnt(void* Clnt) {//����Ĳ����ǿͻ��˶����ڿͻ��˶��������е�����

	ClntObject* Client = (ClntObject*)Clnt;
	
	char buff[256] = { 0 };//�������Կͻ��˵���Ϣ

	char temp[256] = { 0 };//��ʱ���飬���ڴ��buff�е���Ϣ

	while (true) {
		//�������Ըÿͻ��˵���Ϣ

		int Len = recv(Client->GetSocket(), buff, 255, 0);

			if (Len > 0) {

			buff[Len] = 0;//�����һλ����һλ��Ϊ0��������ȷ��ȡ����

			memset(temp, 0, 256);//���

			strcpy_s(temp, buff);//temp1���ڴ��buff�е���Ϣ

			MsgType* msg = (MsgType*)buff;//�����յ�����ϢתΪMsgType��

			//���ݷ��͵���Ϣ����MsgType��ͬ���в�ͬ�Ĵ���
			switch (msg->MsgType) {

				case MSG_SHOW: {

					ShowRoom(*Client, msg);
				}
						 break;

				case MSG_CREATE: {
					CreateRoom(*Client, msg);
				}
						 break;

				case MSG_JOIN: {
					JoinRoom(*Client, msg);
				}
						 break;

				case MSG_LEAVE: {
					WaitForSingleObject(HMute, INFINITE);

					LeaveRoom(*Client, msg);

					ReleaseMutex(HMute);
				}
						 break;

				default://Ĭ�Ͼ�˵������ָ��Ƿ��͵�������Ϣ
					Talk(*Client, temp);
					break;
				}

		}

	}

	return 0;
}

ServerClass::ServerClass() {
	//���������׽���
	ServSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//����TCP�׽���
	if (ServSock == SOCKET_ERROR) {
		cout << "�����׽��ִ���ʧ��" << endl;
		return;
	}

}

ServerClass::~ServerClass() {
	closesocket(ServSock);
	delete[] Clnts;
}

void ServerClass::Bind(const char* ip, unsigned short port) {

	sockaddr_in sock_in;// sockaddr_in�Ǳ���IPv4��ַ��Ϣ�Ľṹ��
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(port);//�˿�
	sock_in.sin_addr.S_un.S_addr = inet_addr(ip);//ip,ֵΪINADDR_ANYʱ���õ��Ƿ�������IP��ַ

	int ret = bind(ServSock, (const sockaddr*)&sock_in, sizeof(sock_in));//��(ip �� socket��)

	if (ret == SOCKET_ERROR) {
		cout << "���׽���ʧ��" << endl;
		return;
	}
	cout << "���׽��ֳɹ�" << endl;
}

void ServerClass::Listen() {

	if (listen(ServSock, 10) == SOCKET_ERROR) {//�������˴��ڶ���������˵ �ں�Ϊ ���׽���ά����������Ӹ���
		cout << "�����׽���ʧ��" << endl;
		return;
	}
	cout << "�����׽��ֳɹ�" << endl;
}

/*�д�����Ҫд�������ˣ����ҿ�*/
void ServerClass::Communication() {
	for (int i = 0; i < MaxNum; i++) {
		//���տͻ��˵�����
		sockaddr_in ClntAddr;
		int clen = sizeof(ClntAddr);

		//���ӿͻ���
		SOCKET ClntSock = accept(ServSock, (sockaddr*)&ClntAddr, &clen);

		if (ClntSock == SOCKET_ERROR) {
			cout << "���տͻ���ʧ��" << GetLastError() << endl;
			closesocket(ClntSock);
			return;
		}
		cout << "���ӿͻ���" << i << "�ɹ�" << endl;

		
		
		//������
		WaitForSingleObject(HMute, INFINITE);
		ClntObject* Clnt = new ClntObject(ClntSock);//������
		Clnts[i] = *Clnt;//������
		CountNum++;
		//���ӿͻ��˳ɹ�������ClntObeject���󣬽��������Clnts����

		ReleaseMutex(HMute);

		HANDLE hTheard = (HANDLE)_beginthreadex(0, 0, (_beginthreadex_proc_type)HandleClnt, (void*)&Clnts[i], 0, 0);

	}

}

SOCKET ServerClass::GetSocket() {
	return ServSock;
}