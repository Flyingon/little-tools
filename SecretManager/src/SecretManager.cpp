#include "SecretManager.h"
#include <wx/clipbrd.h>

enum {
    ID_AddSecret = 1,
    ID_EditSecret = 2,
    ID_DeleteSecret = 3
};

wxBEGIN_EVENT_TABLE(SecretManager, wxPanel)
                EVT_BUTTON(ID_AddSecret, SecretManager::OnAddSecret)
                EVT_BUTTON(ID_EditSecret, SecretManager::OnEditSecret)
                EVT_BUTTON(ID_DeleteSecret, SecretManager::OnDeleteSecret)
wxEND_EVENT_TABLE()

SecretManager::SecretManager(wxWindow* parent)
        : wxPanel(parent), db(nullptr) {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    secretList = new wxListView(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
    secretList->AppendColumn("ID");
    secretList->AppendColumn("Name");
    secretList->AppendColumn("Secret");

    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, ID_AddSecret, "Add Secret"), 0, wxALL, 5);
    buttonSizer->Add(new wxButton(this, ID_EditSecret, "Edit Secret"), 0, wxALL, 5);
    buttonSizer->Add(new wxButton(this, ID_DeleteSecret, "Delete Secret"), 0, wxALL, 5);

    sizer->Add(secretList, 1, wxEXPAND | wxALL, 5);
    sizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    SetSizerAndFit(sizer);

    InitializeDatabase();
    LoadSecretsFromDatabase();

    // 添加事件处理器以支持复制
    secretList->Bind(wxEVT_KEY_DOWN, &SecretManager::OnKeyDown, this);
}


SecretManager::~SecretManager() {
    if (db) {
        sqlite3_close(db);
    }
}

void SecretManager::InitializeDatabase() {
    if (sqlite3_open("secrets.db", &db)) {
        wxMessageBox("Failed to open database", "Error", wxOK | wxICON_ERROR);
        db = nullptr;
    } else {
        const char* createTableSQL = "CREATE TABLE IF NOT EXISTS secrets ("
                                     "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                     "name TEXT NOT NULL, "
                                     "secret TEXT NOT NULL);";
        char* errMsg = nullptr;
        if (sqlite3_exec(db, createTableSQL, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            wxMessageBox("Failed to create table", "Error", wxOK | wxICON_ERROR);
            sqlite3_free(errMsg);
        }
    }
}

void SecretManager::LoadSecretsFromDatabase() {
    const char* query = "SELECT * FROM secrets;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const unsigned char* name = sqlite3_column_text(stmt, 1);
            const unsigned char* secret = sqlite3_column_text(stmt, 2);

            long index = secretList->GetItemCount();
            wxListItem item;
            item.SetId(index);
            item.SetText(wxString::Format("%d", id)); // 确保 %d 匹配 int 类型
            secretList->InsertItem(item);
            secretList->SetItem(index, 1, wxString::FromUTF8(reinterpret_cast<const char*>(name)));
            secretList->SetItem(index, 2, wxString::FromUTF8(reinterpret_cast<const char*>(secret)));
        }
        sqlite3_finalize(stmt);
    } else {
        wxMessageBox("Failed to load secrets from database", "Error", wxOK | wxICON_ERROR);
    }
}

void SecretManager::SaveSecretToDatabase(const wxString& name, const wxString& secret) {
    const char* insertSQL = "INSERT INTO secrets (name, secret) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, insertSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.mb_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, secret.mb_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_DONE) {
            long index = secretList->GetItemCount();
            wxListItem item;
            item.SetId(index);
            item.SetText(wxString::Format("%ld", sqlite3_last_insert_rowid(db))); // 确保 %ld 匹配 long 类型
            secretList->InsertItem(item);
            secretList->SetItem(index, 1, name);
            secretList->SetItem(index, 2, secret);
        } else {
            wxMessageBox("Failed to save secret to database", "Error", wxOK | wxICON_ERROR);
        }
        sqlite3_finalize(stmt);
    }
}

void SecretManager::UpdateSecretInDatabase(long id, const wxString& name, const wxString& secret) {
    const char* updateSQL = "UPDATE secrets SET name = ?, secret = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, updateSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.mb_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, secret.mb_str(), -1, SQLITE_STATIC);
        sqlite3_bind_int(stmt, 3, id);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            wxMessageBox("Failed to update secret in database", "Error", wxOK | wxICON_ERROR);
        }
        sqlite3_finalize(stmt);
    }
}

