//============================================
//  gate�֐�  (gate.cpp)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2017�N04��21��
//  �C����   �N����
//  �C�����e:
//
//
//============================================

//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
#include "gate.h"
#include "notes.h"
#include "bulletBoss.h"
#include "input.h"
#include "boss.h"
#include "sound.h"

#include "heart.h"

#include "polygon.h"

#include "effect.h"

//============================================
//
//  �}�N����`
//
//============================================
#define GATE_TEX_NAME	"data/texture/GAME/CASTLE/gate01.png"	// �e�N�X�`����

#define WIDTH (70)
#define GATE_HP 100	// �ϋv��

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureGate = NULL;//Notes�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferGate = NULL;//�|�C���^�[!!&������

/*��\����*/
GATE g_aGate[GATE_NUM];

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexGate(LPDIRECT3DDEVICE9 pDevice);

//============================================
//
//  ���O  InitGate�֐�
//  ����   void
//  �߂�l void
//  ����   ��̏�����
//
//============================================
void InitGate(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();


	// ��\���̂̏�����

	for(int i = 0 ; i < GATE_NUM ; i++)
	{
		g_aGate[i].bUse = true;
		g_aGate[i].bCol = true;
		g_aGate[i].fPos = D3DXVECTOR3(POSX , (SCREEN_HEIGHT / 100.0f * 26.5f) + ((SCREEN_HEIGHT / 100.0f * 15.0f) + (SCREEN_HEIGHT / 100.0f * 2.75f)) * i, 0.0f);
		g_aGate[i].fSize = D3DXVECTOR2(WIDTH , (SCREEN_HEIGHT / 100.0f * 15.0f));
		g_aGate[i].fUV = D3DXVECTOR2(0.0f , 0.0f);
		g_aGate[i].nHp = GATE_HP;
		g_aGate[i].nHeart = -1;
	} // EO for

	//���_�쐬
	if(FAILED(MakeVertexGate(pDevice)))
	{
		return;
	} // EO if

	// �e�N�X�`���擾
	if(FAILED(D3DXCreateTextureFromFile( pDevice , GATE_TEX_NAME , &g_pTextureGate )))
	{
		MessageBox(NULL , "��e�N�X�`�����擾�ł��܂���ł���" , "ERROR" , MB_OK);
	} // EO if

} // EO InitGate

//============================================
//
//  ���O  UninitGate�֐�
//  ����   void
//  �߂�l void
//  ����   ��̏I��
//
//============================================
void UninitGate(void)
{
	// �C���^�[�t�F�[�X�̉��
	SAFE_RELEASE(g_pTextureGate);
	SAFE_RELEASE(g_pVtxBufferGate);

} // EO UninitGate

//============================================
//
//  ���O  UpdateGate�֐�
//  ����   void
//  �߂�l void
//  ����   ��̍X�V
//
//============================================
void UpdateGate(void)
{
	// �G�Ƃ̓����蔻��
	//���_�o�b�t�@
	VERTEX2D* pVtx;
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferGate -> Lock(0,0,(void**)&pVtx,0);
	int nCntGate;
	for(nCntGate = 0 ; nCntGate < GATE_NUM ; nCntGate++)
	{
		if(g_aGate[nCntGate].bUse == true)
		{
			SetPosHeart(g_aGate[nCntGate].nHeart , D3DXVECTOR2(g_aGate[nCntGate].fPos.x , g_aGate[nCntGate].fPos.y));
			SetUVSizeHeart(g_aGate[nCntGate].nHeart , g_aGate[nCntGate].nHp / 10);
			if(g_aGate[nCntGate].nHp >= 50)
			{
				pVtx[0 + 4 * nCntGate].tex = D3DXVECTOR2( 0.0f , 0.0f );
				pVtx[1 + 4 * nCntGate].tex = D3DXVECTOR2( 0.25f , 0.0f );
				pVtx[2 + 4 * nCntGate].tex = D3DXVECTOR2( 0.0f , 1.0f );
				pVtx[3 + 4 * nCntGate].tex = D3DXVECTOR2( 0.25f , 1.0f );
			}
			else if(g_aGate[nCntGate].nHp < 50 && g_aGate[nCntGate].nHp >= 30)
			{
				pVtx[0 + 4 * nCntGate].tex = D3DXVECTOR2( 0.25f , 0.0f );
				pVtx[1 + 4 * nCntGate].tex = D3DXVECTOR2( 0.5f , 0.0f );
				pVtx[2 + 4 * nCntGate].tex = D3DXVECTOR2( 0.25f , 1.0f );
				pVtx[3 + 4 * nCntGate].tex = D3DXVECTOR2( 0.5f , 1.0f );
			}
			else if(g_aGate[nCntGate].nHp < 30 && g_aGate[nCntGate].nHp > 0)
			{
				pVtx[0 + 4 * nCntGate].tex = D3DXVECTOR2( 0.5f , 0.0f );
				pVtx[1 + 4 * nCntGate].tex = D3DXVECTOR2( 0.75f , 0.0f );
				pVtx[2 + 4 * nCntGate].tex = D3DXVECTOR2( 0.5f , 1.0f );
				pVtx[3 + 4 * nCntGate].tex = D3DXVECTOR2( 0.75f , 1.0f );
			}
			else
			{
				pVtx[0 + 4 * nCntGate].tex = D3DXVECTOR2( 0.75f , 0.0f );
				pVtx[1 + 4 * nCntGate].tex = D3DXVECTOR2( 1.00f , 0.0f );
				pVtx[2 + 4 * nCntGate].tex = D3DXVECTOR2( 0.75f , 1.0f );
				pVtx[3 + 4 * nCntGate].tex = D3DXVECTOR2( 1.00f , 1.0f );
			}

			float a = (float)g_aGate[nCntGate].nHp / 100.0f;
			pVtx[0 + 4 * nCntGate].color = D3DXCOLOR(1.0f , 1.0f * a , 1.0f * a, 1.0f);
			pVtx[1 + 4 * nCntGate].color = D3DXCOLOR(1.0f , 1.0f * a , 1.0f * a, 1.0f);
			pVtx[2 + 4 * nCntGate].color = D3DXCOLOR(1.0f , 1.0f * a , 1.0f * a, 1.0f);
			pVtx[3 + 4 * nCntGate].color = D3DXCOLOR(1.0f , 1.0f * a , 1.0f * a, 1.0f);
		} // EO if
	} // EO for

	g_pVtxBufferGate -> Unlock();

} // EO UpdateGate

