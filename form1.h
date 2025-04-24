    /////////////////////////////////////////////////////////////////////////////
// Name:        form1.h
// Purpose:     
// Author:      Talipov S.N.
// Modified by: 
// Created:     07.04.2025 16:25:00
// RCS-ID:      
// Copyright:   Talipov S.N.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _FORM1_H_
#define _FORM1_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
#include "wx/spinctrl.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
class wxSpinCtrl;
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define form1 10000
#define ID_PANEL 10001
#define ID_BUTTON_START 10002
#define ID_BUTTON_RESET 10005
#define ID_SLIDER_START 10003
#define ID_SPINCTRL_START 10007
#define ID_SLIDER_STOP 10004
#define ID_SPINCTRL_STOP 10006
#define SYMBOL_FORM1_STYLE wxCAPTION|wxSYSTEM_MENU|wxMINIMIZE_BOX|wxCLOSE_BOX
#define SYMBOL_FORM1_TITLE _("DialogBlocksBusStop")
#define SYMBOL_FORM1_IDNAME form1
#define SYMBOL_FORM1_SIZE wxSize(1100, 900)
#define SYMBOL_FORM1_POSITION wxDefaultPosition
////@end control identifiers

#include <unordered_map>

/*!
 * Form1 class declaration
 */

class Form1: public wxFrame
{    
    DECLARE_CLASS( Form1 )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    Form1();
    Form1( wxWindow* parent, wxWindowID id = SYMBOL_FORM1_IDNAME, const wxString& caption = SYMBOL_FORM1_TITLE, const wxPoint& pos = SYMBOL_FORM1_POSITION, const wxSize& size = SYMBOL_FORM1_SIZE, long style = SYMBOL_FORM1_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_FORM1_IDNAME, const wxString& caption = SYMBOL_FORM1_TITLE, const wxPoint& pos = SYMBOL_FORM1_POSITION, const wxSize& size = SYMBOL_FORM1_SIZE, long style = SYMBOL_FORM1_STYLE );

    /// Destructor
    ~Form1();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin Form1 event handler declarations

    /// wxEVT_CLOSE_WINDOW event handler for form1
    void OnCloseWindow( wxCloseEvent& event );

    /// wxEVT_PAINT event handler for ID_PANEL
    void OnPaint( wxPaintEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_START
    void OnButtonStartClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_RESET
    void OnButtonResetClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER_START
    void OnSliderStartUpdated( wxCommandEvent& event );

    /// wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINCTRL_START
    void OnSpinctrlStartUpdated( wxSpinEvent& event );

    /// wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER_STOP
    void OnSliderStopUpdated( wxCommandEvent& event );

    /// wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINCTRL_STOP
    void OnSpinctrlStopUpdated( wxSpinEvent& event );

////@end Form1 event handler declarations
    
    //begin custom event handler declarations
    // These are functions that will be called when specific events occur, such as timers or user input.
    void OnTimer( wxTimerEvent& event );   // Event handler for timer events
    void OnSliderChange( wxCommandEvent& event ); // Event handler for slider value change
    bool IsStopPoint(const wxPoint& point);  // Check if the given point is a bus stop
    bool IsOnOrAfterPoint(const wxPoint& a, const wxPoint& b); // Check if point 'a' is on or after point 'b' in the route
    void InitBusRoute();  // Initializes the bus route with necessary data
    void OnSliderReset();  // Resets the slider to its initial position
    void OnSpinCtrlChange();  // Handles changes to the spin control value
    int HandleSliderGetValue(int value);
    int HandleSliderSetValue(int value);
    
    //end custom event handler declarations

////@begin Form1 member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end Form1 member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();
    
    // begin custom code
    
    // Enum to represent the four possible directions of the bus (for better code clarity and maintainability)
    enum class Direction {
        Left,   // Bus is turning left
        Right,  // Bus is turning right
        Front,  // Bus is moving forward
        Back    // Bus is moving backward
    };

    // Custom hash function for wxPoint to use in unordered_map (for efficient lookups)
    struct PointHash {
        size_t operator()(const wxPoint& p) const {
            return std::hash<int>()(p.x) ^ std::hash<int>()(p.y);  // Combine the x and y coordinates for hashing
        }
    };

    // Map that stores each stop as a key (wxPoint) and its index in the route as the value
    std::unordered_map<wxPoint, int, Form1::PointHash> stopToRouteIndex;

    // Resources for background image and the bus route timer
    wxBitmap backgroundBitmap;  
    wxTimer* timer;  // Timer for periodic updates
    int m_currentPathIndex;  // Current index in the bus route path
    bool m_isMovingBackward;  // Flag to check if the bus is moving in reverse direction
    bool isFirstTick;  // Flag to check if this is the first tick of the timer
    wxPoint busPosition;  // Current position of the bus on the route

    int startStopIndex;  // Index of the starting stop
    int endStopIndex;    // Index of the destination stop

    // List of bus stop coordinates
    std::vector<wxPoint> busStops = {
        {768, 700}, {58, 692}, {56, 389}, {261, 234},
        {259, 70}, {589, 233}, {419, 350}
    };

    // Forward route of the bus, represented as a list of coordinates
    std::vector<wxPoint> routeForward = {
        {768, 700}, {413, 696}, {58, 692},  
        {57, 540}, {56, 389},  
        {56, 309}, {56, 230},  
        {158, 232}, {261, 234},  
        {259, 150}, {259, 70},  
        {424, 80}, {589, 90},  
        {589, 160}, {589, 233},  
        {590, 300}, {590, 350},  
        {504, 350}, {419, 350}  
    };

    // Backward route of the bus, represented as a list of coordinates
    std::vector<wxPoint> routeBackward = { 
        {419, 350}, {504, 350}, {590, 350},  
        {590, 300}, {589, 233}, {589, 160},  
        {589, 90}, {424, 80}, {259, 70},  
        {259, 150}, {261, 234}, {158, 232},  
        {56, 230}, {56, 309}, {56, 389},  
        {57, 540}, {58, 692}, {413, 696}, {768, 700}  
    };

    // Directions for each stop on the forward route
    std::vector<Direction> orientationsForward = {
        Direction::Left, Direction::Left, Direction::Back,
        Direction::Back, Direction::Back,
        Direction::Back, Direction::Back,
        Direction::Right, Direction::Back,
        Direction::Back, Direction::Right,
        Direction::Right, Direction::Front,
        Direction::Front, Direction::Front,
        Direction::Front, Direction::Left,
        Direction::Left, Direction::Left
    };

    // Directions for each stop on the backward route
    std::vector<Direction> orientationsBackward = {
        Direction::Right, Direction::Right, Direction::Right,
        Direction::Back, Direction::Back, Direction::Back,
        Direction::Back, Direction::Left, Direction::Front,
        Direction::Front, Direction::Front, Direction::Left,
        Direction::Left, Direction::Front, Direction::Front,
        Direction::Front, Direction::Front, Direction::Right, Direction::Left, 
    };

    // end custom code


////@begin Form1 member variables
    wxStaticBitmap* m_location_xpm;
    wxPanel* m_draw_panel;
    wxButton* m_btn_start;
    wxButton* m_btn_reset;
    wxSlider* m_slider_start;
    wxSpinCtrl* m_spinctrl_start;
    wxSlider* m_slider_stop;
    wxSpinCtrl* m_spinctrl_stop;
////@end Form1 member variables
};

#endif
    // _FORM1_H_
