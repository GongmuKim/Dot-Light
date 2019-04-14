#include "GameScene.h"
#include "popup.h"
#include "GameMenuScene.h"
#include "data.h"
#include <cmath>
extern int stage,max_stage,stage_star[20][5];
extern Datas *data;
extern CocosDenshion::SimpleAudioEngine *sound;
USING_NS_CC;
#define PTM_RATIO 32.0f
enum {POS1,POS2,POS3,RES,SPS,OFF};//pos1,pos2,pos3,resolution,sprite_start

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	static int initcnt=0;
	initcnt++;
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	CCLog("init%d",initcnt);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	
   /* auto closeItem = MenuItemImage::create(
                                           "star1.png",
                                           "star2.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));*/
	//closeItem->setVisible(false);

    // create menu, it's an autorelease object
   /* auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	/*
	char name[200]={0};
	sprintf(name,"init:%d",initcnt);
    label = LabelTTF::create(name, "Arial", 48);
	//label->setVisible(false);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);*/

    // add "GameScene" splash screen"
    auto sprite = Sprite::create("bg.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
   // this->addChild(sprite, 0);

	winSize=Director::sharedDirector()->getWinSize();
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
	
	mymath=new Mymath();
	get_mirror=false;
	///////////터치
	/////////////
	
	this->shader_test();///////////////////////////
	this->set_data();

	this->set_world();
	this->create_player();
	this->create_enemy();
	//enemy=this->addc(ccp(10,10));
	//b2Body* ball=this->addc();
	this->addmap();
	this->addj();
	this->create_controler();
	r_angle=0.1,before_rangle=0.1;

	
	rend1=new Myray(jb,enemy_list);
	rend2=new Myray(jb,enemy_list);
	for(int i=0;i<360;i++){
		end_ray1[i]=new Myray(jb,enemy_list);
	}

	light=Sprite::create("light.png");
	light->setPosition(ccp(-100,-100));
	//this->addChild(light,-2);
	light->setScale(1.2);

	light2=Sprite::create("light.png");
	light2->setPosition(ccp(-100,-100));
	//this->addChild(light2,-2);
	light->setVisible(false);
	light2->setScale(1.2);
	light2->setVisible(false);

	ref=0;
	//isbg=false;

	

	raycast_index=1;
	ims_t.x=100,ims_t.y=100;
	
	//this->update(0.01);;
	this->schedule(schedule_selector(GameScene::update));
	this->schedule(schedule_selector(GameScene::update_box2d));
	this->schedule(schedule_selector(GameScene::update_enemy));
	this->schedule(schedule_selector(GameScene::update_line));

	/*auto sp=Sprite::create("black_bg.png");
	sp->setPosition(winSize/2);
	this->addChild(sp,0);
	auto seq=Sequence::create(FadeOut::create(0.5),DelayTime::create(0.2),CallFunc::create(this,callfunc_selector(GameScene::set_touch)),NULL);
	sp->runAction(seq);*/
	auto seq=Sequence::create(ScaleTo::create(0.5,1),CallFunc::create(this,callfunc_selector(GameScene::set_touch)),NULL);
	((Sprite*)player->GetUserData())->setScale(0);
	((Sprite*)player->GetUserData())->runAction(seq);
	line_sc=0;

	
	if(initcnt==1){

	}
		CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(GameScene::domenus),
		"exit", NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(GameScene::domenus),
		"menu", NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(GameScene::domenus),
		"restart", NULL);
	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(GameScene::domenus),
		"next", NULL);

	CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
		callfuncO_selector(GameScene::domenus),
		"resume", NULL);






	shape_light = CCDrawNode::create();
	CCPoint pts[370];
	for(int i=0;i<360;i++){
		pts[i]=mymath->getline_end(winSize.width/2.0,winSize.height/2.0,(double)i,500);
	}
	shape_light->drawPolygon(pts, 1, ccc4f(1, 1, 1, 1), 0, ccc4f(1, 0, 0, 1));

	// add shape in stencil
	clip_light = ClippingNode::create();
	clip_light->setAnchorPoint(ccp(0.5, 0.5));
	clip_light->setPosition(ccp(origin.x, origin.y));
	clip_light->setStencil(shape_light);
	this->addChild(clip_light,-2);

	//* pSprite = Sprite::create("HelloWorld2.png");
	//pSprite->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//clip_light->addChild(pSprite);
	//pSprite->setOpacity(150);
	clip_light->addChild(light);
	clip_light->addChild(light2);
	//this->addChild(shape_light);

	
	//clip_light->setStencil(this->getChildByName("SHAPE"));
	//_eventDispatcher->removeAllEventListeners();
	isclear=false;
	return true;

}


