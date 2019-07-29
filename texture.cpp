//============================================
//  �e�N�X�`���֐�  (texture.cpp)
//
//  Author  Information
//  ���O  ���쏫�P
//  �쐬��   2016�N08��25��
//  �C����   2106�N08��28��
//  �C�����e: �Έ� : �C���f�b�N�X���w�肵�ď����֐��ǉ�
//  �C�����e: �Έ� : �C���f�b�N�X���w�肵��pos,uv�𓮂����֐��ǉ�
//  �C�����e: �Έ� : ���C�����w�肵��draw
//
//
//============================================


//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
#include "main.h"
#include "texture.h"

//============================================
//
//  �}�N����`
//
//============================================
#define MAX_TEXTURE (13)								// �e�N�X�`���̍ő吔
#define TEXTURENAME001 "data/texture/GAME/UI/red.png"			//  �^�C�g������
#define TEXTURENAME002 "data/texture/GAME/UI/renga.png"			//  �^�C�g������
#define TEXTURENAME003 "data/texture/GAME/UI/renga.png"			//  �^�C�g������
#define TEXTURENAME004 "data/texture/GAME/UI/renga.png"			//  �^�C�g������
#define TEXTURENAME005 "data/texture/GAME/UI/renga.png"			//  �^�C�g������
#define TEXTURENAME006 "data/texture/GAME/UI/renga.png"			//  �^�C�g������
#define TEXTURENAME007 "data/texture/charctor01.png"			//  �^�C�g������
#define TEXTURENAME008 "data/texture/ui_a.png"			//  a
#define TEXTURENAME009 "data/texture/ui_b.png"			//  b
#define TEXTURENAME010 "data/texture/ui_x.png"			//  x
#define TEXTURENAME011 "data/texture/ui_y.png"			//  y
#define TEXTURENAME012 "data/texture/GAME/UI/resultBar.png"		//  �o�[
#define TEXTURENAME013 "data/texture/GAME/UI/resultBarOn.png"	//  �o�[��

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
LPDIRECT3DTEXTURE9 g_pTexture[MAX_TEXTURE] = {};		// �|�C���^�^ �e�N�X�`���C���^�[�t�F�C�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffer = NULL;			// �|�C���^�^ ���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����œǂݍ��ރe�N�X�`���̖��O������
///////////////////////////////////////////////////////////////////////////////////////////////////////////

TEXTURE_a g_Tex[MAX_TEXTURE] = {							// �e�N�X�`�����̍\���̐���
	{TEXTURENAME001},
	{TEXTURENAME002},
	{TEXTURENAME003},
	{TEXTURENAME004},
	{TEXTURENAME005},
	{TEXTURENAME006},
	{TEXTURENAME007},
	{TEXTURENAME008},
	{TEXTURENAME009},
	{TEXTURENAME010},
	{TEXTURENAME011},
	{TEXTURENAME012},
	{TEXTURENAME013}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
void MakeVertexTexture(LPDIRECT3DDEVICE9 pDevice);			// ���_�쐬
void SetVertexTexture(int nTextureIndex);					// ���_�ݒ�

//============================================
//
//  ���O  InitTextuer�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
HRESULT InitTexture(void)
{
	int nCntTex = 0;			// �J�E���^

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// �e�N�X�`������������
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		g_Tex[nCntTex].fPosX    = 0.0f;		// ���WX
		g_Tex[nCntTex].fPosY    = 0.0f;		// ���WY
		g_Tex[nCntTex].fWidth   = 0.0f;		// ��
		g_Tex[nCntTex].fHeight  = 0.0f;		// ����
		g_Tex[nCntTex].fTposu   = 0.0f;		// U�̒l
		g_Tex[nCntTex].fTposv   = 0.0f;		// V�̒l
		g_Tex[nCntTex].fTwidth  = 0.0f;		// UV�l�̕�
		g_Tex[nCntTex].fTheight = 0.0f;		// UV�l�̍���
		g_Tex[nCntTex].bUse = false;		// �g�p�t���O
	}

	// ���_�̍쐬
	MakeVertexTexture(pDevice);

	// �e�N�X�`���ǂݍ���
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		// �e�N�X�`���ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(
			pDevice,						// �f�o�C�X�ɗ���
			g_Tex[nCntTex].aName,			// �e�N�X�`���̖��O
			&g_pTexture[nCntTex])))			// �e�N�X�`���̌Ăэ��� 
		{
			// �ǂݍ��݂Ɏ��s���Ă�����
			//MessageBox(NULL, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂����B", "�G���[", MB_OK | MB_ICONHAND | MB_DEFBUTTON1);
			//DebugMsgBox(_TEXT("%d�Ԗڂ̃e�N�X�`�����ǂݍ��݂Ɏ��s���܂����B()") , nCntTex + 1);
		}
	}

	return S_OK;
}


