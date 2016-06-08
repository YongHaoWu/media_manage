// media manageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "media_manage.h"
#include "media_manageDlg.h"
#include "Add_Dialog.h"
#include "Delete_Dialog.h"
#include <algorithm>
#include <stdlib.h>
#include <afxinet.h>
#pragma comment(lib,"Winmm.lib")// ������

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CmediamanageDlg �Ի���


NOTIFYICONDATA nid;
CWinThread *check_url;

UINT _check_url(LPVOID lparam)
{
	CmediamanageDlg *pDlg = (CmediamanageDlg *)lparam;
	while(1)
	{
		pDlg->check_update();
		Sleep(1800000);//1800000
	}
	return 0;
}

CmediamanageDlg::CmediamanageDlg(CWnd* pParent /*=NULL*/)
: CDialog(CmediamanageDlg::IDD, pParent)
, choose(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmediamanageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_LBIndex(pDX, IDC_LIST4, (int&)choose);
	DDX_Control(pDX, IDC_BMP, m_image);
}

BEGIN_MESSAGE_MAP(CmediamanageDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	//}}AFX_MSG_MAP
	ON_LBN_SELCHANGE(IDC_LIST4, &CmediamanageDlg::OnLbnSelchangeList4)
	ON_BN_CLICKED(IDC_BUTTON1, &CmediamanageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CmediamanageDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CmediamanageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CmediamanageDlg::OnBnClickedButton3)
	ON_MESSAGE(WM_SHOWTASK, onShowTask )

	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK1, &CmediamanageDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CmediamanageDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CmediamanageDlg ��Ϣ�������

BOOL CmediamanageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	m_image.ModifyStyle( 0, SS_BITMAP | SS_CENTERIMAGE );//����̬�ؼ�����Ϊ��������ʾλͼ�ģ�ֻ����������ͨ���þ�̬�Ի���ı���������ModifyStyle������
	HBITMAP hBmp = (HBITMAP)::LoadImage( 0, "image.bmp", IMAGE_BITMAP, 188, 188, LR_LOADFROMFILE );//��bmp�ļ����ڵ�·��ֱ�Ӷ�ȡ��BMPͼ��ľ����������ת��ΪHBITMAP����
	m_image.SetBitmap( hBmp );//ͨ������m_image�����øþ�̬������ʾ��λͼ�ļ�

	read_config( );
	Load(example);
	flush();
	AnimateWindow(400,AW_ACTIVATE|AW_VER_POSITIVE); 

	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); //6.0.6 or higher (Windows Vista and later)//nid.cbSize=NOTIFYICONDATA_V3_SIZE;//xp

	nid.hWnd=this->m_hWnd;
	nid.uID=IDR_MAINFRAME;
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP|NIF_INFO;
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ����,ע��:�������Ϣ���û��Զ�����Ϣ
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));

	//strcpy(nid.szInfo, "ʲô����ϵͳ������" );//���ݱ���
	wcscpy_s((wchar_t*)nid.szTip,64,(wchar_t*)_T("��Ƶ����")); 
	wcscpy_s( (wchar_t*)nid.szInfoTitle, 64, (wchar_t*)_T("��Ƶ��������") );
	wcscpy_s((wchar_t*)nid.szInfo, 255,  (LPCWSTR)(LPCTSTR)update_list);
	//wcscpy_s(nid.szInfoTitle,_T("����"));
	nid.dwInfoFlags=NIIF_INFO;
	nid.uTimeout=99999;
	Shell_NotifyIcon(NIM_ADD,&nid);//�����������ͼ��
	check_url = ::AfxBeginThread(_check_url, this);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmediamanageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmediamanageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CmediamanageDlg::OnLbnSelchangeList4()//�����б�ʱ��ȡѡ�������
{	
	choose = ( (CListBox*)GetDlgItem(IDC_LIST4) )->GetCurSel();
}

void CmediamanageDlg::Save( std::vector<Media>&m )
{
	CStdioFile file( _T("file.txt"), CFile::modeCreate | CFile::modeWrite );//�ļ������ھʹ����ļ���������������ļ�
	for ( it=m.begin(); it!=m.end(); ++it )
	{ 
		file.WriteString( it->Name + "\n" );
		CString Temp; 
		Temp.Format("%s%d\n", Temp, it->Part);
		file.WriteString( Temp );
		file.WriteString( it->update_remind_flag + "\n" );
	}
	file.Close();
}

