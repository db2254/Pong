#include <SFML/Graphics.hpp>

sf::Vector2f ball_velocity;
bool is_player_serving = true;
const float initial_velocity_x = 100.f; // Horizontal velocity
const float initial_velocity_y = 60.f; // Vertical velocity

// Array to hold the keys for players
const sf::Keyboard::Key controls[4] = {
	sf::Keyboard::A,    // Player1 UP
	sf::Keyboard::Z,    // Player1 Down
	sf::Keyboard::Up,   // Player2 UP
	sf::Keyboard::Down  // Player2 Down
};

// Parameters
const sf::Vector2f paddleSize(25.f, 100.f);
const float ballRadius = 10.f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.f;
const float paddleOffsetWall = 10.f;
const float time_step = 0.017f; // 60fps

// Game objects
sf::CircleShape ball;
sf::RectangleShape paddles[2];

// Initialisation of objects needed for the game
void init() {

	// Set size and origin of paddles
	for (sf::RectangleShape& p : paddles) {
		p.setSize(paddleSize);
		p.setOrigin(paddleSize / 2.f);
	}

	// Set size and origin of ball
	ball.setRadius(ballRadius);
	ball.setOrigin(ballRadius, ballRadius);

	// Reset paddle position
	paddles[0].setPosition(paddleOffsetWall + paddleSize.x / 2.f, gameHeight / 2.f);
	paddles[1].setPosition(gameWidth - paddleOffsetWall - paddleSize.x / 2.f, gameHeight / 2.f);

	// Reset ball position
	ball.setPosition(gameWidth / 2.f, gameHeight / 2.f);

	ball_velocity = { (is_player_serving ? initial_velocity_x : -initial_velocity_x), initial_velocity_y };
}

// All games logic goes here
void update(float dt) {
	// handles paddle movement
	float direction1 = 0.0f;
	if (sf::Keyboard::isKeyPressed(controls[0])) {
		direction1--;
	}
	if (sf::Keyboard::isKeyPressed(controls[1])) {
		direction1++;
	}
	paddles[0].move(sf::Vector2f(0.f, direction1 * paddleSpeed * dt));

	float direction2 = 0.0f;
	if (sf::Keyboard::isKeyPressed(controls[2])) {
		direction2--;
	}
	if (sf::Keyboard::isKeyPressed(controls[3])) {
		direction2++;
	}
	paddles[1].move(sf::Vector2f(0.f, direction2 * paddleSpeed * dt));

	ball.move(ball_velocity * dt);
}

// Draws everything to the window (screen) for the current frame
void render(sf::RenderWindow& window) {
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
}


// Main game loop: handles events, updates game state, and renders the game
int main() {
	sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight), "Pong");
	

	init();

	// SFML clock to calculate dt (delta time)
	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Update game state
		float dt = clock.restart().asSeconds();
		update(dt);

		// Draws everything to window do this every frame
		window.clear(sf::Color::Black);
		render(window);
		window.display();
	}

	return 0;
}
