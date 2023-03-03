//===================================================
//
// �G�l�~�[�w�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object.h"

//--------------------------------
// �O���錾
//--------------------------------
class CModel;	//���f��
class CLine;	//���C��
class CHP;		//HP
class CMessage;	//���b�Z�[�W

//--------------------------------
// �}�N����`
//--------------------------------
#define MAX_ENEMY_PARTS	(3)		//���f���p�[�c�̍ő吔
#define MAX_ENEMY_KEY	(24)	//�L�[�̍ő吔

//================================
// �G�l�~�[�N���X�̒�`
//================================
class CEnemy : public CObject
{
public:
	//�L�[�v�f
	struct KEY
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
	};

	//�L�[���
	struct KEY_SET
	{
		int nFrame;	//�t���[����
		KEY aKey[MAX_ENEMY_PARTS];
	};

	//���[�V�������
	struct MOTION_SET
	{
		bool bLoop;						//���[�v���邩�ǂ���
		int nNumKey;					//�L�[�̍ő吔
		KEY_SET aKeySet[MAX_ENEMY_KEY];	//�L�[�Z�b�g���

		int nStartCollision;			//�����蔻��̊J�n����
		int nDamage;					//�_���[�W��
		int nNumHit;					//�q�b�g��
		int nHitInterval;				//�q�b�g�Ԋu
	};

	//���[�V�����̎��
	enum MOTION_TYPE
	{
		MOTION_IDOL = 0,	//�ҋ@
		MOTION_MOVE,		//�ړ�
		MOTION_ATTACK,		//�@�����U��
		MOTION_SPIN,		//��]�U��
		MOTION_MAX
	};

	enum ENEMYSTATE
	{
		ENEMYSTATE_NONE = 0,
		ENEMYSTATE_BREAK,
		ENEMYSTATE_MAX
	};

	enum GAUGE
	{
		GAUGE_HP = 0,
		GAUGE_BREAK,
		GAUGE_MAX
	};

	CEnemy();			//�R���X�g���N�^
	~CEnemy() override;	//�f�X�g���N�^

	//----------------
	// �����o�֐�
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//----------------
	// �Z�b�^�[
	//----------------
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }			//�ʒu�̐ݒ�
	void SubGauge(float fDamage, GAUGE type);	//�Q�[�W�������̏���

	//----------------
	// �Q�b�^�[
	//----------------
	D3DXVECTOR3 GetPosition() override	{ return m_pos; }		//�ʒu�̎擾
	D3DXVECTOR3 GetRot()				{ return m_rot; }		//�����̎擾
	float GetWidth() override			{ return 0.0f; }		//���̎擾
	float GetHeight() override			{ return 0.0f; }		//�����̎擾
	bool GetHitAtk()				    { return m_bHitAtk; }	//�U�����������������擾
	D3DXVECTOR3 GetSize()				{ return m_size; }		//�傫���̎擾
	D3DXMATRIX GetmtxWorld()			{ return m_mtxWorld; }	//���[���h�}�g���b�N�X�̎擾
	ENEMYSTATE GetState()				{ return m_state; }		//�G�̏�Ԃ̎擾

	//----------------
	// �ÓI�����o�֐�
	//----------------
	static CEnemy* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	void SetModel();	//���f���̐ݒ�
	void SetLine();		//���̐ݒu
	void UpdateLine();	//���̍X�V
	void EnemyAI();		//�G�̓������Ǘ�
	void Attack();		//�U������
	void HitHummer();	//�n���}�[�̓����蔻��
	void NockBack();	//�m�b�N�o�b�N���鏈��
	void Move(D3DXVECTOR3 targetPos);		//�ړ�
	void Rotation(D3DXVECTOR3 targetPos);	//��]

	//���[�V����
	void GetFileMotion();										//�t�@�C�����g�������[�V�����̎擾
	void SetMotion(MOTION_TYPE type, bool bLoop, int nNumKey);	//���[�V�����̐ݒ�
	void ChangeMotion(MOTION_TYPE type);						//���[�V�����̕ύX

private:
	//----------------
	// �萔
	//----------------
	static const int nMaxLine = 24;	//���̍ő吔
	static const float fDefGravity;	//��{�̏d��

	//----------------
	// �����o�ϐ�
	//----------------
	D3DXMATRIX m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_posOld;		//�O�̈ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_rotDest;		//�ړI�̌���
	D3DXVECTOR3 m_vtxMax;		//�傫���̍ő�l
	D3DXVECTOR3 m_vtxMin;		//�傫���̍ŏ��l
	D3DXVECTOR3 m_worldMin;		//���[���h��̍ő�l
	D3DXVECTOR3	m_worldMax;		//���[���h��̍ŏ��l
	D3DXVECTOR3 m_size;			//�傫��
	int m_nMoveTime;			//�ړ��܂ł̎���
	int m_nAttackTime;			//�U���܂ł̎���
	int m_nBreakTime;			//�u���C�N��Ԃ̎���
	int m_nCntFream;			//�t���[�����̃J�E���g
	int m_nHitTime;				//�q�b�g����܂ł̎���
	int m_nCntHit;				//�q�b�g���𐔂���
	float m_fLife;				//�̗�
	float m_fRemLife;			//�c��̗�(%)
	float m_fMaxLife;			//�ő�̗�
	float m_fGravity;			//�d�͂̒l
	float m_fBreak;
	float m_fRemBreak;
	float m_fMaxBreak;
	bool m_bNockBack;			//�m�b�N�o�b�N������
	bool m_bHitAtk;				//�U��������������
	CModel*		m_pModel[MAX_ENEMY_PARTS];	//���f��
	CLine*		m_pLine[nMaxLine];			//���C��
	CHP*		m_pHP[GAUGE_MAX];			//HP
	CMessage*	m_pMessage;					//���b�Z�[�W
	ENEMYSTATE m_state;					//�G�̏��

	/* �� ���[�V������� �� */
	int m_nCurrentKey;						//���݂̃L�[�ԍ�
	int m_nCntMotion;						//���[�V�����J�E���^�[
	MOTION_SET m_aMotionSet[MOTION_MAX];	//���[�V�������
	MOTION_TYPE m_type;						//���݂̃��[�V����
};

#endif