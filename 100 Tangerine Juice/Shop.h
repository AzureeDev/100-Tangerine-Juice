#pragma once
#include <vector>
#include <map>
#include <string>
#include "LClass.h"
#include "World.h"
#include "LButton.h"

using std::vector, std::map, std::string;

class Shop : public LClass
{
private:
	struct TextureDefinition {
		string id;
		shared_ptr<LTexture> instance = nullptr;
	};

	struct CosmeticButtonData {
		string cosmeticId;
		Unit cosmeticUnit;
		shared_ptr<LButton> cosmeticBtn = nullptr;
		shared_ptr<LTexture> starIcon = nullptr;
		shared_ptr<LTexture> starAmount = nullptr;
	};

	enum class PageDirection {
		Previous,
		Next
	};

	World world;
	vector<TextureDefinition> textures = {};
	vector<shared_ptr<LButton>> buttons = {};
	map<unsigned, CosmeticButtonData> cosmeticBtns = {};
	vector<shared_ptr<LButton>> pageBtns = {};
	unsigned currentPage = 1;
	string currentCategory = "";

public:
	void init();
	void createWorld();
	void createTopBar();
	void createContainers();
	void createLContainerButtons();
	void createWalletBar();

	void generateCosmetics(const string category);
	void changePage(const PageDirection direction);
	void statePageBtn(shared_ptr<LButton> btn, const bool active);

	void update(const float dt);

private:
	shared_ptr<LTexture> getUIElement(const string id);
};