//============================================
//
//  ���O  UninitTextuer�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void UninitTexture(void)
{
	int nCntTex = 0;		// �J�E���^

	// �e�N�X�`���C���^�[�t�F�C�X
	for(int i = 0; i< MAX_TEXTURE; i++)
	{
		SAFE_RELEASE(g_pTexture[i]);
	}

	// ���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
	if (g_pVtxBuffer != NULL)
	{
		g_pVtxBuffer->Release();			// ���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X�̉��
		g_pVtxBuffer = NULL;				// �A�h���X��NULL�ɂ���
	}

	// �e�N�X�`������������
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		g_Tex[nCntTex].fPosX = 0;		// ���WX
		g_Tex[nCntTex].fPosY = 0;		// ���WY
		g_Tex[nCntTex].fWidth = 0;		// ��
		g_Tex[nCntTex].fHeight = 0;		// ����
		g_Tex[nCntTex].fTposu = 0;		// U�̒l
		g_Tex[nCntTex].fTposv = 0;		// V�̒l
		g_Tex[nCntTex].fTwidth = 0;		// UV�l�̕�
		g_Tex[nCntTex].fTheight = 0;	// UV�l�̍���
		g_Tex[nCntTex].bUse = false;	// �g�p�t���O
	}
}

//============================================
//
//  ���O  UpdateTextuer�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void UpdateTexture(void)
{

}

//============================================
//
//  ���O  DrawTextuer�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void DrawTexture(int nLayer)
{
	int nCntTexture = 0;			// �J�E���^

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// �v���~�e�B�u�̐ݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBuffer,
		0,								// �I�t�Z�b�g(�P�ʃo�C�g)
		sizeof(VERTEX2D));				// �X�g���C�h�ʁB���_�f�[�^1���̃T�C�Y

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	// �`��
	for (nCntTexture = 0; nCntTexture < MAX_TEXTURE; nCntTexture++)
	{
		// �g�p�t���O��ON�Ȃ�`��
		if (g_Tex[nCntTexture].bUse == true && g_Tex[nCntTexture].nLayer == nLayer)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTexture[nCntTexture]);

			// �v���~�e�B�u�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				nCntTexture * 4,				// �I�t�Z�b�g(���_��)
				NUM_POLYGON);					// �v���~�e�B�u��
		}
	}
}

//============================================
//
//  ���O  SetTexture�֐�
//  ����  �C���f�b�N�X, ���WX, ���WY, ��, ����, U�̒l, V�̒l, UV�̕�, UV�̍���
//  �߂�l
//  ����
//
//============================================
void SetTexture(int nTextureIndex, float fPosX, float fPosY, float fWidth, float fHeight,
	float fTposu, float fTposv, float fTwidth, float fTheight , int nLayer)
{
	// �e�N�X�`������ݒ�
	g_Tex[nTextureIndex].fPosX    = fPosX;		// ���WX
	g_Tex[nTextureIndex].fPosY    = fPosY;		// ���WY
	g_Tex[nTextureIndex].fWidth   = fWidth;		// ��
	g_Tex[nTextureIndex].fHeight  = fHeight;	// ����
	g_Tex[nTextureIndex].fTposu   = fTposu;		// U�̒l
	g_Tex[nTextureIndex].fTposv   = fTposv;		// V�̒l
	g_Tex[nTextureIndex].fTwidth  = fTwidth;	// UV�l�̕�
	g_Tex[nTextureIndex].fTheight = fTheight;	// UV�l�̍���
	g_Tex[nTextureIndex].bUse     = true;		// �g�p�t���O�I��
	g_Tex[nTextureIndex].nLayer = nLayer;       // ���Ԗڂ̃��C���[��

	// ���_�ݒ�
	SetVertexTexture(nTextureIndex);
}

