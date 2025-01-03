﻿// DlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "afxdialogex.h"
#include "DlgImage.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLGIMAGE, pParent)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_UP_PARENT, &CDlgImage::OnBnClickedBtnUpParent)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

#include "gPrjDlg.h"
void CDlgImage::OnBnClickedBtnUpParent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	static int n = 100;
	CgPrjDlg* pDlg = (CgPrjDlg*)m_pParent;
	pDlg->callFunc(n++);
}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//AfxMessageBox(_T("ready?"));


	MoveWindow(0, 0, 640, 480);


	InitImage();
	//int nWidth = 640;
	//int nHeight = 480;
	//int nBpp = 8;

	//m_Image.Create(nWidth, -nHeight, nBpp);
	//if (nBpp == 8) {
	//	static RGBQUAD rgb[256];
	//	for (int i = 0; i < 256; i++)
	//		rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
	//	m_Image.SetColorTable(0, 256, rgb);
	//}

	//int nPitch = m_Image.GetPitch();
	//unsigned char* fm = (unsigned char*)m_Image.GetBits();

	//memset(fm, 0xff, nWidth * nHeight);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}



void CDlgImage::InitImage()
{
	int nWidth = 4096*8;
	int nHeight = 4096*8;
	int nBpp = 8;

	m_Image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}

void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}

	drawData(&dc);
}

// define문은 일반적으로 framework.h
//#define COLOR_RED RGB(0xff, 0, 0)
//#define COLOR_GREEN RGB(0, 0xff, 0)

void CDlgImage::drawData(CDC* pDC)
{
	//srand(static_cast<unsigned>(time(nullptr))); // 난수 시드 초기화

	CRect rect;

	//CBrush brush(RGB(200, 200, 200));   // 회색 브러시 생성
	//CBrush* pOldBrush = pDC->SelectObject(&brush);   // 기존 브러시를 저장

	CPen pen(PS_SOLID, 2, COLOR_RED);   // 빨간색 테두리
	CPen* pOldPen = pDC->SelectObject(&pen);   // 기존 테두리를 저장

	for (int i = 0; i < m_nDataCount; i++) {
		rect.SetRect(m_ptData[i], m_ptData[i]);
		//int nRan = rand() % 16 + 5;   // 랜덤값 생성 (범위: 5 ~ 20)
		rect.InflateRect(1, 1);
		//rect.InflateRect(nRan, nRan);
		pDC->Ellipse(rect);
	}

	//pDC->SelectObject(pOldBrush);   // 이전 브러시 복원
	pDC->SelectObject(pOldPen);   // 이전 펜 복원
}