void CmediamanageDlg::Load(std::vector<Media> &m)
{
	CStdioFile file( _T("file.txt"), CFile::modeRead );
	CString Temp;
	Media newone;
	while( file.ReadString(newone.Name) )
	{
		file.ReadString( Temp );
		newone.Part=atoi( Temp );
		file.ReadString( newone.update_remind_flag );
		m.push_back( newone );
	}
	file.Close();
}
void CmediamanageDlg::OnBnClickedButton1()//����+1
{
	if( example.size()==0 )
		MessageBox("û����Ƶ");
	else if ( choose>=example.size() )
		MessageBox("û��ѡ����Ƶ");
	else
	{
		it = example.begin() + choose;
		++(it->Part);
		CString Temp; 
		Temp.Format(_T("%s\t%d\t"), Temp, it->Part);
		CString Output =  it->Name + Temp + it->update_remind_flag;
		( (CListBox*)GetDlgItem(IDC_LIST4) )->DeleteString(choose);
		( (CListBox*)GetDlgItem(IDC_LIST4) )->InsertString(choose, _T(Output) );
		Save(example);
	}
}

void CmediamanageDlg::OnBnClickedButton2()//����--1
{
	if( example.size()==0 )
		MessageBox("û����Ƶ");
	else if ( choose>=example.size() )
		MessageBox("û��ѡ����Ƶ");
	else
	{
		it = example.begin() + choose;
		if ( it->Part==0 )
			MessageBox("�����Ѿ�Ϊ0");
		else
		{
			--(it->Part);
			CString Temp; 
			Temp.Format(_T("%s\t%d\t"), Temp, it->Part);
			CString Output = it->Name + Temp + it->update_remind_flag;	
			( (CListBox*)GetDlgItem(IDC_LIST4) )->DeleteString(choose);
			( (CListBox*)GetDlgItem(IDC_LIST4) )->InsertString(choose, _T(Output) );
			Save(example);
		}
	}
}

//if( example.size()==0 )//ȫ��+1
//	MessageBox("û����Ƶ");
//else
//{
//	int number=0;
//	for ( it=example.begin(); it!=example.end(); ++it,++number )
//	{
//		++(it->Part);
//		CString Temp; 
//		Temp.Format(_T("%s\t%d"), Temp ,it->Part);
//		CString Output= it->Name  +  Temp ;
//		( (CListBox*)GetDlgItem(IDC_LIST4) )->DeleteString(number);
//		( (CListBox*)GetDlgItem(IDC_LIST4) )->InsertString(number,_T(Output) );
//	}
//	CmediamanageDlg::Save(example);
//}

void CmediamanageDlg::OnBnClickedButton3()//�����Ƶ
{

	Add_Dialog *add_dialog =new Add_Dialog;
	add_dialog->DoModal();
	if ( add_dialog->flag == true )
	{
		int number=0;
		for ( it=example.begin(); it!=example.end(); ++it,	++number);
		//for ( ; number>=0; --number )
		//	( (CListBox*)GetDlgItem(IDC_LIST4) )->DeleteString(number);

		Media newone;
		newone.Name = add_dialog->name; 
		newone.Part = atoi(add_dialog->number);
		newone.update_remind_flag = add_dialog->update_remind_flag; 
		example.push_back(newone);

		CmediamanageDlg::Save(example);
		CString Temp; 
		Temp.Format(_T("%s\t%d\t"), Temp, newone.Part);
		CString Output = newone.Name + Temp + newone.update_remind_flag;	
		( (CListBox*)GetDlgItem(IDC_LIST4) )->InsertString(number, _T(Output) );
	}
	//	add_dialog ->set_parent_dlg(this);  
}


void CmediamanageDlg::OnBnClickedButton4()//ɾ����Ƶ
{	
	if( example.size()==0 )
		MessageBox("û����Ƶ");
	else if ( choose>=example.size() )
		MessageBox("û��ѡ����Ƶ");
	else
	{
		Delete_Dialog *delete_dialog =new Delete_Dialog;
		delete_dialog->DoModal();
		if ( delete_dialog->delete_flag == true )
		{
			it = example.begin() + choose;
			example.erase(it);
			( (CListBox*)GetDlgItem(IDC_LIST4) )->DeleteString(choose);//ɾ����ʾ�Ķ���
			CmediamanageDlg::Save(example);
		}		
	}
}

