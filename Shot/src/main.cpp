#include "lib/framework.hpp"
#include <iostream>
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
		RIGHT,LEFT
	};
	struct Obj{
		Vec2f pos;
		float dir;
	};

	Texture player;
	int directon;
	int shotNum;
	bool flag[3];
	Obj character;
	Obj bullet[3];

public:
	Player(){
		player = Texture("res/player.png");
		character.pos = Vec2f(0, 0);
		directon = LEFT;
		shotNum = 0;
		for (int i = 0; i < 3; i++){
			flag[i] = true;
			bullet[i].pos = Vec2f(0, 0);
			bullet[i].dir = 0;
		}
	}

	void getKey(){
		if (App::get().isPressKey('A')){
			directon = LEFT;
			character.pos.x() -= 5;
		}
		if (App::get().isPressKey('D')){
			directon = RIGHT;
			character.pos.x() += 5;
		}
		if (App::get().isPressKey('W')){
			character.pos.y() += 5;
		}
		if (App::get().isPressKey('S')){
			character.pos.y() -= 5;
		}
		if (App::get().isPushKey(GLFW_KEY_SPACE) && flag[shotNum]){
			if (shotNum == 3)shotNum = 0;
			bullet[shotNum].pos = character.pos;
			bullet[shotNum].dir = (directon == LEFT) ? -10 : 10;
			flag[shotNum] = false;
			shotNum++;
		}
		character.dir = directon == LEFT ? -128 : 128;
	}

	void shot(){
		for (int i = 0; i < 3; i++){
			bullet[i].pos.x() += bullet[i].dir;
			if (abs(bullet[i].pos.x()) > 320){
				flag[i] = true;
			}
		}
	}

	void draw(){
		drawTextureBox(character.pos.x(), character.pos.y(), 128, 256, 0, 0, character.dir, 256, player, Color::white);
		for (int i = 0; i < 3;i++){
			drawFillCircle(bullet[i].pos.x(), bullet[i].pos.y(), 10, 10, 10, Color::yellow);
		}
	}
};

int main() {
	App::get();
	Player player;
	while (App::get().isOpen()) {
		App::get().begin();

		player.shot();
		player.getKey();
		player.draw();

		App::get().end();
	}
}
