#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <sqlite3.h>
#include "SecretDialog.h"

class SecretManager : public wxPanel {
public:
    SecretManager(wxWindow* parent);
    ~SecretManager();

private:
    wxListView* secretList;
    sqlite3* db;

    void InitializeDatabase();
    void LoadSecretsFromDatabase();
    void SaveSecretToDatabase(const wxString& name, const wxString& secret);
    void UpdateSecretInDatabase(long id, const wxString& name, const wxString& secret);
    void DeleteSecretFromDatabase(long id);

    void OnAddSecret(wxCommandEvent &event);
    void OnEditSecret(wxCommandEvent &event);
    void OnDeleteSecret(wxCommandEvent &event);

    void OnKeyDown(wxKeyEvent &event);
wxDECLARE_EVENT_TABLE();
};
