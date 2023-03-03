//==============================================
//
// �o���b�g�̏���
// Author : Sato Teruto
//
//==============================================

//----------------------------
// �C���N���[�h
//----------------------------
#include "bullet.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "enemy.h"
#include "player.h"
#include "damage.h"
#include "sound.h"

//====================================
// �R���X�g���N�^
//====================================
CBullet::CBullet() : CBillBoard(0)
{
}
CBullet::CBullet(int nPriority) : CBillBoard(nPriority)
{
	nLife = 0;	//����
	m_pDamage = nullptr;	//�_���[�W
}

//====================================
// �f�X�g���N�^
//====================================
CBullet::~CBullet()
{

}

//====================================
// ������
//====================================
HRESULT CBullet::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	nLife = 100;
	m_fWidth = 50.0f;
	m_fHeight = 50.0f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	CBillBoard::Init(pos);

	CBillBoard::SetPos(pos);
	CBillBoard::SetSize(m_fWidth, m_fHeight);
	CBillBoard::SetColor(m_col);
	CBillBoard::SetTexture(CTexture::TEXTURE_BULLET);

	return S_OK;
}

//====================================
// �I��
//====================================
void CBullet::Uninit()
{
	CBillBoard::Uninit();
}

//====================================
// �X�V
//====================================
void CBullet::Update()
{
	CBillBoard::Update();

	//------------------------------
	// �G�Ɍ������Ĉړ�
	//------------------------------
	//�G�̈ʒu���擾
	D3DXVECTOR3 enemyPos = CGame::GetEnemy()->GetPosition();
	enemyPos.y += 200.0f;

	//�x�N�g�������߂�
	D3DXVECTOR3 vec(enemyPos - m_pos);

	//�x�N�g���̐��K��
	D3DXVec3Normalize(&vec, &vec);

	//�v���C���[�Ɍ������Ĉړ�
	m_move = vec * 10.0f;
	m_pos += m_move;

	//------------------------------
	// �G�Ƃ̓����蔻��
	//------------------------------
	//�G�̑傫���̎擾
	D3DXVECTOR3 enemySize = CGame::GetEnemy()->GetSize();

	//�G�̒[�̐ݒ�
	float fLeft = enemyPos.x - enemySize.x;
	float fRight = enemyPos.x + enemySize.x;
	float fTop = enemyPos.y + enemySize.y;
	float fBottom = enemyPos.y - enemySize.y;
	float fFront = enemyPos.z - enemySize.z;
	float fBack = enemyPos.z + enemySize.z;

	//--------------------------------
	// �v���C���[�Ƃ̓����蔻��
	//--------------------------------
	float fRange = 30.0f;	//�����蔻��͈̔�
	int nDamage = rand() % 3 + 1;		//�_���[�W��
	
	//�_���[�W�̕\���ʒu�������_���ɐݒ�
	int nWidth = 50;
	int nRandX = rand() % nWidth - (nWidth / 2);
	int nRandY = rand() % nWidth - (nWidth / 2);
	D3DXVECTOR3 damagePos(m_pos.x + (float)nRandX
						  , m_pos.y + (float)nRandY
						  , m_pos.z);

	if (m_pos.x + fRange >= fLeft
		&& m_pos.x - fRange <= fRight
		&& m_pos.y + fRange >= fBottom
		&& m_pos.y - fRange <= fTop
		&& m_pos.z + fRange >= fFront
		&& m_pos.z - fRange <= fBack)
	{//�v���C���[���͈͓��ɓ�������
		CGame::GetEnemy()->SubGauge((float)nDamage, CEnemy::GAUGE_HP);	//�G�̗̑͂̌���
		CGame::GetPlayer()->AddCombo(1);	//�R���{�̉��Z

		//�_���[�W��
		m_pDamage = CDamage::Create(damagePos, nDamage, CDamage::DAMAGE_TYPE_NONE);

		//SE�̍Đ�
		CSound::PlaySound(CSound::SOUND_LABEL_SE_HIT);

		Uninit();
		return;
	}

	//------------------------------
	// �e�������鏈��
	//------------------------------
	nLife--;

	if (nLife <= 0)
	{//�������s������
		Uninit();
		return;
	}
}

//====================================
// �`��
//====================================
void CBullet::Draw()
{
	//�I�u�W�F�N�g�̕`��
	CBillBoard::Draw();
}

//====================================
// ����
//====================================
CBullet* CBullet::Create(D3DXVECTOR3 pos)
{
	CBullet *pBullet = nullptr;

	//----------------------------------
	// �����Ə�����
	//----------------------------------
	pBullet = new CBullet;	//����

	if (pBullet != nullptr)
	{//NULL�`�F�b�N
		//������
		pBullet->Init(D3DXVECTOR3(pos));
	}

	return pBullet;
}