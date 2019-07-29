//-------------------------------------------------------
//	�i���o�[����[number.cpp]
//	Author : KAZUNORI MARUHASHI
//	
//-------------------------------------------------------

//-------------------------------------------------------
//	�X�V����
//-------------------------------------------------------
/*
	2017/02/22
		�쐬


*/
//-------------------------------------------------------
//	�C���N���[�h�t�@�C��
//-------------------------------------------------------
#include "main.h"		//���C���w�b�_
#include "number.h"
#include <math.h>

//-------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------
#define NUMBER_TEXTURENAME "data/TEXTURE/number.png"		//�e�N�X�`���A�h���X

//-------------------------------------------------------
//	�\���̒�`
//-------------------------------------------------------

//-------------------------------------------------------
//	�v���g�^�C�v�錾
//-------------------------------------------------------
HRESULT MakeVertexNumber(LPDIRECT3DDEVICE9 pDevice);
void SetNumberPos(float fPosX, float fPosY);

//-------------------------------------------------------
//	�O���[�o���ϐ�
//-------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferNumber = NULL;

int g_iNumber;

//-------------------------------------------------------
//	�|���S������������
//-------------------------------------------------------
void InitNumber(void)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�̎擾

	//���_�̐ݒ�
	if(FAILED(MakeVertexNumber(pDevice)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐ݒ�Ɏ��s���܂����B", " ", MB_OK);
		return;
	}

	//�^�[�Q�b�g��������
	g_iNumber = 0;
}

//-------------------------------------------------------
//	�|���S���I������
//-------------------------------------------------------
void UninitNumber(void)
{
	if(g_pVtxBufferNumber != NULL)
	{
		g_pVtxBufferNumber -> Release();
		g_pVtxBufferNumber = NULL;
	}
}

//-------------------------------------------------------
//	�|���S���X�V����
//-------------------------------------------------------
void UpdateNumber(void)
{

}

//-------------------------------------------------------
//	���_�̍쐬
//-------------------------------------------------------
HRESULT MakeVertexNumber(LPDIRECT3DDEVICE9 pDevice)
{
	VERTEX2D* pVtx;	//���z�A�h���X�擾�p�|�C���^

	if(FAILED(pDevice -> CreateVertexBuffer(sizeof(VERTEX2D)*8,	//�m�ۂ��������_�o�b�t�@�̐������_��
								  D3DUSAGE_WRITEONLY,	//�m�ۂ����㒆�����邱�Ƃ͂ł��Ȃ�
								  FVF_VERTEX_2D,		//�ꉞ�������Ƃ����C
								  D3DPOOL_MANAGED,		//�������Ǘ����ǂ����邩(����͂��C��)
								  &g_pVtxBufferNumber,
								  NULL)))
	{
		return E_FAIL;
	}

	//���z�A�h���X���擾����
	g_pVtxBufferNumber -> Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�ix, y, z�j
	pVtx[0].pos = D3DXVECTOR3(0.0f-0.5f, 0.0f-0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH-0.5f, 0.0f-0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f-0.5f, SCREEN_HEIGHT-0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH-0.5f, SCREEN_HEIGHT-0.5f, 0.0f);

	//rhw�̐ݒ�(�K��1.0f)
	pVtx[0].rhw =
	pVtx[1].rhw =
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	//�J���[�̐ݒ�
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//�e�N�X�`���\���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	g_pVtxBufferNumber -> Unlock();

	return S_OK;
}

