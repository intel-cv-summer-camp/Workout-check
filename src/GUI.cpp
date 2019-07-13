#include "GUI.h"

GUI::GUI()
{
	this->width = 700;
	this->height = 650;

	if (!this->font.loadFromFile("C:/Most important C/Учёбушка С/CV camp/Workout-check/data/Arial-ItalicMT.ttf"))//шрифт кнопок, если не загрузит- будет точка вместо слова
	{
		// handle error
	}

	this->button[0].setFont(font);
	this->button[0].setColor(sf::Color::Red);
	this->button[0].setString("Start");
	this->button[0].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 1-50, height - 100));
	this->button[0].setCharacterSize(40);
	this->button[0].setStyle(sf::Text::Bold);

	this->button[1].setFont(font);
	this->button[1].setColor(sf::Color::White);
	this->button[1].setString("Exit");
	this->button[1].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 2, height - 100));
	this->button[1].setCharacterSize(40);
	this->button[1].setStyle(sf::Text::Bold);

	selectedItemIndex = 0;
	isMenu = true;
}

GUI::GUI(int width, int height)
{
	this->width = width;
	this->height = height;

	if (!this->font.loadFromFile("C:/Most important C/Учёбушка С/CV camp/Workout-check/data/Arial-ItalicMT.ttf"))//шрифт кнопок, если не загрузит- будет точка вместо слова
	{
		// handle error
	}

	this->button[0].setFont(font);
	this->button[0].setColor(sf::Color::Red);
	this->button[0].setString("Start");
	this->button[0].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 1-50, height - 100));
	this->button[0].setCharacterSize(40);
	this->button[0].setStyle(sf::Text::Bold);

	this->button[1].setFont(font);
	this->button[1].setColor(sf::Color::White);
	this->button[1].setString("Exit");
	this->button[1].setPosition(sf::Vector2f(width / (MAX_NUMBER_OF_ITEMS + 1) * 2, height - 100));
	this->button[1].setCharacterSize(40);
	this->button[1].setStyle(sf::Text::Bold);

	selectedItemIndex = 0;
	isMenu = true;
}