//============================================
//
//  ���O  MakeVertexTexture�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void MakeVertexTexture(LPDIRECT3DDEVICE9 pDevice)
{
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX2D) * (MAX_TEXTURE * NUM_VERTEX),		// ���_�o�b�t�@�̃T�C�Y�B���I�������m��
		D3DUSAGE_WRITEONLY,									// �������݂̂݁B�ő��łł���
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,									// �������Ǘ����@(�f�o�C�X�ɂ��܂���)
		&g_pVtxBuffer,
		NULL);
}

//============================================
//
//  ���O  SetVertexTexture�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void SetVertexTexture(int nTextureIndex)
{
	int nCntTexture = 0;		// �J�E���^
	 VERTEX2D* pVtx;			// ���z�A�h���X�̃|�C���^

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾����G
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�(2D���W�E�E��� Z��N�̏���)
	pVtx[4 * nTextureIndex + 0].pos = D3DXVECTOR3(g_Tex[nTextureIndex].fPosX, g_Tex[nTextureIndex].fPosY, 0.0f);							// ������X,Y,Z
	pVtx[4 * nTextureIndex + 1].pos = D3DXVECTOR3(g_Tex[nTextureIndex].fPosX + g_Tex[nTextureIndex].fWidth, g_Tex[nTextureIndex].fPosY, 0.0f);
	pVtx[4 * nTextureIndex + 2].pos = D3DXVECTOR3(g_Tex[nTextureIndex].fPosX, g_Tex[nTextureIndex].fPosY + g_Tex[nTextureIndex].fHeight, 0.0f);
	pVtx[4 * nTextureIndex + 3].pos = D3DXVECTOR3(g_Tex[nTextureIndex].fPosX + g_Tex[nTextureIndex].fWidth, g_Tex[nTextureIndex].fPosY + g_Tex[nTextureIndex].fHeight, 0.0f);

	// �e�N�X�`����UV�l�ݒ�
	pVtx[4 * nTextureIndex + 0].tex = D3DXVECTOR2(g_Tex[nTextureIndex].fTposu, g_Tex[nTextureIndex].fTposv);								// ������U,V
	pVtx[4 * nTextureIndex + 1].tex = D3DXVECTOR2(g_Tex[nTextureIndex].fTposu + g_Tex[nTextureIndex].fTwidth, g_Tex[nTextureIndex].fTposv);
	pVtx[4 * nTextureIndex + 2].tex = D3DXVECTOR2(g_Tex[nTextureIndex].fTposu, g_Tex[nTextureIndex].fTposv + g_Tex[nTextureIndex].fTheight);
	pVtx[4 * nTextureIndex + 3].tex = D3DXVECTOR2(g_Tex[nTextureIndex].fTposu + g_Tex[nTextureIndex].fTwidth, g_Tex[nTextureIndex].fTposv + g_Tex[nTextureIndex].fTheight);

	// rhw�ƐF�̐ݒ�
	for (nCntTexture = 0; nCntTexture < 4; nCntTexture++) {
		// rhw�̐ݒ�
		pVtx[4 * nTextureIndex + nCntTexture].rhw = 1.0f;			// �K��1.0f������
		// ���_�J���[�̐ݒ�(0�`255�̐����l)
		pVtx[4 * nTextureIndex + nCntTexture].color = D3DCOLOR_RGBA(255, 255, 255, 255);		// �A���t�@�̒l�͂Ƃ肠����255
	}

	// ���_�o�b�t�@�A�����b�N
	g_pVtxBuffer->Unlock();

}

