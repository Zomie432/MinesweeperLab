#include "MinesweeperWindow.h"

wxBEGIN_EVENT_TABLE(MinesweeperWindow, wxFrame)
wxEND_EVENT_TABLE()

MinesweeperWindow::MinesweeperWindow() : wxFrame(nullptr, wxID_ANY, "Minesweeper", wxPoint(400, 200), wxSize(800, 600))
{
	btn = new wxButton * [mFieldWidth * mFieldHeight];
	wxGridSizer* grid = new wxGridSizer(mFieldWidth, mFieldHeight, 0, 0);
	this->SetBackgroundColour(wxColor(1));
	mField = new int[mFieldWidth * mFieldHeight];

	wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	for (int x = 0; x < mFieldWidth; x++)
	{
		for (int y = 0; y < mFieldHeight; y++)
		{
			btn[y * mFieldWidth + x] = new wxButton(this, 10000 + (y * mFieldWidth + x));
			btn[y * mFieldWidth + x]->SetFont(font);

			btn[y * mFieldWidth + x]->SetBackgroundColour(wxColor(255, 153, 153));
			grid->Add(btn[y * mFieldWidth + x], 1, wxEXPAND | wxALL);

			btn[y * mFieldWidth + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, 
				&MinesweeperWindow::OnButtonClick, this);
			mField[y*mFieldWidth + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

MinesweeperWindow::~MinesweeperWindow() {
	delete[]btn;
}

void MinesweeperWindow::OnButtonClick(wxCommandEvent& evt) {
	int x = (evt.GetId() - 10000) % mFieldWidth;
	int y = (evt.GetId() - 10000) / mFieldWidth;

	if (mFirstClick) 
	{
		int mines = 30;
		while (mines) {
			int rx = rand() % mFieldWidth;
			int ry = rand() % mFieldHeight;
			if (mField[ry * mFieldWidth + rx] == 0 && rx != x && ry != y) {
				mField[ry * mFieldWidth + rx] = -1;
				mines--;
			}
		}
		mFirstClick = false;
	}
	
	//disable button
	btn[y * mFieldWidth + x]->SetBackgroundColour(wxColor(255, 102, 102));
	btn[y * mFieldWidth + x]->Enable(false);

	//check if hit mine
	if (mField[y * mFieldWidth + x] == -1) {
		wxMessageBox("Boom - Game Over");

		//reset game
		mFirstClick = true;
		for (int x = 0; x < mFieldWidth; x++)
		{
			for (int y = 0; y < mFieldHeight; y++)
			{
				mField[y * mFieldWidth + x] = 0;
				btn[y * mFieldWidth + x]->SetLabel("");
				btn[y * mFieldWidth + x]->Enable(true);
				btn[y * mFieldWidth + x]->SetBackgroundColour(wxColor(255, 153, 153));
			}
		}
	}
	else {
		// count neighboor mines
		int mineCount = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + i < mFieldWidth && y + j >= 0 && y + j < mFieldHeight) {
					if (mField[(y + j) * mFieldWidth + (x + i)] == -1) {
						mineCount++;
					}
				}
			}
			//update button label to show count
			if (mineCount > 0) {
				btn[y * mFieldWidth + x]->SetLabel(std::to_string(mineCount));
			}
		}
	}
	evt.Skip();
}