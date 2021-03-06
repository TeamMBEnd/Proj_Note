#ifndef _SLIDEBAR_H_
#define _SLIDEBAR_H_

#include "cocos2d.h"
#include <extensions/cocos-ext.h>
#include <math.h>

/**
 *	@class	： SlideBar
 *	@brief	： スライドバークラス
 *	@author	： 新井椋汰
 */

class SlideBar : public cocos2d::extension::ControlSlider
{
protected:
    
    /**　@brief  コンストラクタ*/
    SlideBar();
    
    /**　@brief  デストラクタ*/
    ~SlideBar()= default;
    
public:
    /**
     *  @brief  インスタンスの生成
     * @return	SlideBar   インスタンス
     */
    static SlideBar* create();
    
    /**　@brief  スライドバーの生成
     *   @param0 名前（p1 or p2）
     *   @param1 追加したいレイヤー
     *   @param2 背景スプライト
     *   @param3 効果スプライト
     *   @param4 ボタンスプライト
     *   @param5 位置
     */
    void slideBarCreate(const std::string& name,
                        cocos2d::Layer* layer,
                        const std::string& bgFail,
                        const std::string& progressFail,
                        const std::string& thumbFail,
                        const std::string& selectthumbFail,
                        cocos2d::Vec2 position
                        );

    
    /** @brief スライダーのタッチ判定
     *  @param0 tagName
     *  @param1 レイヤー情報
     */
	bool isTouch(const std::string& name, cocos2d::Layer* layer);

	/** @brief 値の取得
     *  @param0 tagName
     *  @param1 レイヤー情報
     */
    float getValue(const std::string& name,cocos2d::Layer* layer);
    
    /** @brief ポジションの設定
     *  @param0 位置
     *  @param1 レイヤー情報
     */
    void setPosition(cocos2d::Vec2 pos, cocos2d::Layer* layer);
};
#endif