void SecretManager::DeleteSecretFromDatabase(long id) {
    const char* deleteSQL = "DELETE FROM secrets WHERE id = ?;";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(db, deleteSQL, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) != SQLITE_DONE) {
            wxMessageBox("Failed to delete secret from database", "Error", wxOK | wxICON_ERROR);
        }
        sqlite3_finalize(stmt);
    }
}

//void SecretManager::OnAddSecret(wxCommandEvent &event) {
//    wxTextEntryDialog dlg(this, "Enter the name of the secret:", "Add Secret");
//    if (dlg.ShowModal() == wxID_OK) {
//        wxString name = dlg.GetValue();
//
//        wxTextEntryDialog dlg2(this, "Enter the secret:", "Add Secret");
//        if (dlg2.ShowModal() == wxID_OK) {
//            wxString secret = dlg2.GetValue();
//            SaveSecretToDatabase(name, secret);
//        }
//    }
//}

//void SecretManager::OnEditSecret(wxCommandEvent &event) {
//    long itemIndex = -1;
//    itemIndex = secretList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
//    if (itemIndex == -1) {
//        wxMessageBox("Please select an item to edit", "Error", wxOK | wxICON_ERROR);
//        return;
//    }
//
//    long id = wxAtoi(secretList->GetItemText(itemIndex));
//    wxString name = secretList->GetItemText(itemIndex, 1);
//    wxTextEntryDialog dlg(this, "Edit the name of the secret:", "Edit Secret", name);
//    if (dlg.ShowModal() == wxID_OK) {
//        name = dlg.GetValue();
//
//        wxTextEntryDialog dlg2(this, "Edit the secret:", "Edit Secret", secretList->GetItemText(itemIndex, 2));
//        if (dlg2.ShowModal() == wxID_OK) {
//            wxString secret = dlg2.GetValue();
//            UpdateSecretInDatabase(id, name, secret);
//            secretList->SetItem(itemIndex, 1, name);
//            secretList->SetItem(itemIndex, 2, secret);
//        }
//    }
//}

void SecretManager::OnAddSecret(wxCommandEvent &event) {
    SecretDialog dlg(this, "Add Secret");
    if (dlg.ShowModal() == wxID_OK) {
        wxString name = dlg.GetName();
        wxString secret = dlg.GetSecret();
        SaveSecretToDatabase(name, secret);
    }
}

void SecretManager::OnEditSecret(wxCommandEvent &event) {
    long itemIndex = -1;
    itemIndex = secretList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex == -1) {
        wxMessageBox("Please select an item to edit", "Error", wxOK | wxICON_ERROR);
        return;
    }

    long id = wxAtoi(secretList->GetItemText(itemIndex));
    wxString name = secretList->GetItemText(itemIndex, 1);
    wxString secret = secretList->GetItemText(itemIndex, 2);

    SecretDialog dlg(this, "Edit Secret", name, secret);
    if (dlg.ShowModal() == wxID_OK) {
        name = dlg.GetName();
        secret = dlg.GetSecret();
        UpdateSecretInDatabase(id, name, secret);
        secretList->SetItem(itemIndex, 1, name);
        secretList->SetItem(itemIndex, 2, secret);
    }
}

void SecretManager::OnDeleteSecret(wxCommandEvent &event) {
    long itemIndex = -1;
    itemIndex = secretList->GetNextItem(itemIndex, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (itemIndex == -1) {
        wxMessageBox("Please select an item to delete", "Error", wxOK | wxICON_ERROR);
        return;
    }

    long id = wxAtoi(secretList->GetItemText(itemIndex));
    DeleteSecretFromDatabase(id);
    secretList->DeleteItem(itemIndex);
}

void SecretManager::OnKeyDown(wxKeyEvent& event) {
    if (event.ControlDown() && event.GetKeyCode() == 'C') {
        long itemIndex = secretList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
        if (itemIndex != -1) {
            wxString name = secretList->GetItemText(itemIndex, 1);
            wxString secret = secretList->GetItemText(itemIndex, 2);

            if (name.IsEmpty() && secret.IsEmpty()) {
                event.Skip();
                return;
            }

            wxString textToCopy;
            if (!secret.IsEmpty()) {
                textToCopy = secret;
            } else if (!name.IsEmpty()) {
                textToCopy = name;
            }

            if (wxTheClipboard->Open()) {
                wxTheClipboard->SetData(new wxTextDataObject(textToCopy));
                wxTheClipboard->Close();
            }
        }
    } else {
        event.Skip();
    }
}