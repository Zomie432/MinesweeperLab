#include "MinesweeperApp.h"

wxIMPLEMENT_APP(MinesweeperApp);

MinesweeperApp::MinesweeperApp() {

}

MinesweeperApp::~MinesweeperApp() {

}

bool MinesweeperApp::OnInit() {
	minesweeperWindow = new MinesweeperWindow();
	minesweeperWindow->Show();
	return true;
}