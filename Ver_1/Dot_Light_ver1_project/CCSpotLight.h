//
//  CCSpotLight.h
//  exSpotLigt
//
//  Created by 이정우 on 13. 7. 15..
//
//

#ifndef __exSpotLigt__CCSpotLight__
#define __exSpotLigt__CCSpotLight__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class CCSpotLight : public CCSprite {
    public:
       static CCSpotLight* createWithRenderTexture(CCRenderTexture* texture, float radius, ccColor4B color);
    
    private:
        CCSpotLight(CCRenderTexture* texture, float radius, ccColor4B color);
        ~CCSpotLight();
    
    //매 프레임 마다 렌더러를 호출해서 새로 그리기 위한 스케줄러 함수.
    void update (float dt);
    
    //끝날때 보이는 영역이 넓어진다. 세팅된 시간 안에...
    void spreadOutAndRemove();
    void spreadOutTimer(float dt);
    
    //protected 변수 선언과 동시에 getter,setter 설정
    CC_SYNTHESIZE(CCRenderTexture*, rt, rt);
    CC_SYNTHESIZE(float, spotLightRadius, spotLightRadius);
    CC_SYNTHESIZE(ccColor4B, renderColor, renderColor);
};

#endif /* defined(__exSpotLigt__CCSpotLight__) */
