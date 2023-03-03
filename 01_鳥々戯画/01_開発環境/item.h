//=====================================
//
// アイテムヘッダー
// Author : Sato Teruto
//
//=====================================
#ifndef _ITEM_H_
#define _ITEM_H_	

//--------------------------
// インクルード
//--------------------------
#include "object2D.h"

//--------------------------
// アイテムクラス
//--------------------------
class CItem : public CObject2D
{
public:
	enum ITEMTYPE
	{
		ITEMTYPE_HPHEAL = 0,	//HP回復
		ITEMTYPE_MPHEAL,		//MP回復
		ITEMTYPE_MAX
	};

	CItem();			//コンストラクタ
	~CItem() override;	//デストラクタ

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
	static CItem *Create(D3DXVECTOR3 pos, ITEMTYPE type);

private:
	//----------------
	// メンバ変数
	//----------------
	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_rot;		//回転
	int m_nLife;			//寿命
	float m_fWidth;			//幅
	float m_fHeight;		//高さ
	ITEMTYPE m_type;		//種類
};

#endif // !_BULLET_H_