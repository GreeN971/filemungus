#pragma once
#include "CustomDialog.h"

class CreateDialog : public CustomDialog
{
public: 
    CreateDialog(); 
    const wxString &GetNewFileName() const noexcept;

private: 
    wxString m_fileName;
};