void GameScene::shader_test()
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
	
	pProgram->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	pProgram->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	pProgram->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    pProgram->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    pProgram->bindAttribLocation(cocos2d::GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	pProgram->link();
	pProgram->updateUniforms();
	CHECK_GL_ERROR_DEBUG();

	CCShaderCache::getInstance()->addGLProgram(pProgram, "light");
	CHECK_GL_ERROR_DEBUG();
}
GLProgramState* GameScene::start_shader(Sprite* sprite)
{
	GLProgram *program=CCShaderCache::getInstance()->getGLProgram("light");
	GLProgramState *st=GLProgramState::create(program);
	sprite->setGLProgram(program);
	sprite->setGLProgramState(st);
	st->setUniformVec2("resolution", Vec2(sprite->getContentSize().width*sprite->getScale(),sprite->getContentSize().height*sprite->getScale()));
	st->setUniformVec2("sprite_start",Vec2(sprite->getPosition().x-sprite->getContentSize().width/2.0,sprite->getPosition().y-sprite->getContentSize().height/2.0));
	st->setUniformFloat("off",1);//0이면 셰이더 꺼지니까 제대로 다보임
	st->setUniformVec2("pos1", Vec2(-100,-100));
	st->setUniformVec2("pos2", Vec2(-100,-100));
	st->setUniformVec2("pos3", Vec2(-100,-100));//get_mirror
	st->setUniformFloat("width",50.0f);
	//else st->setUniformVec2("pos3", Vec2(rend1->get_resultp().x,rend1->get_resultp().y));




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

	sprite->getShaderProgram()->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
	sprite->getShaderProgram()->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
	sprite->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
	CHECK_GL_ERROR_DEBUG();


	sprite->getShaderProgram()->link();
	CHECK_GL_ERROR_DEBUG();


	sprite->getShaderProgram()->updateUniforms();
	CHECK_GL_ERROR_DEBUG();

	return st;
}

