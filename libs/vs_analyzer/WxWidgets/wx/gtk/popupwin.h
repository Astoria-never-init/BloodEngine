/////////////////////////////////////////////////////////////////////////////
// Name:        wx/gtk/popupwin.h
// Purpose:
// Author:      Robert Roebling
// Created:
// Copyright:   (c) 2001 Robert Roebling
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_GTK_POPUPWIN_H_
#define _WX_GTK_POPUPWIN_H_

//-----------------------------------------------------------------------------
// wxPopUpWindow
//-----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxPopupWindow: public wxPopupWindowBase
{
public:
    wxPopupWindow() = default;
    virtual ~wxPopupWindow();

    wxPopupWindow(wxWindow *parent, int flags = wxBORDER_NONE)
        { (void)Create(parent, flags); }
    bool Create(wxWindow *parent, int flags = wxBORDER_NONE);

    virtual bool Show(bool show = true) override;

    virtual void SetFocus() override;

    // implementation
    // --------------

    // GTK time when connecting to button_press signal
    wxUint32  m_time;

protected:
    virtual void DoSetSize(int x, int y,
                           int width, int height,
                           int sizeFlags = wxSIZE_AUTO) override;

    virtual void DoMoveWindow(int x, int y, int width, int height) override;

#ifdef __WXUNIVERSAL__
    wxDECLARE_EVENT_TABLE();
#endif
    wxDECLARE_DYNAMIC_CLASS(wxPopupWindow);
};

#endif // _WX_GTK_POPUPWIN_H_
