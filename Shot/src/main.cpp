#include "lib/framework.hpp"
#include <iostream>

#define SPEED 7
#define BULLETNUM 3
#define BULLETSPEED 10

class App{
private:
	App(){}
public:
	static AppEnv& get(){
		static   AppEnv env(640,480);
		return env;
	}
};

class Player {
private:
	enum vecter{
		RIGHT = 1,LEFT = -1
	};
	struct Obj{
		Vec2f pos;
		float dir;
	};

	Texture player;
	int direction;
	int shotNum;
	bool flag[BULLETNUM];
	Obj character;
	Obj bullet[BULLETNUM];

public:
	Player(){
		player = Texture("res/player.png");
		character.pos = Vec2f(0, 0);
		direction = LEFT;
		shotNum = 0;
		for (int i = 0; i < BULLETNUM; i++){
			flag[i] = true;
			bullet[i].pos = Vec2f(1000, 1000);
			bullet[i].dir = 0;
		}
	}

	void getKey(){
		if (App::get().isPressKey('A')){
			direction = LEFT;
			character.pos.x() -= SPEED;
		}
		if (App::get().isPressKey('D')){
			direction = RIGHT;
			character.pos.x() += SPEED;
		}
		if (App::get().isPressKey('W')){
			character.pos.y() += SPEED;
		}
		if (App::get().isPressKey('S')){
			character.pos.y() -= SPEED;
		}

		if (App::get().isPushKey(GLFW_KEY_SPACE) && flag[shotNum]){
			if (shotNum == BULLETNUM)shotNum = 0;
			bullet[shotNum].pos = character.pos;
			bullet[shotNum].pos.x() += (player.width() / 2)*character.dir;
			bullet[shotNum].dir = direction*BULLETSPEED;
			flag[shotNum] = false;
			shotNum++;
		}
		character.dir = direction;
	}

	void shot(){
		for (int i = 0; i < BULLETNUM; i++){
			bullet[i].pos.x() += bullet[i].dir;
			if (abs(bullet[i].pos.x()) > 320){
				flag[i] = true;
			}
		}
	}

	void draw(){
		drawTextureBox(character.pos.x(), character.pos.y(),
					   player.width(), player.height(),
					   0, 0,
					   player.width(), player.height(),
					   player, Color::black,
					   0,Vec2f(character.dir,1),Vec2f(64,100));

		for (int i = 0; i < BULLETNUM; i++){
			drawFillCircle(bullet[i].pos.x(), bullet[i].pos.y(),
				10, 10, 10, Color::yellow);
		}
	}
};

int main() {
	App::get();
	Player player;

	App::get().bgColor(Color::white);
	while (App::get().isOpen()) {
		App::get().begin();

		player.shot();
		player.getKey();
		player.draw();

		App::get().end();
	}
}
