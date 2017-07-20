#ifndef _GAME_H
#define _GAME_H

#include <memory>
#include <iostream>
#include <vector>
#include "Utils.h"
namespace Game
{
	struct Stats
	{
		int hp, dmg, speed;
		bool dead;
	};
	class Creature
	{
		private:
		
		Stats stats;
		Utils::MathVector step;
		
		public:
		
		Utils::MathVector pos;
		
		Creature(int hp, int dmg, int speed);
		~Creature();
		void gotoTarget(const Utils::MathVector &v);
		void attack(std::shared_ptr<Creature> p);
		void getAttacked(int dmg);
		int getHP();
	};
	class Effect
	{
		public:
		virtual bool cast()=0;
	};
	class DmgEffect : public Effect
	{
		Utils::Timer timer;
		std::shared_ptr<Creature> target;
		bool casted = false;
		bool casting_trig = false;
		int dmg;
		
		public:
		
		DmgEffect(const std::shared_ptr<Creature> target, int casting_time, int dmg);
		~DmgEffect();
		bool cast();
	};
	
	class Spell
	{
		private:
		
		std::vector<std::unique_ptr<Effect>> effects;
		int current_effect = 0;
		
		public:
		
		bool done_casting = false;
		
		Spell();
		~Spell();
		void addEffect(std::unique_ptr<Effect> effect);
		void cast();
	};
	class Projectile
	{
		Spell spell;
		int x,y;// destination;
		
	};
}

#endif