//============================================
//
//  ���O  DrawGate�֐�
//  ����   void
//  �߂�l void
//  ����   ��̕`��
//
//============================================
void DrawGate(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�p�C�v���C���̐ݒ�
	pDevice -> SetStreamSource(0,//�X�g���[���ԍ�(���{������)
						g_pVtxBufferGate ,//�f�[�^�̂���ꏊ(�擪�A�h���X)
						0,//�I�t�Z�b�g(�P�ʃo�C�g)�A�f�[�^�̂ǂ̕ӂ��玝���Ă��邩,0�͐擪
						sizeof(VERTEX2D) );//�X�g���C�h��(��̒P�ʂ̑傫��)

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	for(int nCntNotes = 0 ; nCntNotes < GATE_NUM ; nCntNotes++ )
	{
		if(g_aGate[nCntNotes].bUse == false)
		{
			int i = 0;
		}
		if(g_aGate[nCntNotes].bUse == true)
		{
			pDevice->SetTexture(0  ,g_pTextureGate);
			//�v���~�e�B�u�̕`��
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCntNotes * 4 ,//�I�t�Z�b�g(���_��)�����_�ڂ���Ƃ邩
				NUM_POLYGON );//�������_�����Ă���΂����̂��A�v���~�e�B�u�̖������������Q���B�p�C�v���C���͐��ꗬ���ɂȂ��Ă��邩��B
		} // EO if
	} // EO fro

} // EO DrawGate

//============================================
//
//  ���O  MakeVertexGate�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
HRESULT MakeVertexGate(LPDIRECT3DDEVICE9 pDevice)
{
	//���_�o�b�t�@�쐬
	if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_NOTES,D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,D3DPOOL_MANAGED,&g_pVtxBufferGate,NULL)))
	{
		MessageBox(NULL , "���_�o�b�t�@�̍쐬�Ɏ��s���܂���" , "ERROR" , MB_OK);
		return E_FAIL;
	} // EO if


	//���_�o�b�t�@
	VERTEX2D* pVtx;
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferGate -> Lock(0,0,(void**)&pVtx,0);

	for(int nCntNotes = 0 ; nCntNotes < GATE_NUM ; nCntNotes++)
	{
		pVtx[0 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aGate[nCntNotes].fPos.x , g_aGate[nCntNotes].fPos.y , 0.0f);
		pVtx[1 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aGate[nCntNotes].fPos.x + WIDTH , g_aGate[nCntNotes].fPos.y , 0.0f);
		pVtx[2 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aGate[nCntNotes].fPos.x , g_aGate[nCntNotes].fPos.y + g_aGate[nCntNotes].fSize.y, 0.0f);
		pVtx[3 + 4 * nCntNotes].pos = D3DXVECTOR3(g_aGate[nCntNotes].fPos.x  + WIDTH , g_aGate[nCntNotes].fPos.y + g_aGate[nCntNotes].fSize.y, 0.0f);

		pVtx[0 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.0f , 0.0f );
		pVtx[1 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.25f , 0.0f );
		pVtx[2 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.0f , 1.0f );
		pVtx[3 + 4 * nCntNotes].tex = D3DXVECTOR2( 0.25f , 1.0f );

		//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
		pVtx[0 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[1 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[2 + 4 * nCntNotes].rhw = 1.0f;
		pVtx[3 + 4 * nCntNotes].rhw = 1.0f;

		//���_�J���[(0�`255�̐����l)
		pVtx[0 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntNotes].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//�����A�����b�N
	g_pVtxBufferGate -> Unlock();

	return S_OK;
}//EOMakeVertexNotes

GATE* GetGate(void)
{
	return &g_aGate[0];
}

void AddLife(int nIdx , int nLife)
{
	g_aGate[nIdx].nHp += nLife;


	if(nLife > 0)
	{
		SetEffect(g_aGate[nIdx].fPos.x + g_aGate[nIdx].fSize.x / 2 , g_aGate[nIdx].fPos.y + g_aGate[nIdx].fSize.y / 2 , g_aGate[nIdx].fSize.x * 3, LINE_HEIGHT ,EFFECT_RECOVER);
	}

	if(nLife < 0)
	{
		PlaySound(SE_GAME_GATE_BREAK);
	}
	if(g_aGate[nIdx].nHp >= 100)
	{
		g_aGate[nIdx].nHp = 100;
	}

	if(g_aGate[nIdx].nHp <= 0)
	{
		g_aGate[nIdx].nHp = 0;
		PlaySound(SE_GAME_GATE_BREAK_ALL);
	}
}
