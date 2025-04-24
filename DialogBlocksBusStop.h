/////////////////////////////////////////////////////////////////////////////
// Name:        DialogBlocksBusStop.h
// Purpose:     
// Author:      Talipov S.N.
// Modified by: 
// Created:     10.04.2025 10:23:52
// RCS-ID:      
// Copyright:   Talipov S.N.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _DIALOGBLOCKSBUSSTOP_H_
#define _DIALOGBLOCKSBUSSTOP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
#include "form1.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * DialogBlocksBusStop class declaration
 */

class DialogBlocksBusStop: public wxApp
{    
    DECLARE_CLASS( DialogBlocksBusStop )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    DialogBlocksBusStop();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin DialogBlocksBusStop event handler declarations
////@end DialogBlocksBusStop event handler declarations

////@begin DialogBlocksBusStop member function declarations
////@end DialogBlocksBusStop member function declarations

////@begin DialogBlocksBusStop member variables
////@end DialogBlocksBusStop member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(DialogBlocksBusStop)
////@end declare app

#endif
    // _DIALOGBLOCKSBUSSTOP_H_
