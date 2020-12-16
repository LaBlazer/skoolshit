#include "common.hpp";

const int SCRWIDTH = 700;
const int SCRHEIGHT = 500;

class AABB {
public:
	float ax;
	float ay;
	float bx;
	float by;

	AABB() {
		this->ax = 0.f;
		this->ay = 0.f;
		this->bx = 0.f;
		this->by = 0.f;
	}

	AABB(float ax, float ay, float bx, float by) {
		this->ax = ax;
		this->ay = ay;
		this->bx = bx;
		this->by = by;
	}

	bool isOverlapping(AABB *col) {
		std::cout << ax << "|" << ay << "|" << bx << "|" << by << std::endl;
		std::cout << col->ax << "|" << col->ay << "|" << col->bx << "|" << col->by << std::endl;
		std::cout << "_____" << std::endl;

		return !(col->ax > bx || col->bx < ax || col->ay < by || col->by > ay);
	}
};

class Pad {
private:
	sf::RectangleShape pad;
	float speed;
	sf::Vector2f position;
	sf::Vector2f def_position;
public:
	Pad(float width, float height, float x, float y, float speed = 100.f): speed(speed), position(x, y), def_position(x, y) {
		pad = sf::RectangleShape(sf::Vector2f(width, height));
		pad.setFillColor(sf::Color::White);
		//pad.setOrigin(width / 2, height / 2);
		pad.setPosition(this->position);
	};

	void Move(float delta, bool up) {
		float motor = up ? delta * -speed : delta * speed;
		position.y += motor;
		pad.setPosition(position);
	};

	void Reset() {
		this->position = this->def_position;
	}

	void Render(sf::RenderWindow *window) {
		window->draw(pad);
	}

	AABB GetAABB() {
		sf::Vector2f size = pad.getSize();
		return AABB(this->position.x, this->position.y, this->position.x + size.x, this->position.y + size.y);
	}
};

class Ball {
private:
	sf::CircleShape ball;
	float speed;
	float radius;
	sf::Vector2f direction;
	sf::Vector2f position;
	sf::Vector2f def_position;
public:
	Ball(float radius, float x, float y, float speed = 100.f) : speed(speed), position(x, y), def_position(x, y), radius(radius) {
		ball = sf::CircleShape(radius);
		ball.setFillColor(sf::Color::Green);
		ball.setPosition(this->position);
	};

	void Move(float delta) {
		sf::Vector2f motor = direction * speed * delta;
		position += motor;
		ball.setPosition(position);
	};

	void SetDirection(sf::Vector2f direction) {
		this->direction = direction;
	}

	sf::Vector2f GetDirection() {
		return this->direction;
	}

	void Reset() {
		this->position = this->def_position;
	}

	AABB GetAABB() {
		return AABB(this->position.x - this->radius, 
			this->position.y - this->radius, 
			this->position.x + this->radius, 
			this->position.y + this->radius);
	}

	bool CheckCollision(AABB *collision) {
		return this->GetAABB().isOverlapping(collision);
	}

	void Render(sf::RenderWindow *window) {
		window->draw(ball);
	}
};

int main()
{
	srand(time(NULL));

	int score_left = 0;
	int score_right = 0;

	sf::RenderWindow window(sf::VideoMode(SCRWIDTH, SCRHEIGHT), "Ponk by Andrej");
	window.setFramerateLimit(60);

	sf::SoundBuffer sb;
	if (!sb.loadFromFile("boop.wav")) {
		std::cout << "Nemozem nacitat zvuk kristaa" << std::endl;
	}
	sf::Sound s(sb);

	sf::Font font;
	if (!font.loadFromFile("sansation.ttf")) {
		std::cout << "Nemozem nacitat font boha" << std::endl;
	}

	//create game objects
	//Balls lmaoooo
	Ball ball(10.f, SCRWIDTH / 2.f, SCRHEIGHT / 2.f);
	ball.SetDirection(sf::Vector2f(1.f, 0.5f));

	//pads
	Pad pad_left(20.f, 60.f, 0, SCRHEIGHT / 2.f);

	sf::Text txt_score_left("Score: 0", font);
	txt_score_left.setFillColor(sf::Color::White);
	txt_score_left.setCharacterSize(20);
	txt_score_left.setPosition(sf::Vector2f(10, 10));

	Pad pad_right(20.f, 60.f, SCRWIDTH - 20, SCRHEIGHT / 2.f);

	sf::Text txt_score_right("Score: 0", font);
	txt_score_right.setFillColor(sf::Color::White);
	txt_score_right.setCharacterSize(20);
	txt_score_right.setPosition(sf::Vector2f(SCRWIDTH - 80, 10));

	sf::Clock clock;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//get the elapsed time
		float delta = clock.restart().asSeconds();;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			pad_left.Move(delta, true);
			std::cout << delta << std::endl;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			pad_left.Move(delta, false);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			pad_right.Move(delta, true);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			pad_right.Move(delta, false);
		}

		//chack pad collisions
		if (ball.CheckCollision(&pad_right.GetAABB()) || ball.CheckCollision(&pad_left.GetAABB())) {
			std::cout << "hit" << std::endl;
			system("pause");
			auto dir = ball.GetDirection();
			dir.x *= -1;
			ball.SetDirection(dir);
		}

		//bounce off walls
		AABB bcoll = ball.GetAABB();
		if (bcoll.by > SCRHEIGHT || bcoll.ay < 0) {
			auto dir = ball.GetDirection();
			dir.y *= -1;
			ball.SetDirection(dir);
		}

		//check for victory
		if (bcoll.ax > SCRWIDTH) {
			//right won
			std::cout << "right won";
			ball.Reset();
		}
		else if (bcoll.bx < 0) {
			//left won
			std::cout << "left won";
			ball.Reset();
		}

		ball.Move(delta);

		window.clear(sf::Color::Black);
		pad_left.Render(&window);
		pad_right.Render(&window);
		ball.Render(&window);

		window.draw(txt_score_left);
		window.draw(txt_score_right);
		window.display();
	}

	return 0;
}