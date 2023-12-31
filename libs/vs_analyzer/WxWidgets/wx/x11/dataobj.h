///////////////////////////////////////////////////////////////////////////////
// Name:        wx/x11/dataobj.h
// Purpose:     declaration of the wxDataObject class for X11
// Author:      Julian Smart
// Copyright:   (c) 1998 Robert Roebling
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_X11_DATAOBJ_H_
#define _WX_X11_DATAOBJ_H_

// ----------------------------------------------------------------------------
// wxDataObject is the same as wxDataObjectBase under X11
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxDataObject : public wxDataObjectBase
{
public:
    wxDataObject();

#ifdef __DARWIN__
    virtual ~wxDataObject() = default;
#endif

    virtual bool IsSupportedFormat( const wxDataFormat& format, Direction dir = Get ) const;
};

#endif //_WX_X11_DATAOBJ_H_

