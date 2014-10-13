
#include "gd.h"
#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    {
//        CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
//        CCFileUtils *pFileUtils = CCFileUtils::sharedFileUtils();
//        std::vector<std::string> searchPaths;
//        
//        CCSize designSize = CCSizeMake(480, 320);
//        CCSize resourceSize;
//        
//        // if the device is iPad
//        if (screenSize.height >= 768) {
//            searchPaths.push_back("hd");
//            searchPaths.push_back("sd");
//            
//            resourceSize = CCSizeMake(1024, 768);
//            designSize = CCSizeMake(1024, 768);
//        }
//        // if the device is iPhone
//        else{
//            // for retina iPhone
//            if (screenSize.height > 320) {
//                searchPaths.push_back("hd");
//                searchPaths.push_back("sd");
//                resourceSize = CCSizeMake(960, 640);
//            }
//            else{
//                searchPaths.push_back("sd");
//                resourceSize = CCSizeMake(480, 320);
//            }
//        }
//        searchPaths.push_back("WhackAMoleSounds");
//        pFileUtils->setSearchPaths(searchPaths);
//        pDirector->setContentScaleFactor(resourceSize.width / designSize.width);
//        
//        CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, kResolutionFixedWidth);
    }
    
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    //
    gdInit();
    
    // create a scene. it's an autorelease object
    CCScene *pScene = GameScene::scene();
    
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
