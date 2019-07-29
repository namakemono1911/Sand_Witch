//============================================
//  Effect�֐�  (Effect.cpp)
//
//  Author  Information
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N07��24��
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
#include "main.h"
#include "effect.h"

//============================================
//
//  �萔�錾
//
//============================================
#define MAX_EFFECT 100

#define EFFECT_ONE_DIS_MAX			3
#define EFFECT_TWO_DIS_MAX			3
#define EFFECT_THREE_DIS_MAX		3
#define EFFECT_FOUR_DIS_MAX			1
#define EFFECT_FIVE_DIS_MAX			3
#define EFFECT_SIX_DIS_MAX			3
#define EFFECT_SEVEN_DIS_MAX		3
#define EFFECT_EIGHT_DIS_MAX		3

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureEffect[EFFECT_MAX] = {};//Effect�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferEffect = NULL;//�|�C���^�[!!&������

/*�m�[�c�\����*/
EFFECT g_aEffect[MAX_EFFECT];

char* EffectTexName[] = {
	"data/TEXTURE/GAME/UI/kaihuku.png",
	"data/TEXTURE/GAME/UI/waza.png",
	"data/TEXTURE/GAME/UI/wazaon.png",
	"data/TEXTURE/GAME/UI/mahou01.png",
	"data/TEXTURE/GAME/UI/mahou02.png",
	"data/TEXTURE/GAME/UI/mahou022.png",
	"data/TEXTURE/GAME/UI/bakuhatu0221.png",
	"data/TEXTURE/GAME/UI/bakuhatu02-2.png",
};

int g_anDisTime[] = {3,3,3 , 1,3,1,1,3
};

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice);//���_�̍쐬

//============================================
//
//  ���O  InitEffect�֐�
//  ����	void
//  �߂�l  void
//  ����  Effect�֌W�̏�����
//
//============================================
HRESULT InitEffect(void)
{
	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//���_�쐬
	if(FAILED(MakeVertexEffect(pDevice)))
	{
		return E_FAIL;
	}//EOif
	
	for(int i = 0 ; i < EFFECT_MAX ; i++)
	{
		//�e�N�X�`���擾
		if(FAILED(
		D3DXCreateTextureFromFile( pDevice , EffectTexName[i] , &g_pTextureEffect[i] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
			))
			{
				//�G���[���b�Z�[�W
				nID = MessageBox(NULL , "�e�N�X�`�����擾�ł��܂���ł����B","",MB_OK | MB_DEFBUTTON1);
			}//EOif
	}

	// �m�[�c�\���̂̏�����
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		g_aEffect[nCntEffect].bUse = false;
		g_aEffect[nCntEffect].bAnim = true;
		g_aEffect[nCntEffect].nMode = EFFECT_MAX;
		g_aEffect[nCntEffect].nAnimFlame = 0;
		g_aEffect[nCntEffect].nAnimFlameMax = 0;
		g_aEffect[nCntEffect].nAnimFlameBuf = 0;
		g_aEffect[nCntEffect].tex.pos = D3DXVECTOR2(0 , 0);
		g_aEffect[nCntEffect].tex.size = D3DXVECTOR2(0 , 0);
		g_aEffect[nCntEffect].poly.pos = D3DXVECTOR3(0 , 0 , 0);
		g_aEffect[nCntEffect].poly.size = D3DXVECTOR3(0 , 0 , 0);

	} // EO for

	return S_OK;
}//EOInitEffect

//============================================
//
//  ���O  UninitEffect�֐�
//  ����	void
//  �߂�l  void
//  ����  Effect�֌W�̏I������
//
//============================================
void UninitEffect(void)
{
	for(int nCntEffect = 0 ; nCntEffect < EFFECT_MAX  ; nCntEffect++)
	{
		//�e�N�X�`���C���^�[�t�F�[�X�̌�Еt��
		SAFE_RELEASE( g_pTextureEffect[nCntEffect] );
	} // EO for

	//���_�o�b�t�@�̌�Еt��
	SAFE_RELEASE( g_pVtxBufferEffect );
}//EOUninitEffect

