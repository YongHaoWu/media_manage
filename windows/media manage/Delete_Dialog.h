#pragma once


// Delete_Dialog �Ի���

class Delete_Dialog : public CDialog
{
	DECLARE_DYNAMIC(Delete_Dialog)

public:
	Delete_Dialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Delete_Dialog();

// �Ի�������
	 enum { IDD = IDD_DIALOG0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	bool delete_flag;
	afx_msg void OnBnClickedOk();
};
