#include "ButtonParser.h"

namespace CCraft
{
	ButtonParser::ButtonParser()
		: logger("BUTTON_PARSER")
	{
		parse("res/buttons.txt");
	}

	void ButtonParser::parse(const char* path)
	{
		std::ifstream stream(path);
		std::string line;

		bool parsingInProgress = false;
		bool parsingCoords = false;
		bool parsingTexturePath = false;
		bool parsingColorSettings = false;

		float tempoArray[30];
		int tempoArrayIndex = 0;
		std::string tempoPath;
		Button::Action tempoAction;
		Button::Color tempoDefColor;
		Button::Color tempoMousedOverColor;
		Button::Color tempoPressedColor;

		while (getline(stream, line) && !(line.find("BREAKPOINT") != std::string::npos))
		{
			if ((line.find("}") != std::string::npos))
			{
				parsingCoords = false;
				parsingTexturePath = false;
				parsingColorSettings = false;
				parsingInProgress = false;
				addTexCoords(tempoArray);
				buttons.emplace_back(std::move(tempoArray), tempoAction, tempoDefColor, tempoMousedOverColor, tempoPressedColor, tempoPath.c_str());
				tempoArrayIndex = 0;
			}

			else if ((line.find("Button{") != std::string::npos)||(line.find("Button {") != std::string::npos))
			{
				parsingInProgress = true;
			}

			else if (parsingInProgress)
			{
				if ((line.find("Coordinates:") != std::string::npos) || (line.find("coordinates:") != std::string::npos))
				{
					parsingCoords = true;
					parsingTexturePath = false;
					parsingColorSettings = false;
				}
					
				else if ((line.find("TextureFilePath:") != std::string::npos) || (line.find("texturefilepath") != std::string::npos))
				{
					parsingCoords = false;
					parsingTexturePath = true;
					parsingColorSettings = false;
				}
				else if ((line.find("ColorSettings:") != std::string::npos) || (line.find("colorsettings") != std::string::npos))
				{
					parsingCoords = false;
					parsingTexturePath = false;
					parsingColorSettings = true;
				}
				else if ((line.find("OnClick:") != std::string::npos) || (line.find("onclick") != std::string::npos))
				{
					parsingCoords = false;
					parsingTexturePath = false;
					parsingColorSettings = false;
					Button::Action tempAction = Button::Action::NONE;

					if (line.find("NONE") != std::string::npos || (line.find("none") != std::string::npos))
						tempAction = Button::Action::NONE;
					else if (line.find("PLAY") != std::string::npos || (line.find("play") != std::string::npos))
						tempAction = Button::Action::PLAY;
					else if (line.find("SETTINGS") != std::string::npos || (line.find("settings") != std::string::npos))
						tempAction = Button::Action::SETTINGS;
					else if (line.find("EXIT") != std::string::npos || (line.find("exit") != std::string::npos))
						tempAction = Button::Action::EXIT;
					tempoAction = tempAction;
				}
				else if (parsingCoords)
				{
					std::stringstream ss[2];
					int index = 0;
					if (!line.empty())
					{
						for (char s : line)
						{
							if (isdigit(s) || s == 'f' || s == '.')
							{
								ss[index] << s;
							}

							else if(!index && s!='\t')
							{
								index++;
							}
						}

						float tempoFloat1 = strtof(ss[0].str().c_str(), 0);
						float tempoFloat2 = strtof(ss[1].str().c_str(), 0);
						tempoArray[tempoArrayIndex] = tempoFloat1;
						tempoArrayIndex++;
						tempoArray[tempoArrayIndex] = tempoFloat2;
						tempoArrayIndex++;
						tempoArray[tempoArrayIndex] = -1.0f;
						tempoArrayIndex += 3;
					}
				}
				else if (parsingTexturePath)
				{
					std::stringstream ss;
					if (!line.empty())
					{
						for (char s : line)
						{
							if (!(s == '\t'))
							{
								ss << s;
							}
						}
						tempoPath = ss.str();
						parsingTexturePath = false;
					}
				}
				else if (parsingColorSettings)
				{
					Button::Color tempColor = Button::Color::WHITE;

					if (line.find("red") != std::string::npos || (line.find("Red") != std::string::npos))
						tempColor = Button::Color::RED;
					else if (line.find("blue") != std::string::npos || (line.find("Blue") != std::string::npos))
						tempColor = Button::Color::BLUE;
					else if (line.find("green") != std::string::npos || (line.find("Green") != std::string::npos))
						tempColor = Button::Color::GREEN;
					else if (line.find("purple") != std::string::npos || (line.find("Purple") != std::string::npos))
						tempColor = Button::Color::PURPLE;
					else if (line.find("orange") != std::string::npos || (line.find("Orange") != std::string::npos))
						tempColor = Button::Color::ORANGE;
					else if (line.find("black") != std::string::npos || (line.find("Black") != std::string::npos))
						tempColor = Button::Color::BLACK;
					else if (line.find("white") != std::string::npos || (line.find("White") != std::string::npos))
						tempColor = Button::Color::WHITE;
					if (line.find("Default:") != std::string::npos || (line.find("default:") != std::string::npos))
						tempoDefColor = tempColor;
					else if (line.find("Pressed:") != std::string::npos || (line.find("pressed:") != std::string::npos))
						tempoPressedColor = tempColor;
					else if (line.find("MousedOver:") != std::string::npos || (line.find("mousedover:") != std::string::npos))
						tempoMousedOverColor = tempColor;
				}

			}
			
		}

	}

	void ButtonParser::addTexCoords(float* data)
	{
		//top left
		data[3] = 0.0f;
		data[4] = 0.0f;
		//bottom left
		data[8] = 0.0f;
		data[9] = 1.0f;
		//top right
		data[13] = 1.0f;
		data[14] = 0.0f;
		//top right
		data[18] = 1.0f;
		data[19] = 0.0f;
		//bottom right
		data[23] = 1.0f;
		data[24] = 1.0f;
		//bottom left
		data[28] = 0.0f;
		data[29] = 1.0f;
	}
}

