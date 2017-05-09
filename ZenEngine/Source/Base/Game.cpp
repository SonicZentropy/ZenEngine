#include "stdafx.h"
#include "Game.h"
#include "Source/Core/Render/Renderer3D.h"
#include "Source/Core/Render/shader/ShaderManager.h"
#include <boost/foreach.hpp>
#include <iostream>
#include "Source/Core/assets/manager/AssetLoader.h"

namespace Zen
{
	sf::RenderWindow* Game::currentWindow;

	Game::Game() :
		window(sf::VideoMode(640, 480), "SFML App")
		, mPlayer()
		
	{
		mPlayer.setRadius(40.f);
		mPlayer.setPosition(100.f, 100.f);

		pRenderer = make_unique<Renderer3D>();
		currentWindow = &window;
	}

	Game::~Game() {}

	bool Game::InitGlew() {
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			/* Problem: glewInit failed, something is seriously wrong. */
			fprintf(stderr, "Error: %p\n", glewGetErrorString(err));
			return false;
		}
		return true;
	}

	bool Game::InitLogger() {
		ZLog::Logger->set_level(spdlog::level::trace);
		//ZLog::Logger->trace("In game run");
		//ZLog::Logger->info("In log", 1, 1.23f);

		//SPDLOG_TRACE(ZLog::Logger, "In {} {}", "Game", "Run");
		//LOG_TRACE("Trace In {} {}", "Game", "Run");
		LOG_DEBUG("Debug in {}", "Game Run");
		//std::string hello("Hello, world!");

		//BOOST_FOREACH(char ch, hello)
		//{
		//	LOG_DEBUG(ch);
		//}
		return true;
	}

	void Game::Run() {
		//auto console = spdlog::stdout_color_mt("console");
		//console->info("In game run");
		
		InitLogger();
		if (!InitGlew())
			return;

		pRenderer->Init();

		
		
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
				else if (event.type == sf::Event::Resized)
					glViewport(0, 0, event.size.width, event.size.height);
			}

			window.clear({255, 255, 255, 255});

			ProcessEvents();
			Update();
			Render();

			

			window.display();
		}

		return;
	}

	void Game::ProcessEvents() {}

	void Game::Update() {}

	void Game::Render() {
		//pRenderer->DrawTriangle();
		pRenderer->Render();
		
	}
}
