#include "Shop.h"
#include "MusicManager.h"
#include "OverlayManager.h"
#include "Globals.h"
#include "Utils.h"
#include "Discord.h"
#include "CosmeticDefinitions.h"

constexpr unsigned MAX_PER_ROW = 6;
constexpr unsigned MAX_PER_PAGE = 12;

void Shop::init()
{
	Discord::setState("In the Shop");
	OverlayManager::fadeOut(9);
	MusicManager::playMusic("assets/musics/shop.mp3");

	this->createWorld();
	this->createTopBar();
	this->createContainers();
	this->createLContainerButtons();
	this->createWalletBar();
}

void Shop::createWorld()
{
	world = World("assets/worlds/r_sky_bw.png");
	world.setWorldColor({ 79, 202, 255, 255 });
	world.setScrollMultiplier(6);
}

void Shop::createTopBar()
{
	shared_ptr<LTexture> topBar = Globals::resources->createLTexture("assets/ui/rect_base.png");
	topBar->setSize(Globals::engine->getDisplaySettings().wsWidth, 96);
	topBar->setPosition(0, 32);
	topBar->setColor({ 12, 12, 12, 255 }, true);

	shared_ptr<LTexture> topBarScroll = Globals::resources->createLTexture("assets/ui/main_menu/topBar.png");
	topBarScroll->setScrollable(true);
	topBarScroll->reverseScroll(true);
	topBarScroll->setPosition(
		{
			0,
			topBar->getY() + 3
		}
	);
	topBarScroll->setColor({ 84, 198, 255, 255 }, true);

	shared_ptr<LTexture> topBarScrollLabel = Globals::resources->createLTexture();
	topBarScrollLabel->createText("SHOP", { 255, 255, 255, 255 }, 0, Globals::resources->getFont("bleachFontLarge"));
	topBarScrollLabel->setPosition(
		{
			Globals::engine->getDisplaySettings().wsWidth - topBarScrollLabel->getWidth() - 20,
			topBarScroll->getY() + (topBarScroll->getHeight() / 2) - (topBarScrollLabel->getHeight() / 2) + 5
		}
	);

	this->textures.push_back({ "topBar" , topBar });
	this->textures.push_back({ "topBarScroll" , topBarScroll });
	this->textures.push_back({ "topBarScrollLabel" , topBarScrollLabel });
}

void Shop::createContainers()
{
	shared_ptr<LTexture> lContainer = Globals::resources->createLTexture("assets/ui/rect_base.png");
	lContainer->setColor({ 0, 0, 0, 200 }, true);
	lContainer->setSize(400, 880);
	lContainer->setPosition(10, this->getUIElement("topBarScroll")->bottom().y + 10);

	shared_ptr<LTexture> rContainer = Globals::resources->createLTexture("assets/ui/rect_base.png");
	rContainer->setColor({ 0, 0, 0, 200 }, true);
	rContainer->setSize(1490, 880);
	rContainer->setPosition(lContainer->right() + 10, lContainer->getY());

	this->textures.push_back({ "lcontainer" , lContainer });
	this->textures.push_back({ "rcontainer" , rContainer });
}

void Shop::createLContainerButtons()
{
	auto createShopBtn = [this](const string btnId, const string btnText, const Vector2i pos, std::function<void()> callback)
	{
		shared_ptr<LButton> btn = Globals::UI->createSharedButton(btnId, "assets/ui/shop/shopBtn.png");
		btn->getTexture().setColor({ 175, 175, 175, 255 }, true);
		btn->setPosition(pos);
		btn->setText(btnText, { 225, 225, 225, 255 });
		btn->setHighlightColor({ 255, 255, 255, 255 });
		btn->supplyCallback(callback);
		this->buttons.push_back(btn);

		return btn;
	};

	auto hairColorBtn = createShopBtn(
		"lContainerHairColor", 
		"Hair Color", 
		{ 
			this->getUIElement("lcontainer")->top().x + 10, 
			this->getUIElement("lcontainer")->top().y + 10, 
		}, 
		[this]() { this->generateCosmetics("hair"); });

	auto clothingColorBtn = createShopBtn(
		"lContainerClothing",
		"Clothing Color",
		{
			hairColorBtn->getTexture().bottom().x,
			hairColorBtn->getTexture().bottom().y + 10,
		},
		[this]() { this->generateCosmetics("clothes"); });

	auto eyeColorBtn = createShopBtn(
		"lContainerEyeColor",
		"Eye Color",
		{
			clothingColorBtn->getTexture().bottom().x,
			clothingColorBtn->getTexture().bottom().y + 10,
		},
		[this]() { this->generateCosmetics("eyes"); });

	auto diceBtn = createShopBtn(
		"lContainerDice",
		"Dice",
		{
			eyeColorBtn->getTexture().bottom().x,
			eyeColorBtn->getTexture().bottom().y + 10,
		},
		[this]() { this->generateCosmetics("dices"); });

	shared_ptr<LButton> lContainerBackBtn = Globals::UI->createSharedButton("lContainerBackBtn", "assets/ui/shop/shopBtn.png");
	lContainerBackBtn->getTexture().setColor({ 175, 175, 175, 255 }, true);
	lContainerBackBtn->setPosition(
		{
			this->getUIElement("lcontainer")->bottom().x + 10,
			this->getUIElement("lcontainer")->bottom().y - lContainerBackBtn->getTexture().getHeight() - 10,
		}
	);
	lContainerBackBtn->setText("Main Menu", { 225, 225, 225, 255 });
	lContainerBackBtn->setHighlightColor({ 255, 255, 255, 255 });

	this->buttons.push_back(lContainerBackBtn);
}

