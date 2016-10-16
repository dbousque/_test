#include "HostnameModule.hpp"
#include "CatModule.hpp"
#include "OsInfosModule.hpp"
#include "DateModule.hpp"
#include "CpuModule.hpp"
#include "NetworkModule.hpp"
#include "RamModule.hpp"
#include "monitorShell.hpp"
#include "monitorGraphic.hpp"
#include <sys/time.h>
#include <unistd.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int				TARGET_FRAMERATE = 5;
unsigned long	TO_WAIT_PER_FRAME = 1000 / TARGET_FRAMERATE;

unsigned long	getCurrentMillis()
{
	struct timeval	t;
	gettimeofday(&t, NULL);
	return t.tv_sec * 1000 + t.tv_usec / 1000;
}

bool getModules(int ac, char ** av, std::vector<IMonitorModule*> & modules)
{
//bloquer insertion multiple
//faire plus elegant que foret d'ifs
//delete propre si echoue
	if (ac == 2)
	{
		modules.push_back(new HostnameModule());
		modules.push_back(new OsInfosModule());
		modules.push_back(new DateModule());
		modules.push_back(new CpuModule());
		modules.push_back(new NetworkModule());
		modules.push_back(new RamModule());
		modules.push_back(new CatModule());
		return (true);
	}
	else
	{
		int i = 2;
		while (i < ac)
		{
			if (!strcmp(av[i], "name"))
				modules.push_back(new HostnameModule());
			else if (!strcmp(av[i], "os"))
				modules.push_back(new OsInfosModule());
			else if (!strcmp(av[i], "date"))
				modules.push_back(new DateModule());
			else if (!strcmp(av[i], "cpu"))
				modules.push_back(new CpuModule());
			else if (!strcmp(av[i], "net"))
				modules.push_back(new NetworkModule());
			else if (!strcmp(av[i], "ram"))
				modules.push_back(new RamModule());
			else
				return (false);
			i++;
		}
		modules.push_back(new CatModule());
		return (true);
	}
}


#include <fstream>
int		main(int argc, char **argv)
{
	std::vector<IMonitorModule*>	modules;
	//std::ofstream	ofs("lol.out");

	if (argc == 1 || (strcmp(argv[1], "-s") && strcmp(argv[1], "-g")) ||
		!getModules(argc, argv, modules))
	{
		std::cout << "Usage: ./ft_gkrellm [-s|-g] [name os date cpu net]" << std::endl;
		std::cout << "Mandatory argument -s for shell display or -g for graphic display."
				  << std::endl;
		std::cout << "Module selection: name os date cpu net ; no argument = all"
				  << std::endl;
	}
	else if (!strcmp(argv[1], "-s"))
	{
		monitorShell	monitor;
		unsigned long	start;
		unsigned long	end;

		for(;;) {
			start = getCurrentMillis();
			erase();
			for (std::vector<IMonitorModule*>::iterator iter = modules.begin(); iter != modules.end(); iter++)
				(*iter)->update();
			monitor.displayModules(modules);
			refresh();
			end = getCurrentMillis();
			if (start + TO_WAIT_PER_FRAME > end)
			{

				timeout((TO_WAIT_PER_FRAME - (end - start)));
				if (getch() == 27)
					break;
			}
		}
	}
	else
	{
		unsigned long	start;
		unsigned long	end;

		sf::RenderWindow window(sf::VideoMode(400, 1380), "ft_gkrellm", sf::Style::Titlebar | sf::Style::Close);
		monitorGraphic	monitor(window);
		sf::ContextSettings settings;
		settings.antialiasingLevel = 8;
		while (window.isOpen())
		{
			start = getCurrentMillis();
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::KeyPressed
					&& event.key.code == sf::Keyboard::Escape)
					window.close();
			}
			window.clear(sf::Color::Black);
			for (std::vector<IMonitorModule*>::iterator iter = modules.begin(); iter != modules.end(); iter++)
				(*iter)->update();
			monitor.displayModules(modules);//we need to give the window...
			window.display();// end the current frame
			end = getCurrentMillis();
			if (start + TO_WAIT_PER_FRAME > end)
				usleep((TO_WAIT_PER_FRAME - (end - start)) * 1000);
		}
	}
	return (0);
}
