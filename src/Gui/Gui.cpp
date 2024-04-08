#include "Gui.hpp"

//Button class

//Initializers
auto gui::Button::initShape(float posX, float posY, float width, float height) -> void {
	this->shape.setPosition(sf::Vector2f(posX, posY));
	this->shape.setSize(sf::Vector2f(sf::Vector2f(width, height)));
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(this->outlineIdleColor);
	this->shape.setFillColor(this->idleColor);
}

auto gui::Button::initText(std::string text, u_short characterSize, const sf::Font& font) -> void {
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize(characterSize);
	this->text.setFillColor(this->textIdleColor);
	this->text.setPosition(
		sf::Vector2f(
			this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
			this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f
		)
	);
}

//Accessors
auto gui::Button::isPressed() const -> bool const {
	if (this->btnState == PRESSED) return true;
	return false;
}

auto gui::Button::getText() const -> std::string const{
    return this->text.getString();
}

//Modifiers
auto gui::Button::setText(const std::string& text) -> void{
    this->text.setString(text);
}


//Constructors & Destructors
gui::Button::Button(
    float posX, float posY, float width, float height,
	std::string text, u_short characterSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, const sf::Font& font,
    sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor
) :

	size(sf::Vector2f(posX, posY)), position(sf::Vector2f(width, height)),
	textIdleColor(textIdleColor), textHoverColor(textHoverColor), textActiveColor(textActiveColor),
	idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor),
	outlineIdleColor(outlineIdleColor), outlineHoverColor(outlineHoverColor),
    outlineActiveColor(outlineActiveColor){
	this->initShape(posX, posY, width, height);
	this->initText(text, characterSize, font);
}

gui::Button::~Button(){
    std::cout << "Button deleted" << std::endl;
}
//Update methods
auto gui::Button::update(const float& dt, const sf::Vector2f& mousePosWindow) -> void {
	this->updateMousePosition(dt, mousePosWindow);
	this->updateBtnState();
}

auto gui::Button::updateBtnState() -> void {
	switch (this->btnState) {
	case IDLE: {
		this->shape.setFillColor(this->idleColor);
		this->shape.setOutlineColor(this->outlineIdleColor);
		this->text.setFillColor(this->textIdleColor);
	}
			 break;
	case HOVER: {
		this->shape.setFillColor(this->hoverColor);
		this->shape.setOutlineColor(this->outlineHoverColor);
		this->text.setFillColor(this->textHoverColor);
	}
			  break;
	case PRESSED: {
		this->shape.setFillColor(this->activeColor);
		this->shape.setOutlineColor(this->outlineActiveColor);
		this->text.setFillColor(this->textActiveColor);
	}
				break;
	default: {
		this->shape.setFillColor(sf::Color::Red);
		this->shape.setOutlineColor(sf::Color::Green);
		this->text.setFillColor(sf::Color::Blue);
	}
		   break;
	}
}

auto gui::Button::updateMousePosition(const float& dt, const sf::Vector2f& mousePosWindow) -> void {
	this->btnState = IDLE;
	if (this->shape.getGlobalBounds().contains(mousePosWindow)) {
		this->btnState = HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->btnState = PRESSED;
	}
}

//Render methods
auto gui::Button::render(std::shared_ptr<sf::RenderTarget> target) const -> void const{
	target->draw(this->shape);
	target->draw(this->text);
}



//DorpDownList

//Initializers
auto gui::DropDownList::initDropDownList(u_short offsetB) -> void{
    auto height = this->stateData.gfxSettings->resolution.width / 25.6f;
    auto offset = this->stateData.gfxSettings->resolution.width / 28.44f;
    auto width = this->stateData.gfxSettings->resolution.width;
    auto tmp = sf::Text();
    
    auto activeText = std::string();
    
    if(name == "Resolution") {
        activeText = std::to_string(this->stateData.gfxSettings->resolution.width) + 'x' + std::to_string(this->stateData.gfxSettings->resolution.height);
        std::cout <<activeText<<std::endl;
    }
    
    if(name == "FullScreen") {
        offsetB = 4;
        if(this->stateData.gfxSettings->fullScreen == 0){
            activeText ="No";
        } else activeText = "Yes";
    }
    
    if(name == "FrameRate") {
        offsetB = 5;
        activeText = std::to_string(this->stateData.gfxSettings->frameRateLimit);
    }
    
    if(name == "VSync") {
        offsetB = 6;
        if(this->stateData.gfxSettings->verticalSync == 0){
            activeText ="No";
        } else activeText = "Yes";
    }

    this->activeElement = std::make_shared<gui::Button>(
        width / 2.5f , //pos_x
        (width / 20.f) * offsetB, //pos_y
        width / 8.53f, //width
        width / 25.6f, //height
        activeText, width / 80.f,
        sf::Color(0, 0, 0, 255),
        sf::Color(250, 250, 250, 250),
        sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 0),
        sf::Color(150, 150, 150, 0),
        sf::Color(20, 20, 20, 0), this->stateData.font
    );
    for (int i = 0; i < this->str.size(); i++) {

    this->dropDownList.push_back(
        std::make_shared<gui::Button>(
            (width / 2.5f) + ((i+1)*width/ 8.53f), //pos_x
            width/ 20.f * offsetB, //pos_y
            width/ 8.53f, //width
            width / 25.6f, //height
            this->str[i], width / 80.f,
            sf::Color(0, 0, 0, 255),
            sf::Color(250, 250, 250, 250),
            sf::Color(20, 20, 20, 50),
            sf::Color(70, 70, 70, 0),
            sf::Color(150, 150, 150, 0),
            sf::Color(20, 20, 20, 0), this->stateData.font
        )
    );
        
    }
}
//Constructors & Destructors