void Shop::createWalletBar()
{
	auto walletFont = Globals::resources->getFont("escom");

	shared_ptr<LTexture> walletBarBg = Globals::resources->createLTexture("assets/ui/rect_base.png");
	shared_ptr<LTexture> walletPlayerName = Globals::resources->createLTexture();
	shared_ptr<LTexture> walletStarIcon = Globals::resources->createLTexture("assets/ui/star.png");
	shared_ptr<LTexture> walletStarAmount = Globals::resources->createLTexture();

	walletBarBg->setColor({ 0, 0, 0, 200 }, true);
	walletBarBg->setSize(Globals::engine->getDisplaySettings().wsWidth, 38);
	walletBarBg->setPosition(0, Globals::engine->getDisplaySettings().wsHeight - walletBarBg->getHeight() - 16);

	walletPlayerName->createText(Globals::account->name(), { 245, 245, 245, 255 }, 0, walletFont);
	walletPlayerName->setPosition(10, walletBarBg->getPosition().y + (walletBarBg->getHeight() / 2) - (walletPlayerName->getHeight() / 2));

	walletStarIcon->setPosition(walletPlayerName->right() + 32, walletBarBg->getPosition().y + (walletBarBg->getHeight() / 2) - (walletStarIcon->getHeight() / 2));

	walletStarAmount->createText("x " + Utils::thousandFormat(Globals::account->stars()), { 245, 245, 245, 255 }, 0, walletFont);
	walletStarAmount->setPosition(walletStarIcon->right() + 16, walletBarBg->getPosition().y + (walletBarBg->getHeight() / 2) - (walletStarAmount->getHeight() / 2));

	this->textures.push_back({ "walletBarBg", walletBarBg });
	this->textures.push_back({ "walletPlayerName", walletPlayerName });
	this->textures.push_back({ "walletStarIcon", walletStarIcon });
	this->textures.push_back({ "walletStarAmount", walletStarAmount });
}

