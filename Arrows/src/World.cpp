#include "World.h"

#include <filesystem>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

World::World()
{
	background = { 0.37, 0.63, 0.76 };
	mainCamera = new kwee::Camera(glm::vec4(0, 0, kwee::Application::getInstance()->getWindowSize()));
	mainCamera->setScale(glm::vec2(0.1f, 0.1f));

//	addObject(grid);
	if (std::filesystem::exists("save.json"))
	{
		boost::property_tree::ptree saveTree;
		boost::property_tree::read_json("save.json", saveTree);
		grid = new Grid{ saveTree.get<int>("size") };
		addObject(grid);
		for (int j = 0; j < grid->getSize().y; j++)
		{
			for (int i = 0; i < grid->getSize().x; i++)
			{
				
				boost::optional<int> opt = saveTree.get_optional<int>("grid." + std::to_string((int)(grid->getSize().x * j) + i));
				if (!opt.has_value())
				{
					Arrow* arrow = grid->createArrow(grid, 
						StringToType(saveTree.get<std::string>("grid." + std::to_string((int)(grid->getSize().x * j) + i) + ".type")),
						StringToDir(saveTree.get<std::string>("grid." + std::to_string((int)(grid->getSize().x * j) + i) + ".direction")));
					arrow->setPosition(grid->GridToWorld({ i, j }));
					grid->arrows[i][j] = arrow;
				}
			}
		}
	}
	else
	{
		grid = new Grid{ 250 };
		addObject(grid);
	}

	phantomArrow = new kwee::GameObject("wire_active");
	phantomArrow->alpha = 0.0;
	phantomArrow->mix = 0.2;
	phantomArrow->color = {1.0, 1.0, 1.0};
	phantomArrow->visible = false;
	addObject(phantomArrow);
}

World::~World()
{
	delete grid;
}