void CmediamanageDlg::flush()//ˢ����ʾ
{
	//sort( example.begin(), example.end() );
	for( it = example.begin(); it != example.end(); ++it )
	{
		CString Output;
		Output.Format("%d",(it->Name).GetLength());
		if ((it->Name).GetLength()>=10)
			Output.Format(_T("%s\t%d\t%s"), it->Name  ,it->Part, it->update_remind_flag );
		else
			Output.Format(_T("%s\t\t%d\t%s"), it->Name  ,it->Part, it->update_remind_flag );
		( (CListBox*)GetDlgItem(IDC_LIST4) )->AddString( LPCTSTR(Output) ) ;
	}
}
//
//void CmediamanageDlg::check_update( )
//{
//	CTime time = CTime::GetCurrentTime(); //��ȡϵͳ����
//	int today_date = time.GetDayOfWeek(); //��ȡ���ڼ���ע��1Ϊ�����죬7Ϊ������
//	//	std::vector <CString> weeks( "������", "����һ"  );
//	/*weeks.push_back("����ʾ");weeks.push_back("������");weeks.push_back("����һ");weeks.push_back("���ڶ�");weeks.push_back("������");weeks.push_back("������");weeks.push_back("������");weeks.push_back("������");*/
//
//	CString weeks[] = { "����ʾ", "������", "����һ", "���ڶ�", "������", "������", "������", "������" };
//	bool flag = 0;
//	for( it = example.begin(); it!= example.end(); ++it )
//	{
//		if ( weeks[today_date] == it->update_remind_flag )
//		{
//			flag = 1;
//			CString Temp;
//			Temp.Format(_T("%s��%d��, "), Temp ,it->Part+1);
//			update_list =  update_list + it->Name + Temp ;
//		}
//	}
//	if ( flag==1 )
//	{
//		update_list += "�����ˣ�";
//		if( true==music_flag )
//		{
//			char program_path[128];
//			GetCurrentDirectory(MAX_PATH,program_path);
//			strcat_s(program_path, "\\music.wav");
//			/*	char buf[128];
//			MCI_OPEN_PARMS mciOpen; 
//			MCIERROR   mciError;   
//			mciOpen.lpstrDeviceType = "mpegvideo";   
//			mciOpen.lpstrElementName = program_path;
//			mciError = mciSendCommand( 0, MCI_OPEN,MCI_OPEN_TYPE   |   MCI_OPEN_ELEMENT,(DWORD)&mciOpen);   
//			if(mciError)   
//			{   
//			mciGetErrorString(mciError,buf,128);   
//			MessageBox("send MCI_PLAY command failed", "ERROR");    
//			return;   
//			}   */
//			PlaySound(program_path,NULL,SND_FILENAME|SND_ASYNC); //�첽����
//			//		PlaySound(program_path,NULL,SND_FILENAME|SND_SYNC);
//
//		}
//	}
//}


LRESULT CmediamanageDlg::onShowTask(WPARAM wParam,LPARAM lParam)//wParam���յ���ͼ���ID����lParam���յ���������Ϊ
{
	if(wParam!=IDR_MAINFRAME)
		return 1;
	switch(lParam)
	{
	case WM_RBUTTONUP:			//�Ҽ�����ʱ������ݲ˵�������ֻ��һ��"�ر�"
		{
			LPPOINT lpoint=new tagPOINT;
			::GetCursorPos(lpoint);			//�õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();				//����һ������ʽ�˵�			
			menu.AppendMenu(MF_STRING,WM_DESTROY,_T("�ر�"));   //���Ӳ˵���"�ر�"�����������ϢWM_DESTROY�������ڣ������أ��������������			
			menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this);//ȷ������ʽ�˵���λ��			
			SetForegroundWindow();
			HMENU hmenu=menu.Detach();   //��Դ����
			menu.DestroyMenu();
			delete lpoint;
		}break;
	case WM_LBUTTONDBLCLK:    //˫������Ĵ���
		{
			this->ShowWindow(SW_SHOW);    //�򵥵���ʾ���������¶�
		}
		break;
	}
	return 0;
}


void CmediamanageDlg::OnClose()
{
	AnimateWindow(500,AW_HIDE|AW_BLEND); 
	this->ShowWindow(SW_HIDE);
}

void CmediamanageDlg::OnDestroy()
{
	CDialog::OnDestroy();
	Shell_NotifyIcon(NIM_DELETE,&nid);//��������ͼ��
}


