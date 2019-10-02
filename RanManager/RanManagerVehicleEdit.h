#pragma once


// CRanManagerVehicleEdit dialog
class	CRanManagerVehicleTab;
class CRanManagerVehicleEdit : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerVehicleEdit)

public:
	CRanManagerVehicleEdit(LOGFONT logfont);
	virtual ~CRanManagerVehicleEdit();

// Dialog Data
	enum { IDD = IDD_RM_VEHICLE_EDIT };

protected:
	CRanManagerVehicleTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerVehicleTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetVehicle(int nVehicleNum);
	void			GetVehicle(int nVehicleNum);
	void			GetOwner(int nChaNum);

public:
	CComboBox		m_cType;
	CComboBox		m_cStatus;
	CSliderCtrl		Slider_Battery;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonChgOwner();
	afx_msg void OnBnClickedButtonChgItem();
	afx_msg void OnBnClickedButtonV1Set();
	afx_msg void OnBnClickedButtonV2Set();
	afx_msg void OnBnClickedButtonV1Reset();
	afx_msg void OnBnClickedButtonV2Reset();
	afx_msg void OnBnClickedBtnEditSave();
	afx_msg void OnBnClickedBtnEditCancel();
	afx_msg void OnNMCustomdrawSliderVFull(NMHDR *pNMHDR, LRESULT *pResult);
};