//============================================
//
//  ���O  UpdateEffect�֐�
//  ����	void
//  �߂�l  void
//  ����  Effect�֌W�̍X�V����
//
//============================================
void UpdateEffect(void)
{
	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo

		//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferEffect -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

	// UV�A�j���[�V�����Ńm�[�c
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		// �g�p�`�F�b�N
		if(g_aEffect[nCntEffect].bUse == true)
		{
			if(g_aEffect[nCntEffect].bAnim == true)
			{
				g_aEffect[nCntEffect].nAnimFlame++;
				if(g_aEffect[nCntEffect].nAnimFlame > g_aEffect[nCntEffect].nAnimFlameMax)
				{
					if(g_aEffect[nCntEffect].nAnimFlameBuf == 0)
					{
						g_aEffect[nCntEffect].nAnimFlame = 0;
						g_aEffect[nCntEffect].tex.pos += g_aEffect[nCntEffect].tex.size;
					}

					if(g_aEffect[nCntEffect].tex.pos.x >= 1.0f || g_aEffect[nCntEffect].nAnimFlameBuf != 0)
					{
						// ���ʏ���(�ʏ�e)
						if(g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_NORMAL_1)
						{
							if(g_aEffect[nCntEffect].nAnimFlameBuf == 0)
							{
								SetEffect(g_aEffect[nCntEffect].poly.pos.x , g_aEffect[nCntEffect].poly.pos.y , g_aEffect[nCntEffect].poly.size.x,
									g_aEffect[nCntEffect].poly.size.y , EFFECT_MAGIC_ON_NORMAL_2);
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								g_aEffect[nCntEffect].tex.pos -= g_aEffect[nCntEffect].tex.size;
							}
							else
							{
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								if(g_aEffect[nCntEffect].nAnimFlameBuf >= g_anDisTime[4] * 10.0f)
								{
									g_aEffect[nCntEffect].bAnim = false;
								}
							}
						}
						else if(g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_EXPLOSION_1)
						{
							if(g_aEffect[nCntEffect].nAnimFlameBuf == 0)
							{
								SetEffect(g_aEffect[nCntEffect].poly.pos.x , g_aEffect[nCntEffect].poly.pos.y , g_aEffect[nCntEffect].poly.size.x,
									g_aEffect[nCntEffect].poly.size.y , EFFECT_MAGIC_ON_EXPLOSION_2);
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								g_aEffect[nCntEffect].tex.pos -= g_aEffect[nCntEffect].tex.size;
							}
							else
							{
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								if(g_aEffect[nCntEffect].nAnimFlameBuf >= g_anDisTime[6] * 10.0f + g_anDisTime[7] * 10.0f)
								{
									g_aEffect[nCntEffect].bAnim = false;
								}
							}
						}
						else if(g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_EXPLOSION_2)
						{
							if(g_aEffect[nCntEffect].nAnimFlameBuf == 0)
							{
								SetEffect(g_aEffect[nCntEffect].poly.pos.x , g_aEffect[nCntEffect].poly.pos.y , g_aEffect[nCntEffect].poly.size.x,
									g_aEffect[nCntEffect].poly.size.y , EFFECT_MAGIC_ON_EXPLOSION_3);
								g_aEffect[nCntEffect].bAnim = false;
								g_aEffect[nCntEffect].fAlphaDif += 0.02f;
								g_aEffect[nCntEffect].nAnimFlameBuf++;
								g_aEffect[nCntEffect].tex.pos -= g_aEffect[nCntEffect].tex.size;
							}
						}
						else if(g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_EXPLOSION_3 || g_aEffect[nCntEffect].nMode == EFFECT_MAGIC_ON_NORMAL_2)
						{
							g_aEffect[nCntEffect].bAnim = false;
							g_aEffect[nCntEffect].fAlphaDif = 0.008f;
							g_aEffect[nCntEffect].tex.pos -= g_aEffect[nCntEffect].tex.size;
						}
						else
						{
							g_aEffect[nCntEffect].bUse = false;
						}
					}
				}
			}
			else
			{
				g_aEffect[nCntEffect].fAlpha -= g_aEffect[nCntEffect].fAlphaDif;
				if(g_aEffect[nCntEffect].fAlpha <= 0.0f)
				{
					g_aEffect[nCntEffect].bUse = false;
				}
			}

			//���_���W�̐ݒ�(2D���W , �E��� )
			setBuffer(&pVtx[4 * nCntEffect], g_aEffect[nCntEffect].poly);

		    //�e���_�̃e�N�X�`�����W�̐ݒ�
			setTexture(&pVtx[4 * nCntEffect], g_aEffect[nCntEffect].tex);

			//���_�J���[(0�`255�̐����l)
			pVtx[0 + 4 * nCntEffect].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aEffect[nCntEffect].fAlpha);
			pVtx[1 + 4 * nCntEffect].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aEffect[nCntEffect].fAlpha);
			pVtx[2 + 4 * nCntEffect].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aEffect[nCntEffect].fAlpha);
			pVtx[3 + 4 * nCntEffect].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aEffect[nCntEffect].fAlpha);
		} // EO if
	} // EO for

	g_pVtxBufferEffect->Unlock ();												//���b�N����

}//EOUpdateEffect