void GUI::MoveLeft()
{
	if (selectedItemIndex - 1 >= 0)
	{
		button[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex--;
		button[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void GUI::MoveRight()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		button[selectedItemIndex].setColor(sf::Color::White);
		selectedItemIndex++;
		button[selectedItemIndex].setColor(sf::Color::Red);
	}
}

void GUI::Run()
{
	sf::RenderWindow window(sf::VideoMode(width, height), "Look at da beautiful creature", sf::Style::None);
	window.setPosition(sf::Vector2i((sf::VideoMode::getDesktopMode().width - width) / 2, (sf::VideoMode::getDesktopMode().height - height) / 2));

	cv::VideoCapture cap(0);
	cv::Mat frameRGB, frameRGBA;
	sf::Image img;
	sf::Texture texture;
	sf::Texture menubackground;
	menubackground.loadFromFile("C:/Most important C/Учёбушка С/CV camp/Workout-check/data/menubg.jpg");
	sf::Event event;
	sf::Sprite sprite, menubg(menubackground);
	bool click = false;

	while (window.isOpen())
	{
		if (isMenu)
		{
			if (sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55, height - 95, 280 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55), 595 - (height - 95)).contains(sf::Mouse::getPosition(window))) { MoveLeft(); } //start
			if (sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5, height - 95, 545 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5), 595 - (height - 95)).contains(sf::Mouse::getPosition(window))) { MoveRight(); } //exit

			bool debug = false;
			if (debug)
			{
				cout << "start rectLeft " << width / ((MAX_NUMBER_OF_ITEMS + 1) * 1) - 50 << " rectTop " << height - 100 << " width " << 280 - (width / ((MAX_NUMBER_OF_ITEMS + 1) * 1) - 55) << " height " << 280 - (height - 100)
					<< " x,y: " << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;
				cout << " exit rectLeft " << width / ((MAX_NUMBER_OF_ITEMS + 1) * 2) - 50 << " rectTop " << height - 100 << " width " << 545 - (width / ((MAX_NUMBER_OF_ITEMS + 1) * 2) - 55) << " height " << 595 - (height - 100)
					<< " x,y: " << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;
			}

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Left:
						this->MoveLeft();
						break;
					case sf::Keyboard::Right:
						this->MoveRight();
						break;
					case sf::Keyboard::Return:
						switch (this->GetPressedItem())
						{
						case 0:
							isMenu = false; //переход в старт
							button[0].setString("Next");
							button[1].setString("Return");
							break;
						case 1:
							window.close();
							break;
						}
						break;
					}

					break;
				case sf::Event::MouseButtonPressed:
					if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
						&& 
						((sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55, height - 95, 280 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55), 595 - (height - 95)).contains(sf::Mouse::getPosition(window))) 
						|| 
						(sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5, height - 95, 545 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5), 595 - (height - 95)).contains(sf::Mouse::getPosition(window)))))
						click = true;
					else
						click = false;
					break;
				case sf::Event::MouseButtonReleased:
					if (click
						&&
						((sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55, height - 95, 280 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55), 595 - (height - 95)).contains(sf::Mouse::getPosition(window)))
						||
						(sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5, height - 95, 545 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5), 595 - (height - 95)).contains(sf::Mouse::getPosition(window)))))
					{
						if (selectedItemIndex == 0) { isMenu = false; button[0].setString("Next"); button[1].setString("Return"); } //переход в старт
						if (selectedItemIndex == 1) { window.close(); }
					}
					break;
				case sf::Event::Closed:
					window.close();
					break;
				}
			}

			window.clear();
			window.draw(menubg);
			window.draw(button[1]);
			window.draw(button[0]);
			window.display();
		}
		else
		{
			cap >> frameRGB;
			if (frameRGB.empty())
			{
				break;
			}

			cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);
			Filter filter;
			frameRGBA = filter.ResizeFilter(frameRGBA, 300, 500, CV_8UC4);

			img.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());

			if (!texture.loadFromImage(img))
			{
				break;
			}

			sprite.setTexture(texture);
			sprite.setPosition(100, 100);

			if (sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55, height - 95, 280 - 10 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55), 595 - (height - 95)).contains(sf::Mouse::getPosition(window))) { MoveLeft(); } //start
			if (sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5, height - 95, 545 + 20 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5), 595 - (height - 95)).contains(sf::Mouse::getPosition(window))) { MoveRight(); } //exit

			

			bool debug = false;
			if (debug)
			{
				cout << "start rectLeft " << width / ((MAX_NUMBER_OF_ITEMS + 1) * 1) - 50 << " rectTop " << height - 100 << " width " << 280 - (width / ((MAX_NUMBER_OF_ITEMS + 1) * 1) - 55) << " height " << 280 - (height - 100)
					<< " x,y: " << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;
				cout << " exit rectLeft " << width / ((MAX_NUMBER_OF_ITEMS + 1) * 2) - 50 << " rectTop " << height - 100 << " width " << 545 - (width / ((MAX_NUMBER_OF_ITEMS + 1) * 2) - 55) << " height " << 595 - (height - 100)
					<< " x,y: " << sf::Mouse::getPosition(window).x << " " << sf::Mouse::getPosition(window).y << endl;
			}

			while (window.pollEvent(event))
			{
				switch (event.type)
				{
				case sf::Event::KeyReleased:
					switch (event.key.code)
					{
					case sf::Keyboard::Left:
						this->MoveLeft();
						break;
					case sf::Keyboard::Right:
						this->MoveRight();
						break;
					case sf::Keyboard::Return:
						switch (this->GetPressedItem())
						{
						case 0:
							//следующее упражнение
							break;
						case 1:
							isMenu = true; //возврат в меню
							button[0].setString("Start");
							button[1].setString("Exit");
							break;
						}
						break;
					}
					break;
				case sf::Event::MouseButtonPressed:
					if ((sf::Mouse::isButtonPressed(sf::Mouse::Left))
						&&
						((sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55, height - 95, 280 - 10 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55), 595 - (height - 95)).contains(sf::Mouse::getPosition(window)))
						||
						(sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5, height - 95, 545 + 20 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5), 595 - (height - 95)).contains(sf::Mouse::getPosition(window)))))
						click = true;
					else
						click = false;
					break;
				case sf::Event::MouseButtonReleased:
					if (click
						&&
						((sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55, height - 95, 280 -10 - (width / (MAX_NUMBER_OF_ITEMS + 1) * 1 - 55), 595 - (height - 95)).contains(sf::Mouse::getPosition(window)))
							||
							(sf::IntRect(width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5, height - 95, 545 +20- (width / (MAX_NUMBER_OF_ITEMS + 1) * 2 - 5), 595 - (height - 95)).contains(sf::Mouse::getPosition(window)))))
					{
						if (selectedItemIndex == 0) {} //следующее упражнение
						if (selectedItemIndex == 1) { isMenu = true; button[0].setString("Start"); button[1].setString("Exit"); } //возврат в меню
					}
					break;
				case sf::Event::Closed:
					window.close();
					break;
				}
			}

			window.clear();
			window.draw(menubg);
			window.draw(sprite);
			window.draw(button[1]);
			window.draw(button[0]);
			window.display();
		}
	}
}