void GameScene::set_data()
{
	start_pos[1].x=50,start_pos[1].y=1080-165;
	end_pos[1].x=1800,end_pos[1].y=490;
	enemy_cnt[1]=0;
	mirror_pos[1].x=100,mirror_pos[1].y=100;
	star_pos[1][1].x=220,star_pos[1][1].y=760;
	star_pos[1][2].x=900,star_pos[1][2].y=880;
	star_pos[1][3].x=925,star_pos[1][3].y=110;

	
	start_pos[2].x=100,start_pos[2].y=1080-100;
	end_pos[2].x=1800,end_pos[2].y=540;
	enemy_cnt[2]=0;
	mirror_pos[2].x=100,mirror_pos[2].y=100;
	star_pos[2][1]=ccp(135,487);
	star_pos[2][2]=ccp(1300,800);
	star_pos[2][3]=ccp(1060,910);





	


	start_pos[3].x=960,start_pos[3].y=200;
	end_pos[3].x=1800,end_pos[3].y=710;
	enemy_cnt[3]=1;
	enemy_pos[3][1].x=960,enemy_pos[3][1].y=680;
	enemy_speed[3][1]=10;
	mirror_pos[3].x=100,mirror_pos[3].y=100;
	star_pos[3][1]=ccp(750,100);
	star_pos[3][2]=ccp(955,495);
	star_pos[3][3]=ccp(1400,540);
	


	start_pos[4].x=100,start_pos[4].y=570;
	end_pos[4].x=1820,end_pos[4].y=770;
	enemy_cnt[4]=2;
	enemy_pos[4][1].x=470,enemy_pos[4][1].y=895;
	enemy_pos[4][2].x=1170,enemy_pos[4][2].y=650;
	enemy_speed[4][1]=20;
	enemy_speed[4][2]=20;
	mirror_pos[4].x=110,mirror_pos[4].y=1000;
	star_pos[4][1]=ccp(810,770);
	star_pos[4][2]=ccp(1330,565);
	star_pos[4][3]=ccp(1215,930);

	
	start_pos[5].x=140,start_pos[5].y=1080-510;
	end_pos[5].x=1820,end_pos[5].y=winSize.height/2.0;
	enemy_cnt[5]=1;
	enemy_pos[5][1].x=1300,enemy_pos[5][1].y=1080-830;
	enemy_speed[5][1]=10;
	mirror_pos[5].x=100,mirror_pos[5].y=100;
	star_pos[5][1]=ccp(1035,465);
	star_pos[5][2]=ccp(1185,110);
	star_pos[5][3]=ccp(1160,860);

	
	start_pos[6].x=300,start_pos[6].y=1080-580;
	end_pos[6].x=1820,end_pos[6].y=winSize.height/2.0;
	enemy_cnt[6]=2;
	enemy_pos[6][1].x=1030,enemy_pos[6][1].y=1080-760;
	enemy_pos[6][2].x=1430,enemy_pos[6][2].y=1080-270;
	enemy_speed[6][1]=10;
	enemy_speed[6][2]=10;
	mirror_pos[6].x=100,mirror_pos[5].y=100;
	star_pos[6][1]=ccp(260,990);
	star_pos[6][2]=ccp(1390,100);
	star_pos[6][3]=ccp(1700,900);

	
	start_pos[7].x=100,start_pos[7].y=1080-100;
	end_pos[7].x=1080,end_pos[7].y=1080-670;
	enemy_cnt[7]=3;
	enemy_pos[7][1].x=85,enemy_pos[7][1].y=1080-575;
	enemy_pos[7][2].x=730,enemy_pos[7][2].y=1080-980;
	enemy_pos[7][3].x=705,enemy_pos[7][3].y=1000;
	enemy_speed[7][1]=10;
	enemy_speed[7][2]=10;
	enemy_speed[7][3]=10;
	mirror_pos[7].x=100,mirror_pos[7].y=100;
	star_pos[7][1]=ccp(75,660);
	star_pos[7][2]=ccp(960,1000);
	star_pos[7][3]=ccp(870,100);

	
	start_pos[8].x=80,start_pos[8].y=1080-590;
	end_pos[8].x=1785,end_pos[8].y=1080-143;
	enemy_cnt[8]=3;
	enemy_pos[8][1].x=735,enemy_pos[8][1].y=1080-151;
	enemy_pos[8][2].x=690,enemy_pos[8][2].y=1080-1040;
	enemy_pos[8][3].x=1350,enemy_pos[8][3].y=1080-1040;
	enemy_speed[8][1]=10;
	enemy_speed[8][2]=10;
	enemy_speed[8][3]=10;
	mirror_pos[8].x=100,mirror_pos[8].y=100;
	star_pos[8][1]=ccp(95,900);
	star_pos[8][2]=ccp(1215,1015);
	star_pos[8][3]=ccp(1275,250);

	
	start_pos[9].x=100,start_pos[9].y=1080-100;
	end_pos[9].x=540,end_pos[9].y=1080-860;
	enemy_cnt[9]=3;
	enemy_pos[9][1].x=960,enemy_pos[9][1].y=1080-255;
	enemy_pos[9][2].x=80,enemy_pos[9][2].y=1080-570;
	enemy_pos[9][3].x=1375,enemy_pos[9][3].y=1080-990;
	enemy_speed[9][1]=30;
	enemy_speed[9][2]=10;
	enemy_speed[9][3]=10;
	mirror_pos[9].x=1500,mirror_pos[9].y=1080-100;
	star_pos[9][1]=ccp(75,635);
	star_pos[9][2]=ccp(1220,745);
	star_pos[9][3]=ccp(1075,100);

	
	start_pos[10].x=150,start_pos[10].y=500;
	end_pos[10].x=1800,end_pos[10].y=500;
	enemy_cnt[10]=2;
	enemy_pos[10][1].x=511,enemy_pos[10][1].y=1000;
	enemy_pos[10][2].x=1500,enemy_pos[10][2].y=1000;
	enemy_pos[10][3].x=1375,enemy_pos[10][3].y=1080-990;
	enemy_speed[10][1]=30;
	enemy_speed[10][2]=30;
	enemy_speed[10][3]=30;
	mirror_pos[10].x=100,mirror_pos[10].y=100;
	star_pos[10][1]=ccp(940,1025);
	star_pos[10][2]=ccp(940,400);
	star_pos[10][3]=ccp(845,565);




}
void GameScene::set_world()
{
	b2Vec2 gravity(0.0,0.0f);
	world=new b2World(gravity);
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);	
	world->SetContactListener(this);
	//m_debugDraw=new GLESDebugDraw(PTM_RATIO);
	//world->SetDebugDraw(m_debugDraw);

	char name1[20]={0},name2[20]={0};
	sprintf(name1,"map/map.png",stage);
	sprintf(name2,"map",stage);
	b2BodyDef bodyDef;
	CCSprite *ims;
	ims=CCSprite::create(name1);
	this->addChild(ims,0);
	ims->setPosition(winSize/2);
	//ims->setVisible(false);
	ims->setColor(Color3B(100,100,100));
	bodyDef.userData=ims;

	bodyDef.type = b2_staticBody;

	bodyDef.position.Set(winSize.width/2.0/PTM_RATIO,winSize.height/2.0/PTM_RATIO);

	b2Body* body = world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	
	GB2ShapeCache *sc = GB2ShapeCache::getInstance();
	sc->addFixturesToBody(body,name2);
	ims->setAnchorPoint(sc->anchorPointForShape(name2));

}
void GameScene::create_player()
{
	CCLog("create_player");
	player=this->addc(start_pos[stage],"player.png",15);
	((Sprite*)player->GetUserData())->setName("player");
	((Sprite*)player->GetUserData())->setTag(777);

	

	line1=Sprite::create("line.png");
	line1->setAnchorPoint(ccp(0,0.5));
	this->addChild(line1,-2);

	line2=Sprite::create("line.png");
	line2->setAnchorPoint(ccp(0,0.5));
	this->addChild(line2,-2);
	line2->setVisible(false);
	line1->setScaleY(0.7);
	line2->setScaleY(0.7);
}
void GameScene::create_enemy()
{	
	list<enemy*>::iterator it;
	for(int i=1;i<=enemy_cnt[stage];i++){
		enemy_list.push_back(new enemy(i,enemy_speed[stage][i],this->addc(enemy_pos[stage][i],"enemy.png",30)));
	}
}
void GameScene::create_controler()
{
	joystick=Sprite::create("joystick.png");
	this->addChild(joystick,10);

	joystick_bg=Sprite::create("joystick_bg.png");
	this->addChild(joystick_bg,9);
	joystick_bg->setPosition(joystick_bg->getContentSize()/2);
	joystick->setPosition(joystick_bg->getPosition());
	
	auto st_anglebg=Sprite::create("control_bg.png");
	st_anglebg->setPosition(ccp(winSize.width-st_anglebg->getContentSize().width/2.0,st_anglebg->getContentSize().height/2.0));
	this->addChild(st_anglebg,9);

	st_angle=Sprite::create("control.png");
	st_angle->setPosition(ccp(winSize.width-st_angle->getContentSize().width/2.0,st_angle->getContentSize().height/2.0));
	this->addChild(st_angle,9);

	

	control_angle=Sprite::create("control2.png");
	control_angle->setPosition(ccp(winSize.width-control_angle->getContentSize().width/2.0,control_angle->getContentSize().height/2.0));
	this->addChild(control_angle,9);

	isjoystick=false;
	iscontrol=false;
	joystick_g=joystick_bg->getPosition();
}

b2Body* GameScene::addc(Point pos,char sp_name[], double rad)
{
		b2BodyDef bodyDef;
	CCSprite *ims=CCSprite::create(sp_name);
	ims->setPosition(pos);
	this->addChild(ims,-1);
	//ims->setVisible(false);
	bodyDef.userData=ims;

	bodyDef.type = b2_dynamicBody;

	bodyDef.position.Set(pos.x/PTM_RATIO, pos.y/PTM_RATIO);

	b2Body* body = world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius=rad/PTM_RATIO;


	b2FixtureDef fixtureDef;

	fixtureDef.shape = &circle;

	fixtureDef.density = 3.0f;

	fixtureDef.friction = 1.0f;

	fixtureDef.restitution = 0.0f;

	body->CreateFixture(&fixtureDef);

	body->SetGravityScale(1.0f);

	return body;
}