gui::DropDownList::DropDownList(
        const std::string& name,u_short buttonWidth,
        StateData& stateData, std::vector<std::string> str,
        bool shown) : name(name), stateData(stateData),
        str(str), shownList(shown){
    this->initDropDownList();
}
//Update methods
auto gui::DropDownList::update(const float& dt, const sf::Vector2f& mousePosition) -> void{
	this->activeElement->update(dt, mousePosition);
	if (this->activeElement->isPressed() && this->timer.getKeyTime()) {
		if (this->shownList)
			this->shownList = false;
		else this->shownList = true;
	}
	if(this->shownList)
		for (auto& it : this->dropDownList) {
			it->update(dt, mousePosition);
			if (it->isPressed() && this->timer.getKeyTime()) {
                this->activeElement->setText(it->getText());
				this->shownList = false;
			}
		}
    this->timer.updateKeyTime(dt);

}
//Render methods
auto gui::DropDownList::render(std::shared_ptr<sf::RenderTarget> target) const -> void const{
	this->activeElement->render(target);
    if (this->shownList) for (auto& it : this->dropDownList)
        it->render(target);
}


//Getters
auto gui::DropDownList::getResolution() const -> const sf::VideoMode{
    auto text = my::splitTextByLetter(this->activeElement->getText(), 'x');
    return sf::VideoMode(std::stoi(text.first), std::stoi(text.second));
}

auto gui::DropDownList::getFullScreen() const -> const bool{
    if(this->activeElement->getText() == "No"){
        return false;
    }
    else if(this->activeElement->getText() == "Yes"){
        return true;
    }
    
}

auto gui::DropDownList::getFrameRate() const -> const u_short{
    return std::stoi(this->activeElement->getText());
}

auto gui::DropDownList::getVSync() const -> const bool{
    if(this->activeElement->getText() == "No"){
        return 0;
    }
    else {
        return 1;
    }
}

auto gui::DropDownList::getShown() const -> const bool{
    return this->shownList;
}

auto gui::DropDownList::setShown() -> void{
    if(!this->shownList)
        this->shownList = true;
    else this->shownList = false;
}
auto gui::DropDownList::getText() const -> const std::string{
    return this->activeElement->getText();
}



//Other public methods

//TextureSelector class

//Initializers
auto gui::TextureSelector::initBounds(const float& posX, const float& posY, const float& width, const float& height) -> void {
    this->bounds.setSize(sf::Vector2f (width, height));
    this->bounds.setPosition(posX, posY);
    this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
    this->bounds.setOutlineThickness(1.f);
    this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));
}

auto gui::TextureSelector::initSpriteSheet(const float& posX, const float& posY, const sf::Texture& textureSheet) -> void {
    this->sheet.setTexture(textureSheet);
    this->sheet.setPosition(posX, posY);
    if(this->bounds.getSize().x < this->sheet.getGlobalBounds().width){
        this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
    }
    if(this->bounds.getSize().y < this->sheet.getGlobalBounds().height){
        this->sheet.setTextureRect(sf::IntRect(0, 0, this->sheet.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
    }
}

auto gui::TextureSelector::initSelector(const float& posX, const float& posY) -> void {
    this->selector.setPosition(posX, posY);
    this->selector.setSize(sf::Vector2f(this->gridSizeU, this->gridSizeU));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineColor(sf::Color(219, 165, 255, 255));
    this->selector.setOutlineThickness(1.f);
}



//Constructors & Destructors
gui::TextureSelector::TextureSelector(
        const float& posX, const float& posY, const float& width, const float& height,
        const u_short& gridSizeU, const sf::Texture& textureSheet, StateData& stateData
    ): active(false), gridSizeU(gridSizeU), position(posX, posY) {
    this->initBounds(posX, posY, width, height);
    this->initSpriteSheet(posX, posY, textureSheet);
    this->initSelector(posX, posY);

    this->internalRect = sf::IntRect(posX, posY, gridSizeU, gridSizeU);


}
//Update methods
auto gui::TextureSelector::update(const sf::Vector2u& mousePosF) -> void {
  this->internalRect.left = (this->selector.getPosition().x) - this->position.x;
  this->internalRect.top = (this->selector.getPosition().y) - this->position.y;
  this->selector.setPosition(
      sf::Vector2f (
          static_cast<float>(mousePosF.x) * this->gridSizeU,
          static_cast<float>(mousePosF.y)* this->gridSizeU)
      );
}

//Render methods
auto gui::TextureSelector::render(std::shared_ptr<sf::RenderTarget> target)-> void {
  target->draw(this->bounds);
  target->draw(this->sheet);
  target->draw(this->selector);
}




//Other Public methods
auto gui::TextureSelector::getActive() const -> const bool {
    return this->active;
}

auto gui::TextureSelector::getInternalRect() const -> const sf::IntRect & {
    return this->internalRect;
}
auto gui::TextureSelector::getBounds(const sf::Vector2f& mousePosWindow) const -> const bool {
  if (this->bounds.getGlobalBounds().contains(mousePosWindow)) return true;
  else return false;
}
auto gui::TextureSelector::setActive(const bool& yn) -> void { this->active = yn; }

auto gui::TextureSelector::getPosition() const -> const sf::Vector2f & {
  return this->selector.getPosition();
}