//============================================
//
//  ���O  OffTexture�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void OffTexture(int nIndex)
{
	if(g_Tex[nIndex].bUse == true)
	{
		g_Tex[nIndex].bUse = false;
	} // EO if
}

//============================================
//
//  ���O  MovePosTexture�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void MovePosTexture(int nIndex , float fMoveX , float fMoveY) // �e�N�X�`���̃|�W�V�����ړ�
{
	// �e�N�X�`������ݒ�
	g_Tex[nIndex].fPosX += fMoveX;			// ���WX
	g_Tex[nIndex].fPosY += fMoveY;			// ���WY

	int nCntTexture = 0;		// �J�E���^
	VERTEX2D* pVtx;			// ���z�A�h���X�̃|�C���^

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾����G
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�(2D���W�E�E��� Z��N�̏���)
	pVtx[4 * nIndex + 0].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX,  g_Tex[nIndex].fPosY, 0.0f);							// ������X,Y,Z
	pVtx[4 * nIndex + 1].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX + g_Tex[nIndex].fWidth, g_Tex[nIndex].fPosY, 0.0f);
	pVtx[4 * nIndex + 2].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX,  g_Tex[nIndex].fPosY + g_Tex[nIndex].fHeight, 0.0f);
	pVtx[4 * nIndex + 3].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX + g_Tex[nIndex].fWidth, g_Tex[nIndex].fPosY + g_Tex[nIndex].fHeight, 0.0f);

	// ���_�o�b�t�@�A�����b�N
	g_pVtxBuffer->Unlock();
} // EO MovePosTexture

//============================================
//
//  ���O  MoveUVTexture�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void MoveUVTexture(int nIndex , float fMoveU , float fMoveV) // �e�N�X�`����UV�ړ�
{
	// �e�N�X�`������ݒ�
	g_Tex[nIndex].fTposu += fMoveU;			// ���WY
	g_Tex[nIndex].fTposv += fMoveV;			// ���WY

	int nCntTexture = 0;		// �J�E���^
	 VERTEX2D* pVtx;			// ���z�A�h���X�̃|�C���^

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾����G
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`����UV�l�ݒ�
	pVtx[4 * nIndex + 0].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu,  g_Tex[nIndex].fTposv);
	pVtx[4 * nIndex + 1].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu + g_Tex[nIndex].fTwidth, g_Tex[nIndex].fTposv);
	pVtx[4 * nIndex + 2].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu,  g_Tex[nIndex].fTposv + g_Tex[nIndex].fTheight);
	pVtx[4 * nIndex + 3].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu + g_Tex[nIndex].fTwidth, g_Tex[nIndex].fTposv + g_Tex[nIndex].fTheight);

	// ���_�o�b�t�@�A�����b�N
	g_pVtxBuffer->Unlock();
} // EO MoveUVTexture

//============================================
//
//  ���O  GetTexturePosX�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
float GetTexturePosX(int nIndex) // X���W�̎擾
{

	return g_Tex[nIndex].fPosX;

} // EO GetTexturePosX
//============================================
//
//  ���O  GetTexturePosY�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
float GetTexturePosY(int nIndex) // Y���W�̎擾
{

	return g_Tex[nIndex].fPosY;

} // EO GetTexturePosY

//============================================
//
//  ���O  MovePosTexture�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void SetPosTexture(int nIndex , float fMoveX , float fMoveY) // �e�N�X�`���̃|�W�V�����ړ�
{
	// �e�N�X�`������ݒ�
	g_Tex[nIndex].fPosX = fMoveX;			// ���WX
	g_Tex[nIndex].fPosY = fMoveY;			// ���WY

	int nCntTexture = 0;		// �J�E���^
	VERTEX2D* pVtx;			// ���z�A�h���X�̃|�C���^

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾����G
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�(2D���W�E�E��� Z��N�̏���)
	pVtx[4 * nIndex + 0].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX,  g_Tex[nIndex].fPosY, 0.0f);							// ������X,Y,Z
	pVtx[4 * nIndex + 1].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX + g_Tex[nIndex].fWidth, g_Tex[nIndex].fPosY, 0.0f);
	pVtx[4 * nIndex + 2].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX,  g_Tex[nIndex].fPosY + g_Tex[nIndex].fHeight, 0.0f);
	pVtx[4 * nIndex + 3].pos = D3DXVECTOR3(g_Tex[nIndex].fPosX + g_Tex[nIndex].fWidth, g_Tex[nIndex].fPosY + g_Tex[nIndex].fHeight, 0.0f);

	// ���_�o�b�t�@�A�����b�N
	g_pVtxBuffer->Unlock();
} // EO MovePosTexture

