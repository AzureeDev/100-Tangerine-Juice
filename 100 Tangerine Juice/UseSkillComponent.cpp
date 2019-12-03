#include "UseSkillComponent.h"
#include "Globals.h"

UseSkillComponent::UseSkillComponent()
{
}

UseSkillComponent::~UseSkillComponent()
{
	Globals::UI->destroyButton("skillComponentBack");

	for (size_t i = 0; i < this->skillButtons.size(); ++i)
	{
		Globals::UI->destroyButton(this->skillButtons[i].skillIdentifier + "_btn");
	}

	componentBack = nullptr;
}

void UseSkillComponent::init()
{
	componentBg.setNewTexture("assets/ui/rect_base.png");
	componentBg.setColor({ 0, 0, 0, 230 }, true);
	componentBg.setSize(1200, 128 * 3);
	componentBg.placeMiddleScreen();

	componentBack = Globals::UI->createButton("skillComponentBack", "assets/ui/ig/backBtn.png");
	componentBack->supplyCallback([this]() { this->destroyComponent();  });
	componentBack->setPosition(
		{
			componentBg.getX() + (componentBg.getWidth() / 2) - componentBack->getTexture().getWidth() / 2,
			componentBg.getY() + componentBg.getHeight() - componentBack->getTexture().getHeight() - 16
		}
	);

	componentTotalPwrIcon.setNewTexture("assets/ui/stats/pwr_large.png");
	componentTotalPwrIcon.setPosition(
		{
			componentBg.getX() + componentBg.getWidth() - componentTotalPwrIcon.getWidth() - 128,
			componentBg.getY() + componentBg.getHeight() - componentTotalPwrIcon.getHeight() - 10,
		}
	);

	componentTotalPwrAmount.createText(std::to_string(Globals::gameManager->getLocalUnit()->getCurrentPower()), { 255, 255, 255, 255 }, 0, Globals::resources->getFont("defaultFontLarge"));
	componentTotalPwrAmount.setPosition(
		{
			componentTotalPwrIcon.getX() + componentTotalPwrIcon.getWidth() + 32,
			componentTotalPwrIcon.getY() + (componentTotalPwrIcon.getHeight() / 2) - componentTotalPwrAmount.getHeight() / 2
		}
	);

	this->generateSkillButtons();
}

