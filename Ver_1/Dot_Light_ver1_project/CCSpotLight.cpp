//
//  CCSpotLight.cpp
//  exSpotLigt
//
//  Created by 이정우 on 13. 7. 15..
//
//

#include "CCSpotLight.h"

#define THIS CCSpotLight

THIS* THIS::createWithRenderTexture(CCRenderTexture* texture, float radius, ccColor4B color) {
	CCSpotLight* spr = new CCSpotLight(texture, radius, color);
    if(spr) {
        spr->autorelease();
        return spr;
    } else {
        delete spr;
        return NULL;
    }
}

CCSpotLight::CCSpotLight(CCRenderTexture* texture, float radius, ccColor4B color) {
    if(!CCSprite::init()) {
        return;
    }
    
        this->setPosition(CCPoint(240,160));
        this->setrt(texture);
        this->spotLightRadius = radius;
        this->renderColor = color;
        this->scheduleUpdate();
    
}

THIS::~THIS() {
    
}

void THIS::update(float dt) {
    //전달 받은 rt(렌더링 할 수 있는 녀석)로 배경을 클리어하고 그리기를 시작한다.
    int segs = 4;
    
    rt->clear(255,255,0,255);
    rt->begin();
    
    //기본 세이더를 받아와서 세팅한다.
    setShaderProgram (CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    CC_NODE_DRAW_SETUP();
    
    //점의 색깔을 지정한다.
    ccColor4B* colors = new ccColor4B [segs];
    colors[0] = ccc4(255, 0, 0, 255);
    for (int i=1; i < segs; i++){
        colors[i] = ccc4(0, 0, 0, 255);
    }
    int nVertices = 0;
    
    CCPoint* vertices = new CCPoint [segs];
    vertices[nVertices++] = getPosition();
    vertices[nVertices++] = CCPointMake(100.0f, 100.0f);
    vertices[nVertices++] = CCPointMake(200.0f, 100.0f);
    vertices[nVertices++] = CCPointMake(150.0f, 200.0f);
    
    
    //사용할 기능을 활성화한다. 정점 배열을 사용하겠다고 알리고, 색깔을 입히겠다고도 알림.
//    CC_ENABLE_DEFAULT_GL_STATES();
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
    
    //rt를 glview에 바인딩한다. 형태는 2D
    glBindTexture(GL_TEXTURE_2D, (GLuint) rt);
    
    //정점 배열을 이용해서 점을 찍는다.
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    //각 점의 영역의 색깔을 지정한다.
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors);
    
    //삼각현을 그린다.
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    //gl을 그리는 과정에 에러가 있는지 체크한다.
    CHECK_GL_ERROR_DEBUG();
    
    //렌더링을 종료한다.
    rt->end();
    //동적으로 활당했던 배열을 정리한다.
    delete [] colors;
    delete [] vertices;
}

void THIS::spreadOutAndRemove() {
	this->schedule(schedule_selector(CCSpotLight::spreadOutTimer));
}

void THIS::spreadOutTimer(float dt) {
    this->spotLightRadius += 3;
    if(this->spotLightRadius > 300) {
        this->unschedule(schedule_selector(CCSpotLight::spreadOutTimer));
        this->unscheduleUpdate();
        this->rt->removeFromParentAndCleanup(true);
        this->removeFromParentAndCleanup(true);
    }
}
