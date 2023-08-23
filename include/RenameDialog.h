#pragma once
#include "CustomDialog.h"

class RenameDialog : public CustomDialog
{
public: 
    RenameDialog(const wxString &path, const wxString &fileName); 
    const wxString &GetNewFileName() const noexcept;

private: 
    const wxString &m_path;
    wxString m_fileName;
};