void UseSkillComponent::generateSkillButtons()
{
	vector<SkillData> skillData = Globals::gameManager->getLocalUnit()->getSkills();

	for (size_t i = 0; i < skillData.size(); ++i)
	{
		/* Definition */
		SkillButtonDef skill;
		string skillIdentifier = skillData[i].skillIdentifier;
		shared_ptr<LTexture> skillNameTexture = shared_ptr<LTexture>(new LTexture);
		shared_ptr<LTexture> skillDescTexture = shared_ptr<LTexture>(new LTexture);
		shared_ptr<LTexture> skillIconTexture = shared_ptr<LTexture>(new LTexture);
		shared_ptr<LTexture> skillPwrIconTexture = shared_ptr<LTexture>(new LTexture);
		shared_ptr<LTexture> skillPwrAmountTexture = shared_ptr<LTexture>(new LTexture);
		shared_ptr<LButton> skillBtn = Globals::UI->createSharedButton(skillData[i].skillIdentifier + "_btn", "assets/ui/rect_base.png");

		skillNameTexture->createText(skillData[i].skillName, { 255, 255, 255, 255 });
		skillDescTexture->createText(skillData[i].skillDescription, { 150, 150, 150, 255 }, 715, Globals::resources->getFont("defaultFontSmall"));
		skillIconTexture->setNewTexture(skillData[i].skillIconPath);
		skillPwrIconTexture->setNewTexture("assets/ui/stats/pwr.png");
		skillPwrAmountTexture->createText(std::to_string(skillData[i].skillCost), { 255, 0, 255, 255 });
		skillBtn->getTexture().setSize(this->componentBg.getWidth() - 20, skillIconTexture->getHeight());
		skillBtn->getTexture().setColor({ 255, 255, 255, 0 }, true);
		skillBtn->setHighlightColor({ 255, 255, 255, 25 });
		skillBtn->supplyCallback([this, skillIdentifier]() { this->useSkill(skillIdentifier); });

		/* Check availability by current state & current power */
		this->checkSkillAvailability(skillNameTexture, skillDescTexture, skillBtn, skillData[i]);

		/* Data insertion in Skill object */
		skill.skillIdentifier = skillIdentifier;
		skill.skillIcon = skillIconTexture;
		skill.skillName = skillNameTexture;
		skill.skillDesc = skillDescTexture;
		skill.skillPwrIcon = skillPwrIconTexture;
		skill.skillPwrAmount = skillPwrAmountTexture;
		skill.skillBtn = skillBtn;

		/* Placement */
		if (i == 0)
		{
			skillBtn->setPosition({ this->componentBg.getX() + 10, this->componentBg.getY() + 10 });

			skill.skillIcon->setPosition(
				{
					this->componentBg.getX() + 10,
					this->componentBg.getY() + 10
				}
			);
		}
		else
		{
			skillBtn->setPosition(
				{
					skillButtons[i - 1].skillBtn->getX(),
					skillButtons[i - 1].skillBtn->getY() + skillButtons[i - 1].skillBtn->getTexture().getHeight() + 32
				}
			);

			skill.skillIcon->setPosition(
				{
					skillButtons[i - 1].skillIcon->getX(),
					skillButtons[i - 1].skillIcon->getY() + skillButtons[i - 1].skillIcon->getHeight() + 32
				}
			);
		}

		skill.skillName->setPosition(
			{
				skill.skillIcon->getX() + skill.skillIcon->getWidth() + 10,
				skill.skillIcon->getY() + (skill.skillIcon->getHeight() / 2) - skill.skillName->getHeight() / 2
			}
		);

		skill.skillPwrIcon->setPosition(
			{
				skill.skillName->getX() + 300,
				skill.skillIcon->getY() + (skill.skillIcon->getHeight() / 2) - skill.skillPwrIcon->getHeight() / 2
			}
		);

		skill.skillPwrAmount->setPosition(
			{
				skill.skillPwrIcon->getX() + skill.skillPwrIcon->getWidth() + 8,
				skill.skillIcon->getY() + (skill.skillIcon->getHeight() / 2) - skill.skillPwrAmount->getHeight() / 2
			}
		);

		skill.skillDesc->setPosition(
			{
				skill.skillPwrIcon->getX() + 100,
				skill.skillIcon->getY() + (skill.skillIcon->getHeight() / 2) - skill.skillDesc->getHeight() / 2
			}
		);

		/* Insertion */
		skillButtons.push_back(skill);
	}
}

void UseSkillComponent::checkSkillAvailability(shared_ptr<LTexture>& skillNamePtr, shared_ptr<LTexture>& skillDescPtr, shared_ptr<LButton>& skillBtnPtr, SkillData& skillData)
{
	/*
		Enables the button if it can be used.
	*/

	const int currentPower = Globals::gameManager->getLocalUnit()->getCurrentPower();

	if (currentPower < skillData.skillCost)
	{
		skillNamePtr->setColor({ 255, 100, 100, 255 }, true);
		skillDescPtr->setColor({ 200, 50, 50, 255 }, true);
		skillBtnPtr->setEnabled(false);
	}

	if (!skillData.skillConditionFunction(Globals::gameManager->getLocalUnit()))
	{
		skillNamePtr->setColor({ 255, 100, 100, 255 }, true);
		skillDescPtr->setColor({ 200, 50, 50, 255 }, true);
		skillBtnPtr->setEnabled(false);
	}
}

void UseSkillComponent::useSkill(string skillIdentifier)
{
	/*
		Post successful press on a skill button
	*/

	SDL_Log("Using the skill %s", skillIdentifier.c_str());


	Globals::gameManager->useSkill(skillIdentifier);
	Globals::engine->destroyClass("UseSkillComponent");
}

void UseSkillComponent::destroyComponent()
{
	Globals::gameManager->getLocalUnit()->activateTurnButtons();
	Globals::engine->destroyClass("UseSkillComponent");
}

void UseSkillComponent::update(const float dt)
{
	componentBg.render();
	componentBack->render();
	componentTotalPwrIcon.render();
	componentTotalPwrAmount.render();

	for (auto& skill : skillButtons)
	{
		skill.skillBtn->render();
		skill.skillIcon->render();
		skill.skillName->render();
		skill.skillDesc->render();
		skill.skillPwrIcon->render();
		skill.skillPwrAmount->render();
	}
}
