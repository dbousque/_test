

#include "Background.hpp"

static int count = 0;

std::string		background_repr[13] = {
std::string("                        ,sdPBbs.                            "),
std::string("                      ,d$$$$$$$$b.                          "),
std::string("                     d$P'`Y'`Y'`?$b                         "),
std::string("                    d'    `  '  \\ `b                        "),
std::string("                   /    |        \\  \\                       "),
std::string("                  /    / \\       |   \\                      "),
std::string("             _,--'        |      \\    |                     "),
std::string("           /' _/          \\   |        \\                    "),
std::string("        _/' /'             |   \\        `-.__               "),
std::string("    __/'       ,-'    /    |    |     \\      `--...__       "),
std::string("  /'          /      |    / \\     \\     `-.           `\\    "),
std::string(" /    /;;,,__-'      /   /    \\            \\            `-. "),
std::string("/    |;;;;;;;\\                                             \\")
};

std::string		background_repr2[13] = {
std::string("          (`  ).                   _             "),
std::string("         (     ).              .:(`  )`.         "),
std::string("        _(       '`.          :(   .    )        "),
std::string("    .=(`(      .   )     .--  `.  (    ) )       "),
std::string("   ((    (..__.:'-'   .+(   )   ` _`  ) )        "),
std::string("   `(       ) )       (   .  )     (   )  ._     "),
std::string("     ` __.:'   )     (   (   ))     `-'.-(`  )   "),
std::string("  ( )       --'       `- __.'         :(      )) "),
std::string(" (_.'          .')                    `(    )  ))"),
std::string("                                                 "),
std::string("                                                 "),
std::string("                                                 "),
std::string("                                                 ")
};

Background::Background(int x, int y) :
	GameEntity(x, y, count % 2 == 0 ? background_repr : background_repr2, 13, COLOR_YELLOW)
{
	count++;
}

Background::Background(Background &other) :
	GameEntity(other)
{
}

Background::~Background()
{
}

Background	&Background::operator=(Background &other)
{
	return *(new Background(other));
}

void		Background::move(int dx, int dy)
{
	this->_x += dx;
	this->_y += dy;
}

bool	Background::outOfBounds()
{
	if (this->_x + this->getReprLenAtScale() <= 0)
		return true;
	return false;
}

void	Background::display() const
{
	attroff(A_BOLD);
	this->GameEntity::display();
	attron(A_BOLD);
}