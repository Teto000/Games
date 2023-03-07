//=====================================
//
// スキルヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _SKILL_H_
#define _SKILL_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// スキルクラス
//--------------------------
class CSkill : public CObject2D
{
public:
	//---------------------------
	// スキル列挙型の定義
	//---------------------------
	enum SKILLTYPE
	{
		SKILLTYPE_HEAL = 0,			//回復
		SKILLTYPE_SPEEDUP_FIRE,		//発射速度強化
		SKILLTYPE_ATTACKUP,			//攻撃力上昇
		SKILLTYPE_SPEEDUP,			//速度上昇
		SKILLTYPE_MAX,
	};

	CSkill();			//コンストラクタ
	~CSkill() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit(void) override;
	void Update(void) override;
	void Draw(void) override;

	//----------------
	// 静的メンバ関数
	//----------------
	static CSkill *Create(SKILLTYPE type);

private:
	//----------------
	// 定数
	//----------------
	static const float nSkillSpeed;
	static const int nMaxTimer = 60;

	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXVECTOR3 m_move;	//移動量
	int m_nCntTimer;	//文字の表示時間
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
	SKILLTYPE m_type;	//種類
};

#endif // !_PLAYER_H_