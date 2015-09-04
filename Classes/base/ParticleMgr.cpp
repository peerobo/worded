//
//  ParticleMgr.cpp
//  other game
//
//  Created by Duc_NH on 7/26/14.
//
//

#include "ParticleMgr.h"
#include "../GlobalVar.h"
ParticleMgr* ParticleMgr::instance = new ParticleMgr();

ParticleMgr* ParticleMgr::getInstance()
{
    return instance;
}

ParticleMgr::ParticleMgr()
{
}

ParticleSystemQuad* ParticleMgr::showParticle(std::string particlePath, std::string textureName, Node* stage, int zOrder, bool hasColor, Color4F startColor, Color4F endColor)
{
	ParticleSystemQuad* particle = ParticleSystemQuad::create(particlePath);	
	SpriteFrame* sprFrm = SpriteFrameCache::getInstance()->getSpriteFrameByName(textureName);
	particle->setTextureWithRect(sprFrm->getTexture(), sprFrm->getRect());
	if (hasColor)
	{
		particle->setStartColor(startColor);
		particle->setEndColor(endColor);
	}
	
	if (zOrder == -1)
		zOrder = 101;
	if (stage)
		stage->addChild(particle, zOrder);
	else
		GlobalVar::curScene->addChild(particle, zOrder);
	return particle;
}

void ParticleMgr::showParticleNoReturn(std::string particlePath, std::string textureName, Node* stage, int zOrder, bool hasColor, Color4F startColor, Color4F endColor)
{
	showParticle(particlePath, textureName, stage, zOrder, hasColor,startColor,endColor);
}