/*****************************************************************************
explo.cpp
Aythor	: ���@��
Data	: 2016_06_08
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "explo.h"
#include "notes.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define TEX_SIZE		(D3DXVECTOR2(1.f / 20, 1.f))	//�e�N�X�`���T�C�Y
#define MAX_EXPLO		(15)		//��x�ɕ`��ł���ő吔
#define ANIME_FRAME		(30)		//�Đ�FPS

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON		conf;		//�|���S���̊e��ݒ�
	TEXTURE	  	tex;		//�e�N�X�`���ݒ�
	int			frameCnt;	//�t���[���J�E���^
	bool	  	use;		//�g�p�t���O
}EXPLO;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexExplo(LPDIRECT3DDEVICE9 pDevice);

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureExplo = NULL ;	//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferExplo = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

EXPLO		g_explo[MAX_EXPLO];		//�w�i�\����
UINT		g_numExplo = 0;			//���ݗL���ȍ\���̂̐�

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initExplo
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initExplo(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�\���̏�����
	for(int i = 0; i < MAX_EXPLO; i++)
	{
		g_explo[i].tex.size = TEX_SIZE;
		g_explo[i].use = false;
	}

	g_numExplo = 0;

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/GAME/BULLET/explosion.png", &g_pTextureExplo)))
	{
		MessageBox(NULL, "bg", "�G���[", MB_OK);
	}

	//�f�o�C�X�擾
	makeVertexExplo(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitExplo
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitExplo(void)
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	if (g_pTextureExplo != NULL)
	{
		g_pTextureExplo->Release();
		g_pTextureExplo = NULL;
	}

	//���_�o�b�t�@�Ǘ��̉��
	if (g_pVtxBufferExplo != NULL)
	{
		g_pVtxBufferExplo->Release();
		g_pVtxBufferExplo = NULL;
	}

	g_numExplo = 0;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateExplo
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateExplo(void)
{
	//���X�V
	for (UINT i = 0, j = 0; j < g_numExplo; i++)
	{
		if (g_explo[i].use == true)
		{
			//�e�N�X�`���A�j��
			g_explo[i].frameCnt++;
			if (g_explo[i].frameCnt % (60 / ANIME_FRAME) == 0)
			{
				g_explo[i].tex.pos.x += g_explo[i].tex.size.x;
				if (g_explo[i].tex.pos.x >= 1.f)
				{
					//�폜
					g_explo[i].use = false;
					g_numExplo--;
				}
			}

			j++;
		}
	}

	//���o�^
	VERTEX2D *pVtx;

	g_pVtxBufferExplo->Lock(0, 0, (void**)&pVtx, 0);
	
	for (UINT i = 0, j = 0; j < g_numExplo; i++)
	{
		if (g_explo[i].use == true)
		{
			//���_
			setBuffer(pVtx, g_explo[i].conf);

			//�e�N�X�`��
			setTexture(pVtx, g_explo[i].tex);

			j++;
		}

		pVtx += NUM_VERTEX;
	}

	g_pVtxBufferExplo->Unlock();

}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawExplo
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawExplo(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferExplo, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���ݒ�
	pDevice->SetTexture(0, g_pTextureExplo);

	//�|���S���̕`��
	for(UINT i = 0, j = 0; j < g_numExplo; i++)
	{
		if (g_explo[i].use == true)
		{
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,	//�|���S���̎��
				0,						//�I�t�Z�b�g(���_��)
				NUM_POLYGON				//�|���S���̐�
			);

			j++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexExplo
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexExplo(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^

	//���_�o�b�t�@�̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX * MAX_EXPLO,		//���_�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//�������Ǘ����@
		&g_pVtxBufferExplo,					//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
		NULL
	)
	))

	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferExplo->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < MAX_EXPLO; i++)
	{
		//rhw�̐ݒ�(�K��1.0f)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�(0~155�̐����l)
		pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += NUM_VERTEX;
	}

	//���̂�����A�[�����b�N��
	g_pVtxBufferExplo->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setExploType
//�Ԃ�l	: 
//����		: �w�i�摜�ݒ�
//////////////////////////////////////////////////////////////////////////////
void	setExplo(D3DXVECTOR3 pos, float size)
{
	for(int i = 0; i < MAX_EXPLO; i++)
	{
		if(g_explo[i].use == false)
		{
			g_explo[i].conf.pos = pos;
			g_explo[i].conf.size = D3DXVECTOR3(size, NOTES_HEIGHT, 0.f);
			g_explo[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
			g_explo[i].frameCnt = 0;
			g_explo[i].use = true;

			g_numExplo++;

			//���o�^
			VERTEX2D *pVtx;

			g_pVtxBufferExplo->Lock(0, 0, (void**)&pVtx, 0);

			//�|�C���^�ړ�
			pVtx += NUM_VERTEX * i;

			//���_
			setBuffer(pVtx, g_explo[i].conf);

			//�e�N�X�`��
			setTexture(pVtx, g_explo[i].tex);

			g_pVtxBufferExplo->Unlock();

			break;
		}
	}
}