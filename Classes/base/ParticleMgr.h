//
//  ParticleMgr.h
//  other game
//
//  Created by Duc_NH on 7/26/14.
//
//

#ifndef __other_game__ParticleMgr__
#define __other_game__ParticleMgr__

#include "cocos2d.h"//;
using namespace cocos2d;

enum E_PARTICLE_TYPE {
    PAR_EXPLODE1 = 0,
    PAR_CAST1,
    PAR_WINDX,
    PAR_WINDY,
    PAR_SMOKE,
    PAR_MISSILE,
    PAR_MAGNET,
    PAR_WAVE
};

class ParticleMgr {
public:
    static ParticleMgr* instance;
    static ParticleMgr* getInstance();
	ParticleSystemQuad* showParticle(std::string particlePath, std::string textureName, Node* stage = NULL, int zOrder = -1, bool hasColor = false, Color4F startColor = Color4F::WHITE, Color4F endColor = Color4F::WHITE);
	void showParticleNoReturn(std::string particlePath, std::string textureName, Node* stage = NULL, int zOrder = -1, bool hasColor = false, Color4F startColor = Color4F::WHITE, Color4F endColor = Color4F::WHITE);
private:
	ParticleMgr();		
};

#endif /* defined(__other_game__ParticleMgr__) */
