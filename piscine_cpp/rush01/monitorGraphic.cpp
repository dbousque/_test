

#include "monitorGraphic.hpp"

monitorGraphic::monitorGraphic(sf::RenderWindow &window) :
	_window(window)
{
	this->_title_font.loadFromFile("UndergroundNF.ttf");
	this->_text_font.loadFromFile("Ubuntu-M.ttf");
}

monitorGraphic::monitorGraphic(monitorGraphic const &other) :
	_window(other.getWindow())
{
	this->_title_font.loadFromFile("UndergroundNF.ttf");
	this->_text_font.loadFromFile("Ubuntu-M.ttf");
}

monitorGraphic::~monitorGraphic()
{
}

monitorGraphic	&monitorGraphic::operator=(monitorGraphic const &other)
{
	return *(new monitorGraphic(other));
}


void        monitorGraphic::displayModules(std::vector<IMonitorModule*> modules)
{
	this->_displayTitle();
	this->_current_y = 90;
	for (std::vector<IMonitorModule*>::iterator iter = modules.begin(); iter != modules.end(); iter++)
	{
		this->_current_x = 20;
		this->_current_y += this->_displayModule(**iter) + 20;
	}
}

void        monitorGraphic::eventHandler()
{

}

void        monitorGraphic::optionsHandler()
{

}

void        monitorGraphic::closeAll()
{

}

void        monitorGraphic::init()
{

}

sf::RenderWindow	&monitorGraphic::getWindow() const
{
	return this->_window;
}

void        monitorGraphic::_displayTitle()
{
	sf::Text text;
	text.setFont(this->_title_font);
	text.setFillColor(sf::Color(66, 134, 244));
	text.setString("ft_gkrellm");
	text.setCharacterSize(70);
	text.setPosition(45, 2);
	this->_window.draw(text);
}

void        monitorGraphic::_displayRectangle(int start_x, int start_y, int width, int height)
{
	sf::RectangleShape shape(sf::Vector2f(width, height));

	shape.setFillColor(sf::Color(0, 0, 0, 0));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color(255, 255, 255));
	shape.setPosition(start_x, start_y);
	this->_window.draw(shape);
}

int			monitorGraphic::_actualDisplayGraph(int value, std::list<int> &graph, int display_y)
{
	int		max_val;
	int		i;
	int		graph_id;
	int		prev_val;
	int		val;

	i = 0;
	graph_id = *(graph.begin());
	graph.pop_front();
	graph.pop_front();
	graph.push_front(graph_id);
	graph.push_back(value);
	max_val = *(std::max_element(graph.begin(), graph.end()));
	for (std::list<int>::iterator iter = graph.begin(); iter != graph.end(); iter++)
	{
		val = *iter;
		if (i > 1)
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(40 + ((i - 2) * 4), display_y + 100 - (prev_val * 100 / max_val)), sf::Color(244, 223, 66)),
				sf::Vertex(sf::Vector2f(40 + ((i - 2) * 4) + 4, display_y + 100 - (val * 100 / max_val)), sf::Color(244, 223, 66))
			};
			this->_window.draw(line, 2, sf::Lines);
		}
		i++;
		prev_val = *iter;
	}
	return (120);
}

int			monitorGraphic::_displayGraph(int val, int graph_id, int display_y)
{
	display_y += 10;
	sf::RectangleShape shape(sf::Vector2f(316, 100));
	shape.setPosition(40, display_y);
	shape.setFillColor(sf::Color(66, 140, 244, 100));
	this->_window.draw(shape);
	for (size_t i = 0; i < this->_graphs.size(); i++)
	{
		if (*(this->_graphs[i].begin()) == graph_id)
			return this->_actualDisplayGraph(val, this->_graphs[i], display_y);
	}
	std::list<int> lst(79, 0);
	this->_graphs.push_back(lst);
	this->_graphs[this->_graphs.size() - 1].push_back(1);
	this->_graphs[this->_graphs.size() - 1].push_front(graph_id);
	return this->_actualDisplayGraph(val, this->_graphs[this->_graphs.size() - 1], display_y);
}

int			monitorGraphic::_displayField(Field &field, int display_y)
{
	std::string			text_str;
	sf::Text text;
	text.setFont(this->_text_font);
	text.setFillColor(sf::Color(255, 255, 255));
	text.setCharacterSize(14);

	if (field.getType() == Field::INTEGER || field.getType() == Field::INTEGER_PERCENT)
		text_str = std::to_string(*(static_cast<int*>(field.getData())));
	if (field.getType() == Field::INTEGER_PERCENT)
		text_str += "%";
	if (field.getType() == Field::FLOATING)
		text_str = std::to_string(*(static_cast<float*>(field.getData())));
	if (field.getType() == Field::STRING)
		text_str = *(static_cast<std::string*>(field.getData()));
	if (field.getType() == Field::GRAPH_INT)
		return this->_displayGraph(*(static_cast<int*>(field.getData())), field.getId(), display_y);
	text.setString(text_str);
	text.setPosition((400 - text.getLocalBounds().width) / 2, display_y);
	this->_window.draw(text);
	return (20);
}

int        monitorGraphic::_displayModule(IMonitorModule &module)
{
	std::vector<Field*>	&fields = *(module.getFields());
	std::string			*title = static_cast<std::string*>(fields[0]->getData());
	
	this->_displayRectangle(this->_current_x, this->_current_y, 360, 30);
	sf::Text text;
	text.setFont(this->_text_font);
	text.setFillColor(sf::Color(244, 66, 66));
	text.setString(*title);
	text.setCharacterSize(16);
	text.setPosition((400 - text.getLocalBounds().width) / 2, this->_current_y + 6);
	this->_window.draw(text);

	int		height_taken = 30;

	for (size_t i = 1; i < fields.size(); i++)
	{
		height_taken += this->_displayField(*(fields[i]), this->_current_y + height_taken + 10);
	}

	height_taken += 18;
	this->_displayRectangle(this->_current_x, this->_current_y, 360, height_taken);
	return height_taken;
}