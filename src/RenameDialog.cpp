#include "RenameDialog.h"
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/log.h>

RenameDialog::RenameDialog(const wxString &path, const wxString &fileName) 
    : CustomDialog("Rename Dialog")
    , m_path(path)
    , m_fileName(fileName)
{
    SetMinSize(wxSize(300,-1)); /* TODO */ 
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *content = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *textSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText *statText = new wxStaticText(this, wxID_ANY, "New filename");
    statText->SetFont(statText->GetFont().Scale(1.0f));
    wxTextCtrl *inputText = new wxTextCtrl(this, wxID_ANY);
    inputText->SetValue(m_fileName);
    inputText->SetFont(inputText->GetFont().Scale(1.0));
    inputText->SetMinSize(wxSize(200,-1));

    textSizer->Add(statText, 0, wxRIGHT | wxALIGN_CENTER, 4);
    textSizer->Add(inputText, 1, wxEXPAND | wxTOP | wxRIGHT, 4);

    wxButton *ok = new wxButton(this, wxID_ANY, "OK");
    ok->Bind(wxEVT_BUTTON, [this, inputText](wxCommandEvent&){
        SetSucces(true);
        m_fileName = inputText->GetValue();
        Close();
    });

    wxButton *cancel = new wxButton(this, wxID_ANY, "Cancel");
    cancel->Bind(wxEVT_BUTTON, [this](wxCommandEvent&){ Close(); });
    
    buttonSizer->AddSpacer(10);
    buttonSizer->Add(ok, 0, wxALL | wxBOTTOM, 4);
    buttonSizer->AddStretchSpacer();
    buttonSizer->Add(cancel, 0, wxALL | wxBOTTOM, 4);
    buttonSizer->AddSpacer(10);

    content->Add(textSizer, 0, wxLEFT, 4);
    content->AddSpacer(20);
    content->Add(buttonSizer, 1, wxLEFT | wxEXPAND, 4);
    sizer->Add(content, 1, wxEXPAND);


    SetSizerAndFit(sizer);
        
}

const wxString &RenameDialog::GetNewFileName() const noexcept
{
   return m_fileName; 
}
