#include "MainFrame.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
                EVT_MENU(wxID_EXIT, MainFrame::OnExit)
                EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
        : wxFrame(nullptr, wxID_ANY, title, pos, size) {
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to Secret Manager!");

    // Add SecretManager
    secretManager = new SecretManager(this);
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(secretManager, 1, wxEXPAND | wxALL, 5);
    SetSizerAndFit(sizer);
}

void MainFrame::OnExit(wxCommandEvent &event) {
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent &event) {
    wxMessageBox("This is a wxWidgets Secret Manager", "About Secret Manager", wxOK | wxICON_INFORMATION);
}
