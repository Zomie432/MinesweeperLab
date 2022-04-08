#pragma once
#include "wx/wx.h"

class MinesweeperWindow : public wxFrame
{
public:
	int mFieldWidth = 10;
	int mFieldHeight = 10;
	wxButton **btn;
	int* mField = nullptr;
	bool mFirstClick = true;

	MinesweeperWindow();
	~MinesweeperWindow();
	void OnButtonClick(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

