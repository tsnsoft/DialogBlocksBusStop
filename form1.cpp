/////////////////////////////////////////////////////////////////////////////
// Name:        form1.cpp
// Purpose:
// Author:      Talipov S.N.
// Modified by:
// Created:     07.04.2025 17:25:21
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
#include <wx/dcbuffer.h>
#endif

////@begin includes
////@end includes

#include "form1.h"

////@begin XPM images
#include "tsnsoft.xpm"
#include "bus_b.xpm"
#include "location_white_nums.xpm"
#include "bus_f.xpm"
#include "bus_r.xpm"
#include "bus_l.xpm"
////@end XPM images

/*
 * Form1 type definition
 */

IMPLEMENT_CLASS(Form1, wxFrame)

/*
 * Form1 event table definition
 */

BEGIN_EVENT_TABLE(Form1, wxFrame)

////@begin Form1 event table entries
    EVT_CLOSE( Form1::OnCloseWindow )
    EVT_BUTTON( ID_BUTTON_START, Form1::OnButtonStartClick )
    EVT_BUTTON( ID_BUTTON_RESET, Form1::OnButtonResetClick )
    EVT_SLIDER( ID_SLIDER_START, Form1::OnSliderStartUpdated )
    EVT_SPINCTRL( ID_SPINCTRL_START, Form1::OnSpinctrlStartUpdated )
    EVT_SLIDER( ID_SLIDER_STOP, Form1::OnSliderStopUpdated )
    EVT_SPINCTRL( ID_SPINCTRL_STOP, Form1::OnSpinctrlStopUpdated )
////@end Form1 event table entries
EVT_TIMER(wxID_ANY, Form1::OnTimer)

END_EVENT_TABLE()

/*
 * Form1 constructors
 */

Form1::Form1()
{
    Init();
}

Form1::Form1(wxWindow *parent, wxWindowID id, const wxString &caption, const wxPoint &pos, const wxSize &size, long style)
{
    Init();
    Create(parent, id, caption, pos, size, style);
}

/*
 * Form1 creator
 */

bool Form1::Create(wxWindow *parent, wxWindowID id, const wxString &caption, const wxPoint &pos, const wxSize &size, long style)
{
    ////@begin Form1 creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    SetIcon(GetIconResource(wxT("tsnsoft.xpm")));
    if (GetSizer())
    {
        GetSizer()->SetSizeHints(this);
    }
    Centre();
    ////@end Form1 creation
    return true;
}

/*
 * Form1 destructor
 */

Form1::~Form1()
{
    ////@begin Form1 destruction
    ////@end Form1 destruction
    if (timer)
    {
        if (timer->IsRunning())
        {
            timer->Stop();
        }
        delete timer;
        timer = nullptr;
    }
}

/*
 * Member initialisation
 */

void Form1::Init()
{
    ////@begin Form1 member initialisation
    m_location_xpm = NULL;
    m_draw_panel = NULL;
    m_btn_start = NULL;
    m_btn_reset = NULL;
    m_slider_start = NULL;
    m_spinctrl_start = NULL;
    m_slider_stop = NULL;
    m_spinctrl_stop = NULL;
    ////@end Form1 member initialisation

    // init routeForward hash table
    for (int i = 0; i < static_cast<int>(routeForward.size()); ++i)
    {
        stopToRouteIndex[routeForward[i]] = i;
    }

    // time init
    if (!timer)
    {
        timer = new wxTimer(this);
    }

    Form1::InitBusRoute();
}

/*
 * Control creation for Form1
 */

