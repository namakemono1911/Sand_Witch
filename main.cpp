/*****************************************************************************
main.cpp
Aythor	: ���@��
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include <time.h>
#include "main.h"
#include "polygon.h"
#include "input.h"
#include "sound.h"
#include "particle.h"
#include "fade.h"
#include "bg.h"
#include "game.h"
#include "title.h"
#include "stageselect.h"
#include "result.h"

#include "inputX.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define CLASS_NAME	"sand which"	//�E�B���h�E�̃N���X��
#define WINDOW_NAME	"sand which"	//�E�B���h�E�̖��O

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT init (HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void uninit ( void );
void update ( void );
void draw ( void );

#ifdef _DEBUG
void drawFPS ( void );
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3D9			g_PD3D = NULL;				//Direct3D�C���^�[�t�F�C�X
LPDIRECT3DDEVICE9	g_PD3DDevice = NULL;		//Direct3D�f�o�C�X�̃|�C���^
int		g_nCountFPS = NULL;		//FPS�J�E���^�[
MODE	g_mode = MODE_NULL;		//�Q�[���V�[���J�ڕϐ�

//�f�o�b�O�p�ϐ�
#ifdef _DEBUG
LPD3DXFONT g_pFont = NULL;	//�t�H���g�ւ̃C���^�[�t�F�[�X
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
//�֐���	: WinMain
//�Ԃ�l	: 
//����		: �E�B���h�E�̐ݒ�
//////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	//�ϐ��錾
	HWND hWnd;
	MSG msg;

	DWORD dwFrameCount;
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	
	//srand��seed�ݒ�
	srand((unsigned int)time(NULL));

	//�`��E�B���h�E�T�C�Y�ݒ�
	RECT cr = {10, 10, SCREEN_WIDTH, SCREEN_HEIGHT};
	DWORD style = WS_OVERLAPPEDWINDOW;
	AdjustWindowRect(&cr, style, FALSE);

	//�f�X�N�g�b�v�̃T�C�Y�擾
	RECT dr;
	GetWindowRect(GetDesktopWindow(), &dr);

	int ww = cr.right - cr.left;				//�E�B���h�E�̕�
	int wh = cr.bottom - cr.top;				//�E�B���h�E�̍���

	int dw = dr.right - dr.left;				//�f�X�N�g�b�v�̕�
	int dh = dr.bottom - dr.top;				//�f�X�N�g�b�v�̍���

	int wx = ww > dw ? 0 : (dw - ww) / 2;		//�f�X�N�g�b�v�̕\���ʒuX
	int wy = wh > dh ? 0 : (dh - wh) / 2;		//�f�X�N�g�b�v�̕\���ʒuY

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);				//WNDCLASSEX�̃������T�C�Y���w��
	wcex.style			= CS_CLASSDC;						//�\������E�B���h�E�̃X�^�C����ݒ�
	wcex.lpfnWndProc	= WndProc;							//�E�B���h�E�v���V�[�W���̃A�h���X�i�֐����j���w�肷��
	wcex.cbClsExtra		= 0;								//�ʏ�͎g�p���Ȃ��̂�"0"���w��
	wcex.cbWndExtra		= 0;								//�ʏ�͎g�p���Ȃ��̂�"0"���w��
	wcex.hInstance		= hInstance;						//WinMain�̃p�����[�^�̃C���X�^���X�n���h��
	wcex.hIcon			= NULL;								//�g�p����A�C�R�����w��iWindows�������Ă���
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);		//�}�E�X�J�[�\�����w��
	wcex.hbrBackground	= (HBRUSH) (COLOR_WINDOW + 1);		//�E�B���h�E�̃N���C�A���g�̈�̔w�i�F���w��
	wcex.lpszMenuName	= NULL;								//Window�ɂ��郁�j���[��ݒ�
	wcex.lpszClassName	= CLASS_NAME;						//�E�B���h�E�N���X�̖��O
	wcex.hIconSm		= NULL;								//�������A�C�R�����w�肳�ꂽ�ꍇ�̏����L�q

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E���쐬
	hWnd = CreateWindowEx(0,		//�g���E�B���h�E�X�^�C��
		CLASS_NAME, WINDOW_NAME,	//�E�B���h�E�N���X�̖��O
		WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME),		//���E�B���h�E�X�^�C��
		wx,							//�E�B���h�E�̍���X���W
		wy,							//�E�B���h�E�̍���Y���W
		ww,							//�E�B���h�E�̕�
		wh,							//�E�B���h�E�̍���
		NULL,						//�e�E�B���h�E�̃n���h��
		NULL,						//���j���[�n���h���܂��͎q�E�B���h�EID
		hInstance,					//�C���X�^���X
		NULL);						//�E�B���h�E�쐬�f�[�^

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);		//�w�肳�ꂽ�E�B���h�E��\��
	UpdateWindow(hWnd);				//�E�B���h�E�X�V
	

	//�ϐ�������
	if(FAILED(init(hInstance, hWnd, TRUE)))
	{
		MessageBox(hWnd, "���������s", "�G���[", MB_RIGHT);
		return 0;
	}

	//����\�ݒ�
	timeBeginPeriod(1);

	//�e�J�E���^�[�̏�����
	dwCurrentTime = 0;
	dwFrameCount = 0;
	dwExecLastTime = timeGetTime();
	dwFPSLastTime = timeGetTime();
	
#if _DEBUG
		//�����t�H���g�ݒ�
		D3DXCreateFont(g_PD3DDevice,
			18, 
			0, 
			0, 
			0, 
			FALSE, 
			SHIFTJIS_CHARSET, 
			OUT_DEFAULT_PRECIS, 
			DEFAULT_QUALITY, 
			DEFAULT_PITCH, 
			"Tarminal", 
			&g_pFont);
#endif //_DEDBUG

	//���b�Z�[�W���[�v
	for(;;)
	{
		//�������Ԏ擾
		dwCurrentTime = timeGetTime();

		//FPS�擾
		if((dwCurrentTime - dwFPSLastTime) >= 500)
		{
			g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
			dwFPSLastTime = dwCurrentTime;
			dwFrameCount = 0;
		}

		if(dwCurrentTime - dwExecLastTime >= 1000 / 60)
		{
			//�����������Ԏ擾
			dwExecLastTime = dwCurrentTime;

			if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
			{

				//Windows�̏���
				if(msg.message == WM_QUIT)
				{
					break;
				}
				else
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}

			//Directx�̏���
			update();
			draw();

			dwFrameCount++;
		}
	}
	
	uninit();
	return (int)msg. wParam;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: WndProc
//�Ԃ�l	: 
//����		: �E�B���h�E�v���V�[�W��
//			  (CALLBACK : Win32API�֐����Ăяo���Ƃ��̋K��
//			  hWnd		: �E�B���h�E�̃n���h��
//			  uMsg		: ���b�Z�[�W�̎��ʎq
//			  wParam	: ���b�Z�[�W�̍ŏ��̃p�����[�^
//			  lParam	: ���b�Z�[�W��2�Ԗڂ̃p�����[�^
//////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//��M���b�Z�[�W����
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			//�Z�[�u�̊m�F�]�n
			PostQuitMessage(0);
			break;
		}
		
	case WM_KEYDOWN:
		{
			switch(wParam)
			{
			case VK_ESCAPE:
				{
					UINT ID = MessageBox(NULL, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_ICONEXCLAMATION);
					if(ID == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				}
			}
		}

	default:
		{
			break;
		}
	}
	
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//////////////////////////////////////////////////////////////////////////////
//�֐���	: Init
//�Ԃ�l	: 
//����		: ����������
//////////////////////////////////////////////////////////////////////////////
HRESULT init (HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�ϐ��錾
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	//Direct3D�C���^�[�t�F�C�X�̎擾
	g_PD3D = Direct3DCreate9(D3D9b_SDK_VERSION);

	if(g_PD3D == NULL)
	{
		return E_FAIL;
	}

	if(FAILED(g_PD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���g�p�����[�^�[�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	//Direct3D�f�o�C�X�̍쐬
	if(FAILED(g_PD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp, &g_PD3DDevice)))
	{
		//�n�[�h�E�F�A�ŕ`��ł��Ȃ������璸�_������software�`�悪hardware�ŏ���
		if(FAILED(g_PD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &g_PD3DDevice)))
		{
			//�ŏI��i�A�S��software�ŏ���
			if(FAILED(g_PD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,&d3dpp, &g_PD3DDevice)))
			{
				return E_FAIL;
			}
		}

	}

	//�f�o�C�X�̏�����
	initDevice();

	//�L�[�{�[�h�ݒ�̏�����
	InitKeyboard(hInstance, hWnd);

	//�T�E���h�̏�����
	InitSound(hWnd);

	//�t�F�[�h������
	initFade();

	//bg������
	initBg();

	//��ʑJ�ڏ�����
	setMode(TITLE_MODE);

	// XInput������
	InitXInput();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninit
//�Ԃ�l	: 
//����		: �I������
//////////////////////////////////////////////////////////////////////////////
void uninit ( void )
{
	//�L�[�{�[�h�I��
	UninitKeyboard();

	//�T�E���h�I��
	UninitSound();

	//�t�F�[�h�I��
	uninitFade();
	
	//XInput�I��
	UninitXInput();

	//���݂̓����Ă��郂�[�h�I��
	setMode(MODE_NULL);

	//Direct3D�f�o�C�X�̉��
	if(g_PD3DDevice != NULL)
	{
		g_PD3DDevice->Release();
		g_PD3DDevice = NULL;
	}

	//Direct3D�C���^�[�t�F�C�X�̉��
	if(g_PD3D != NULL)
	{
		g_PD3D->Release();
		g_PD3D = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: update
//�Ԃ�l	: 
//����		: �X�V����
//////////////////////////////////////////////////////////////////////////////
void update ( void )
{
	static int i = 0;
	//�L�[�{�[�h�X�V
	UpdateKeyboard();
	
	//XInput�X�V
	UpdateXInput();

	if(GetKeyXInputRelease(0))
	{
		i++;
	} // EO if

	if(i > 5)
	{
		int ii = 0;
	}

	//�t�F�[�h�X�V
	updateFade();
	
	//bg�X�V
	updateBg();

	//���[�h���ƍX�V
	switch(g_mode)
	{
	case TITLE_MODE:		//�^�C�g��
		UpdateTitle();
		break;

	case STAGE_SELECT:		//�X�e�[�W�Z���N�g
		UpdateStageSelect();
		break;

	case GAME_MODE:			//�Q�[��
		updateGame();
		break;

	case RESULT_MODE:		//���U���g
		UpdateResult();
		break;

	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: draw
//�Ԃ�l	: 
//����		: �`�揈��
//////////////////////////////////////////////////////////////////////////////
void draw ( void )
{
	//�ϐ��錾
	
	//��ʁi�o�b�N�o�b�t�@�j
	g_PD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	//�`��J�n
	if(SUCCEEDED(g_PD3DDevice->BeginScene()))
	{
		//bg�`��
		drawBg();

		//���[�h���ƍX�V
		switch(g_mode)
		{
		case TITLE_MODE:		//�^�C�g��
			DrawTitle();
			break;

		case STAGE_SELECT:		//�X�e�[�W�Z���N�g
			DrawStageSelect();
			break;

		case GAME_MODE:			//�Q�[��
			drawGame();
			break;

		case RESULT_MODE:		//���U���g
			drawGame();
			DrawResult();
			break;
		}

		//�t�F�[�h�`��
		drawFade();

#ifdef _DEBUG
		//FPS�J�E���^�[
		//drawFPS();
#endif //_DEBUG

		//�`��I��
		g_PD3DDevice->EndScene();
		
	}

	//�o�b�N�o�b�t�@�̓���ւ�
	g_PD3DDevice->Present(NULL, NULL, NULL, NULL);

}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: getDevice
//�Ԃ�l	: 
//����		: �f�o�C�X�|�C���^�̎擾
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DDEVICE9 getDevice ( void )
{
	return g_PD3DDevice;
}

#ifdef _DEBUG
//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawFPS
//�Ԃ�l	: 
//����		: FPS�J�E���^�[�`��
//////////////////////////////////////////////////////////////////////////////
void drawFPS ( void )
{
	//�ϐ��錾
	char aStr[256];
	RECT rc = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	sprintf(&aStr[0], "FPS:%d", g_nCountFPS);
	g_pFont->DrawText(NULL, (LPCSTR)aStr, -1, &rc, DT_RIGHT, D3DCOLOR_RGBA(64, 200, 64, 255));
}
#endif //_DEBUG

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setMode
//�Ԃ�l	: 
//����		: �Q�[�����[�h�ݒ�
//////////////////////////////////////////////////////////////////////////////
void	setMode	( MODE mode )
{
	//�ϐ��錾
	MODE	oldMode;	//�ύX�O�̃Q�[�����[�h

	oldMode = g_mode;
	g_mode = mode;

	//�O��̃V�[���I��
	switch(oldMode)
	{
	case TITLE_MODE:		//�^�C�g��
	{
		UninitTitle();
		break;
	}

	case STAGE_SELECT:		//�X�e�[�W�Z���N�g
	{
		UninitStageSelect();
		break;
	}

	case GAME_MODE:			//�Q�[��
	{
		break;
	}

	case RESULT_MODE:		//���U���g
	{
		uninitGame();
		UninitResult();
		break;
	}
	}

	//���̃V�[��
	switch(g_mode)
	{
	case TITLE_MODE:		//�^�C�g��
	{
		InitTitle();
		break;
	}

	case STAGE_SELECT:		//�X�e�[�W�Z���N�g
	{
		InitStageSelect();
		break;
	}

	case GAME_MODE:			//�Q�[��
	{
		initGame();
		break;
	}

	case RESULT_MODE:		//���U���g
	{
		InitResult();
		break;
	}
	}
}