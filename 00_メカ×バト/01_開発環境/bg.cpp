//===================================================
//
// �w�i�̏���
// Author:Teruto Sato
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "bg.h"
#include "renderer.h"
#include "texture.h"

//========================
// �R���X�g���N�^
//========================
CBg::CBg() : CObject(1)
{
	m_pObject2D = nullptr;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	m_nFlashTime = 0;	//�_�Ŏ���
	m_fWidth = 0.0f;	//��
	m_fHeight = 0.0f;	//����
}

//========================
// �f�X�g���N�^
//========================
CBg::~CBg()
{

}

//========================
// ������
//========================
HRESULT CBg::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;
	m_nFlashTime = 0;
	m_fWidth = SCREEN_WIDTH;
	m_fHeight = SCREEN_HEIGHT;

	if (m_pObject2D != nullptr)
	{
		m_pObject2D->Init(m_pos);

		//-------------------------
		// ��ނ��Ƃ̏���
		//-------------------------
		switch (m_type)
		{
		//�^�C�g����ʂ̔w�i
		case BGTYPE_TITLE:
			m_pObject2D->SetTexture(CTexture::TEXTURE_TITLE);
			m_fWidth = 1000.0f;
			m_fHeight = 300.f;
			break;

		//���U���g��ʂ̔w�i
		case BGTYPE_RESULT:
			m_pObject2D->SetTexture(CTexture::TEXTURE_RESULT);
			break;

		//����������
		case BGTYPE_MANUAL:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_MANUAL);
			break;

		//�`���[�g���A��1
		case BGTYPE_TUTORIAL1:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TUTORIAL1);
			break;

		//�`���[�g���A��2
		case BGTYPE_TUTORIAL2:
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TUTORIAL2);
			break;

		//�L�[�����̎w��
		case BGTYPE_PRESS:
			m_fWidth = 1000.0f;
			m_fHeight = 150.0f;
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_PRESS);
			break;

		//�R���{UI�̔w�i
		case BGTYPE_COMBO:
			m_fWidth = 200.0f;
			m_fHeight = 180.0f;
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_COMBO);
			break;

		//�^�C�}�[UI�̔w�i
		case BGTYPE_TIMER:
			m_fWidth = 200.0f;
			m_fHeight = 180.0f;
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_TIMER);
			break;

		//�v���C���[��HP�̕���
		case BGTYPE_PLAYER_HP:
			m_fWidth = 330.0f;
			m_fHeight = 50.0f;
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_PLAYER_HP);
			break;

		//�G��HP�̕���
		case BGTYPE_ENEMY_HP:
			m_fWidth = 330.0f;
			m_fHeight = 50.0f;
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_ENEMY_HP);
			break;

		//������
		case BGTYPE_BLACK:
			m_fWidth = SCREEN_WIDTH;
			m_fHeight = SCREEN_HEIGHT;
			m_col.a = 0.0f;
			m_pObject2D->SetTexture(CTexture::TEXTURE_BG_BLACK);
			m_pObject2D->SetColor(m_col);
			break;

		default:
			break;
		}

		m_pObject2D->SetSize(m_fWidth, m_fHeight);
	}

	return S_OK;
}

//========================
// �I��
//========================
void CBg::Uninit()
{

}

//========================
// �X�V
//========================
void CBg::Update()
{
	if (m_type == BGTYPE_PRESS)
	{//�L�[�����w���Ȃ�
		//---------------------------
		// �_�ŏ���
		//---------------------------
		//�_�Ŏ��Ԃ𐔂���
		m_nFlashTime++;

		//�����x�̕ύX
		if (m_nFlashTime <= 60)
		{
			//�s�����ɂ���
			m_col.a -= 0.012f;
		}
		else
		{
			//�������ɂ���
			m_col.a += 0.012f;

			if (m_nFlashTime > 120)
			{
				m_nFlashTime = 0;	//���Ԃ̃��Z�b�g
			}
		}
	}
	else if (m_type == BGTYPE_BLACK)
	{//���Ȃ�
		if (m_col.a <= 1.0f)
		{
			m_col.a += 0.005f;
		}
	}

	//�F�̐ݒ�
	m_pObject2D->SetColor(m_col);
}

//========================
// �`��
//========================
void CBg::Draw()
{

}

//========================
// ����
//========================
CBg* CBg::Create(D3DXVECTOR3 pos, BGTYPE type)
{
	CBg *pBg = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pBg = new CBg;	//����
	pBg->m_pObject2D = new CObject2D(1);

	if (pBg != nullptr)
	{//NULL�`�F�b�N
		//�ϐ��ɑ��
		pBg->m_type = type;

		//������
		pBg->Init(pos);
	}

	return pBg;
}