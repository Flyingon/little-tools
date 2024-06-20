#pragma once
#include <wx/wx.h>

class SecretDialog : public wxDialog {
public:
    SecretDialog(wxWindow* parent, const wxString& title, const wxString& name = "", const wxString& secret = "");

    wxString GetName() const { return nameTextCtrl->GetValue(); }
    wxString GetSecret() const { return secretTextCtrl->GetValue(); }

private:
    wxTextCtrl* nameTextCtrl;
    wxTextCtrl* secretTextCtrl;
};
