// Add_Dialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "media_manage.h"
#include "Add_Dialog.h"

Add_Dialog *add_dialog= new Add_Dialog;
// Add_Dialog �Ի���

IMPLEMENT_DYNAMIC(Add_Dialog, CDialog)



BOOL Add_Dialog::OnInitDialog()
{
	( (CComboBox*)GetDlgItem(IDC_COMBO1) )->AddString("x") ;//�������ȹ̶�һ���ؼ�������
	( (CComboBox*)GetDlgItem(IDC_COMBO1) )->AddString("��") ;
	//( (CComboBox*)GetDlgItem(IDC_COMBO1) )->AddString("����һ") ;
	//( (CComboBox*)GetDlgItem(IDC_COMBO1) )->AddString("���ڶ�") ;
	//( (CComboBox*)GetDlgItem(IDC_COMBO1) )->AddString("������") ;
	//( (CComboBox*)GetDlgItem(IDC_COMBO1) )->AddString("������") ;
	//( (CComboBox*)GetDlgItem(IDC_COMBO1) )->AddString("������") ;
	//( (CComboBox*)GetDlgItem(IDC_COMBO1) )->AddString("������") ;
	( (CComboBox*)GetDlgItem(IDC_COMBO1) )->SetCurSel( 0 );
	return TRUE;
}
Add_Dialog::Add_Dialog(CWnd* pParent /*=NULL*/)
: CDialog(Add_Dialog::IDD, pParent)
, name(_T(""))
, number(_T(""))
, flag(false)
{

}

Add_Dialog::~Add_Dialog()
{
}

void Add_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, name);//��ؼ��������� �ǳ���Ҫ��������dialogֱ���໥��������
	DDX_Text(pDX, IDC_EDIT2, number);
}


BEGIN_MESSAGE_MAP(Add_Dialog, CDialog)
	ON_BN_CLICKED(IDOK, &Add_Dialog::OnBnClickedOk)
END_MESSAGE_MAP()


// Add_Dialog ��Ϣ�������

void Add_Dialog::OnBnClickedOk()
{
	CEdit* pEdit; 
	pEdit = (CEdit*) GetDlgItem( IDC_EDIT1 ); 
	pEdit-> GetWindowText( add_dialog->name );
	if( add_dialog->name == "" )
		add_dialog->name = "δ����";
	pEdit = (CEdit*) GetDlgItem( IDC_EDIT2 );
	pEdit-> GetWindowText( add_dialog->number );

	( (CComboBox*)GetDlgItem(IDC_COMBO1) )->GetWindowText(update_remind_flag);


	//do 
	//{
	//	pEdit-> GetWindowText( add_dialog->number );
	//	if ( atoi(add_dialog->number)<0 )      ����
	//		MessageBox( "���������0������" );
	//} while ( atoi( add_dialog->number )<0 );
	flag = 1;
	AnimateWindow(100,AW_HIDE|AW_BLEND);      //���Ի�����ʧ���� 

	OnOK();
}