void Shop::generateCosmetics(const string category)
{
	this->cosmeticBtns.clear();

	if (category != this->currentCategory)
	{
		this->currentCategory = category;
		this->currentPage = 1;
	}

	if (category == "hair")
	{
		for (size_t i = 0 + (MAX_PER_PAGE * (this->currentPage - 1)); i < (MAX_PER_PAGE * this->currentPage); ++i)
		{
			if (i <= CosmeticDefinitions::getAllHairs().size() - 1)
			{
				const auto cosmetic = CosmeticDefinitions::getAllHairs()[i];
				bool firstIndex = i == 0 + (MAX_PER_PAGE * (this->currentPage - 1));

				shared_ptr<LButton> btn = Globals::UI->createSharedButton(cosmetic.id + "_" + std::to_string(i) + "_btn", "assets/ui/rect_base.png");
				btn->getTexture().setSize(244, 312);
				btn->getTexture().setColor({ 0, 0, 0, 100 }, true);
				btn->setHighlightColor({ 79, 202, 255, 35 });

				if (firstIndex)
				{
					btn->setPosition(
						{
							this->getUIElement("rcontainer")->getX() + 5,
							this->getUIElement("rcontainer")->getY() + 5,
						}
					);
				}
				else
				{
					const auto previousCosmeticBtn = this->cosmeticBtns[i - 1];

					btn->setPosition(
						{
							previousCosmeticBtn.cosmeticBtn->getTexture().right() + 3,
							previousCosmeticBtn.cosmeticBtn->getY(),
						}
					);

					if (i % MAX_PER_ROW == 0)
					{
						btn->setX(this->cosmeticBtns[0].cosmeticBtn->getX());
						btn->setY(btn->getY() + btn->getTexture().getHeight() + 5);
					}
				}

				shared_ptr<LTexture> starIcon = Globals::resources->createLTexture("assets/ui/star.png");
				starIcon->setPosition(
					{
						btn->getTexture().bottom().x + 10,
						btn->getTexture().bottom().y - starIcon->getHeight() - 10,
					}
				);

				shared_ptr<LTexture> starAmount = Globals::resources->createLTexture();
				starAmount->createText(Utils::thousandFormat(cosmetic.cost), { 245, 245, 245, 255 }, 0, Globals::resources->getFont("escom32"));
				starAmount->setPosition(
					{
						starIcon->right() + 10,
						starIcon->getY()
					}
				);

				CosmeticButtonData data =
				{
					cosmetic.id,
					Unit(cosmetic.unitId, "aggressive"),
					btn,
					starIcon,
					starAmount
				};

				data.cosmeticUnit.applyCosmetic(cosmetic.id, "hair");
				data.cosmeticUnit.setPosition(
					{
						btn->getX() + (btn->getTexture().getWidth() / 2) - (data.cosmeticUnit.texture().getSheetSize() / 2),
						btn->getY() - 115
					}
				);

				this->cosmeticBtns.insert({ static_cast<unsigned>(i), data });
			}
		}
	}


	shared_ptr<LButton> pagePrevious = Globals::UI->createSharedButton("pagePrevious_btn", "assets/ui/shop/btnPrevious.png");
	shared_ptr<LButton> pageNext = Globals::UI->createSharedButton("pageNext_btn", "assets/ui/shop/btnNext.png");

	pagePrevious->supplyCallback([this]() { this->changePage(PageDirection::Previous); });
	pageNext->supplyCallback([this]() { this->changePage(PageDirection::Next); });

	pagePrevious->setPosition(
		{
			this->getUIElement("rcontainer")->bottom().x + (this->getUIElement("rcontainer")->getWidth() / 2) - (pagePrevious->getTexture().getWidth()) - 48,
			this->getUIElement("rcontainer")->bottom().y - pagePrevious->getTexture().getHeight() - 10,
		}
	);

	pageNext->setPosition(
		{
			pagePrevious->getX() + pagePrevious->getTexture().getWidth() + 48,
			pagePrevious->getY()
		}
	);

	if (this->currentPage <= 1)
	{
		statePageBtn(pagePrevious, false);
	}
	else
	{
		statePageBtn(pagePrevious, true);
	}

	if (CosmeticDefinitions::getAllHairs().size() > (MAX_PER_PAGE * this->currentPage))
	{
		statePageBtn(pageNext, true);
	}
	else
	{
		statePageBtn(pageNext, false);
	}

	this->pageBtns = { pageNext, pagePrevious };
}

void Shop::changePage(const PageDirection direction)
{
	switch (direction)
	{
	case PageDirection::Previous:
		this->currentPage--;
		break;

	case PageDirection::Next:
		this->currentPage++;
		break;
	}

	this->generateCosmetics(this->currentCategory);
}

void Shop::statePageBtn(shared_ptr<LButton> btn, const bool active)
{
	if (active)
	{
		btn->setEnabled(true);
		btn->setHighlightColor({ 79, 202, 255, 255 });
		btn->getTexture().setColor({ 50, 172, 225, 255 }, true);
	}
	else
	{
		btn->setEnabled(false);
		btn->getTexture().setColor({ 50, 172, 225, 125 }, true);
	}
}

void Shop::update(const float dt)
{
	world.render();

	for (const auto& ltexture : this->textures)
	{
		ltexture.instance->render();
	}

	for (const auto& button : this->buttons)
	{
		button->render();
	}

	for (auto& cosmetic : this->cosmeticBtns)
	{
		cosmetic.second.cosmeticBtn->render();
		cosmetic.second.cosmeticUnit.render({});
		cosmetic.second.starAmount->render();
		cosmetic.second.starIcon->render();
	}

	for (auto& pageBtn : this->pageBtns)
	{
		pageBtn->render();
	}
}

shared_ptr<LTexture> Shop::getUIElement(const string id)
{
	for (const auto& element : this->textures)
	{
		if (element.id == id)
		{
			return element.instance;
		}
	}

	return nullptr;
}
