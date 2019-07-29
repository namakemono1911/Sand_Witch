//============================================
//  Warning�֌W  (Warning.c)
//
//  Author  Information
//  �N���X  AT12D249
//  �o�Ȕԍ�  1��
//  ���O  �Έ�  �Y��
//  �쐬��   2016�N6��29��
//  �C����   �N����
//
//============================================

//============================================
//
//  �C���N���[�h�t�@�C��
//
//============================================
#include "main.h"
#include "warning.h"
#include "player.h"
#include "notes.h"

//============================================
//
//  �ϐ���`
//
//============================================
/*�w�i�֌W*/
#define WARNING_FILE_NAME   "data/TEXTURE/GAME/UI/warn.png"          //�o�b�N�O���E���h�̃t�@�C����
#define WARNING_FILE_NAME1  "data/TEXTURE/GAME/UI/warning.png"          //�o�b�N�O���E���h�̃t�@�C����
#define WARNING_NUM         (20)                 // ���[�j���O�̐�
#define WARNING_X           (0.0f)            //���[�j���O1���ڂ�X���W
#define WARNING_Y           (90.0f)             //���[�j���O1���ڂ�Y���W
#define WARNING_WIDTH       (100)             //���[�j���O1���̕�
#define WARNING_HEIGHT      (LINE_HEIGHT- 20.0f)             //���[�j���O1���̍���
#define WARNING_MAX_FLAME   (45.0f)               // ���[�j���O���_�ł���Ԋu
#define WARNING_SUB         (1.0f / WARNING_MAX_FLAME) // �����ɂȂ�Ԋu

#define WARNING_ANIM_COUNT 3

//============================================
//
//  �v���g�^�C�v�錾
//
//============================================
HRESULT MakeVertexWarning(LPDIRECT3DDEVICE9 pDevice);			// ���_�쐬

//============================================
//
//  �O���[�o���ϐ�
//
//============================================
//LP�̓|�C���^�[!!
LPDIRECT3DTEXTURE9 g_pTextureWarning[2] = {};//BG�̒���e�N�X�`���A�e�N�X�`���C���^�[�t�F�[�X

/*���_�o�b�t�@�Ǘ��p*/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferWarning = NULL;//�|�C���^�[!!&������

WARNING		  g_aWarning[WARNING_NUM];		  // �\�����[�j���O�\����

//============================================
//
//  ���O  InitWarning�֐�
//  ����   void
//  �߂�l void
//  ���� ���[�j���O�֌W�̏���������
//
//============================================
HRESULT InitWarning()
{
	int nCnt = 0;

	UINT nID;  //���b�Z�[�W�{�b�N�X�̕Ԃ�l������
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	
	//�e�N�X�`���擾
	//�G���[�`�F�b�N�K�{
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , WARNING_FILE_NAME , &g_pTextureWarning[0] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "���[�j���O�e�N�X�`�����擾�ł��܂���ł����B","�Ђ���ف`��",MB_OK | MB_DEFBUTTON1);
		}//EOif
	//�G���[�`�F�b�N�K�{
	if(FAILED(
		D3DXCreateTextureFromFile( pDevice , WARNING_FILE_NAME1 , &g_pTextureWarning[1] )//�e�N�X�`���̓ǂݍ��݁A�f�B�X�N����ǂݍ��ނ�!!!!!!
		))
		{
			//�G���[���b�Z�[�W
			nID = MessageBox(NULL , "���[�j���O�e�N�X�`�����擾�ł��܂���ł����B","�Ђ���ف`��",MB_OK | MB_DEFBUTTON1);
		}//EOif
	
	// �\�����[�j���O�\���̂̏�����
	for(nCnt = 0; nCnt < WARNING_NUM;nCnt++)
	{
		g_aWarning[nCnt].bUse = false;
		g_aWarning[nCnt].fPos.x = WARNING_X;
		g_aWarning[nCnt].fPos.y = WARNING_Y;
		g_aWarning[nCnt].bFlash = false;
		g_aWarning[nCnt].fAlpha = 0.0f;
		g_aWarning[nCnt].nCntflash = 0;
		g_aWarning[nCnt].nMaxFlash = WARNING_MAX_FLAME;

	} // EO for

	//���_�쐬
	if(FAILED(MakeVertexWarning(pDevice)))
	{
		return E_FAIL;
	}//EOif

	return S_OK;
}//EOInitWarning

//============================================
//
//  ���O  UnitnitWarning�֐�
//  ����   void
//  �߂�l void
//  ���� ���[�j���O�֌W�̏I������
//
//============================================
void UninitWarning()
{
	// �e�N�X�`���C���^�[�t�F�C�X
	SAFE_RELEASE(g_pTextureWarning[0]);
	SAFE_RELEASE(g_pTextureWarning[1]);

	// ���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X
	if (g_pVtxBufferWarning != NULL)
	{
		g_pVtxBufferWarning->Release();			// ���_�o�b�t�@�Ǘ��C���^�[�t�F�C�X�̉��
		g_pVtxBufferWarning = NULL;				// �A�h���X��NULL�ɂ���
	}
}//EOUninitWarning

