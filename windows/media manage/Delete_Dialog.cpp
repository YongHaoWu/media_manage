// Delete_Dialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "media_manage.h"
#include "Delete_Dialog.h"


// Delete_Dialog �Ի���

IMPLEMENT_DYNAMIC(Delete_Dialog, CDialog)

Delete_Dialog::Delete_Dialog(CWnd* pParent /*=NULL*/)
	: CDialog(Delete_Dialog::IDD, pParent)
	, delete_flag(false)
{

}

Delete_Dialog::~Delete_Dialog()
{
}

void Delete_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Delete_Dialog, CDialog)
	ON_BN_CLICKED(IDOK, &Delete_Dialog::OnBnClickedOk)
END_MESSAGE_MAP()


// Delete_Dialog ��Ϣ�������

void Delete_Dialog::OnBnClickedOk()
{
	delete_flag = true;
	OnOK();
}
