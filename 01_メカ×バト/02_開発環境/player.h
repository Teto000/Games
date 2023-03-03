//===================================================
//
// �v���C���[�w�b�_�[
// Author:Teruto Sato
//
//===================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_	//��d�C���N���[�h�h�~

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object.h"

//--------------------------------
// �O���錾
//--------------------------------
class CModel;		//���f��
class CLine;		//���C��
class CHP;			//HP
class CCombo;		//�R���{
class CDamage;		//�_���[�W
class COrbit;		//�O��
class CBullet;		//�e
class CMessage;		//���b�Z�[�W
class CBg;			//�w�i

//--------------------------------
// �}�N����`
//--------------------------------
#define MAX_PARTS	(7)		//���f���p�[�c�̍ő吔
#define MAX_KEY		(24)	//�L�[�̍ő吔

//================================
// �v���C���[�N���X�̒�`
//================================
class CPlayer : public CObject
{
public:
	//-------------------------
	// �L�[�v�f
	//-------------------------
	struct KEY
	{
		D3DXVECTOR3 pos;	//�ʒu
		D3DXVECTOR3 rot;	//����
	};

	//-------------------------
	// �L�[���
	//-------------------------
	struct KEY_SET
	{
		int nFrame;	//�t���[����
		KEY aKey[MAX_PARTS];
	};

	//-------------------------
	// ���[�V�������
	//-------------------------
	struct MOTION_SET
	{
		bool bLoop;					//���[�v���邩�ǂ���
		int nNumKey;				//�L�[�̍ő吔
		KEY_SET aKeySet[MAX_KEY];	//�L�[�Z�b�g���

		int nStartCollision;		//�����蔻��̊J�n����
		int nNextAtkTime;			//���̍U���̓��͊J�n����
		int nNumPoint;				//����|�C���g��
		int nCritical;				//�N���e�B�J����
		int nNumHit;				//�q�b�g��
		int nHitInterval;			//�q�b�g�Ԋu
		int nBreakDamage;			//�u���C�N�Q�[�W�ɗ^����_���[�W
		float fDamageMag;			//�_���[�W�{��(magnification)
	};

	//-------------------------
	// �v���C���[�̃X�e�[�^�X
	//-------------------------
	struct PLAYER_STATUS
	{
		int nAttackTime;	//�U������
		int nComboValue;	//�R���{�̉��Z�l
		float nAttack;		//�U����
		float fSpeed;		//���x
		float fLife;		//�̗�
		float fRemLife;		//�c��̗�(%)
		float fMaxLife;		//�ő�̗�
		bool bAvoidance;	//������
	};

	//-------------------------
	// ���[�V�����̎��
	//-------------------------
	enum MOTION_TYPE
	{
		MOTION_IDOL = 0,	//�ҋ@
		MOTION_MOVE,		//�ړ�
		MOTION_ATTACK_1,	//�ʏ�U��(1�i��)
		MOTION_ATTACK_2,	//�ʏ�U��(2�i��)
		MOTION_ATTACK_SPIN,	//��]�؂�
		MOTION_MAX
	};

	CPlayer();				//�R���X�g���N�^
	~CPlayer() override;	//�f�X�g���N�^

	//-------------------------
	// �����o�֐�
	//-------------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	//-------------------------
	// �Z�b�^�[
	//-------------------------
	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }						//�ʒu�̐ݒ�
	void SetAttack(float nAttack)	  { m_status.nAttack = nAttack; }		//�U���͂̐ݒ�
	void SetSpeed(float fSpeed)		  { m_status.fSpeed = fSpeed; }			//���x�̐ݒ�
	void SetComboValue(int nValue)    { m_status.nComboValue = nValue; }	//�R���{�̉��Z�l�̐ݒ�
	void AddCombo(int nNumber);		//�R���{���̉��Z
	void AddLife(float fDamage);	//HP�������̏���
	void NockBack(float fHeight);	//�m�b�N�o�b�N

	//-------------------------
	// �Q�b�^�[
	//-------------------------
	D3DXVECTOR3 GetPosition() override { return m_pos; }				//�ʒu�̎擾
	D3DXVECTOR3 GetRot()			   { return m_rot; }				//�����̎擾
	D3DXVECTOR3 GetSize()			   { return m_size; }				//�傫���̎擾
	D3DXMATRIX GetmtxWorld()		   { return m_mtxWorld; }			//���[���h�}�g���b�N�X�̎擾
	const int GetSwordNumber()		   { return nSwordNumber; }			//�����f���̔ԍ����擾
	float GetWidth() override		   { return 0.0f; }					//���̎擾
	float GetHeight() override		   { return 0.0f; }					//�����̎擾
	bool GetHitAttack()				   { return m_bFinishAttack; }		//�U���𓖂Ă������擾
	bool GetAvoidance()				   { return m_status.bAvoidance; }	//�����Ԃ̎擾
	CModel* GetModel(int nNum)		   { return m_pModel[nNum]; }		//���f���̎擾
	CCombo* GetCombo()				   { return m_pCombo; }				//�R���{�̎擾
	PLAYER_STATUS GetStatus()		   { return m_status; }				//�X�e�[�^�X�̎擾
	MOTION_TYPE GetMotion()			   { return m_type; }				//���[�V�����̎�ނ̎擾

	//-------------------------
	// �ÓI�����o�֐�
	//-------------------------
	static CPlayer* Create();