void  CmediamanageDlg::read_config( )
{
	CButton* startup_pBtn = (CButton*)GetDlgItem( IDC_CHECK1 );//��ȡ�Ƿ񿪻��Զ����� 
	CStdioFile file(_T("config.txt"), CFile::modeRead );
	CString Temp; 
	file.ReadString( Temp );
	startup_flag = atoi( Temp );
	startup_pBtn->SetCheck( startup_flag );

	CButton* music_pBtn = (CButton*)GetDlgItem( IDC_CHECK2 );//��ȡ�Ƿ񲥷���ʾ����
	file.ReadString( Temp );
	music_flag = atoi( Temp );
	music_pBtn->SetCheck(music_flag);
	file.Close();
}
void CmediamanageDlg::OnBnClickedCheck1()//�޸Ŀ����Զ�����
{

	CStdioFile file( _T("config.txt"), CFile::modeCreate | CFile::modeWrite );//�ļ������ھʹ����ļ���������������ļ�
	//	startup_flag_Temp.Format("%s%d\n", startup_flag_Temp, startup_flag );
	//	file.WriteString(startup_flag_Temp);

	TCHAR path[MAX_PATH];
	CString keyStr;
	CString fileName;
	HKEY hRegKey;
	GetModuleFileName(NULL,path,sizeof(path));
	CString strPath = path;
	keyStr =_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if(RegOpenKey(HKEY_LOCAL_MACHINE,keyStr,&hRegKey) !=  ERROR_SUCCESS)
		return ;
	_wsplitpath((wchar_t*)strPath.GetBuffer(0),NULL,NULL,(wchar_t*)fileName.GetBufferSetLength(MAX_PATH+1),NULL);
	if ( startup_flag )
	{
		file.WriteString(_T("0\n"));//����������
		startup_flag = 0;
		RegDeleteValue ( hRegKey, fileName );   
	}
	else
	{
		file.WriteString(_T("1\n"));//��������
		startup_flag = 1;
		if( !::RegSetValueEx(hRegKey, fileName, 0, REG_SZ, (CONST BYTE *)strPath.GetBuffer(0), strPath.GetLength() ) != ERROR_SUCCESS )
			return;
		strPath.ReleaseBuffer();
	}
	RegCloseKey( hRegKey );

	CString music_flag_Temp;
	music_flag_Temp.Format("%s%d\n", music_flag_Temp, music_flag );
	file.WriteString( music_flag_Temp );

	//if ( music_flag )
	//	file.WriteString(_T("1\n"));//����������
	//else
	//	file.WriteString(_T("0\n"));//��������

	file.Close();
}

void CmediamanageDlg::OnBnClickedCheck2()// ������ʾ��
{
	CStdioFile file( _T("config.txt"), CFile::modeCreate | CFile::modeWrite );//�ļ������ھʹ����ļ���������������ļ�
	if ( startup_flag )
		file.WriteString(_T("1\n"));
	else
		file.WriteString(_T("0\n")); 

	if ( music_flag )
	{
		file.WriteString(_T("0\n"));//����������
		music_flag = 0;
	}
	else
	{
		file.WriteString(_T("1\n"));//��������
		music_flag = 1;
	}

	file.Close();
}

void CmediamanageDlg::check_update()
{
	CInternetSession session; 
	CHttpFile* pfile = (CHttpFile *)session.OpenURL("http://110.75.189.200/chris/calculator/pc_latest.php");   
	DWORD status_code;    
	pfile -> QueryInfoStatusCode(status_code);
	if(status_code == HTTP_STATUS_OK)    
	{      
		CString update_name;
		//	AfxMessageBox("get in");
		if( pfile->ReadString(update_name) )
		{
			bool flag = 0;
			char *pStr = update_name.GetBuffer(update_name.GetLength()); //ȡ��str�����ԭʼ�ַ���
			int nBufferSize = MultiByteToWideChar(CP_UTF8, 0, pStr, -1, NULL, 0); //ȡ�����軺��Ķ���
			wchar_t *pBuffer = (wchar_t*)malloc(nBufferSize * sizeof(wchar_t));//���뻺��ռ�
			MultiByteToWideChar(CP_UTF8, 0, pStr, -1 , pBuffer, nBufferSize*sizeof(wchar_t));//ת��

			char* mbs = new char[ nBufferSize*sizeof(wchar_t) ];
			WideCharToMultiByte( CP_ACP, 0, pBuffer, -1, mbs, nBufferSize*sizeof(wchar_t), NULL, NULL);  
			char *tokens = strtok(mbs,"@");
			update_list = "";
			while(tokens)
			{
				for( it = example.begin(); it!= example.end(); ++it )
				{
					if ( it->Name == tokens && it->update_remind_flag!="����ʾ" )
					{
						flag = 1;
						if(update_list != "")
							update_list =  update_list + "��" +tokens;
						else
							update_list = tokens;
					}
				}
				tokens = strtok(NULL,"@");
			}
			if ( flag==1 )
			{
				update_list += " �����ˣ�";
				if( true==music_flag )
				{
					char program_path[128];
					GetCurrentDirectory(MAX_PATH,program_path);
					strcat_s(program_path, "\\music.wav");
					PlaySound(program_path,NULL,SND_FILENAME|SND_ASYNC); //�첽����
				}
				AfxMessageBox(update_list);
			}
			delete[] mbs;
			free(pBuffer); //�ͷŻ���
		}

	}
	pfile -> Close();    
	delete pfile;    
	session.Close();  
}