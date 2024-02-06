
// MFC_DrawmanageDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC_Drawmanage.h"
#include "MFC_DrawmanageDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCDrawmanageDlg 对话框



CMFCDrawmanageDlg::CMFCDrawmanageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_DRAWMANAGE_DIALOG, pParent)
	,  LineWidth(0)
	, m_LineType(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDrawmanageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, LineWidth);
	DDX_Radio(pDX, IDC_RADIO1, m_LineType);
	DDX_Control(pDX, IDC_COMBO1, m_filled);
	DDX_Control(pDX, IDC_COMBO2, m_Mode);
}

BEGIN_MESSAGE_MAP(CMFCDrawmanageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCDrawmanageDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCDrawmanageDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCDrawmanageDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCDrawmanageDlg::OnBnClickedRadio2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMFCDrawmanageDlg::OnCbnSelchangeCombo1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCDrawmanageDlg::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CMFCDrawmanageDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// CMFCDrawmanageDlg 消息处理程序

BOOL CMFCDrawmanageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	LineColor = RGB(0, 0, 255);
	ShapeColor = RGB(255, 0, 0);
	LineWidth = 5;

	m_filled.AddString(TEXT("无填充"));
	m_filled.AddString(TEXT("有填充"));
	m_filled.SetCurSel(0);

	Mode = LineMode;
	m_Mode.AddString(TEXT("画线"));
	m_Mode.AddString(TEXT("画点"));
	m_Mode.AddString(TEXT("画矩形"));
	m_Mode.AddString(TEXT("画圆"));
	m_Mode.AddString(TEXT("自由绘图"));
	m_Mode.SetCurSel(0);

	UpdateData(false);


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCDrawmanageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCDrawmanageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCDrawmanageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCDrawmanageDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	CColorDialog colorDlg(LineColor);
	if (IDOK == colorDlg.DoModal()) {
		LineColor = colorDlg.GetColor();

	}
}


void CMFCDrawmanageDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
	CString str;
	str.Format(TEXT("%d"), LineWidth);
	MessageBox(str);

}


void CMFCDrawmanageDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	LineType = false;
}


void CMFCDrawmanageDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	LineType = true;
}


void CMFCDrawmanageDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_filled.GetCurSel();
	/*CString str;
	str.Format(TEXT("%d"), index);*/


	if (index == 0) {
		isfilled = false;
		MessageBox(TEXT("无填充"), TEXT("提示"));
	}
	else {
		isfilled = true;
		MessageBox(TEXT("有填充"), TEXT("提示"));
	}
	
}


void CMFCDrawmanageDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DownPoint = point;
	if (Mode == PointMode) {
		CClientDC dc(this); // 用于绘制的设备上下文
		dc.SetPixel(point.x, point.y, LineColor);
	}



	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCDrawmanageDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpPoint = point;
	switch (Mode)
	{
	case LineMode:
		DrawLine();
		break;
	case PointMode:
		break;
	case EllipseMode:
		DrawEllipse();
		break;
	case RectangleMode:
		break;
	case OwnerDrawMode:
		break;
	default:
		break;
	}
	
	
	
	
	
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCDrawmanageDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CColorDialog ShapeColorDlg(ShapeColor);
	if (IDOK == ShapeColorDlg.DoModal()) {
		ShapeColor = ShapeColorDlg.GetColor();

	}
}

void CMFCDrawmanageDlg::DrawLine()
{
	CClientDC dc(this); // 用于绘制的设备上下文
	CPen pen(LineType, LineWidth, LineColor);  //创建红色画笔
	CPen* poldPen = dc.SelectObject(&pen);  //选择画笔到设备
	dc.MoveTo(DownPoint.x, DownPoint.y);
	dc.LineTo(UpPoint.x, UpPoint.y);
	dc.SelectObject(poldPen);  //恢复原始画笔
}

void CMFCDrawmanageDlg::DrawEllipse()
{
	CClientDC dc(this);
	CPen outlinePen(LineType, LineWidth, LineColor);
	CPen* poldPen = dc.SelectObject(&outlinePen);
	CBrush* PoldBrush;
	CBrush fillbrush(ShapeColor);
	CBrush transparentBrush;
	transparentBrush.CreateStockObject(NULL_BRUSH);
	if (isfilled) {

		PoldBrush = dc.SelectObject(&fillbrush);
	}
	else {

		PoldBrush = dc.SelectObject(&transparentBrush);
	}



	dc.Ellipse(DownPoint.x, DownPoint.y, UpPoint.x, UpPoint.y);
	dc.SelectObject(poldPen);
	dc.SelectObject(PoldBrush);
}


void CMFCDrawmanageDlg::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_Mode.GetCurSel();
	if (index == 0) {
		Mode = LineMode;
		MessageBox(TEXT("画线"), TEXT("提示"));
	}
	else if(index ==1){
		Mode = PointMode;
		MessageBox(TEXT("画点"), TEXT("提示"));
	}
	else if (index == 2) {
		Mode = RectangleMode;
		MessageBox(TEXT("画矩形"), TEXT("提示"));
	}
	else if (index == 3) {
		Mode = EllipseMode;
		MessageBox(TEXT("画圆"), TEXT("提示"));
	}
	else if (index == 4) {
		Mode = OwnerDrawMode;
		MessageBox(TEXT("自由绘图"), TEXT("提示"));
	}
}
