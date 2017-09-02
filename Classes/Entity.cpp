#include "Entity.h"
#include "GlobeDefine.h"

	
Entity::Entity()
{
	m_sprite = NULL;
	m_nHp = 0;
	m_nSpeed = 0;
	m_sName = "";
	m_isDead = false;
}


Entity::~Entity()
{
}

Sprite * Entity::getSprite()
{
	return m_sprite;
}

void Entity::bindSprite(Sprite * sprite)
{
	if (this->m_sprite != NULL)
	{
		sprite->removeAllChildrenWithCleanup(true);

	}
	this->m_sprite = sprite;
	this->addChild(m_sprite);
	
	Size size = m_sprite->getContentSize();
	this->setContentSize(size);
	onBindSprite();
}

void Entity::hurtMe(int nHurtValue)
{
	if (m_isDead)
	{
		return;
	}

	int nAfterHp = getnHp() - nHurtValue;
	onHurt(nHurtValue);
	
	if (nAfterHp >0)
	{
		setnHp(nAfterHp);
	}
	else {
		if (m_fShowTime == -999)
		{
			onDead();
			return;
		}
		m_isDead = true;
		onDead();
	}
}

bool Entity::isDead()
{
	return m_isDead;
}

void Entity::onDead()
{
	this->setVisible(false);
}

void Entity::onHurt(int nHurtValue)
{
	
}

void Entity::onBindSprite()
{
}


