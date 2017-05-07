#pragma once
#include "SFML/Graphics.hpp"
#include <GL/glew.h>

namespace Zen {
	class Renderer;

	class Game
	{
	public:
		Game();
		~Game();
		bool InitGlew();
		bool InitLogger();

		void Run();

	private:
		void ProcessEvents();
		void Update();
		void Render();

		sf::RenderWindow window;
		sf::CircleShape mPlayer;

		
		unique_ptr<Renderer> pRenderer;
	};
}
