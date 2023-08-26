#pragma once
#include "CustomDialog.h"

enum class FF 
{
    IsFolder,     
    IsFile
};

class RemoveDialog : public CustomDialog
{
public: 
    RemoveDialog(); 
    const wxString &GetNewFileName() const noexcept;

private: 
    wxString m_fileName;
};