private:
	//-------------------------
	// �v���C�x�[�g�֐�
	//-------------------------
	void MoveKeyboard(int nUpKey, int nDownKey, int nLeftKey, int nRightKey);	//�ړ�
	void MoveJoypad();			//�W���C�p�b�h���g�����ړ�
	void SetRot();				//�p�x�̐ݒ�

	void AttackManager();		//�U���̊Ǘ�
	void EnhanceAttack();		//�U�����������鏈��
	void Attack();				//�U������
	void HitSword();			//����������������
	bool GetOutAttack(bool equal, bool and);	//�U����Ԃ��ǂ�����Ԃ�

	void SetModel();											//���f���̐ݒ�
	void GetFileMotion();										//�t�@�C�����g�������[�V�����̎擾
	void SetMotion(MOTION_TYPE type, bool bLoop, int nNumKey);	//���[�V�����̐ݒ�
	void ChangeMotion(MOTION_TYPE type);						//���[�V�����̕ύX

private:
	//-------------------------
	// �萔
	//-------------------------
	static const int nMaxLine = 12;				//���̍ő吔
	static const int nSwordNumber = 4;			//�����f���̔ԍ�
	static const int nResetModeTime = 600;		//���[�h�`�F���W�I���܂ł̎���
	static const int nNeedEnhanceCombo = 30;	//�U���̋����ɕK�v�ȃR���{��
	static const float fDefaultAttack;			//��{�̍U����
	static const float fDefaultSpeed;			//��{�̑��x

	//-------------------------
	// �����o�ϐ�
	//-------------------------
	D3DXMATRIX	m_mtxWorld;		//���[���h�}�g���b�N�X
	D3DXMATRIX	m_mtxRot;		//��]�}�g���b�N�X(�ۑ��p)
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_posOld;		//�O�̈ʒu
	D3DXVECTOR3 m_Offset;		//����ւ̃I�t�Z�b�g���W
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_rot;			//����
	D3DXVECTOR3 m_rotDest;		//�ړI�̌���
	D3DXVECTOR3 m_vtxMax;		//�傫���̍ő�l
	D3DXVECTOR3 m_vtxMin;		//�傫���̍ŏ��l
	D3DXVECTOR3 m_size;			//�傫��
	D3DXVECTOR3 m_worldMin;		//���[���h��̍ő�l
	D3DXVECTOR3	m_worldMax;		//���[���h��̍ŏ��l
	int m_nNumCombo;			//�R���{��
	int m_nCntHit;				//�q�b�g���𐔂���
	int m_nHitTime;				//�q�b�g�܂ł̎��Ԃ𐔂���
	int m_nCntModeTime;			//���[�h�I���܂ł̎��Ԃ𐔂���
	int m_nAvoidTime;			//�������
	int m_nAvoidStan;			//����d��
	int m_nWheelRotValue;		//�^�C���̉�]��
	int m_nBulletTime;			//�e�̔��ˎ���
	int m_nCntAttack;			//�A�����𐔂���
	float m_fSizeWidth;			//�T�C�Y(��)
	float m_fSizeDepth;			//�T�C�Y(���s��)
	float m_fGravity;			//�d�͂̒l
	float m_rotWheel;			//�^�C���̉�]��
	bool m_bFinishAttack;		//�U�����I��������
	bool m_bHit;				//1�q�b�g�������
	bool m_bNockBack;			//�m�b�N�o�b�N���Ă�����
	bool m_bEnhance;			//�Z�������������
	bool m_bCntAttack;			//�A�����𐔂�����
	CHP*		m_pHP;			//HP
	CCombo*		m_pCombo;		//�R���{
	CDamage*	m_pDamage;		//�_���[�W
	COrbit*		m_pOrbit;		//�O��
	CBullet*	m_pBullet;		//�e
	CMessage*	m_pMessage;		//���b�Z�[�W
	CBg*		m_pBg;			//�w�i

	//�񋓌^
	PLAYER_STATUS m_status;		//�X�e�[�^�X

	/* �� ���f����� �� */
	CModel*  m_pModel[MAX_PARTS];		//���f��
	CLine* m_pLine[nMaxLine];			//���C��

	/* �� ���[�V������� �� */
	int m_nCurrentKey;						//���݂̃L�[�ԍ�
	int m_nCntMotion;						//���[�V�����J�E���^�[
	MOTION_SET m_aMotionSet[MOTION_MAX];	//���[�V�������
	MOTION_TYPE m_type;						//���݂̃��[�V����
	MOTION_TYPE m_typeOld;					//1�O�̃��[�V����
};

#endif