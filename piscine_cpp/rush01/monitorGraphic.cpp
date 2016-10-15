monitorGraphic::monitorGraphic( void ) {

}

monitorGraphic::monitorGraphic( monitorGraphic const & src ) {

}

monitorGraphic::~monitorGraphic( void ) {

}

monitorGraphic &			monitorGraphic::operator=( monitorGraphic const & rhs ) {

}

void						monitorGraphic::displayModule(IMonitorModules & const module) {

}

void						monitorGraphic::eventHandler() {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    if (window.pollEvent(event)) {
        // "close requested" event: we close the window
		if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			window.close();
		}
    }

}

void						monitorGraphic::optionsHandler() {

}

void						monitorGraphic::closeAll() {

}

void						monitorGraphic::mainLoop() {
		eventHandler();
	    window.clear(sf::Color::Black);
	    displayModule();
	    
}