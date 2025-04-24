/////////////////////////////////////////////////////////////////////////////
// Name:        DialogBlocksBusStop.cpp
// Purpose:     
// Author:      Talipov S.N.
// Modified by: 
// Created:     10.04.2025 10:23:52
// RCS-ID:      
// Copyright:   Talipov S.N.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "DialogBlocksBusStop.h"

////@begin XPM images

////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( DialogBlocksBusStop )
////@end implement app


/*
 * DialogBlocksBusStop type definition
 */

IMPLEMENT_CLASS( DialogBlocksBusStop, wxApp )


/*
 * DialogBlocksBusStop event table definition
 */

BEGIN_EVENT_TABLE( DialogBlocksBusStop, wxApp )

////@begin DialogBlocksBusStop event table entries
////@end DialogBlocksBusStop event table entries

END_EVENT_TABLE()


/*
 * Constructor for DialogBlocksBusStop
 */

DialogBlocksBusStop::DialogBlocksBusStop()
{
    Init();
}


/*
 * Member initialisation
 */

void DialogBlocksBusStop::Init()
{
////@begin DialogBlocksBusStop member initialisation
////@end DialogBlocksBusStop member initialisation
}

/*
 * Initialisation for DialogBlocksBusStop
 */

bool DialogBlocksBusStop::OnInit()
{    
////@begin DialogBlocksBusStop initialisation
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.

#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
    Form1* mainWindow = new Form1( NULL );
    mainWindow->Show(true);
////@end DialogBlocksBusStop initialisation

    return true;
}


/*
 * Cleanup for DialogBlocksBusStop
 */

int DialogBlocksBusStop::OnExit()
{    
////@begin DialogBlocksBusStop cleanup
    return wxApp::OnExit();
////@end DialogBlocksBusStop cleanup
}

