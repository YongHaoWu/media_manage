// media manage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//


#pragma once

#ifndef _meida
#define _media
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CmediamanageApp:
// �йش����ʵ�֣������ media manage.cpp
//

class CmediamanageApp : public CWinApp
{
public:
	CmediamanageApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmediamanageApp theApp;
#endif 