//===================================================
//
// 2D�|���S���̏���
// Author:Teruto Sato
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "polygon.h"
#include "renderer.h"
#include "texture.h"
#include "game.h"
#include "camera.h"

//========================
// �R���X�g���N�^
//========================
CPolygon::CPolygon() : CObject2D(1)
{
	m_fRadius = 0.0f;
	m_type = POLYGONTYPE_NONE;
}

//========================
// �f�X�g���N�^
//========================
CPolygon::~CPolygon()
{

}

//========================
// ������
//========================
HRESULT CPolygon::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_fRadius = 100.0f;

	CObject2D::Init(pos);

	CObject2D::SetSize(m_fRadius, m_fRadius);
	CObject2D::SetTexture(CTexture::TEXTURE_AIM);

	return S_OK;
}

//========================
// �I��
//========================
void CPolygon::Uninit()
{
	CObject2D::Uninit();
}

//========================
// �X�V
//========================
void CPolygon::Update()
{
	CObject2D::Update();
}

//========================
// �`��
//========================
void CPolygon::Draw()
{
	if (CGame::GetCamera()->GetLockOn())
	{//���b�N�I����ԂȂ�
		CObject2D::Draw();
	}
}

//========================
// ����
//========================
CPolygon* CPolygon::Create(CPolygon::POLYGONTYPE type)
{
	CPolygon *pPolygon = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pPolygon = new CPolygon;	//����;

	if (pPolygon != nullptr)
	{//NULL�`�F�b�N
		//�ϐ��ɑ��
		pPolygon->m_type = type;

		//������
		pPolygon->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50.0f, 0.0f));
	}

	return pPolygon;
}