//============================================
//
//  ���O  UpdataWarning�֐�
//  ����   void
//  �߂�l void
//  ���� ���[�j���O�֌W�̍X�V����
//
//============================================
void UpdateWarning()
{
	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferWarning -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

		// �ő吔��
	for(int nCntNotes = 0 ; nCntNotes < WARNING_NUM ; nCntNotes++)
	{
		if(g_aWarning[nCntNotes].bUse == true)
		{
			switch(g_aWarning[nCntNotes].type)
			{
			case WARNING_NORMAL:
				{
					g_aWarning[nCntNotes].fAlpha -= 0.005f;
					if(g_aWarning[nCntNotes].fAlpha >= 1.0f)
					{
						g_aWarning[nCntNotes].bUse = false;
					}
					//���_�J���[(0�`255�̐����l)
					pVtx[0 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[1 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[2 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[3 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);

					pVtx [ 0 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x , g_aWarning[nCntNotes].fPos.y , 0.0f);
					pVtx [ 1 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x + WARNING_WIDTH ,g_aWarning[nCntNotes].fPos.y , 0.0f);
					pVtx [ 2 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x , g_aWarning[nCntNotes].fPos.y + WARNING_HEIGHT , 0.0f);
					pVtx [ 3 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x + WARNING_WIDTH , g_aWarning[nCntNotes].fPos.y +WARNING_HEIGHT , 0.0f);
				}
				break;
			case WARNING_BOSS:
				{

					if(g_aWarning[nCntNotes].bFlash == false)
					{

						g_aWarning[nCntNotes].fAlpha -= 0.05f;
						if(g_aWarning[nCntNotes].fAlpha <= 0.0f)
						{
							g_aWarning[nCntNotes].nCntflash++;
								if(g_aWarning[nCntNotes].nCntflash >= WARNING_ANIM_COUNT)
							{
								g_aWarning[nCntNotes].bUse = false;
							}
							g_aWarning[nCntNotes].bFlash = true;
						} // EO if
					} // EO if
					else
					{
						g_aWarning[nCntNotes].fAlpha += 0.05f;
						if(g_aWarning[nCntNotes].fAlpha >= 1.0f)
						{
							g_aWarning[nCntNotes].bFlash = false;
						} // EO if
					}
					//���_�J���[(0�`255�̐����l)
					pVtx[0 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[1 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[2 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);
					pVtx[3 + 4 * nCntNotes].color = D3DXCOLOR(1.0f , 1.0f , 1.0f , g_aWarning[nCntNotes].fAlpha);

					pVtx [ 0 + 4*nCntNotes] . pos = D3DXVECTOR3 (0.0f , 0.0f , 0.0f);
					pVtx [ 1 + 4*nCntNotes] . pos = D3DXVECTOR3 (SCREEN_WIDTH,0.0f, 0.0f);
					pVtx [ 2 + 4*nCntNotes] . pos = D3DXVECTOR3 (0.0f ,SCREEN_HEIGHT, 0.0f);
					pVtx [ 3 + 4*nCntNotes] . pos = D3DXVECTOR3 (SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
				}
				break;
			}

		} // EO if
	} // EO for

	//�����A�����b�N
	g_pVtxBufferWarning -> Unlock();
}//EOUpdateWarning

//============================================
//
//  ���O  DrawWarning�֐�
//  ����   void
//  �߂�l void
//  ����  ���[�j���O�֌W�̕`�揈��
//
//============================================
void DrawWarning()
{
	/*�ϐ��錾*/
	int i = 0;

	//�e�N�X�`���ݒ�
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	// �v���~�e�B�u�̐ݒ�
	pDevice->SetStreamSource(
		0,
		g_pVtxBufferWarning,
		0,								// �I�t�Z�b�g(�P�ʃo�C�g)
		sizeof(VERTEX2D));				// �X�g���C�h�ʁB���_�f�[�^1���̃T�C�Y

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D | D3DFVF_TEX1);

	// �`��
	for (int i  = 0; i < WARNING_NUM; i++)
	{
		// �g�p�t���O��ON�Ȃ�`��
		if (g_aWarning[i].bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			switch(g_aWarning[i].type)
			{
			case WARNING_NORMAL:
				{
					pDevice->SetTexture(0, g_pTextureWarning[0]);
				}
				break;
			case WARNING_BOSS:
				{
					pDevice->SetTexture(0, g_pTextureWarning[1]);
				}
				break;
			}

			// �v���~�e�B�u�̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,			// �v���~�e�B�u�̎��
				i * 4,				// �I�t�Z�b�g(���_��)
				NUM_POLYGON);					// �v���~�e�B�u��
		}
	}
}//EODrawWarning

//============================================
//
//  ���O  MakeVertexWarning�֐�
//  ����
//  �߂�l
//  ����
//
//============================================
HRESULT MakeVertexWarning(LPDIRECT3DDEVICE9 pDevice)
{
	//���_�o�b�t�@�쐬
	if(FAILED(
		pDevice -> CreateVertexBuffer(sizeof(VERTEX2D) * NUM_VERTEX * WARNING_NUM,//�쐬���������_�o�b�t�@�̃T�C�Y = 1�̒��_�̃T�C�Y * ���_��
																	//�ǂꂭ�炢�������ق������A�������߂�����ӂ₷��Ł[�[�[
			D3DUSAGE_WRITEONLY,									//���_�o�b�t�@�̎g�p���@�A�������ݐ�p�Ȃ̂ŁA���炭�ő�
			FVF_VERTEX_2D,										//NULL��0�ł����v�A�}�i�[�I�ɂ͏�������B���̃o�b�t�@�̒��_�t�H�[�}�b�g��₤
			D3DPOOL_MANAGED,									//�������Ǘ��ǂ�����ݒ�A���̏�Ԃ̓f�o�C�X�ɂ��C��
			&g_pVtxBufferWarning,						//�o���オ�������_�o�b�t�@���Ǘ�����A�h���X
			NULL)												//�䂾�����NULL
	))
	{
		return E_FAIL;
	}


	//���_�o�b�t�@
	VERTEX2D* pVtx;//���z�A�h���X���擾���邽�߂̃|�C���^�[�A������hiaruyo
	//���_�o�b�t�@�����b�N���āA���z�A�h���X���擾����
	g_pVtxBufferWarning -> Lock(0,	//�ǂ����烍�b�N���邩
								0,				//�ǂ��܂Ń��b�N���邩(0~0�őS�����b�N)
								(void**)&pVtx,	//�|�C���^�̃|�C���^(�A�h���X�������ꂽ�������̃A�h���X)
								0);				//�l�ڒ��ׂ�Ɩʔ��������B

		// �ő吔��
	for(int nCntNotes = 0 ; nCntNotes < WARNING_NUM ; nCntNotes++)
	{
		
		//���_���W�̐ݒ�(2D���W , �E��� )
		pVtx [ 0 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x , g_aWarning[nCntNotes].fPos.y , 0.0f);
		pVtx [ 1 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x + WARNING_WIDTH ,g_aWarning[nCntNotes].fPos.y , 0.0f);
		pVtx [ 2 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x , g_aWarning[nCntNotes].fPos.y + WARNING_HEIGHT , 0.0f);
		pVtx [ 3 + 4*nCntNotes] . pos = D3DXVECTOR3 (g_aWarning[nCntNotes].fPos.x + WARNING_WIDTH , g_aWarning[nCntNotes].fPos.y +WARNING_HEIGHT , 0.0f);

	    //�e���_�̃e�N�X�`�����W�̐ݒ�
		pVtx [ 0 + 4*nCntNotes] . tex = D3DXVECTOR2 (0 , 0);
		pVtx [ 1 + 4*nCntNotes] . tex = D3DXVECTOR2 (1 , 0);
		pVtx [ 2 + 4*nCntNotes] . tex = D3DXVECTOR2 (0 , 1);
		pVtx [ 3 + 4*nCntNotes] . tex = D3DXVECTOR2 (1 , 1);

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
	g_pVtxBufferWarning -> Unlock();

	return S_OK;
}

//============================================
//
//  ���O  SetWarning�֐�
//  ����   void
//  �߂�l void
//  ����  ���[�j���O�̃Z�b�g
//
//============================================
int SetWarning (float fPosY  , WARNING_TYPE type)
{
	for(int nCnt = 0 ; WARNING_NUM ; nCnt++)
	{
		if(g_aWarning[nCnt].bUse == false)
		{
			g_aWarning[nCnt].bFlash = true;
			g_aWarning[nCnt].fAlpha = 1.0f;
			g_aWarning[nCnt].fPos = D3DXVECTOR2(0.0f , fPosY);
			g_aWarning[nCnt].nCntflash = 0;
			g_aWarning[nCnt].nMaxFlash = WARNING_MAX_FLAME;
			g_aWarning[nCnt].bUse = true;
			g_aWarning[nCnt].type = type;
			switch(type)
			{
			case WARNING_NORMAL:
				{
					float x = SCREEN_WIDTH / 100.0f * 90;
					g_aWarning[nCnt].fPos.x = x;
				}
				break;
			case WARNING_BOSS:
				{
					g_aWarning[nCnt].fPos.x = 0.0f;
				}
				break;
			}
			return nCnt;
		} // EO if
	} // EO for

	return -1;
}//EOSetWarning

//============================================
//
//  ���O  OffWarning�֐�
//  ����   int nIndex
//  �߂�l void
//  ���� ���[�j���O�̃C���f�b�N�X�w��I��
//
//============================================
void OffWarning(int nIndex)
{
	if(g_aWarning[nIndex].bUse == true && nIndex != -1)
	{
		g_aWarning[nIndex].bUse = false;
	} // EO if
}//EOUninitWarning
