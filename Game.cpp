#include "Game.h"
using namespace Game;
//-------------Creature------------		
Creature::Creature(int hp, int dmg, int speed)
{
	stats.hp = hp;
	stats.dmg = dmg;
	stats.speed = speed;
	pos.x = 10;
	pos.y = 10;
}
Creature::~Creature(){}
void Creature::gotoTarget(const Utils::MathVector &v)
{	
	if(std::abs(pos.x-v.x) > 5 || std::abs(pos.y-v.y) > 5)
	{			
		step = v;
		step = step - pos;
		step.normalize();
		step = step * stats.speed;
		pos = pos + step;
	}	
}
void Creature::attack(std::shared_ptr<Creature> p){p->getAttacked(stats.dmg);}
void Creature::getAttacked(int dmg){stats.hp -= dmg;}
int Creature::getHP(){return stats.hp;}
	
//-------------DmgEffect------------	
DmgEffect::DmgEffect(const std::shared_ptr<Creature> target, int casting_time, int dmg)
			:target(target),dmg(dmg){ timer.setTick(casting_time); }
DmgEffect::~DmgEffect(){}
bool DmgEffect::cast()
{
	if(!casting_trig)
	{
		casting_trig = true;
		timer.reset();
	}
	if(!casted)
	{
		casted = timer.isTime();			
		if(casted)
			target->getAttacked(dmg);
	}
	return casted;
}

//-------------Spell------------
Spell::Spell(){}
Spell::~Spell(){}		
void Spell::addEffect(std::unique_ptr<Effect> effect){effects.push_back(std::move(effect));}
void Spell::cast()
{				
	if(current_effect < effects.size())
	{
		if( effects[current_effect]->cast() )
			current_effect++;
	}
	else
	{	
		done_casting = true;
	}
}
//-------------Spell------------
	