#include "SecretDialog.h"

SecretDialog::SecretDialog(wxWindow* parent, const wxString& title, const wxString& name, const wxString& secret)
        : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(300, 200)) {

    wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
    nameSizer->Add(new wxStaticText(this, wxID_ANY, "Name:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    nameTextCtrl = new wxTextCtrl(this, wxID_ANY, name);
    nameSizer->Add(nameTextCtrl, 1, wxALL | wxEXPAND, 5);

    wxBoxSizer* secretSizer = new wxBoxSizer(wxHORIZONTAL);
    secretSizer->Add(new wxStaticText(this, wxID_ANY, "Secret:"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    secretTextCtrl = new wxTextCtrl(this, wxID_ANY, secret);
    secretSizer->Add(secretTextCtrl, 1, wxALL | wxEXPAND, 5);

    topSizer->Add(nameSizer, 0, wxALL | wxEXPAND, 5);
    topSizer->Add(secretSizer, 0, wxALL | wxEXPAND, 5);

    wxSizer* buttonSizer = CreateSeparatedButtonSizer(wxOK | wxCANCEL);
    topSizer->Add(buttonSizer, 0, wxALL | wxEXPAND, 5);

    SetSizerAndFit(topSizer);
}
