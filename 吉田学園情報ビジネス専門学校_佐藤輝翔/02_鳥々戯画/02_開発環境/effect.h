//=====================================
//
// エフェクトヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _EFFECT_H_
#define _EFFECT_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// エネミークラス
//--------------------------
class CEffect : public CObject2D
{
public:
	CEffect();				//コンストラクタ
	~CEffect() override;	//デストラクタ

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
	static CEffect *Create(D3DXVECTOR3 pos);

private:
	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXCOLOR m_col;	//色
	float m_fRadius;	//半径(大きさ)
};

#endif // !_EFFECT_H_