#include "DisplaySettingsMenu.hpp"

//DisplaySettings Class

//Initializers

auto DisplaySettingsMenu::initGui(u_short offsetB) -> void {
    auto height = this->stateData.gfxSettings->resolution.width / 25.6f;
	auto offset = this->stateData.gfxSettings->resolution.width / 28.44f;
	auto tmp = sf::Text();
    auto width =this->stateData.gfxSettings->resolution.width;
	tmp.setCharacterSize(this->characterSize);
    
    
	for (int i = 0; i < this->buttonNames.size(); i++) {
        //Option texts
		if (i < buttonNames.size() - 2) {
                    this->buttons[buttonNames[i]] = std::make_unique<gui::Button>(
                        width/ 3.5f, //pos_x
                        (width / 19.5f) * (i + offsetB), //pos_y
                        width/ 8.53f, //width
                        width / 25.6f, //height
                        buttonNames[i], width / 80.f,
                        sf::Color(0, 0, 0, 255),
                        sf::Color(250, 250, 250, 250),
                        sf::Color(20, 20, 20, 50),
                        sf::Color(70, 70, 70, 0),
                        sf::Color(150, 150, 150, 0),
                        sf::Color(20, 20, 20, 0), this->stateData.font
                    );
                    tmp.setString(buttonNames[i]);
		}
        // Back button
		else if (i == buttonNames.size() - 2) {
			tmp.setString(buttonNames[i]);
			this->buttons[buttonNames[i]] = std::make_unique<gui::Button>(
                (width / 2.5f) + ((width/ 8.56f) / 1), //pos_x
                (width / 20.f) * (i + offsetB + 1), //pos_y
                width/ 8.53f, //width
                width / 25.6f, //height
                buttonNames[i], width / 80.f,
				sf::Color(0, 0, 0, 255),
				sf::Color(250, 250, 250, 250),
				sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 0),
				sf::Color(150, 150, 150, 0),
				sf::Color(20, 20, 20, 0), this->stateData.font
			);
		}
		//Confirm Button
		else if (i == buttonNames.size() - 1) {
			tmp.setString(buttonNames[i]);
			this->buttons[buttonNames[i]] = std::make_unique<gui::Button>(
                (width/ 1.6f )+ ((width/ 8.56f) / i), //pos_x
                (width / 20.f) * (i + offsetB), //pos_y
                width/ 8.53f, //width
                width / 25.6f, //height
                buttonNames[i], width / 80.f,
				sf::Color(0, 0, 0, 255),
				sf::Color(250, 250, 250, 250),
				sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 0),
				sf::Color(150, 150, 150, 0),
				sf::Color(20, 20, 20, 0), this->stateData.font
			);
		}
	}
}

auto DisplaySettingsMenu::initText() -> void {
    this->text.setFont(this->stateData.font);
	this->text.setFillColor(sf::Color::White);
    this->text.setString("Display Settings");
	this->text.setCharacterSize(this->stateData.gfxSettings->resolution.width / 36.57f);
	this->text.setPosition(
		sf::Vector2f(
			this->stateData.gfxSettings->resolution.width / 2.f - this->text.getGlobalBounds().width / 2.f,
			this->stateData.gfxSettings->resolution.height / 2.f - (7 * this->text.getGlobalBounds().height)
		)
	);
    
}

auto DisplaySettingsMenu::initBackground() -> void {

	auto offset = this->stateData.gfxSettings->resolution.width / 36.54f;

	this->background.setSize(
        sf::Vector2f(
            this->stateData.gfxSettings->resolution.width / 2.f+ (4 * offset),
            this->stateData.gfxSettings->resolution.height / 2.f + (3 * offset)
                     )
        );
	this->background.setPosition(
            sf::Vector2f(
                this->stateData.gfxSettings->resolution.width / 5.f,
                this->stateData.gfxSettings->resolution.height / 4.f - 2 * offset
                )
            );
	this->background.setFillColor(sf::Color(0, 0, 0, 100));

	this->transparentBackground.setSize(
        sf::Vector2f(
            this->stateData.gfxSettings->resolution.width,
            this->stateData.gfxSettings->resolution.height
            )
        );
	this->transparentBackground.setPosition(0, 0);
	this->transparentBackground.setFillColor(sf::Color(215, 215, 215, 100));
}

