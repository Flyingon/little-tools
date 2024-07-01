#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/listbox.h>

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    void OnOpenFile(wxCommandEvent& event);
    void OnProcess(wxCommandEvent& event);

    wxBoxSizer* m_mainSizer;
    wxBoxSizer* m_leftSizer;
    wxBoxSizer* m_centerSizer;
    wxBoxSizer* m_rightSizer;

    wxListBox* m_functionList;
    wxListBox* m_leftImageList;
    wxListBox* m_rightImageList;

wxDECLARE_EVENT_TABLE();
};

enum
{
    ID_OpenFile = 1,
    ID_ProcessFunction
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
                EVT_MENU(ID_OpenFile, MyFrame::OnOpenFile)
                EVT_LISTBOX(ID_ProcessFunction, MyFrame::OnProcess)
wxEND_EVENT_TABLE()

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("Image Processing Tool");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_OpenFile, "&Open...\tCtrl-O");

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");

    SetMenuBar(menuBar);

    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);

    m_leftSizer = new wxBoxSizer(wxVERTICAL);
    m_leftImageList = new wxListBox(this, wxID_ANY);
    m_leftSizer->Add(m_leftImageList, 1, wxEXPAND | wxALL, 5);

    m_centerSizer = new wxBoxSizer(wxVERTICAL);
    m_functionList = new wxListBox(this, ID_ProcessFunction);
    m_functionList->Append("Grayscale");
    m_functionList->Append("Blur");
    m_functionList->Append("Edge Detection");
    m_centerSizer->Add(m_functionList, 1, wxEXPAND | wxALL, 5);

    m_rightSizer = new wxBoxSizer(wxVERTICAL);
    m_rightImageList = new wxListBox(this, wxID_ANY);
    m_rightSizer->Add(m_rightImageList, 1, wxEXPAND | wxALL, 5);

    m_mainSizer->Add(m_leftSizer, 1, wxEXPAND | wxALL, 5);
    m_mainSizer->Add(m_centerSizer, 1, wxEXPAND | wxALL, 5);
    m_mainSizer->Add(m_rightSizer, 1, wxEXPAND | wxALL, 5);

    SetSizer(m_mainSizer);
}

void MyFrame::OnOpenFile(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, _("Open Image file"), "", "",
                                "Image files (*.jpg;*.png)|*.jpg;*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString path = openFileDialog.GetPath();
    m_leftImageList->Append(path);

    // Add code to load and display the image in the left image list.
}

void MyFrame::OnProcess(wxCommandEvent& event)
{
    int selection = m_functionList->GetSelection();
    wxString selectedFunction = m_functionList->GetString(selection);
    wxString selectedImagePath = m_leftImageList->GetStringSelection();

    // Add code to process the selected image using the selected function and display the result.
    // For example:
    if (selectedFunction == "Grayscale") {
        // Process image to grayscale and add to m_rightImageList
    } else if (selectedFunction == "Blur") {
        // Process image to blur and add to m_rightImageList
    } else if (selectedFunction == "Edge Detection") {
        // Process image to edge detection and add to m_rightImageList
    }
}
