#pragma once

#include <wx/wx.h>
#include "SecretManager.h"

class MainFrame : public wxFrame {
public:
    MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnExit(wxCommandEvent &event);

    void OnAbout(wxCommandEvent &event);

    SecretManager *secretManager;

wxDECLARE_EVENT_TABLE();
};
