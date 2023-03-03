//=====================================
//
// エクスプロージョンヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// エクスプロージョンクラス
//--------------------------
class CExplosion : public CObject2D
{
public:
	CExplosion();			//コンストラクタ
	~CExplosion() override;	//デストラクタ

	//----------------
	// メンバ関数
	//----------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//----------------
	// 静的メンバ関数
	//----------------
	static CExplosion *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;	//位置
	D3DXCOLOR m_col;	//色
	int m_nLife;		//寿命
	float m_fWidth;		//幅
	float m_fHeight;	//高さ
};

#endif // !_EXPLOSION_H_