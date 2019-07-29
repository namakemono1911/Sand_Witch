/*****************************************************************************
tutorial.cpp
Aythor	: ���@��
Data	: 2017_06_21
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define	MAX_TUTO	(29)		//�`���[�g���A���̉摜�̐�
#define POP_SPD		(0.1f)		//�|�b�v�A�b�v�X�s�[�h

#define TUTO_MSG_SIZE	(D3DXVECTOR3(1000.f, 200.f, 0.f))	//�`���[�g���A�����b�Z�[�W�̃T�C�Y

#define POP_HEIGHT	(SCREEN_HEIGHT - TUTO_MSG_SIZE.y * 0.5f - 50.f)	//�|�b�v�A�b�v���鍂��
#define POP_DOWN_HE	(SCREEN_HEIGHT + TUTO_MSG_SIZE.y *0.5f)			//�|�b�v�_�E�����鍂��

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	TUTO_00 = 0,		//�`���[�g���A�����n�߂܂�
	TUTO_01,			//�ړI
	TUTO_02,			//�v���C���[
	TUTO_03,			//��
	TUTO_04,			//�i�s�x�o�[
	TUTO_05,			//����
	TUTO_06,			//�ʏ�e
	TUTO_07,			//�ʏ�e
	TUTO_08,			//���@�̔���
	TUTO_09,			//���@�̔���
	TUTO_10,			//�N�[���^�C��
	TUTO_11,			//����e
	TUTO_12,			//�s��
	TUTO_13,			//�s��
	TUTO_14,			//�s��
	TUTO_15,			//�{�X
	TUTO_16,			//�{�X

	//�`���[�g���A�������摜
	TUTO_DSP_00,		//�ŏ��̉��
	TUTO_DSP_01,		//�v���C���[
	TUTO_DSP_02,		//��
	TUTO_DSP_03,		//�i�s�x�o�[
	TUTO_DSP_04,		//����
	TUTO_DSP_05,		//�X�q
	TUTO_DSP_06,		//�ʏ�e1
	TUTO_DSP_07,		//�ʏ�e2
	TUTO_DSP_08,		//���@����
	TUTO_DSP_09,		//�G
	TUTO_DSP_10,		//�N�[���^�C��
	TUTO_DSP_11,		//����e
	TUTO_DSP_12,		//���̐������
	TUTO_DSP_13,		//�s��
	TUTO_DSP_14,		//���̐������
	TUTO_DSP_15,		//�{�X
	TUTO_DSP_16,		//�{�X�̊j
	TUTO_TYPE_MAX,		//�e�N�X�`���ő吔
}TUTO_TYPE;

typedef struct
{
	POLYGON		conf;	//�|���S���ݒ�
	TEXTURE		tex;	//�e�N�X�`���ݒ�
	int			achive;	//�i�s�x
	TUTO_TYPE	type;	//�e�N�X�`���^�C�v
}TUTO;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexTuto(LPDIRECT3DDEVICE9 pDevice);
void	popupTuto(void);
void	popdownTuto(void);
void	changeTutoDsp(int achive);

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureTuto[TUTO_TYPE_MAX] = {NULL};	//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTuto = NULL;			//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
char	*g_texNameTuto[] = 
{
	//���b�Z�[�W
	"data/TEXTURE/TUTORIAL/tuto00.png",		//�`���[�g���A�����b�Z�[�W00
	"data/TEXTURE/TUTORIAL/tuto01.png",		//�`���[�g���A�����b�Z�[�W01
	"data/TEXTURE/TUTORIAL/tuto02.png",		//�`���[�g���A�����b�Z�[�W02
	"data/TEXTURE/TUTORIAL/tuto03.png",		//�`���[�g���A�����b�Z�[�W03
	"data/TEXTURE/TUTORIAL/tuto04.png",		//�`���[�g���A�����b�Z�[�W04
	"data/TEXTURE/TUTORIAL/tuto05.png",		//�`���[�g���A�����b�Z�[�W05
	"data/TEXTURE/TUTORIAL/tuto06.png",		//�`���[�g���A�����b�Z�[�W06
	"data/TEXTURE/TUTORIAL/tuto07.png",		//�`���[�g���A�����b�Z�[�W07
	"data/TEXTURE/TUTORIAL/tuto08.png",		//�`���[�g���A�����b�Z�[�W08
	"data/TEXTURE/TUTORIAL/tuto09.png",		//�`���[�g���A�����b�Z�[�W09
	"data/TEXTURE/TUTORIAL/tuto10.png",		//�`���[�g���A�����b�Z�[�W10
	"data/TEXTURE/TUTORIAL/tuto11.png",		//�`���[�g���A�����b�Z�[�W11
	"data/TEXTURE/TUTORIAL/tuto12.png",		//�`���[�g���A�����b�Z�[�W12
	"data/TEXTURE/TUTORIAL/tuto13.png",		//�`���[�g���A�����b�Z�[�W13
	"data/TEXTURE/TUTORIAL/tuto14.png",		//�`���[�g���A�����b�Z�[�W14
	"data/TEXTURE/TUTORIAL/tuto15.png",		//�`���[�g���A�����b�Z�[�W15
	"data/TEXTURE/TUTORIAL/tuto16.png",		//�`���[�g���A�����b�Z�[�W16

	//�}��
	"data/TEXTURE/TUTORIAL/tuto_dsp00.jpg",	//�`���[�g���A���}��00
	"data/TEXTURE/TUTORIAL/tuto_dsp01.jpg",	//�`���[�g���A���}��01
	"data/TEXTURE/TUTORIAL/tuto_dsp02.jpg",	//�`���[�g���A���}��02
	"data/TEXTURE/TUTORIAL/tuto_dsp03.jpg",	//�`���[�g���A���}��03
	"data/TEXTURE/TUTORIAL/tuto_dsp04.jpg",	//�`���[�g���A���}��04
	"data/TEXTURE/TUTORIAL/tuto_dsp05.jpg",	//�`���[�g���A���}��05
	"data/TEXTURE/TUTORIAL/tuto_dsp06.jpg",	//�`���[�g���A���}��06
	"data/TEXTURE/TUTORIAL/tuto_dsp07.jpg",	//�`���[�g���A���}��07
	"data/TEXTURE/TUTORIAL/tuto_dsp08.jpg",	//�`���[�g���A���}��08
	"data/TEXTURE/TUTORIAL/tuto_dsp09.jpg",	//�`���[�g���A���}��09
	"data/TEXTURE/TUTORIAL/tuto_dsp10.jpg",	//�`���[�g���A���}��10
	"data/TEXTURE/TUTORIAL/tuto_dsp11.jpg",	//�`���[�g���A���}��11
	"data/TEXTURE/TUTORIAL/tuto_dsp12.jpg",	//�`���[�g���A���}��12
	"data/TEXTURE/TUTORIAL/tuto_dsp13.jpg",	//�`���[�g���A���}��13
	"data/TEXTURE/TUTORIAL/tuto_dsp14.jpg",	//�`���[�g���A���}��14
	"data/TEXTURE/TUTORIAL/tuto_dsp15.jpg",	//�`���[�g���A���}��15
	"data/TEXTURE/TUTORIAL/tuto_dsp16.jpg",	//�`���[�g���A���}��15
};

TUTO	g_tuto;		//�`���[�g���A���̐ݒ�
TUTO	g_tutoDsp;	//�`���[�g���A���}���̐ݒ�

bool	g_popUp = false;	//�|�b�v�A�b�v���Ă邩�ǂ���
bool	g_popDown = true;	//�|�b�v�_�E�����Ă邩�ǂ���

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initTuto
//�Ԃ�l	: 
//����		: �`���[�g���A��������
//////////////////////////////////////////////////////////////////////////////
HRESULT	initTuto	(void)
{
	//�t�F�[�h�C��
	startFadeIn(60, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//�ϐ�������
	g_tuto.achive = 0;
	g_tutoDsp.achive = 0;
	g_tuto.conf.size = TUTO_MSG_SIZE;
	g_tuto.conf.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT + g_tuto.conf.size.x * 0.5f, 0.f);
	g_tuto.tex.pos = D3DXVECTOR2(0.f, 0.f);
	g_tuto.tex.size = D3DXVECTOR2(1.f, 1.f);

	g_tutoDsp.conf.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f);
	g_tutoDsp.conf.size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.f);
	g_tutoDsp.tex.pos = D3DXVECTOR2(0.f, 0.f);
	g_tutoDsp.tex.size = D3DXVECTOR2(1.f, 1.f);

	g_popUp = false;
	g_popDown = true;

	//�e�N�X�`���̓ǂݍ���
	LPDIRECT3DDEVICE9	pDevice = getDevice();		//�f�o�C�X���
	for (int i = 0; i < TUTO_TYPE_MAX; i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(pDevice, g_texNameTuto[i], &g_pTextureTuto[i])))
		{
			MessageBox(NULL, "tutorial", "�G���[", MB_OK);
		}
	}

	//���_�o�b�t�@�쐬
	makeVertexTuto(pDevice);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateTuto
//�Ԃ�l	: 
//����		: �`���[�g���A���X�V
//////////////////////////////////////////////////////////////////////////////
void uninitTuto(void)
{
	//���_�o�b�t�@�����[�X
	if (g_pVtxBufferTuto != NULL)
	{
		g_pVtxBufferTuto->Release();
		g_pVtxBufferTuto = NULL;
	}

	//�e�N�X�`���o�b�t�@�����[�X
	for (int i = 0; i < TUTO_TYPE_MAX; i++)
	{
		if (g_pTextureTuto[i] != NULL)
		{
			g_pTextureTuto[i]->Release();
			g_pTextureTuto[i] = NULL;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateTuto
//�Ԃ�l	: 
//����		: �`���[�g���A���X�V
//////////////////////////////////////////////////////////////////////////////
void updateTuto(void)
{
	if (g_popDown == false)
	{
		popdownTuto();

		if (g_tuto.achive >= TUTO_16)
		{
			startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), STAGE_SELECT);
		}
	}
	else if (g_popUp == false)
	{
		if (g_tuto.achive <= TUTO_16)
		{
			popupTuto();
		}
	}

	//�e�N�X�`���ύX
	changeTutoDsp(g_tutoDsp.achive);

	//���_���X�V
	VERTEX2D	*pVtx;
	g_pVtxBufferTuto->Lock(0, 0, (void**)&pVtx, 0);

	//�}�������̍X�V
	setBuffer(pVtx, g_tutoDsp.conf);
	setTexture(pVtx, g_tutoDsp.tex);

	pVtx += NUM_VERTEX;

	//���b�Z�[�W�X�V
	setBuffer(pVtx, g_tuto.conf);
	setTexture(pVtx, g_tuto.tex);

	g_pVtxBufferTuto->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawTuto
//�Ԃ�l	: 
//����		: �`���[�g���A���`��
//////////////////////////////////////////////////////////////////////////////
void drawTuto(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	int		i;		//loop

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferTuto, 0, sizeof(VERTEX2D));

	//�|���S���̕`��
	for (i = 0; i < TUTO_TYPE_MAX; i++)
	{
		////�}�������`��
		//pDevice->SetTexture(0, g_pTextureTuto[g_tutoDsp.type]);

		//pDevice->DrawPrimitive
		//(
		//	D3DPT_TRIANGLESTRIP,	//�|���S���̎��
		//	0,						//�I�t�Z�b�g(���_��)
		//	NUM_POLYGON				//�|���S���̐�
		//);

		//���b�Z�[�W�����`��
		if (g_tuto.achive <= TUTO_16)
		{
			pDevice->SetTexture(0, g_pTextureTuto[g_tuto.achive]);

			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,	//�|���S���̎��
				NUM_VERTEX,				//�I�t�Z�b�g(���_��)
				NUM_POLYGON				//�|���S���̐�
			);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexTuto
//�Ԃ�l	: 
//����		: ���_�o�b�t�@�쐬
//////////////////////////////////////////////////////////////////////////////
void addAchive(void)
{
	g_tuto.achive++;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: startPopdown
//�Ԃ�l	: 
//����		: �|�b�v�_�E���J�n
//////////////////////////////////////////////////////////////////////////////
void startPopdown(void)
{
	g_popDown = false;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexTuto
//�Ԃ�l	: 
//����		: ���_�o�b�t�@�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexTuto(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^
	int		i;		//loop

	//���_�o�b�t�@�̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX2D) * NUM_VERTEX * 2,	//���_�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//�������Ǘ����@
		&g_pVtxBufferTuto,					//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
		NULL)))
	{
		return E_FAIL;
	}

	g_pVtxBufferTuto->Lock(0, 0, (void**)&pVtx, 0);

	//���_���
	setBuffer(pVtx, g_tutoDsp.conf);

	//�e�N�X�`�����W
	setTexture(pVtx, g_tutoDsp.tex);

	//rhw�̐ݒ�(�K��1.0f)
	pVtx[0].rhw = pVtx[1].rhw =
		pVtx[2].rhw = pVtx[3].rhw = 1.f;

	//���_�J���[�̐ݒ�(0~155�̐����l)
	pVtx[0].color = pVtx[1].color =
		pVtx[2].color = pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx += NUM_VERTEX;

	//���_���
	setBuffer(pVtx, g_tuto.conf);

	//�e�N�X�`�����W
	setTexture(pVtx, g_tuto.tex);

	//rhw�̐ݒ�(�K��1.0f)
	pVtx[0].rhw = pVtx[1].rhw = 
	pVtx[2].rhw = pVtx[3].rhw = 1.f;

	//���_�J���[�̐ݒ�(0~155�̐����l)
	pVtx[0].color = pVtx[1].color = 
	pVtx[2].color = pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);


	g_pVtxBufferTuto->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: popupTuto
//�Ԃ�l	: true�ōX�V����
//����		: �`���[�g���A�����b�Z�[�W�\��
//////////////////////////////////////////////////////////////////////////////
void	popupTuto(void)
{
	g_tuto.conf.pos.y -= (g_tuto.conf.pos.y - POP_HEIGHT) * POP_SPD;
	g_popUp = false;

	if (g_tuto.conf.pos.y <= POP_HEIGHT)
	{
		g_tuto.conf.pos.y = POP_HEIGHT;
		g_popUp = true;
		g_tutoDsp.achive++;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: popdownTuto
//�Ԃ�l	: true�ōX�V����
//����		: �`���[�g���A�����b�Z�[�W�\��
//////////////////////////////////////////////////////////////////////////////
void	popdownTuto(void)
{
	g_tuto.conf.pos.y += 50.f;
	g_popDown = false;

	if (g_tuto.conf.pos.y >= POP_DOWN_HE)
	{
		g_tuto.conf.pos.y = POP_DOWN_HE;
		g_popDown = true;
		g_popUp = false;
		g_tuto.achive++;
		g_tutoDsp.achive++;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: changeTuto
//�Ԃ�l	: 
//����		: �e�N�X�`��
//////////////////////////////////////////////////////////////////////////////
void	changeTutoDsp(int achive)
{
	switch(achive)
	{
	case 0:
	{
		g_tutoDsp.type = TUTO_DSP_00;
		break;
	}

	case 1:
	{
		g_tutoDsp.type = TUTO_DSP_00;
		break;
	}

	case 2:
	{
		g_tutoDsp.type = TUTO_DSP_01;
		break;
	}

	case 3:
	{
		g_tutoDsp.type = TUTO_DSP_02;
		break;
	}

	case 4:
	{
		g_tutoDsp.type = TUTO_DSP_03;
		break;
	}

	case 5:
	{
		g_tutoDsp.type = TUTO_DSP_04;
		break;
	}

	case 6:
	{
		g_tutoDsp.type = TUTO_DSP_06;
		break;
	}

	case 7:
	{
		g_tutoDsp.type = TUTO_DSP_07;
		break;
	}

	case 8:
	{
		g_tutoDsp.type = TUTO_DSP_08;
		break;
	}

	case 9:
	{
		g_tutoDsp.type = TUTO_DSP_09;
		break;
	}

	case 10:
	{
		g_tutoDsp.type = TUTO_DSP_10;
		break;
	}

	case 11:
	{
		g_tutoDsp.type = TUTO_DSP_11;
		break;
	}

	case 12:
	{
		g_tutoDsp.type = TUTO_DSP_13;
		break;
	}

	case 13:
	{
		g_tutoDsp.type = TUTO_DSP_13;
		break;
	}

	case 14:
	{
		g_tutoDsp.type = TUTO_DSP_13;
		break;
	}

	case 15:
	{
		g_tutoDsp.type = TUTO_DSP_15;
		break;
	}

	case 16:
	{
		g_tutoDsp.type = TUTO_DSP_16;
		break;
	}
	}
}