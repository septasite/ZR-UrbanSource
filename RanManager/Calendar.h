#pragma once


// CCalendar dialog

class CCalendar : public CDialog
{
	DECLARE_DYNAMIC(CCalendar)

public:
	CCalendar(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCalendar();

// Dialog Data
	enum { IDD = IDD_CALENDAR };

public:
	SYSTEMTIME		sTime; 

	SYSTEMTIME	GetTime() {return sTime;}
	void SetTime (SYSTEMTIME sNewTime);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