void Form1::CreateControls()
{
    ////@begin Form1 content construction
    Form1* itemFrame1 = this;

    wxBoxSizer* itemBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    itemFrame1->SetSizer(itemBoxSizer1);

    wxStaticBitmap* itemStaticBitmap2 = new wxStaticBitmap( itemFrame1, wxID_STATIC, itemFrame1->GetBitmapResource(wxT("bus_b.xpm")), wxDefaultPosition, wxSize(374, 174), 0 );
    itemStaticBitmap2->Show(false);
    itemBoxSizer1->Add(itemStaticBitmap2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_location_xpm = new wxStaticBitmap( itemFrame1, wxID_STATIC, itemFrame1->GetBitmapResource(wxT("location_white_nums.xpm")), wxDefaultPosition, wxSize(831, 762), 0 );
    m_location_xpm->Show(false);
    itemBoxSizer1->Add(m_location_xpm, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBitmap* itemStaticBitmap4 = new wxStaticBitmap( itemFrame1, wxID_STATIC, itemFrame1->GetBitmapResource(wxT("bus_f.xpm")), wxDefaultPosition, wxSize(154, 189), 0 );
    itemStaticBitmap4->Show(false);
    itemBoxSizer1->Add(itemStaticBitmap4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBitmap* itemStaticBitmap5 = new wxStaticBitmap( itemFrame1, wxID_STATIC, itemFrame1->GetBitmapResource(wxT("bus_r.xpm")), wxDefaultPosition, wxSize(154, 189), 0 );
    itemStaticBitmap5->Show(false);
    itemBoxSizer1->Add(itemStaticBitmap5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticBitmap* itemStaticBitmap3 = new wxStaticBitmap( itemFrame1, wxID_STATIC, itemFrame1->GetBitmapResource(wxT("bus_l.xpm")), wxDefaultPosition, wxSize(374, 174), 0 );
    itemStaticBitmap3->Show(false);
    itemBoxSizer1->Add(itemStaticBitmap3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemFrame1->SetSizer(itemBoxSizer2);

    m_draw_panel = new wxPanel( itemFrame1, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    m_draw_panel->SetExtraStyle(wxWS_EX_VALIDATE_RECURSIVELY);
    itemBoxSizer2->Add(m_draw_panel, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxGridSizer* itemGridSizer4 = new wxGridSizer(0, 2, 0, 0);
    itemBoxSizer2->Add(itemGridSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemGridSizer4->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_btn_start = new wxButton( itemFrame1, ID_BUTTON_START, _("Start"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(m_btn_start, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_btn_reset = new wxButton( itemFrame1, ID_BUTTON_RESET, _("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer3->Add(m_btn_reset, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer4 = new wxBoxSizer(wxVERTICAL);
    itemGridSizer4->Add(itemBoxSizer4, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer4->Add(itemBoxSizer5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText1 = new wxStaticText( itemFrame1, wxID_STATIC, _("Start Point"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(itemStaticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_slider_start = new wxSlider( itemFrame1, ID_SLIDER_START, 1, 1, 6, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
    itemBoxSizer5->Add(m_slider_start, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_spinctrl_start = new wxSpinCtrl( itemFrame1, ID_SPINCTRL_START, wxT("1"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 6, 1 );
    itemBoxSizer5->Add(m_spinctrl_start, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer4->Add(itemBoxSizer8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText9 = new wxStaticText( itemFrame1, wxID_STATIC, _("  End Point"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer8->Add(itemStaticText9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_slider_stop = new wxSlider( itemFrame1, ID_SLIDER_STOP, 2, 2, 7, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
    itemBoxSizer8->Add(m_slider_stop, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_spinctrl_stop = new wxSpinCtrl( itemFrame1, ID_SPINCTRL_STOP, wxT("2"), wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 2, 7, 2 );
    itemBoxSizer8->Add(m_spinctrl_stop, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    // Connect events and objects
    m_draw_panel->Connect(ID_PANEL, wxEVT_PAINT, wxPaintEventHandler(Form1::OnPaint), NULL, this);
    ////@end Form1 content construction

    // Custom code
    m_draw_panel->SetMinSize(wxSize(831, 768));
    m_draw_panel->SetBackgroundStyle(wxBG_STYLE_PAINT); // Важно для корректной работы буферизации

    // load background image to buffer
    backgroundBitmap = wxBitmap(location_white_nums_xpm);
}

/*
 * begin custom functions
 */
// Initializes the bus route
void Form1::InitBusRoute()
{
    m_isMovingBackward = false;                     // Set moving backward flag to false, as we start in the forward direction
    isFirstTick = true;                             // Indicate that this is the first tick (used to track state)
    busPosition = routeForward[m_currentPathIndex]; // Set bus position to the first point in the forward route
    m_currentPathIndex = 0;                         // Reset current path index to the beginning of the route
    startStopIndex = 0;                             // Set the start stop index to the first stop (0)

    // Set end stop index to 1 or the last stop in the route
    endStopIndex = std::min(1, static_cast<int>(routeForward.size()) - 1); // Ensure the endpoint is within bounds

    Refresh(); // Refresh the screen to update the bus route visualization

    // Reset the spinner values after initialization (helps with user interaction)
    OnSpinCtrlChange();
}

// Check if point a is on or after point b on the route (used for comparison)
bool Form1::IsOnOrAfterPoint(const wxPoint &a, const wxPoint &b)
{
    return a.x >= b.x && a.y >= b.y; // Returns true if point a is to the right or below point b
}

// Check if the point is within 5 pixels of any stop point in the bus route
bool Form1::IsStopPoint(const wxPoint &point)
{
    // Iterate over all bus stops to find if the point is close to any of them
    for (const auto &stop : busStops)
    {
        if (abs(stop.x - point.x) <= 5 && abs(stop.y - point.y) <= 5) // 5 pixels tolerance
            return true;                                              // If a stop is found, return true
    }
    return false; // If no stop is found, return false
}

int Form1::HandleSliderGetValue(int value)
{
    return value - 1;
}

int Form1::HandleSliderSetValue(int value)
{
    return value + 1;
}

void Form1::OnSliderChange(wxCommandEvent &event)
{
    // Get the object that triggered the event (either start or stop slider)
    wxObject *obj = event.GetEventObject();

    // Check if the event was triggered by the start slider
    if (obj == m_slider_start)
        startStopIndex = HandleSliderGetValue(m_slider_start->GetValue()); // Update the start stop index based on slider value
    // Check if the event was triggered by the stop slider
    else if (obj == m_slider_stop)
        endStopIndex = HandleSliderGetValue(m_slider_stop->GetValue()); // Update the end stop index based on slider value

    // Optional debug log to print start and end stop indices
    // wxLogMessage("start point: %d", startStopIndex);
    // wxLogMessage("end point: %d", endStopIndex);

    // Check if the start stop index is greater than or equal to the end stop index
    if (startStopIndex >= endStopIndex)
    {
        // If the end stop index has reached the maximum value, ensure it doesn't increase further
        int newEndPoint = std::min(endStopIndex + 1, m_slider_stop->GetMax()); // Calculate new end stop (prevent overflow)

        // Update the end stop index and set the start stop index one less than the end
        endStopIndex = newEndPoint;
        startStopIndex = endStopIndex - 1;

        // Set the new values for the sliders based on updated indices
        m_slider_stop->SetValue(HandleSliderSetValue(newEndPoint));
        m_slider_start->SetValue(HandleSliderSetValue(newEndPoint - 1));

        // Optional debug log to check updated values
        // wxLogMessage("[OnSliderChange] setter %d %d %d %d", startStopIndex, endStopIndex, static_cast<int>(busStops.size()), m_currentPathIndex);

        // Look up the stop index in the route map to find the corresponding route index
        auto it = stopToRouteIndex.find(busStops[startStopIndex]);
        if (it != stopToRouteIndex.end())
        {
            // If the stop is found, update the current path index and bus position
            int newCurrentPathIndex = it->second;           // Get the route index for the bus stop
            m_currentPathIndex = newCurrentPathIndex;       // Update the current path index
            busPosition = routeForward[m_currentPathIndex]; // Update the bus position based on the new path index

            // Refresh the display to show the updated bus position
            Refresh();
        }
        else
        {
            // Log an error if the bus stop index is not found in the route
            wxLogMessage("Error: BusStop index %d is not found in route!", startStopIndex);
        }
    }

    // Update the spinner control value based on the changes
    OnSpinCtrlChange();
}

// Function triggered by spin control changes
void Form1::OnSpinCtrlChange()
{
    // Check if the spin controls are valid before proceeding
    if (m_spinctrl_start && m_spinctrl_stop)
    {
        // Set the value of the start spin control based on the current value of the start slider
        m_spinctrl_start->SetValue(m_slider_start->GetValue());

        // Set the value of the stop spin control based on the current value of the stop slider
        m_spinctrl_stop->SetValue(m_slider_stop->GetValue());
    }
    // In case the spin controls are not initialized (this block is commented out)
    // else {
    //     wxLogError("Spin controls are not initialized!");  // Log error if controls are not available
    // }
}

// Function triggered every timer tick
void Form1::OnTimer(wxTimerEvent &event)
{
    // Check if the bus is not moving backward
    if (!m_isMovingBackward)
    {
        // Ensure the current path index is within bounds of the forward route
        if (static_cast<std::size_t>(m_currentPathIndex + 1) < routeForward.size())
        {
            // Increment the path index to move forward to the next point
            m_currentPathIndex++;

            // Update the bus position based on the new path index
            busPosition = routeForward[m_currentPathIndex];

            // Log the new bus position (disabled for now)
            // wxLogMessage("Moving forward to: (%d, %d)", busPosition.x, busPosition.y);

            // Check if the bus has reached the stop at the end point
            if (busPosition == busStops[endStopIndex])
            {
                // Log the bus reaching the final destination (disabled for now)
                // wxLogMessage("Bus stop reached at final destination: (%d, %d)", busPosition.x, busPosition.y);

                // Stop the timer when the bus reaches the end
                timer->Stop();
            }
        }
    }
    else
    { // If the bus is moving backward
        // Ensure the current path index is greater than 0 before moving backwards
        if (m_currentPathIndex > 0)
        {
            // Decrement the path index to move backward to the previous point
            m_currentPathIndex--;

            // Update the bus position based on the new path index
            busPosition = routeBackward[m_currentPathIndex];

            // Log the new bus position while moving backward (disabled for now)
            // wxLogMessage("Returning to: (%d, %d)", busPosition.x, busPosition.y);

            // Check if the bus has reached the start point
            if (busPosition == busStops[startStopIndex])
            {
                // Log the bus returning to the start point (disabled for now)
                // wxLogMessage("Returned to start point: (%d, %d)", busPosition.x, busPosition.y);

                // Stop the timer when the bus reaches the start
                timer->Stop();
            }
        }
    }

    // Log the current path index for debugging (disabled for now)
    // wxLogMessage("Current point index: %d", m_currentPathIndex);

    // Refresh the screen to reflect the updated bus position
    Refresh();
}

// Function to reset the sliders based on the start and end stop indexes
void Form1::OnSliderReset()
{
    // Set the stop slider to the value of the final stop index
    m_slider_stop->SetValue(HandleSliderSetValue(endStopIndex));

    // Set the start slider to the value of the starting stop index
    m_slider_start->SetValue(HandleSliderSetValue(startStopIndex));
}

/*
 * end custom functions
 */

/*
 * wxEVT_CLOSE_WINDOW event handler for form1
 */

void Form1::OnCloseWindow(wxCloseEvent &event)
{
    ////@begin wxEVT_CLOSE_WINDOW event handler for form1 in Form1.
    // Before editing this code, remove the block markers.
    event.Skip();
    ////@end wxEVT_CLOSE_WINDOW event handler for form1 in Form1.
}

/*
 * wxEVT_PAINT event handler for ID_PANEL
 */

void Form1::OnPaint(wxPaintEvent &event)
{
    // Create a device context (DC) for painting, associated with the panel
    // wxDynamicCast ensures we get the correct window type (wxWindow in this case)
    // wxPaintDC dc(wxDynamicCast(event.GetEventObject(), wxWindow));

    wxBufferedPaintDC dc(wxDynamicCast(event.GetEventObject(), wxWindow));
    // wxBufferedPaintDC dc(this);

    // Draw the background bitmap at position (0, 0)
    // This happens only once per paint event
    dc.DrawBitmap(backgroundBitmap, 0, 0, false); // Draw the background image

    // Determine the orientation of the bus based on whether it's moving backward or forward
    wxBitmap bus; // Declare a wxBitmap object to hold the bus image
    Form1::Direction currentOrientation = m_isMovingBackward ? orientationsBackward[m_currentPathIndex] : orientationsForward[m_currentPathIndex];

    // Choose the correct bus image based on the current orientation
    // If the bus is facing left
    if (currentOrientation == Form1::Direction::Left)
        bus = wxBitmap(bus_l_xpm); // Load the bus image for the left direction
    // If the bus is facing backward
    else if (currentOrientation == Form1::Direction::Back)
        bus = wxBitmap(bus_b_xpm); // Load the bus image for the backward direction
    // If the bus is facing forward
    else if (currentOrientation == Form1::Direction::Front)
        bus = wxBitmap(bus_f_xpm); // Load the bus image for the forward direction
    // If the bus is facing right
    else if (currentOrientation == Form1::Direction::Right)
        bus = wxBitmap(bus_r_xpm); // Load the bus image for the right direction

    wxImage img = bus.ConvertToImage();
    // Try to find XPM color "#" — it's #FCFEFC
    //img.SetMaskColour(0xFC, 0xFE, 0xFC);  // Прямое указание цвета
    img.ConvertToGreyscale();
    img.SetMaskColour(252, 254, 252); // equal for "#"
    bus = wxBitmap(img);

    // Calculate the position to draw the bus on the screen
    // Center the bus image around its current position (since the image may not be centered at the point)
    int bus_x = busPosition.x - (bus.GetWidth() / 2);  // Calculate the x-coordinate for the top-left corner of the bus
    int bus_y = busPosition.y - (bus.GetHeight() / 2); // Calculate the y-coordinate for the top-left corner of the bus

    // Draw the bus image at the calculated position
    // 'true' indicates that the bus image should be transparent where applicable
    dc.DrawBitmap(bus, bus_x, bus_y, true); // Draw the bus at the calculated position
}

/*
 * Should we show tooltips?
 */

bool Form1::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap Form1::GetBitmapResource(const wxString &name)
{
    // Bitmap retrieval
    ////@begin Form1 bitmap retrieval
    wxUnusedVar(name);
    if (name == wxT("bus_b.xpm"))
    {
        wxBitmap bitmap(bus_b_xpm);
        return bitmap;
    }
    else if (name == wxT("location_white_nums.xpm"))
    {
        wxBitmap bitmap(location_white_nums_xpm);
        return bitmap;
    }
    else if (name == wxT("bus_f.xpm"))
    {
        wxBitmap bitmap(bus_f_xpm);
        return bitmap;
    }
    else if (name == wxT("bus_r.xpm"))
    {
        wxBitmap bitmap(bus_r_xpm);
        return bitmap;
    }
    else if (name == wxT("bus_l.xpm"))
    {
        wxBitmap bitmap(bus_l_xpm);
        return bitmap;
    }
    return wxNullBitmap;
    ////@end Form1 bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon Form1::GetIconResource(const wxString &name)
{
    // Icon retrieval
    ////@begin Form1 icon retrieval
    wxUnusedVar(name);
    if (name == wxT("tsnsoft.xpm"))
    {
        wxIcon icon(tsnsoft_xpm);
        return icon;
    }
    return wxNullIcon;
    ////@end Form1 icon retrieval
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON
 */

void Form1::OnButtonStartClick(wxCommandEvent &event)
{
    // Ensure that the start and end stop indices are within valid range
    // Checking if the start stop index is within the bounds of the busStops vector
    if (startStopIndex < 0 || startStopIndex >= static_cast<int>(busStops.size()))
    {
        wxLogMessage("Start point is out of range."); // Log an error if start index is invalid
        return;                                       // Stop execution if startStopIndex is out of range
    }

    // Checking if the end stop index is within the bounds of the busStops vector
    if (endStopIndex < 0 || endStopIndex >= static_cast<int>(busStops.size()))
    {
        wxLogMessage("End point is out of range."); // Log an error if end index is invalid
        return;                                     // Stop execution if endStopIndex is out of range
    }

    int endRouteIndex;

    // Find the route index for the end stop using the busStops vector and stopToRouteIndex map
    auto it = stopToRouteIndex.find(busStops[endStopIndex]);
    if (it != stopToRouteIndex.end())
    {
        endRouteIndex = it->second; // If found, set the endRouteIndex to the corresponding value
    }
    else
    {
        // If the end stop is not found in the route, log the error
        wxLogMessage("End stop not found in route.");
        return; // Stop execution as the end stop is not part of the route
    }

    // Check if the current path index has already passed or reached the end stop
    if (m_currentPathIndex >= endRouteIndex)
    {
        wxLogMessage("The bus has already reached or passed the end stop."); // Log if the bus is already at or past the destination
        return;                                                              // Stop execution if the bus is already at or past the end stop
    }

    // Update the current path index if it is less than the start stop index
    // Ensures that the bus starts from the correct stop if the current path index is too low
    if (m_currentPathIndex < startStopIndex)
    {
        m_currentPathIndex = startStopIndex;            // Set the current path index to the start stop index
        busPosition = routeForward[m_currentPathIndex]; // Update the bus position to the start stop
    }

    // Start the timer only if it's not already running
    if (!timer->IsRunning())
    {
        // If the current path index is less than the start stop index, reset it to the start
        if (m_currentPathIndex < startStopIndex)
        {
            m_currentPathIndex = startStopIndex;            // Set current path index to start stop index
            busPosition = routeForward[m_currentPathIndex]; // Set bus position to start stop location
        }

        // Start the timer to begin the movement with a 500 ms interval
        timer->Start(500);
    }
}

/*
 * wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER_START
 */

void Form1::OnSliderStartUpdated(wxCommandEvent &event)
{
    OnSliderChange(event);
}

/*
 * wxEVT_COMMAND_SLIDER_UPDATED event handler for ID_SLIDER_STOP
 */

void Form1::OnSliderStopUpdated(wxCommandEvent &event)
{
    OnSliderChange(event);
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON_STOP
 */

void Form1::OnButtonResetClick(wxCommandEvent &event)
{
    //wxLogMessage("Reset Button Clicked!");
    OnSliderReset();
    InitBusRoute();
    OnSliderReset();
    InitBusRoute();
}

/*
 * wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINCTRL_START
 */

void Form1::OnSpinctrlStartUpdated(wxSpinEvent &event)
{
    // Get the current value from the spin control
    int newStartValue = m_spinctrl_start->GetValue();

    // Check if the new value is greater than the maximum allowed value for the slider
    if (!(newStartValue > m_slider_start->GetMax()))
    {
        // Set the slider value to the new start value if it's within the max range
        m_slider_start->SetValue(HandleSliderSetValue(newStartValue)); // Apply the new value to the slider (ensuring it doesn't exceed max)
    }

    // Call the OnSliderChange function to update any other dependent elements
    OnSliderChange(event);

    // Call the OnSpinCtrlChange function to handle any updates triggered by the spin control
    OnSpinCtrlChange();
}

/*
 * wxEVT_COMMAND_SPINCTRL_UPDATED event handler for ID_SPINCTRL_STOP
 */
void Form1::OnSpinctrlStopUpdated(wxSpinEvent &event)
{
    // Get the current value from the stop spin control
    int newStopValue = m_spinctrl_stop->GetValue();

    // Log the new stop value and the maximum value of the slider for debugging purposes
    // wxLogMessage("%d %d", newStopValue, m_slider_stop->GetMax());

    // Check if the new stop value is less than or equal to the maximum allowed value for the slider
    if (newStopValue <= m_slider_stop->GetMax())
    {
        // Set the slider value to the new stop value if it's within the max range
        m_slider_stop->SetValue(HandleSliderSetValue(newStopValue)); // Apply the new value to the slider (ensuring it doesn't exceed max)
    }

    // Call the OnSliderChange function to update any other dependent elements
    OnSliderChange(event);

    // Call the OnSpinCtrlChange function to handle any updates triggered by the spin control
    OnSpinCtrlChange();
}
