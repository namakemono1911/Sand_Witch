/*****************************************************************************
fcoh.cpp
Aythor	: ���@��
Data	: 2017_06_05
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "fcoh.h"
#include "gate.h"
#include "notes.h"
#include "boss.h"
#include "nucleusBoss.h"
#include "bulletBoss.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define WIDTH		((float)SCREEN_WIDTH)	//��
#define HEIGHT		(200.f)					//����
#define MOVE		(50.f)					//���肭�鑬�x
#define COUNT_DOWN	(60)					//�K�E�Z��������܂ł̃t���[����
#define DAMAGE		(10)					//�^������_���[�W
#define NEED_ENERGY	(0)						//�K�E�Z�ɕK�v�ȃG�l���M�[

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON	conf;		//�|���S���̐ݒ�
	TEXTURE	tex;		//�e�N�X�`��
	UINT	count;		//�J�E���g�_�E��
	int		energy;		//�G�l���M�[
	bool	move;		//�����Ă�t���O
	bool	use;		//�g�p�t���O
}FCOH;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexFcoh(LPDIRECT3DDEVICE9 pDevice);

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureFcoh = NULL;			//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferFcoh = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

FCOH	g_fcoh[2];		//�K�E�Z�̐ݒ�
#define FCOH_TEX_NAME "data/TEXTURE/GAME/BULLET/killing.png"

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initFcoh
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initFcoh(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�\���̏�����
	for(int i = 0; i < 2; i++)
	{
		g_fcoh[i].use = false;
		g_fcoh[i].move = false;
		g_fcoh[i].count = 0;
		g_fcoh[i].conf.size = D3DXVECTOR3(WIDTH, HEIGHT, 0.f);
		g_fcoh[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
		g_fcoh[i].tex.size = D3DXVECTOR2(0.1f, 1.0f);
		g_fcoh[i].energy = 0;
	}

	//�e�N�X�`���̓ǂݍ���
	if (FAILED(D3DXCreateTextureFromFile(pDevice, FCOH_TEX_NAME, &g_pTextureFcoh)))
	{
		MessageBox(NULL, "killing", "�G���[", MB_OK);
	}

	//�f�o�C�X�擾
	makeVertexFcoh(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitFcoh
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitFcoh(void)
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	if (g_pTextureFcoh != NULL)
	{
		g_pTextureFcoh->Release();
		g_pTextureFcoh = NULL;
	}

	//���_�o�b�t�@�Ǘ��̉��
	if (g_pVtxBufferFcoh != NULL)
	{
		g_pVtxBufferFcoh->Release();
		g_pVtxBufferFcoh = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateFcoh
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateFcoh(void)
{
	//�ϐ��錾
	VERTEX2D	*pVtx;

	//�g�p����Ă���΍��W�X�V
	if(g_fcoh[0].use == true)
	{
		if(g_fcoh[0].move == true)
		{
			g_fcoh[0].conf.pos.y += MOVE;
			g_fcoh[1].conf.pos.y -= MOVE;

			g_fcoh[0].tex.pos.x += g_fcoh[0].tex.size.x;
			g_fcoh[1].tex.pos.x += g_fcoh[1].tex.size.x;

			if(g_fcoh[0].conf.pos.y >= SCREEN_HEIGHT * 0.5f - HEIGHT * 0.5f)
			{
				g_fcoh[0].conf.pos.y = SCREEN_HEIGHT * 0.5f - HEIGHT * 0.5f;
				g_fcoh[1].conf.pos.y = SCREEN_HEIGHT * 0.5f + HEIGHT * 0.5f;
				g_fcoh[0].move = false;
				g_fcoh[1].move = false;
			}
		}
		else
		{
			g_fcoh[0].count++;
			g_fcoh[0].tex.pos.x += g_fcoh[0].tex.size.x;
			g_fcoh[1].tex.pos.x += g_fcoh[1].tex.size.x;
			if(g_fcoh[0].count >= COUNT_DOWN)
			{
				g_fcoh[0].use = false;
				g_fcoh[1].use = false;
			}
		}
	}

	//���_���o�^
	g_pVtxBufferFcoh->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < 2; i++)
	{
		setBuffer(pVtx, g_fcoh[i].conf);
		setTexture(pVtx, g_fcoh[i].tex);
		pVtx += NUM_VERTEX;
	}

	g_pVtxBufferFcoh->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawFcoh
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawFcoh(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferFcoh, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, g_pTextureFcoh);

	for(int i = 0; i < 2 && g_fcoh[0].use == true; i++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,	//�|���S���̎��
			NUM_VERTEX * i,			//�I�t�Z�b�g(���_��)
			NUM_POLYGON				//�|���S���̐�
		);
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexFcoh
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexFcoh(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^

								//���_�o�b�t�@�̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX * 2,	//���_�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//�������Ǘ����@
		&g_pVtxBufferFcoh,					//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
		NULL)))
	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferFcoh->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < 2; i++)
	{
		//�e�N�X�`���ݒ�
		setTexture(pVtx, g_fcoh[i].tex);

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
	g_pVtxBufferFcoh->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setFcoh
//�Ԃ�l	: 
//����		: ��������ۂ����܂񂱂ɓ�����������I
//////////////////////////////////////////////////////////////////////////////
void	setFcoh(void)
{
	if(g_fcoh[0].use == false && g_fcoh[0].energy >= NEED_ENERGY)
	{
		g_fcoh[0].conf.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, -HEIGHT, 0.f);
		g_fcoh[1].conf.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT + HEIGHT, 0.f);

		g_fcoh[0].tex.pos = D3DXVECTOR2(0.0f,0.0f);
		g_fcoh[1].tex.pos = D3DXVECTOR2(0.0f,0.0f);

		g_fcoh[0].tex.size = D3DXVECTOR2(0.1f,1.0f);
		g_fcoh[1].tex.size = D3DXVECTOR2(0.1f,1.0f);

		g_fcoh[0].count = 0;
		g_fcoh[0].use = true;
		g_fcoh[1].use = true;
		g_fcoh[0].move = true;
		g_fcoh[1].move = true;

		g_fcoh[0].energy = 0;

		//���_�o�^
		VERTEX2D	*pVtx;

		g_pVtxBufferFcoh->Lock(0, 0, (void**)&pVtx, 0);

		setBuffer(pVtx, g_fcoh[0].conf);
		
		pVtx += NUM_VERTEX;

		setBuffer(pVtx, g_fcoh[1].conf);

		g_pVtxBufferFcoh->Unlock();
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: damageFcoh
//�Ԃ�l	: 
//����		: �E����
//////////////////////////////////////////////////////////////////////////////
void damageFcoh(void)
{
	//�E�����i�G�j
	NOTES *notes = GetNotes();	//�m�[�c�̐擪
	for (int i = 0; i < MAX_NOTES; i++)
	{
		if(notes->fPos.x + notes->fWidth >= 0.f && notes->fPos.x <= SCREEN_WIDTH)
		{
			AddDameage(i, DAMAGE);
		}

		notes++;
	}

	//�E�����i�{�X�j
	BOSSNUCLEUS *boss = GetNucleusBoss();
	if (boss->fPos.x + boss->fWidth >= 0.f && boss->fPos.x <= SCREEN_WIDTH)
	{
		AddDameageBoss(0, DAMAGE);
	}

	//�E�����i�{�X�e�j
	BOSSBULLET	*bosBlt = GetBulletBoss();
	for (int i = 0; i < MAX_BOSSBULLET; i++)
	{
		if (bosBlt->fPos.x + bosBlt->fWidth >= 0.f && bosBlt->fPos.x <= SCREEN_WIDTH)
		{
			AddDmgBulletBoss(0, DAMAGE);
		}
		bosBlt++;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: getFcohFlag
//�Ԃ�l	: 
//����		: ������������
//////////////////////////////////////////////////////////////////////////////
bool getFcohFlag(void)
{
	return g_fcoh[0].use;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: getFcohMove
//�Ԃ�l	: 
//����		: ���܂񂱁`�i�C�����Ȉ��A�j
//////////////////////////////////////////////////////////////////////////////
bool getFcohMove(void)
{
	return g_fcoh[0].move;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: addFcohEnergy
//�Ԃ�l	: 
//����		: �G�l���M�[��[
//////////////////////////////////////////////////////////////////////////////
void addFcohEnergy(int addNum)
{
	g_fcoh[0].energy += addNum;
}