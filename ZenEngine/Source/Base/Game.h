#pragma once
#include "SFML/Graphics.hpp"
#include <GL/glew.h>

namespace Zen {
	class Renderer3D;

	class Game
	{
	public:
		Game();
		~Game();
		bool InitGlew();
		bool InitLogger();

		void Run();
		static sf::RenderWindow* currentWindow;
	private:
		void ProcessEvents();
		void Update();
		void Render();

		sf::RenderWindow window;
		sf::CircleShape mPlayer;

		
		unique_ptr<Renderer3D> pRenderer;
	};
}
