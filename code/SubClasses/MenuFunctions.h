#pragma once

#include "../Classes/Engine.h"

class MenuFunctions
{
private:
	EngineTypes::Menu::buttons_count_t last_select_button_index;
public:

	MenuFunctions();

	void Back();
	void Exit();
    
    void IndicatedMenuFunction(Menu* menu);

	~MenuFunctions();
};