//============================================
//
//  ���O  MoveUVTexture�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void SetUVTexture(int nIndex , float fMoveU , float fMoveV) // �e�N�X�`����UV�ړ�
{
	// �e�N�X�`������ݒ�
	g_Tex[nIndex].fTposu = fMoveU;			// ���WY
	g_Tex[nIndex].fTposv = fMoveV;			// ���WY

	int nCntTexture = 0;		// �J�E���^
	 VERTEX2D* pVtx;			// ���z�A�h���X�̃|�C���^

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾����G
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`����UV�l�ݒ�
	pVtx[4 * nIndex + 0].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu,  g_Tex[nIndex].fTposv);
	pVtx[4 * nIndex + 1].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu + g_Tex[nIndex].fTwidth, g_Tex[nIndex].fTposv);
	pVtx[4 * nIndex + 2].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu,  g_Tex[nIndex].fTposv + g_Tex[nIndex].fTheight);
	pVtx[4 * nIndex + 3].tex = D3DXVECTOR2(g_Tex[nIndex].fTposu + g_Tex[nIndex].fTwidth, g_Tex[nIndex].fTposv + g_Tex[nIndex].fTheight);

	// ���_�o�b�t�@�A�����b�N
	g_pVtxBuffer->Unlock();
} // EO MoveUVTexture

//============================================
//
//  ���O  MovePosTexture�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
void SetColorTexture(int nIndex , float r , float g , float b , float alpha) // �e�N�X�`���̃|�W�V�����ړ�
{
	VERTEX2D* pVtx;			// ���z�A�h���X�̃|�C���^

	// ���_�o�b�t�@�����b�N���ĉ��z�A�h���X���擾����G
	g_pVtxBuffer->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�(2D���W�E�E��� Z��N�̏���)
	pVtx[4 * nIndex + 0].color = D3DXCOLOR(r, g , b , alpha);							// ������X,Y,Z
	pVtx[4 * nIndex + 1].color = D3DXCOLOR(r, g , b , alpha);
	pVtx[4 * nIndex + 2].color = D3DXCOLOR(r, g , b , alpha);
	pVtx[4 * nIndex + 3].color = D3DXCOLOR(r, g , b , alpha);

	// ���_�o�b�t�@�A�����b�N
	g_pVtxBuffer->Unlock();
} // EO MovePosTexture

TEXTURE_a* GetTexture(int nIndex)
{
	return &g_Tex[nIndex];
}

void AllOffTexture(void)
{
	int nCntTex = 0;
	// �e�N�X�`������������
	for (nCntTex = 0; nCntTex < MAX_TEXTURE; nCntTex++)
	{
		g_Tex[nCntTex].fPosX = 0;		// ���WX
		g_Tex[nCntTex].fPosY = 0;		// ���WY
		g_Tex[nCntTex].fWidth = 0;		// ��
		g_Tex[nCntTex].fHeight = 0;		// ����
		g_Tex[nCntTex].fTposu = 0;		// U�̒l
		g_Tex[nCntTex].fTposv = 0;		// V�̒l
		g_Tex[nCntTex].fTwidth = 0;		// UV�l�̕�
		g_Tex[nCntTex].fTheight = 0;	// UV�l�̍���
		g_Tex[nCntTex].bUse = false;	// �g�p�t���O
	}
} // EO AllOffTexture