//============================================
//
//  ���O  DrawEffect�֐�
//  ����	void
//  �߂�l  void
//  ����  Effect�֌W�̕`�揈��
//
//============================================
void DrawEffect(void)
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//�p�C�v���C���̐ݒ�
	pDevice -> SetStreamSource(0,//�X�g���[���ԍ�(���{������)
						g_pVtxBufferEffect ,//�f�[�^�̂���ꏊ(�擪�A�h���X)
						0,//�I�t�Z�b�g(�P�ʃo�C�g)�A�f�[�^�̂ǂ̕ӂ��玝���Ă��邩,0�͐擪
						sizeof(VERTEX2D) );//�X�g���C�h��(��̒P�ʂ̑傫��)

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice -> SetFVF( FVF_VERTEX_2D | D3DFVF_TEX1 );

	// �ő吔�`�F�b�N
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse == true)
		{

			pDevice -> SetTexture( 0 , g_pTextureEffect[g_aEffect[nCntEffect].nMode] );

			//�v���~�e�B�u�̕`��
			pDevice -> DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v���~�e�B�u�̎��
				nCntEffect * 4 ,//�I�t�Z�b�g(���_��)�����_�ڂ���Ƃ邩
				NUM_POLYGON );//�������_�����Ă���΂����̂��A�v���~�e�B�u�̖������������Q���B�p�C�v���C���͐��ꗬ���ɂȂ��Ă��邩��B
		} // EO if
	} // EO for
}//EODarwEffect

//============================================
//
//  ���O  MakeVertexEffect�֐�
//  ����	LPDIRECT3DDEVICE9 pDevice
//  �߂�l  void
//  ����  ���_�̍쐬
//
//============================================
HRESULT MakeVertexEffect(LPDIRECT3DDEVICE9 pDevice)
{

	//���_�o�b�t�@�쐬
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * MAX_EFFECT,//�쐬���������_�o�b�t�@�̃T�C�Y = 1�̒��_�̃T�C�Y * ���_��
																	//�ǂꂭ�炢�������ق������A�������߂�����ӂ₷��Ł[�[�[
			D3DUSAGE_WRITEONLY,									//���_�o�b�t�@�̎g�p���@�A�������ݐ�p�Ȃ̂ŁA���炭�ő�
			FVF_VERTEX_2D,										//NULL��0�ł����v�A�}�i�[�I�ɂ͏�������B���̃o�b�t�@�̒��_�t�H�[�}�b�g��₤
			D3DPOOL_MANAGED,									//�������Ǘ��ǂ�����ݒ�A���̏�Ԃ̓f�o�C�X�ɂ��C��
			&g_pVtxBufferEffect,						//�o���オ�������_�o�b�t�@���Ǘ�����A�h���X
			NULL)												//�䂾�����NULL
	))
	{
		return E_FAIL;
	}


	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferEffect -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

		// �ő吔��
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		//rhw�̐ݒ�(�K��1.0f������!!!!!!!!)
		pVtx[0 + 4 * nCntEffect].rhw = 1.0f;
		pVtx[1 + 4 * nCntEffect].rhw = 1.0f;
		pVtx[2 + 4 * nCntEffect].rhw = 1.0f;
		pVtx[3 + 4 * nCntEffect].rhw = 1.0f;

		//���_�J���[(0�`255�̐����l)
		pVtx[0 + 4 * nCntEffect].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[1 + 4 * nCntEffect].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[2 + 4 * nCntEffect].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);
		pVtx[3 + 4 * nCntEffect].color = D3DCOLOR_RGBA(255 , 255 , 255 , 255);

	} // EO for

	//�����A�����b�N
	g_pVtxBufferEffect -> Unlock();

	return S_OK;

}//EOMakeVertexEffect

//============================================
//
//  ���O  SetEffect�֐�
//  ����	void
//  �߂�l  float fPosX ,float fPosY,float fWidth,float fHeught,Effect_MODE nMode
//  ����  �m�[�c���Z�b�g
//
//============================================
void    SetEffect    (float fPosX , // ���S���WX
	float fPosY,					   // ���S���WY
	float fWidth,					   // ��
	float fHeught,					   // ����
	EFFECT_MODE nMode			   // ���
	)
{
	for(int nCntEffect = 0 ; nCntEffect < MAX_EFFECT ; nCntEffect++)
	{
		if(g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].bUse = true;
			g_aEffect[nCntEffect].nMode = nMode;
			g_aEffect[nCntEffect].tex.pos = D3DXVECTOR2(0 , 0);
			g_aEffect[nCntEffect].tex.size = D3DXVECTOR2(0.1f , 1);
			g_aEffect[nCntEffect].poly.size = D3DXVECTOR3(fWidth , fHeught , 0);
			g_aEffect[nCntEffect].poly.pos= D3DXVECTOR3(fPosX , fPosY , 0);
			g_aEffect[nCntEffect].nAnimFlame = 0;
			g_aEffect[nCntEffect].nAnimFlameBuf = 0;
			g_aEffect[nCntEffect].bAnim = true;
			g_aEffect[nCntEffect].nAnimFlameMax = g_anDisTime[nMode];
			g_aEffect[nCntEffect].fAlpha = 1.0f;
			g_aEffect[nCntEffect].fAlphaDif = 0.01f;
			
			return;
		} // EO if
	} // EO for
} // EO SetEffect