void DrawNumber(int iNumber, int iDigit, D3DXVECTOR2 Pos, D3DXVECTOR2 Size, float fMargin, LPDIRECT3DTEXTURE9 pTexture)
{
	
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�̎擾
	
	pDevice ->SetStreamSource(0, 
							  g_pVtxBufferNumber,
							  0,					//�I�t�Z�b�g
							  sizeof(VERTEX2D));		//�X�g���C�h��
	

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	pDevice -> SetTexture(0, pTexture);

	int iValue = iNumber;
	int iDrawNumber = 0;

	for(int iAllNumber = 0; iAllNumber < iDigit; iAllNumber++){
		iDrawNumber = iValue % 10;
		iValue *= 0.1f;

		SetNumber(iDrawNumber, Pos - D3DXVECTOR2(fMargin * iAllNumber, 0.0f), Size);

		//�v���~�e�B�u�̕`��
		pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								 0,					//�I�t�Z�b�g(���_��)
								 4);			//�v���~�e�B�u��
		//���������݂��Ȃ��ꍇ
		if(iValue < 1){
			break;
		}
	}
}

void DrawNumberFloat(float iNumber, int iDigit, int fFloatDigit, D3DXVECTOR2 Pos, D3DXVECTOR2 Size, float fMargin, LPDIRECT3DTEXTURE9 pTexture)
{
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//�f�o�C�X�̎擾
	VERTEX2D* pVtx;	//���z�A�h���X�擾�p�|�C���^

	//�������̕`��
	DrawNumber((int)iNumber, iDigit, Pos, Size, fMargin, pTexture);

	//===== �����_�̕`�� =====//

	//���z�A�h���X���擾����
	g_pVtxBufferNumber -> Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�ix, y, z�j
	pVtx[0].pos = D3DXVECTOR3(Pos.x + fMargin - Size.x * 0.5f, Pos.y - Size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pos.x + fMargin + Size.x * 0.5f, Pos.y - Size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pos.x + fMargin - Size.x * 0.5f, Pos.y + Size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pos.x + fMargin + Size.x * 0.5f, Pos.y + Size.y * 0.5f, 0.0f);

	//�e�N�X�`���\���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.5f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	g_pVtxBufferNumber -> Unlock();

	pDevice ->SetStreamSource(0, 
							  g_pVtxBufferNumber,
							  0,					//�I�t�Z�b�g
							  sizeof(VERTEX2D));		//�X�g���C�h��

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF(FVF_VERTEX_2D);

	pDevice -> SetTexture(0, pTexture);

	//�v���~�e�B�u�̕`��
	pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
								0,					//�I�t�Z�b�g(���_��)
								4);			//�v���~�e�B�u��

	//===== �����_�̕`�� �I��=====//

	float iSelf = iNumber;

	for(int iLoop = 0; iLoop < fFloatDigit; iLoop++){
		 iSelf *= 10;

		 //�������̕`��
		DrawNumber((int)iSelf, 1, Pos + D3DXVECTOR2(fMargin * (2.0f + 1.0f * iLoop), 0.0f), Size, -fMargin, pTexture);
	}

	

}

void SetNumber(int iNumber, D3DXVECTOR2 Pos, D3DXVECTOR2 Size)
{
	VERTEX2D* pVtx;	//���z�A�h���X�擾�p�|�C���^

	//���z�A�h���X���擾����
	g_pVtxBufferNumber -> Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�ix, y, z�j
	pVtx[0].pos = D3DXVECTOR3(Pos.x - Size.x * 0.5f, Pos.y - Size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(Pos.x + Size.x * 0.5f, Pos.y - Size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(Pos.x - Size.x * 0.5f, Pos.y + Size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(Pos.x + Size.x * 0.5f, Pos.y + Size.y * 0.5f, 0.0f);

	//�e�N�X�`���\���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.1f * iNumber, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f * iNumber + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f * iNumber, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.1f * iNumber + 0.1f, 0.5f);

	g_pVtxBufferNumber -> Unlock();
}

//-------------------------------------------------------
//	�F�̐ݒ�
//-------------------------------------------------------
void SetColor(D3DXCOLOR color)
{
	VERTEX2D* pVtx;	//���z�A�h���X�擾�p�|�C���^

	//���z�A�h���X���擾����
	g_pVtxBufferNumber -> Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[0].color = color;
	pVtx[1].color = color;
	pVtx[2].color = color;
	pVtx[3].color = color;

	g_pVtxBufferNumber -> Unlock();
}