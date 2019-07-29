/*****************************************************************************
actibate.cpp
Aythor	: ���@��
Data	: 2017_06_04
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "input.h"
#include "polygon.h"
#include "activate.h"
#include "notes.h"

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
#define ACTIVE_MAX		(100)		//�ő吔	
#define ANIME_FRAME		(30)		//�e�N�X�`���A�j����FPS
#define ACTIVE_SIZE		(D3DXVECTOR3(LINE_HEIGHT, LINE_HEIGHT, 0.f))	//�|���S���̃T�C�Y

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON		conf;		//�|���S���̊e��ݒ�
	TEXTURE		tex;		//UV�ݒ�
	int			frame;		//�t���[����
	ACTIVE_TYPE	type;		//�e�N�X�`���̃^�C�v
	bool		use;		//�g�p�t���O
}ACTIVE;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexActive(LPDIRECT3DDEVICE9 pDevice);

//////////////////////////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureActive[ACTIVE_TYPE_MAX] = { NULL };	//�e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferActive = NULL;	//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

ACTIVE		g_active[ACTIVE_MAX];		//�w�i�\����
UINT		g_numActive = 0;			//�����\���̂��L���ɂȂ��Ă��邩
const char	*texNameActive[ACTIVE_TYPE_MAX] =
{
	"data/TEXTURE/mh.png",
};

//////////////////////////////////////////////////////////////////////////////
//�֐���	: initActive
//�Ԃ�l	: 
//����		: �|���S��������
//////////////////////////////////////////////////////////////////////////////
void initActive(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�|�C���^�擾

	//�\���̏�����
	for(int i = 0; i < ACTIVE_MAX; i++)
	{
		g_active[i].conf.size = ACTIVE_SIZE;
		g_active[i].tex.size = D3DXVECTOR2(1.f / 11.f, 1.f);
		g_active[i].use = false;
	}

	g_numActive = 0;

	//�e�N�X�`���̓ǂݍ���
	for (int i = 0; i < ACTIVE_TYPE_MAX; i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(pDevice, texNameActive[i], &g_pTextureActive[i])))
		{
			MessageBox(NULL, "bg", "�G���[", MB_OK);
		}
	}

	//�f�o�C�X�擾
	makeVertexActive(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: uninitActive
//�Ԃ�l	: 
//����		: �|���S���I��
//////////////////////////////////////////////////////////////////////////////
void uninitActive(void)
{
	//�e�N�X�`���C���^�[�t�F�C�X�̉��
	for (int i = 0; i < ACTIVE_TYPE_MAX; i++)
	{
		if (g_pTextureActive[i] != NULL)
		{
			g_pTextureActive[i]->Release();
			g_pTextureActive[i] = NULL;
		}
	}

	//���_�o�b�t�@�Ǘ��̉��
	if (g_pVtxBufferActive != NULL)
	{
		g_pVtxBufferActive->Release();
		g_pVtxBufferActive = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: updateActive
//�Ԃ�l	: 
//����		: �|���S���X�V
//////////////////////////////////////////////////////////////////////////////
void updateActive(void)
{
	//�g�p����Ă�����̍X�V
	for(UINT i = 0, j = 0; j < g_numActive; i++)
	{
		//�g���Ă���\���̒T��
		if(g_active[i].use == true)
		{
			//�e�N�X�`���A�j���[�V����
			g_active[i].frame++;
			if (g_active[i].frame % (60 / ANIME_FRAME) == 0)
			{
				g_active[i].tex.pos.x += g_active[i].tex.size.x;
				if(g_active[i].tex.pos.x >= 1.f)
				{
					g_active[i].use = false;
					g_numActive--;
				}

			}
			j++;
		}
	}

	//���_���X�V
	VERTEX2D *pVtx;
	g_pVtxBufferActive->Lock(0, 0, (void**)&pVtx, 0);

	for(UINT i = 0, j = 0; j < g_numActive; i++)
	{
		if(g_active[i].use == true)
		{
			//���_���o�^
			setBuffer(pVtx, g_active[i].conf);

			//�e�N�X�`��
			setTexture(pVtx, g_active[i].tex);

			j++;
		}

		pVtx += NUM_VERTEX;
	}

	g_pVtxBufferActive->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: drawActive
//�Ԃ�l	: 
//����		: �|���S���`��
//////////////////////////////////////////////////////////////////////////////
void drawActive(void)
{
	//�ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�X�g���[���쐬
	pDevice->SetStreamSource(0, g_pVtxBufferActive, 0, sizeof(VERTEX2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(UINT i = 0, j = 0; j < g_numActive; i++)
	{
		if(g_active[i].use == true)
		{
			pDevice->SetTexture(0, g_pTextureActive[g_active[i].type]);

			//�|���S���̕`��
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,	//�|���S���̎��
				NUM_VERTEX * i,			//�I�t�Z�b�g(���_��)
				NUM_POLYGON				//�|���S���̐�
			);

			j++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: makeVertexActive
//�Ԃ�l	: 
//����		: ���_�쐬
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexActive(LPDIRECT3DDEVICE9 pDevice)
{
	//�ϐ��錾
	VERTEX2D *pVtx = NULL;;		//���z�A�h���X�p�|�C���^

								//���_�o�b�t�@�̐ݒ�
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX * ACTIVE_MAX,		//���_�o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,					//���_�o�b�t�@�̎g�p���@
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//�������Ǘ����@
		&g_pVtxBufferActive,				//���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
		NULL
	)
	))

	{
		return E_FAIL;
	}

	//���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾
	g_pVtxBufferActive->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < ACTIVE_MAX; i++)
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
	}

	//���̂�����A�[�����b�N��
	g_pVtxBufferActive->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//�֐���	: setActivate
//�Ԃ�l	: 
//����		: ����
//////////////////////////////////////////////////////////////////////////////
void	setActivate	(D3DXVECTOR3 pos, ACTIVE_TYPE type)
{
	//�ϐ��錾
	VERTEX2D	*pVtx;

	//���_�o�b�t�@���b�N
	g_pVtxBufferActive->Lock(0, 0, (void**)&pVtx, 0);

	//�g���Ă��Ȃ��z��T��
	for(int i = 0; i < ACTIVE_MAX; i++)
	{
		if(g_active[i].use == false)
		{
			//���ݒ�
			g_active[i].conf.pos = pos;
			g_active[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
			g_active[i].use = true;

			//���_���o�^
			setBuffer(pVtx, g_active[i].conf);

			//�e�N�X�`��
			setTexture(pVtx, g_active[i].tex);
			
			g_numActive++;
			break;
		}

		pVtx += NUM_VERTEX;
	}

	//�A�����b�N
	g_pVtxBufferActive->Unlock();
}