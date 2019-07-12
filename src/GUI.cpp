#include "GUI.h"

GUI::GUI()
{
	this->width = 500;
	this->height = 600;
}

GUI::GUI(int width, int height)
{
	this->width = width;
	this->height = height;
}

void GUI::Run()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Look at da beautiful creature"/*, sf::Style::None*/);
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	cv::VideoCapture cap(0);
	cv::Mat frameRGB, frameRGBA;
	sf::Image img;
	sf::Texture texture;
	sf::Event event;
	sf::Sprite sprite;

	while (window.isOpen())
	{
		cap >> frameRGB;
		if (frameRGB.empty())
		{
			break;
		}

		cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);
		img.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

		if (!texture.loadFromImage(img))
		{
			break;
		}

		sprite.setTexture(texture);

		window.clear();
		window.draw(sprite);
		window.display();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}
}