void GameScene::addmap()
{
	
	char name1[20]={0},name2[20]={0};
	sprintf(name1,"map/%d.png",stage);
	sprintf(name2,"%d",stage);
	b2BodyDef bodyDef;
	CCSprite *ims;
	ims=CCSprite::create(name1);
	this->addChild(ims,0);
	ims->setPosition(winSize/2);
	//ims->setVisible(false);
	bodyDef.userData=ims;

	bodyDef.type = b2_staticBody;

	bodyDef.position.Set(winSize.width/2.0/PTM_RATIO,winSize.height/2.0/PTM_RATIO);

	b2Body* body = world->CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	
	GB2ShapeCache *sc = GB2ShapeCache::getInstance();
	sc->addFixturesToBody(body,name2);
	ims->setAnchorPoint(sc->anchorPointForShape(name2));



	//방해물(그냥 검은색으로만되있는거)

	/*
	sprintf(name1,"map/%db.png",stage);
	auto sp=Sprite::create(name1);
	sp->setPosition(winSize/2.0);
	this->addChild(sp,0);*/

	//끝나는곳
	auto end_bg=Sprite::create("end_bg.png");
	end_bg->setPosition(end_pos[stage]);
	this->addChild(end_bg,1);

	auto end=Sprite::create("end.png");
	end->setPosition(end_pos[stage]);
	this->addChild(end,1);
	end->setName("END");


	//거울아이템
	auto mirror=Sprite::create("mirror.png");
	mirror->setPosition(mirror_pos[stage]);
	this->addChild(mirror,-100);
	mirror->setTag(4);
	
	mirror->setName("MIRROR");
	st_mirror=this->start_shader(mirror);


	//스타
	
	for(int i=1;i<=3;i++){
		get_stars[i]=false;
		Sprite* star;
		if(stage_star[stage][i]==1)star=Sprite::create("star2.png");
		else star=Sprite::create("star1.png");
		star->setPosition(star_pos[stage][i]);
		this->addChild(star,-1);
		star->setTag(i);
		star->setScale(0.7);

		sprintf(name1,"STAR%d",i);
		star->setName(name1);
		if(stage_star[stage][i]!=1) st_star[i]=this->start_shader(star);

		Sprite* star_bg;
		if(stage_star[stage][i]==0)star_bg=Sprite::create("star_bg.png");
		else star_bg=Sprite::create("star1.png");
		star_bg->setAnchorPoint(ccp(1,0.5));
		star_bg->setPosition(ccp(winSize.width-(star_bg->getContentSize().width)*(3-i),winSize.height-star_bg->getContentSize().height/2));
		this->addChild(star_bg,2);
	}
	

}
void GameScene::addj()
{
	char name1[20]={0},name2[20]={0};
	sprintf(name1,"map/%dj.png",stage);
	sprintf(name2,"%dj",stage);
	b2BodyDef bodyDef;
	CCSprite *ims;
	ims=CCSprite::create(name1);
	ims->setPosition(winSize/2);
	this->addChild(ims,1);
	//ims->setVisible(false);
	bodyDef.userData=ims;

	bodyDef.type = b2_staticBody;

	bodyDef.position.Set(winSize.width/2.0f/PTM_RATIO,winSize.height/2.0f/PTM_RATIO);

	b2Body* body = world->CreateBody(&bodyDef);


	b2FixtureDef fixtureDef;

	
	GB2ShapeCache *sc = GB2ShapeCache::getInstance();
	sc->addFixturesToBody(body,name2);
	ims->setAnchorPoint(sc->anchorPointForShape(name2));
	jb=body;
}
void GameScene::update(float dt)
{

	Point rrr;
	b2RayCastCallback *callback;
	


	player->SetTransform(player->GetPosition(),CC_DEGREES_TO_RADIANS( r_angle));


	if(mymath->getdist(((Sprite*)player->GetUserData())->getPosition(),end_pos[stage])<50) this->clear();
	
	if(get_mirror==false&&mymath->getdist(((Sprite*)player->GetUserData())->getPosition(),mirror_pos[stage])<50){//거울먹기
		get_mirror=true;
		light2->setVisible(true);
		line2->setVisible(true);
		this->getChildByName("MIRROR")->setVisible(false);
	}

	for(int i=1;i<=3;i++){//별먹는거
		if(get_stars[i]==false&&mymath->getdist(    ccp(player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO), star_pos[stage][i]     )<65){
			char name[200]={0};
			sprintf(name,"STAR%d",i);
			Sprite *sp=((Sprite*)this->getChildByName(name));
			sp->setZOrder(1);
			auto move=MoveTo::create(0.5,ccp(winSize.width-(sp->getContentSize().width)*(3-i)-sp->getContentSize().width/2.0,
				winSize.height-sp->getContentSize().height/2));
			auto acts=EaseIn::create(move,3.0);
			auto scale=ScaleTo::create(0.5,1);
			auto spw=Spawn::create(acts,scale,NULL);
			Sequence *seq=Sequence::create(spw,NULL);
			get_stars[i]=true;
			sp->runAction(seq);
			break;
		}
	}
	//sprintf(name,"(%.0lf,%.0lf),(%.0lf,%.0lf) angle:%.5lf",player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO,rend1->get_resultp().x,rend1->get_resultp().y,rend1->get_angle());
	//label->setString(name);



	this->update_gl_state(dt);
}
///죽는거 여기있음
void GameScene::update_enemy(float dt)//죽는거 여기있음
{
	for(list<enemy*>::iterator it=enemy_list.begin();it!=enemy_list.end();it++){
		(*it)->update(dt,world,ccp(player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO));
		Point pos1=((Sprite*)(*it)->get_body()->GetUserData())->getPosition();
		Point pos2=((Sprite*)player->GetUserData())->getPosition();
		double dist=mymath->getdist(pos1,pos2);
		if(dist<45){//게임오버
			this->die();
			
		}
	}
}
void GameScene::update_line(float dt){
	rend1->go_raycast_angle(player->GetPosition(),r_angle,world,3000);
	light->setPosition(rend1->get_resultp());
	rend2->go_raycast_angle(rend1->get_result(),rend1->get_ref_angle(),world,3000);
	light2->setPosition(rend2->get_resultp());

	Sprite *sp=(Sprite*)player->GetUserData();

	line1->setPosition(sp->getPosition());
	line1->setRotation(-r_angle);
	
	if(line_sc<1.0){
		line_sc+=dt*2.0,line1->setScaleY(line_sc*0.7);
	}
	else line_sc=1.0;
	line1->setScaleX(mymath->getdist(sp->getPosition(),
		rend1->get_resultp())/1920.0  *line_sc);

	line2->setPosition(rend1->get_resultp());
	line2->setRotation(-mymath->getangle(rend1->get_resultp(),rend2->get_resultp()));
	line2->setScaleX(mymath->getdist(rend1->get_resultp(),rend2->get_resultp())/1920.0);



	Color3B color=Color3B::WHITE;
	double dist=mymath->getdist(ccp(player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO),rend1->get_resultp());
	if(dist>255.0) dist=255.0;
	if(ispause) dist=255.0;
	//dist=10000;
	//color.r;

	if(rend1->contact_j()) line2->setVisible(false),light2->setVisible(false);
	else if(rend1->contact_j()==false&&get_mirror) line2->setVisible(true),light2->setVisible(true);
	//light->setVisible(false);
	if(rend1->contact_j()){
	color.g=dist;
	color.b=dist;
	}
	line1->setColor(color),line2->setColor(color),light->setColor(color),light2->setColor(color);
	((Sprite*)player->GetUserData())->setColor(color);

	


	//CCDrawNode* shape = CCDrawNode::create();

	//CCPoint pts[370];
	//for(int i=0;i<360;i++){
	//	pts[i]=mymath->getline_end(winSize.width/2.0,winSize.height/2.0,(double)i,500);
	//	//pts[i]=ccp()
	//	//pts[i]=ccp(0,0);
	//}
	////pts[2]=winSize;
	////pts[3]=ccp(winSize.width,0);

	//shape->drawPolygon(pts, 360, ccc4f(1, 1, 1, 1), 0, ccc4f(1, 0, 0, 1));

	//clip_light->setStencil(this->getChildByName("SHAPE"));


	/*
	auto spr=Sprite::create("light.png");
	spr->setPosition(rend1->get_resultp());
	this->addChild(spr,-2);*/

}
void GameScene::update_gl_state(float dt)
{
	/*
	state->setUniformVec2("pos1", Vec2(player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO));
	state->setUniformVec2("pos2", Vec2(rend1->get_resultp().x,rend1->get_resultp().y));

	st_mirror->setUniformVec2("pos1", Vec2(player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO));
	st_mirror->setUniformVec2("pos2", Vec2(rend1->get_resultp().x,rend1->get_resultp().y));

	if(get_mirror)state->setUniformVec2("pos3", Vec2(rend2->get_resultp().x,rend2->get_resultp().y)),st_mirror->setUniformVec2("pos3", Vec2(rend2->get_resultp().x,rend2->get_resultp().y));
	else state->setUniformVec2("pos3", Vec2(rend1->get_resultp().x,rend1->get_resultp().y)),st_mirror->setUniformVec2("pos3", Vec2(rend1->get_resultp().x,rend1->get_resultp().y));*/


	

	//((Sprite*)this->getChildByName("MIRROR"))->getGLProgram();
	
	//this->set_gl_state(((Sprite*)this->getChildByName("ims"))->getGLProgramState(),1);
	this->set_gl_state(st_mirror,1);
	for(int i=1;i<=3;i++){
		if(stage_star[stage][i]==1) continue;
		if(get_stars[i])this->set_gl_state(st_star[i],0);
		else this->set_gl_state(st_star[i],1);
	}
}
void GameScene::update_box2d(float dt)
{
	if(stage==10&&ispause==false)jb->SetTransform( jb->GetPosition(),jb->GetAngle()+CC_DEGREES_TO_RADIANS(-360.0/6.0*dt) );
	int velocityIterations = 8;
	int positionIterations = 1;
	world->Step(dt, velocityIterations, positionIterations);
	for(b2Body *b=world->GetBodyList();b;b=b->GetNext())
	{
		if(b->GetUserData()!=NULL)
		{
			CCSprite *bd=(CCSprite*)b->GetUserData();
			bd->setPosition(ccp(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO));
			bd->setRotation(-1*CC_RADIANS_TO_DEGREES(b->GetAngle()));
			//bd->setVisible(false);
		}
	}
}
void GameScene::set_touch()
{
	light->setVisible(true);
	   auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(GameScene::onTouchesMoved, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(GameScene::onTouchesCancelled, this);
    listener->onTouchesEnded = CC_CALLBACK_2(GameScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	ispause=false;

		//백키
	auto keylistener=EventListenerKeyboard::create();
	keylistener->onKeyReleased=CC_CALLBACK_2(GameScene::onKeyReleased,this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener,this);

	char name[200]={0};
	for(int i=1;i<=3;i++){
				sprintf(name,"STAR%d",i);
				((Sprite*)this->getChildByName(name))->setZOrder(-100);
			}
}



void GameScene::set_gl_state(GLProgramState* st, bool off)
{
	st->setUniformFloat("off",off);//0이면 셰이더 꺼지니까 제대로 다보임
	st->setUniformVec2("pos1", Vec2(player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO));
	st->setUniformVec2("pos2", Vec2(rend1->get_resultp().x,rend1->get_resultp().y));
	st->setUniformFloat("r_angle",mymath->angleto0360(r_angle)),st->setUniformFloat("r_angle2",mymath->angleto0360(rend1->get_ref_angle()));
	if(get_mirror)st->setUniformVec2("pos3", Vec2(rend2->get_resultp().x,rend2->get_resultp().y));
	else st->setUniformVec2("pos3", Vec2(rend1->get_resultp().x,rend1->get_resultp().y));
}
void GameScene::clear()
{
	//stage++;
	for(list<enemy*>::iterator it=enemy_list.begin();it!=enemy_list.end();it++){
		(*it)->stop();
	}

	sound->stopAllEffects();
	if(stage+1>data->get_max_stage()) data->set_max_stage(stage+1),max_stage++;
	for(int i=1;i<=3;i++){
		if(stage_star[stage][i]==0&&get_stars[i]==1){//처음별먹은거
			effect_star[i]=1,stage_star[stage][i]=1,data->set_stage_star(stage,i);
		}
		else if(stage_star[stage][i]==1) effect_star[i]=2;//이번판에 먹든안먹든 옛날에 먹었던거
		else effect_star[i]=0;//그냥 아직 못먹은거
	}

	
	player->SetLinearVelocity(b2Vec2((end_pos[stage].x/PTM_RATIO-player->GetPosition().x),(end_pos[stage].y/PTM_RATIO-player->GetPosition().y)));
	_eventDispatcher->removeAllEventListeners();
	ispause=true;
		joystick->setPosition(joystick_bg->getPosition());
		this->unschedule(schedule_selector(GameScene::update));
		//this->unschedule(schedule_selector(GameScene::update_box2d));
		this->unschedule(schedule_selector(GameScene::update_enemy));
		((Sprite*)this->getChildByName("END"))->runAction(FadeOut::create(1));
		CallFunc *action=CallFuncN::create(this,callfuncN_selector(GameScene::popup_open));
		Sequence *seq=Sequence::create(MoveTo::create(1,end_pos[stage]),action,NULL);
		((Sprite*)player->GetUserData())->setTag(2);
		((Sprite*)player->GetUserData())->setZOrder(10);
		((Sprite*)player->GetUserData())->runAction(seq);
		isclear=true;
}
void GameScene::die()
{
	char name[200]={0};
	sound->stopAllEffects();
			this->unschedule(schedule_selector(GameScene::update));
			this->unschedule(schedule_selector(GameScene::update_enemy));
			this->unschedule(schedule_selector(GameScene::update_box2d));
			CallFunc *action=CCCallFuncN::create(this, callfuncN_selector(GameScene::popup_open));
			Sequence *seq=Sequence::create(FadeIn::create(0.5),DelayTime::create(0.2),action,NULL);

			auto black_bg=Sprite::create("black_bg.png");
			black_bg->setOpacity(0);
			black_bg->setPosition(winSize/2);
			black_bg->setTag(3);
			this->addChild(black_bg,0);
			black_bg->runAction(seq);
			
			for(int i=1;i<=3;i++){
				sprintf(name,"STAR%d",i);
				((Sprite*)this->getChildByName(name))->setZOrder(1);
			}
}

//void GameScene::menuCloseCallback(Ref* pSender)
//{/*
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif*/
//	if(isbg) isbg=false;
//	else isbg=true;
//}




void GameScene::onTouchesBegan(const std::vector<Touch*>&touches, Event* unused_event)
{
	Point touchStart;
	char name[200]={0};

	
	


	if(ispause) return;
	for (auto iter = touches.begin(); iter != touches.end(); iter++)
	{
		touchStart = (*iter)->getLocation();
		//this->addc(touchStart,"enemy.png",30);

		sprintf(name,"(%.0lf,%.0lf)",touchStart.x,touchStart.y);
		//label->setString(name);
		ims_t=touchStart;
		//state->setUniformVec2("resolution", Vec2(touchStart.x,touchStart.y));
		//((Sprite*)this->getChildByName("sss"))->setPosition(touchStart);
		if(control_angle->boundingBox().containsPoint(touchStart)&&iscontrol==false){
			r_angle=mymath->getangle(control_angle->getPosition(),touchStart);
			st_angle->setRotation(-r_angle);
			start_angle=mymath->getangle(control_angle->getPosition(),touchStart);
			bh_angle=start_angle;
			before_rangle=r_angle;
			before_angle=control_angle->getRotation()*-1;
			iscontrol=(*iter)->getID()+1;
		}
		else if(joystick_bg->boundingBox().containsPoint(touchStart)&&isjoystick==false){
			isjoystick=(*iter)->getID()+1;
			//this->addc(touchStart);
		}


		/*
		CCPoint pts[370];
		int k=1;
	shape_light->clear();
	for(int i=0;i<360/k;i++){
		end_ray1[i]->go_raycast_angle(b2Vec2(touchStart.x/PTM_RATIO,touchStart.y/PTM_RATIO),(double)i*k,world);
		pts[i]=end_ray1[i]->get_resultp();
		//auto sp=Sprite::create("lights.png");
		//sp->setPosition(end_ray1[i]->get_resultp());
		//this->addChild(sp,100);
		
	}
	//pts[0]=ccp(0,0);
	//shape_light->drawpol
	//pts[0]=ccp(0,0),pts[1]=ccp(winSize.width,0),pts[2]=ccp(touching.x,touching.y);
	shape_light->drawPolygon(pts, 360/k, ccc4f(1, 1, 1, 1), 0, ccc4f(1, 1, 1, 1));
	clip_light->setStencil(shape_light);*/
	}

}
 
void GameScene::onTouchesMoved(const std::vector<Touch*>&touches, Event* unused_event) 
{
	Point touching;
	if(ispause) return;
	for (auto iter = touches.begin(); iter != touches.end(); iter++)
	{
		touching = (*iter)->getLocation();
		//this->draw_light(touching);

		ims_t=touching;
		if((*iter)->getID()+1==isjoystick){
			joystick_h=touching;
			
			double angle=mymath->getangle(joystick_g,joystick_h);	
			double len=mymath->getdist(joystick_g,joystick_h);
			//r_angle=angle;
			if(len>150.0){
				joystick_h.x=150*   cos(CC_DEGREES_TO_RADIANS( angle))+joystick_g.x;
				joystick_h.y=150*sin(CC_DEGREES_TO_RADIANS( angle))+joystick_g.y;
			}

			joystick->setPosition(joystick_h);
			player->SetLinearVelocity(b2Vec2((joystick_h.x-joystick_g.x)*0.07,(joystick_h.y-joystick_g.y)*0.07));
		}
		else if((*iter)->getID()+1==iscontrol)
		{
			double h_angle=mymath->getangle(control_angle->getPosition(),touching);
			//r_angle= before_rangle +(h_angle-start_angle)/3.0;
			double gap=h_angle-bh_angle;
			if(gap>180) gap-=360;
			else if(gap<-180) gap+=360;
			r_angle+=(gap)/10.0;
			bh_angle=h_angle;
			control_angle->setRotation((before_angle +(h_angle-start_angle))*-1);
			st_angle->setRotation(-r_angle);
			if(bh_angle<start_angle&&h_angle>start_angle){
			}
			
			/*char name[200]={0};
			sprintf(name,"%lf",(h_angle-bh_angle)*1000);
			label->setString(name);*/
		}
	}



}
 
void GameScene::onTouchesCancelled(const std::vector<Touch*>&touches, Event* unused_event) 
{
}
 
void GameScene::onTouchesEnded(const std::vector<Touch*>&touches, Event* unused_event) 
{
    Point touchEnd;
	if(ispause) return;
	for (auto iter = touches.begin(); iter != touches.end(); iter++)
	{
		if((*iter)->getID()+1==isjoystick){
		player->SetLinearVelocity(b2Vec2(0,0));
		isjoystick=0;
		joystick->setPosition(joystick_bg->getPosition());
		}
		else if((*iter)->getID()+1==iscontrol){
			iscontrol=0;
		}
	}
}









void GameScene::draw(Renderer* renderer, const kmMat4& transform, uint32_t transformUpdated)
{

	//if(ispause) label->setString("pause");
	//else label->setString("normal");
	//ccDrawSolidRect(Vec2(0,0),winSize,Color4F(0,1,0,255));
	glLineWidth(5);
    ccDrawColor4F(255, 255, 255, 255);
	//ccDrawLine(Vec2(player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO),r_end);
	//ccDrawLine(r_end,r_end2);

	//CocosDenshion::SimpleAudioEngine *sound=CocosDenshion::SimpleAudioEngine::sharedEngine();
	//int k=sound->playEffect("s");
	
	//line2->setVisible(false);

	//ccDrawLine(Vec2(r_end.x,r_end.y),Vec2(normalp.x+r_end.x,normalp.y+r_end.y));

	
	//this->draw_light(ccp(player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO),333);
	Point light_pos=mymath->getline_end(light->getPosition().x,light->getPosition().y,r_angle+180,5);
	Point light_pos2=mymath->getline_end(light2->getPosition().x,light2->getPosition().y,rend1->get_ref_angle()+180,5);
	
	shape_light->clear();
	this->draw_light(light_pos,100);
	this->draw_light(light_pos2,100);
	

	//shape_light->drawTriangle(ccp(0,0),ccp(100,100),ccp(100,0),Color4F::WHITE);
	//shape_light->drawTriangle(ccp(500,500),ccp(600,600),ccp(600,500),Color4F::WHITE);
	//shape_light->drawSegment(ccp(0,0),ccp(100,100),10,Color4F::WHITE);

	//pts[0]=ccp(100,100),pts[1]=ccp(300,100),pts[2]=ccp(300,300),pts[3]=ccp(100,300),pts[4]=ccp(250,200);
	//shape_light->drawPolygon(pts, 5, ccc4f(1, 1, 1, 1), 0, ccc4f(1, 0, 0, 1));
	
	//shape_light->drawPolygon(pts, 360/k, ccc4f(1, 1, 1, 1), 0, ccc4f(1, 0, 0, 1));
	
	//GL_POLYGON;
	//glDrawArrays(GL_POLYGON,
	//ccDrawSolidPoly(pts,360/k,ccColor4F::RED);
	//shape_light->drawPolygon(pts,360/k,Color4F::BLUE,0,Color4F::BLUE);
	//shape_light->setBlendFunc(
	//clip_light->setStencil(shape_light);




}
void GameScene::draw_light(Point pos,double len)
{
	int k=1;
	Point pts[370];
	end_ray1[0]->go_raycast_angle(b2Vec2(pos.x/PTM_RATIO,pos.y/PTM_RATIO),0.0,world,len);
	pts[0]=end_ray1[0]->get_resultp();
	
	for(int i=1;i<360/k;i++){
		end_ray1[i]->go_raycast_angle(b2Vec2(pos.x/PTM_RATIO,pos.y/PTM_RATIO),(double)i*k,world,len);
		pts[i]=end_ray1[i]->get_resultp();
		ccDrawColor4F(0, 0, 255, 255);
		//ccDrawLine(pts[i-1],pts[i]);
		//shape_light->drawTriangle(pts[i-2],pts[i-1],pts[i],Color4F::WHITE);
		
		shape_light->drawTriangle(pos,pts[i-1],pts[i],ccColor4F::RED);

		ccDrawColor4F(255, 0, 0, 255);
		//ccDrawSolidCircle(pts[i],5,0,50);
		//shape_light->drawDot(pts[i],10,Color4F::WHITE);
		//auto sp=Sprite::create("lights.png");
		//sp->setPosition(end_ray1[i]->get_resultp());
		//this->addChild(sp,100);

	}
	shape_light->drawTriangle(ccp(player->GetPosition().x*PTM_RATIO,player->GetPosition().y*PTM_RATIO),pts[360/k-1],pts[0],ccColor4F::RED);
}


void GameScene::domenus(CCObject *obj)
{
	sound->resumeAllEffects();
	CCLog("do_menus");
	//노티피케이션 받기

	Node* node = (Node*) obj;	
	int tag=node->getTag();

	Director::sharedDirector()->resume();
	//this->set_touch();
	ispause=false;
	//this->removeChildByName("pause");

	CCString *pParam=(CCString*)obj;
	//CCLog("notification %s", pParam->getCString());
	//_eventDispatcher->setEnabled(true);
	if(tag==0)Director::sharedDirector()->replaceScene(GameMenuScene::createScene()),sound->stopAllEffects();
	else if(tag==1)CCLog("restarts"),Director::sharedDirector()->replaceScene(GameScene::createScene()),sound->stopAllEffects(),CCLog("restarte");
	else if(tag==2)Director::sharedDirector()->end();
	else if(tag==3)stage++,Director::sharedDirector()->replaceScene(GameScene::createScene()),sound->stopAllEffects();
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{	
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE&&ispause==false)
	{
		Director::sharedDirector()->pause();
		Director::sharedDirector()->setAnimationInterval(1.0/60.0);
		Node *n=Node::create();
		n->setTag(1);
		this->popup_open(n);
		joystick->setPosition(joystick_bg->getPosition());
		player->SetLinearVelocity(b2Vec2(0,0));
		//Director::sharedDirector()->replaceScene(GameScene::createScene());
	}
}

void GameScene::popup_open(Node *node)
{
	CCLog("create_popup");
	sound->pauseAllEffects();
		ispause=true;
		Director::sharedDirector()->pause();
		Director::sharedDirector()->setAnimationInterval(1.0/60.0);
		//_eventDispatcher->removeAllEventListeners();
		//_eventDispatcher->setEnabled(false);
		//CCScene* pScene=Popup::scene();
		Popup* pScene=new Popup(node->getTag());
		pScene->setPosition(winSize/2);
		pScene->setName("pause");
		this->addChild(pScene,100);
		joystick->setPosition(joystick_bg->getPosition());
		player->SetLinearVelocity(b2Vec2(0,0));

		if(isclear) this->star_effect();
}
void GameScene::star_effect()
{
	Director::sharedDirector()->resume();
	ScaleTo *act[5];
	double delay=0.5;
	double time=-delay,gap=300;
	double star_scale=2;
	Point pos=ccp(winSize.width/2.0-gap,winSize.height/2.0-170);
	for(int i=1;i<=3;i++)
	{
		auto sp=Sprite::create("star1.png");
		sp->setPosition(pos);
		sp->setScale(0);
		this->addChild(sp,101);
		if(stage_star[stage][i]==0||(effect_star[i]==1)){
			auto spbg=Sprite::create("star_bg.png");
			spbg->setPosition(pos);
			spbg->setScale(star_scale);
			this->addChild(spbg,102);
		}
		else if(stage_star[stage][i]==1) sp->setScale(star_scale);
		if(effect_star[i]==1){
			time+=delay;
			auto act1=EaseIn::create(ScaleTo::create(delay,star_scale),7.0);
			sp->runAction(Sequence::create(DelayTime::create(time),   act1,NULL));
		}
		pos.x+=gap;
	}
	

}
GameScene::~GameScene()
{	
	CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}

void GameScene::BeginContact(b2Contact* contact)
{
	b2Body *A=contact->GetFixtureA()->GetBody(),*B=contact->GetFixtureB()->GetBody();
	if(A!=player&&B!=player) return;
	if((A==player&&B==jb)||(A==jb&&B==player)){this->die();}

}
void GameScene::EndContact(b2Contact* contact)
{
    //충돌 되었던 녀석들이 떨어질 때...
}
void GameScene::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
 

//움직여서 박은 놈. 계속 호출됨 

}

void GameScene::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)

{

    //당한 놈. 계속 호출됨. 

}

