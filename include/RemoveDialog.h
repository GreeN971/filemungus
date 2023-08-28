#pragma once
#include "CustomDialog.h"

class RemoveDialog : public CustomDialog
{
public: 
    RemoveDialog(); 
    const wxString &GetNewFileName() const noexcept;

private: 
    wxString m_fileName;
};
