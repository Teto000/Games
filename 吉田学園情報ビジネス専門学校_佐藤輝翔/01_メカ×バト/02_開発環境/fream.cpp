//===================================================
//
// �Q�[�W�̃t���[������
// Author : Sato Teruto
//
//===================================================

//-----------------------
// �C���N���[�h
//-----------------------
#include "fream.h"

//==========================
// �R���X�g���N�^
//==========================
CFream::CFream() : CObject2D(0)
{
}

//==========================
// �f�X�g���N�^
//==========================
CFream::~CFream()
{

}

//==========================
// ������
//==========================
HRESULT CFream::Init(D3DXVECTOR3 pos)
{
	CObject2D::Init(pos);

	//�傫���̐ݒ�
	CObject2D::SetSize(m_fWidth, m_fHeight);

	//�F�̐ݒ�
	CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_NONE);

	return S_OK;
}

//==========================
// �I��
//==========================
void CFream::Uninit()
{
	CObject2D::Uninit();
}

//==========================
// �X�V
//==========================
void CFream::Update()
{
	CObject2D::Update();
}

//==========================
// �`��
//==========================
void CFream::Draw()
{
	CObject2D::Draw();
}

//==========================
// ����
//==========================
CFream* CFream::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CFream *pFream = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pFream = new CFream;	//����

	if (pFream != nullptr)
	{//NULL�`�F�b�N
		//�ϐ��ɑ��
		pFream->m_pos = pos;			//�ʒu
		pFream->m_fWidth = fWidth;		//��
		pFream->m_fHeight = fHeight;	//����

		//������
		pFream->Init(D3DXVECTOR3(pos));
		pFream->SetObjType(OBJTYPE_GAUGE);
	}

	return pFream;
}