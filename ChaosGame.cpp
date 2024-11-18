// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1440, 900); //VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);
	
	vector<Vector2f> vertices;
	vector<Vector2f> points;

	srand(time(0));
	int gameMode = 0;

	while (window.isOpen() && gameMode == 0)
	{
		Text menu, options;
		Font font;

		font.loadFromFile("SparkyStonesRegular-BW6ld.ttf");
		menu.setFont(font);
		options.setFont(font);

		menu.setString("\t\tWelcome to the Chaos Game!\nWhat shape would you like to create?\n");
		options.setString("T: Triangle\n\nH: Hexagon");

		menu.setCharacterSize(40); // in pixels, not points!
		menu.setFillColor(Color::White);
		menu.setStyle(Text::Italic);
		menu.setPosition(400.f, 200.f);

		options.setCharacterSize(30); // in pixels, not points!
		options.setFillColor(Color::White);
		options.setStyle(Text::Italic);
		options.setPosition(630.f, 360.f);

		window.clear();
		window.draw(menu);
		window.draw(options);

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::T))
		{
			gameMode = 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::H))
		{
			gameMode = 2;
		}

		window.display();
	}

	while (window.isOpen())
	{
		/*
		****************************************
		Communication with the user
		****************************************
		*/
		Text text, menu, options;
		Font font;

		font.loadFromFile("SparkyStonesRegular-BW6ld.ttf");
		text.setFont(font); 

		if (vertices.size() < 3 && gameMode == 1)
		{		
			text.setString("Please click on any three points on the screen to create the vertices for the triangle");
		}
		else if (vertices.size() < 6 && gameMode == 2)
		{
			text.setString("Please click on any six points on the screen to create the vertices for the hexagon");
		}
		else if (points.size() == 0)
		{
			text.setString("Click once again time to start a Chaos Game!");
		}
		else
		{
			text.setString("Chaos is happening...");
		}

		text.setCharacterSize(30); // in pixels, not points!
		text.setFillColor(Color::White);
		text.setStyle(Text::Italic);
		text.setPosition(10.f, 10.f);
		
		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
		    if (event.type == Event::Closed)
		    {
					// Quit the game when the window is closed
					window.close();
		    }
		    if (event.type == sf::Event::MouseButtonPressed)
		    {
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;
	
					if(vertices.size() < 3 && gameMode == 1)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (vertices.size() < 6 && gameMode == 2)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if(points.size() == 0)
					{
						points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
				}
		    }
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
	
		if(points.size() > 0)
		{
		    ///generate more point(s)
			Vector2f point = points.back();

		    ///select random vertex
			Vector2f randVertex;

			if (gameMode == 1) 
			{ 
				randVertex = vertices[rand() % 3]; 

				///calculate midpoint between random vertex and the last point in the vector
				/// midpoint formula: <(x1 + x2) / 2; (y1 + y2) / 2>
				Vector2f newPoint((point.x + randVertex.x) / 2, (point.y + randVertex.y) / 2);
				points.push_back(newPoint);
			}
			else if (gameMode == 2) 
			{ 
				randVertex = vertices[rand() % 6]; 

				///stepping 2/3 away from current dot to random vertex
				Vector2f newPoint(
					point.x + (2.0f / 3.0f) * (randVertex.x - point.x),
					point.y + (2.0f / 3.0f) * (randVertex.y - point.y));

				points.push_back(newPoint);
			}
		}
	
		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		window.draw(text);

		///Vertices
		for(int i = 0; i < vertices.size(); i++)
		{
		    RectangleShape rect(Vector2f(10,10));
		    rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
		    rect.setFillColor(Color::Blue);
		    window.draw(rect);
		}

		///Points
		for (int i = 0; i < points.size(); i++)
		{
			CircleShape cir(2);
			cir.setPosition(Vector2f(points[i].x, points[i].y));
			cir.setFillColor(Color::Cyan);
			window.draw(cir);
		}
		window.display();
	}
}
