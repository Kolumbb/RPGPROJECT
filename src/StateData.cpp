#include "StateData.hpp"

//GFXSettings class

//Constructors & Destructors
GFXSettings::GFXSettings() {
    this->title = "Platformer";
    this->loadGraphicsFromFile();
}



//Public methods
void GFXSettings::saveToFile(const std::filesystem::path& path) {
    auto fs = std::fstream(path);
    if (fs) {
        fs >> this->resolution.width >> this->resolution.height;
        fs >> this->fullScreen;
        fs >> this->frameRateLimit;
        fs >> this->verticalSync;
        fs >> this->contextSettings.antialiasingLevel;
    }
    else std::cout << "PLEASE CHECK GRAPHICS SETTINGS LOCATION - THERE IS NO FILE" << std::endl;

    fs.close();
}

auto GFXSettings::loadGraphicsFromFile(const std::filesystem::path& path) -> void{
    auto ifs = std::ifstream(path);
    if (ifs.good()) {
        ifs >> this->resolution.width >> this->resolution.height;
        ifs >> this->fullScreen;
        ifs >> this->frameRateLimit;
        ifs >> this->verticalSync;
        ifs >> this->contextSettings.antialiasingLevel;
    }else{
        std::cout << "PLEASE CHECK GRAPHICS SETTINGS LOCATION - THERE IS NO FILE" << std::endl;
    }
    ifs.close();
}


//StateData class

//Initializers

auto StateData::initFont(
    const std::filesystem::path& path) -> void{
    this->font.loadFromFile(path.string());
}

auto StateData::initSupportedKeys(const std::filesystem::path& path) -> void {
    auto file = std::fstream(path);
    auto key = std::string();
    auto key_value = int();
    if (file)
        while (file >> key >> key_value)
            this->supportedKeys[key] = key_value;

    file.close();
}

auto StateData::initWindow() -> void{
    if(this->gfxSettings->fullScreen){
        this->window = std::make_shared<sf::RenderWindow>(
                this->gfxSettings->resolution,
                this->gfxSettings->title,
                sf::Style::Fullscreen,
                this->gfxSettings->contextSettings
                );
    }
    else{
        this->window = std::make_shared<sf::RenderWindow>(
                this->gfxSettings->resolution,
                this->gfxSettings->title,
                sf::Style::Titlebar || sf::Style::Close,
                this->gfxSettings->contextSettings
        );
    }
    this->window->setFramerateLimit(this->gfxSettings->frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings->verticalSync);
}

auto StateData::initGFXSettings() -> void{
    this->gfxSettings = std::make_shared<GFXSettings>();
}

//Constructors & Destructors
StateData::StateData(): gridSizeF(32.f) {
	this->initSupportedKeys();
	this->initFont();
	this->initGFXSettings();
	this->initWindow();
}




