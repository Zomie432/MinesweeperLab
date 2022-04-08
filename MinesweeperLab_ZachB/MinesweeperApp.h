#pragma once
#include "wx/wx.h"
#include "MinesweeperWindow.h"


class MinesweeperApp : public wxApp
{
private:
	MinesweeperWindow* minesweeperWindow = nullptr;
public:
	MinesweeperApp();
	~MinesweeperApp();

	virtual bool OnInit();
};