auto DisplaySettingsMenu::initDropDownLists() -> void{
    std::vector<std::string> videoModes = {"1920x1080", "1280x720"};
    this->dropDownLists["Resolution"] = std::make_unique<gui::DropDownList>("Resolution", this->buttonsWidth,  this->stateData, videoModes);
    std::vector<std::string> fullScreen = {"Yes", "No"};
    this->dropDownLists["FullScreen"] = std::make_unique<gui::DropDownList>("FullScreen", this->buttonsWidth, this->stateData, fullScreen);
    std::vector<std::string> frameRate = {"120", "60"};
    this->dropDownLists["FrameRate"] = std::make_unique<gui::DropDownList>("FrameRate", this->buttonsWidth, this->stateData, frameRate);
    std::vector<std::string> verticalSync = {"Yes", "No"};
    this->dropDownLists["VSync"] = std::make_unique<gui::DropDownList>("VSync", this->buttonsWidth, this->stateData, verticalSync);

}


//Constructors & Destructors
DisplaySettingsMenu::DisplaySettingsMenu(StateData& stateData, const u_short& buttonsWidth, const u_short& characterSize, bool menu) :
Menu(stateData, buttonsWidth, characterSize)  {
    
    this->buttonNames = std::vector<std::string>{
        "Resolution: ",
        "Full Screen: ",
        "Frame Rate Limit: ",
        "VSync: ",
        "Back",
        "Confirm"
    };

    this->initGui();
    this->initDropDownLists();
	this->initText();
	this->initBackground();
 
}



//Update methods
auto DisplaySettingsMenu::update(const float& dt, const sf::Vector2f& mousePosition) -> void {
	this->updateGui(dt, mousePosition);
}

auto DisplaySettingsMenu::updateGui(const float& dt, const sf::Vector2f& mousePosition) -> void {
    for(auto& it : this->dropDownLists) it.second->update(dt, mousePosition);
    this->buttons["Back"]->update(dt, mousePosition);
    this->buttons["Confirm"]->update(dt, mousePosition);

}
//Render methods
auto DisplaySettingsMenu::render(std::shared_ptr<sf::RenderTarget> target) -> void {
	this->renderBackground(target);
	this->renderGui(target);

    
}

auto DisplaySettingsMenu::renderBackground(std::shared_ptr<sf::RenderTarget> target)  -> void {
	target->draw(this->transparentBackground);
	target->draw(this->background);
	target->draw(this->text);
}

auto DisplaySettingsMenu::renderGui(std::shared_ptr<sf::RenderTarget> target) -> void {
    for (auto& it : this->buttons) it.second->render(target);
    for(auto& it : this->dropDownLists) it.second->render(target);



}

//Getters


//Setters
auto DisplaySettingsMenu::setResolution() -> void{
        this->stateData.gfxSettings->resolution = this->dropDownLists["Resolution"]->getResolution();
        
        this->stateData.gfxSettings->fullScreen = this->dropDownLists["FullScreen"]->getFullScreen();
    
        this->stateData.gfxSettings->frameRateLimit = this->dropDownLists["FrameRate"]->getFrameRate();   
    
    this->stateData.gfxSettings->verticalSync = this->dropDownLists["VSync"]->getVSync();


    this->initBackground();
    this->initGui();
    this->initText();
    this->initDropDownLists();

    if(this->stateData.gfxSettings->fullScreen){
        this->stateData.window->create(
                this->stateData.gfxSettings->resolution,
                this->stateData.gfxSettings->title,
                0,
                this->stateData.gfxSettings->contextSettings
        );
    }
    else{
        this->stateData.window->create(
                this->stateData.gfxSettings->resolution,
                this->stateData.gfxSettings->title,
                1,
                this->stateData.gfxSettings->contextSettings
        );
    }


}

auto DisplaySettingsMenu::setFullScreen() -> void{




}



