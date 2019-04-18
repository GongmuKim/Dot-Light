#include "TitleScene.h"
#include "GameMenuScene.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"
USING_NS_CC;
extern CocosDenshion::SimpleAudioEngine *sound;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
	static int inits=0;
	inits++;
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	winSize=Director::sharedDirector()->getInstance()->getWinSize();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

	
	auto bgsp=Sprite::create("light_p.png");
	bgsp->setPosition(winSize/2);
	bgsp->setColor(ccColor3B::WHITE);
	bgsp->setScale(150);
	this->addChild(bgsp,3);
	if(inits==1)bgsp->runAction(FadeOut::create(0.5));
	else bgsp->setVisible(false);
	
		auto bgm_btn=MenuItemToggle::createWithTarget(this,menu_selector(GameMenuScene::menuCloseCallback),MenuItemImage::create("menu/bgm.png","menu/bgms.png"),MenuItemImage::create("menu/soundx.png","menu/soundxs.png"),NULL);
	bgm_btn->setPosition(ccp(winSize.width-(bgm_btn->getContentSize().width/2.0+50),winSize.height-(bgm_btn->getContentSize().height/2.0+50)));
	bgm_btn->setTag(1);
	if(sound->getBackgroundMusicVolume()<0.5) bgm_btn->setSelectedIndex(1);

	auto ef_btn=MenuItemToggle::createWithTarget(this,menu_selector(GameMenuScene::menuCloseCallback),MenuItemImage::create("menu/ef.png","menu/efs.png"),MenuItemImage::create("menu/soundx.png","menu/soundxs.png"),NULL);
	ef_btn->setPosition(ccp(winSize.width-(ef_btn->getContentSize().width*1.5+50),winSize.height-(ef_btn->getContentSize().height/2.0+50)));
	ef_btn->setTag(2);
	if(sound->getEffectsVolume()<0.5) ef_btn->setSelectedIndex(1);

    // create menu, it's an autorelease object
    auto menu = Menu::create(bgm_btn,ef_btn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    /*
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
	//label->setVisible(false);
    // add the label as a child to this layer
    this->addChild(label, 1);
	label->setName("L");*/

    // add "TitleScene" splash screen"
    auto sprite = Sprite::create("bg.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	end.x=winSize.width/2.0,end.y=winSize.height;
	this->shader_test();

	bg_st=this->start_shader(sprite);
	//btn_st=this->start_shader(closeItem);

	this->schedule(schedule_selector(TitleScene::update_gl_state));

	mymath=new Mymath();

		   auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(TitleScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(TitleScene::onTouchesMoved, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(TitleScene::onTouchesCancelled, this);
    listener->onTouchesEnded = CC_CALLBACK_2(TitleScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyReleased = CC_CALLBACK_2(TitleScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	r_angle=90;
	movetime=0;
	movebh=1;

    return true;
}

void TitleScene::update_gl_state(float dt)
{
	if(movetime>0) movetime-=dt;
	else{
		r_angle+=dt*movebh*50;
		if(r_angle>=90+45){
			if(movebh>=-1) movebh-=dt*5;
			else movebh=-1;
		}
		else if(r_angle<=90-45){
			if(movebh<=1) movebh+=dt*5;
			else movebh=1;
		}
	}
	/*char name[200]={0};
	sprintf(name,"%.5lf",r_angle);
	((LabelTTF*)this->getChildByName("L"))->setString(name);*/
	end=mymath->getline_end(winSize.width/2.0,winSize.height/2.0,r_angle,3000);
	this->set_gl_state(bg_st,1);
	//this->set_gl_state(btn_st,1);
}
void TitleScene::set_gl_state(GLProgramState *st,bool off)
{
	st->setUniformFloat("off",off);//0이면 셰이더 꺼지니까 제대로 다보임
	st->setUniformVec2("pos1", Vec2(winSize.width/2.0,0));
	st->setUniformVec2("pos2", Vec2(end.x,end.y));
	st->setUniformVec2("pos3", Vec2(end.x,end.y));	
	st->setUniformFloat("r_angle",mymath->angleto0360(r_angle)),st->setUniformFloat("r_angle2",mymath->angleto0360(r_angle));
}

void TitleScene::shader_test()
{

	
	const GLchar* fragmentSource;
	//const GLchar* vertSource = (GLchar*)CCString::createWithContentsOfFile(FileUtils::getInstance()->fullPathFromRelativeFile("vs_timer.fsh", "./Resources"))->getCString();

	char *name;
	fragmentSource=(GLchar*)CCString::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("light.frag").c_str())->getCString();
	

	/*
        	 fragmentSource =
 "#ifdef GL_ES \n \
        precision mediump float; \n \
        #endif \n \
        //uniform sampler2D u_texture; \n \
        varying vec2 v_texCoord; \n \
        varying vec4 v_fragmentColor; \n \
        void main(void) \n \
        { \n \
        // Convert to greyscale using NTSC weightings \n \
        vec4 color = texture2D(CC_Texture0, v_texCoord).rgba;\n \
        float grey = dot(color.rgb, vec3(0.1, 0.1, 0.1)); \n \
        gl_FragColor = vec4(grey, grey, grey,color.a); \n \
        }";*/
	

	
			 CCGLProgram* pProgram = new GLProgram();
		//GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragmentSource);
	pProgram->initWithVertexShaderByteArray(ccPositionTextureColor_noMVP_vert, fragmentSource);
	auto gp = GLProgramState::create(pProgram);
	gp->setUniformVec2("resolution", Vec2(1920.0,1080.0));
	pProgram->release();
	CHECK_GL_ERROR_DEBUG();
	
	/*pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
*/
	pProgram->addAttribute("a_position", kCCVertexAttrib_Position);
	pProgram->addAttribute("a_color", kCCVertexAttrib_Color);
	pProgram->addAttribute("a_texCoord", kCCVertexAttrib_TexCoords);


    pProgram->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    pProgram->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	pProgram->link();
	pProgram->updateUniforms();
	CHECK_GL_ERROR_DEBUG();

	CCShaderCache::getInstance()->addGLProgram(pProgram, "light");
	CHECK_GL_ERROR_DEBUG();
}
GLProgramState* TitleScene::start_shader(Sprite* sprite)
{
	GLProgram *program=CCShaderCache::getInstance()->getGLProgram("light");
	GLProgramState *st=GLProgramState::create(program);
	sprite->setGLProgram(program);
	sprite->setGLProgramState(st);
	st->setUniformVec2("resolution", Vec2(sprite->getContentSize().width,sprite->getContentSize().height));
	st->setUniformVec2("sprite_start",Vec2(sprite->getPosition().x-sprite->getContentSize().width/2.0,sprite->getPosition().y-sprite->getContentSize().height/2.0));
	st->setUniformFloat("off",1);//0이면 셰이더 꺼지니까 제대로 다보임
	st->setUniformVec2("pos1", Vec2(winSize.width/2.0,winSize.height/2.0));
	st->setUniformVec2("pos2", Vec2(end.x,end.y));
	st->setUniformVec2("pos3", Vec2(end.x,end.y));
	st->setUniformFloat("width",150);




	/*
	u_loc[sprite->getTag()][RES] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "resolution");
	u_loc[sprite->getTag()][SPS] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "sprite_start");
	u_loc[sprite->getTag()][POS1] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "pos1");
	u_loc[sprite->getTag()][POS2] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "pso2");
	u_loc[sprite->getTag()][POS3] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "pso3");
	u_loc[sprite->getTag()][OFF] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "off");
	*/
	//st->setUniformTexture("u_normals",sprite->getTexture());
	//st->setUniformTexture("u_normals",sprite->getTexture());

		/*
	sprite->getShaderProgram()->addAttribute(cocos2d::kCCAttributeNamePosition, kCCVertexAttrib_Position);
	sprite->getShaderProgram()->addAttribute(cocos2d::kCCAttributeNameColor, kCCVertexAttrib_Color);
	sprite->getShaderProgram()->addAttribute(cocos2d::kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);*/

	sprite->getShaderProgram()->addAttribute("a_position", kCCVertexAttrib_Position);
	sprite->getShaderProgram()->addAttribute("a_color", kCCVertexAttrib_Color);
	sprite->getShaderProgram()->addAttribute("a_texCoord", kCCVertexAttrib_TexCoords);
	CHECK_GL_ERROR_DEBUG();


	sprite->getShaderProgram()->link();
	CHECK_GL_ERROR_DEBUG();


	sprite->getShaderProgram()->updateUniforms();
	CHECK_GL_ERROR_DEBUG();
	
	sprite->setGLProgram(program);

	return st;
}
GLProgramState* TitleScene::start_shader(MenuItemImage* sprite)
{
	GLProgram *program=CCShaderCache::getInstance()->getGLProgram("light");
	GLProgramState *st=GLProgramState::create(program);
	sprite->setGLProgram(program);
	sprite->setGLProgramState(st);
	st->setUniformVec2("resolution", Vec2(sprite->getContentSize().width,sprite->getContentSize().height));
	st->setUniformVec2("sprite_start",Vec2(sprite->getPosition().x-sprite->getContentSize().width/2.0,sprite->getPosition().y-sprite->getContentSize().height/2.0));
	st->setUniformFloat("off",1);//0이면 셰이더 꺼지니까 제대로 다보임
	st->setUniformVec2("pos1", Vec2(winSize.width/2.0,winSize.height/2.0));
	st->setUniformVec2("pos2", Vec2(end.x,end.y));
	st->setUniformVec2("pos3", Vec2(end.x,end.y));




	/*
	u_loc[sprite->getTag()][RES] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "resolution");
	u_loc[sprite->getTag()][SPS] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "sprite_start");
	u_loc[sprite->getTag()][POS1] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "pos1");
	u_loc[sprite->getTag()][POS2] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "pso2");
	u_loc[sprite->getTag()][POS3] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "pso3");
	u_loc[sprite->getTag()][OFF] = glGetUniformLocation(sprite->getShaderProgram()->getProgram(), "off");
	*/
	//st->setUniformTexture("u_normals",sprite->getTexture());
	//st->setUniformTexture("u_normals",sprite->getTexture());
/*
	sprite->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	sprite->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	sprite->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);*/

	sprite->getShaderProgram()->addAttribute("a_position", kCCVertexAttrib_Position);
	sprite->getShaderProgram()->addAttribute("a_color", kCCVertexAttrib_Color);
	sprite->getShaderProgram()->addAttribute("a_texCoord", kCCVertexAttrib_TexCoords);
	CHECK_GL_ERROR_DEBUG();


	sprite->getShaderProgram()->link();
	CHECK_GL_ERROR_DEBUG();


	sprite->getShaderProgram()->updateUniforms();
	CHECK_GL_ERROR_DEBUG();

	return st;
}

void TitleScene::menuCloseCallback(Ref* pSender)
{
	Node* node = (Node*) pSender;	
	int tag=node->getTag();
	if(tag==1){
		sound->setBackgroundMusicVolume((sound->getBackgroundMusicVolume()-1.0)*-1.0);
		UserDefault::sharedUserDefault()->setBoolForKey("bg",sound->getBackgroundMusicVolume());
	}
	else if(tag==2){
		sound->setEffectsVolume((sound->getEffectsVolume()-1.0)*-1.0);
		UserDefault::sharedUserDefault()->setBoolForKey("ef",sound->getEffectsVolume());
	}
}


void TitleScene::onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event)
{
	Director::sharedDirector()->replaceScene(GameMenuScene::createScene());
}
 
void TitleScene::onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event) 
{



}
 
void TitleScene::onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event) 
{
}
 
void TitleScene::onTouchesEnded(const std::vector<Touch*>&touches, Event* unused_event) 
{
}

void TitleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		Director::sharedDirector()->end();
	}
}