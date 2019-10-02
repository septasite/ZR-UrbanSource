#pragma once


// CRanManagerVehicleDefault dialog
class	CRanManagerVehicleTab;
class CRanManagerVehicleDefault : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerVehicleDefault)

public:
	CRanManagerVehicleDefault(LOGFONT logfont);
	virtual ~CRanManagerVehicleDefault();

// Dialog Data
	enum { IDD = IDD_RM_VEHICLE_BLANK };

protected:
	CRanManagerVehicleTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerVehicleTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetVehicle(int nVehicleNum);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};
