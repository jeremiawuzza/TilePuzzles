/** Brownian Motion 2015
 * \date : 27.07.15
 * \file :SFGUIfunctions.cpp
 * \brief : This is the SFGUI component of the puzzle;
 the other parts are in SFMLfunctions.cpp.
*/

#include "Puzzle.hpp"

void Puzzle::SFGSetup()
{   m_desktop.SetProperty( "*",  "FontSize",20);
    m_desktop.SetProperty("*", "FontName", DP "LithosPro-Bold.otf");
    m_desktop.LoadThemeFromFile(DP "Cezanne.theme"); }

/// *********************************************
void Puzzle::Run()
{   Grid(); /// in SFMLFunctions.cpp
    Setup();    /// in SFMLFunctions.cpp
    SFGSetup();
    Widgets();

    Render(); }
/// *********************************************

void Puzzle::Widgets()
{   m_padding = 10;
    m_simulation_size = {(float)m_imagesize.x, (float)m_imagesize.y };
    imageFrame = sfg::Frame::Create();
    menuFrame = sfg::Frame::Create();
    keyFrame = sfg::Frame::Create("Key");
    key_canvas = sfg::Canvas::Create();
    keyWindow = sfg::Window::Create();
    auto divV = sfg::Separator::Create( sfg::Separator::Orientation::VERTICAL );
    auto divH = sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL );
    auto divH2 = sfg::Separator::Create( sfg::Separator::Orientation::HORIZONTAL );
    Title = sfg::Label::Create(TPIC);
    scrambleButton = sfg::Button::Create("SCRAMBLE");
    resetButton = sfg::Button::Create("RESET");
    menuFrame->SetRequisition({0,140});
    scrambleButton->SetRequisition({0,40});
    resetButton->SetRequisition({0,40});
    Moves = sfg::Label::Create("count: 0");
    keyWindow->SetStyle(0);
    keyWindow->Add( key_canvas );
    key_canvas->SetRequisition( sf::Vector2f( m_key.getSize().x * key_sprite.getScale().x,
                                m_key.getSize().y * key_sprite.getScale().y ) );
    keyFrame->Add(keyWindow);
    imageFrame->SetRequisition(m_simulation_size);
    Signals(); /// signals functions in SFSignals.cpp

    auto rightBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5);
    rightBox->Pack(Title, false);
    rightBox->Pack(divH, false);
    rightBox->Pack(scrambleButton, false);
    rightBox->Pack(resetButton, false);
    rightBox->Pack(menuFrame, false);
    rightBox->Pack(keyFrame, false);
    rightBox->Pack(divH2);
    rightBox->Pack(Moves, false);
    auto leftBox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5);
    leftBox->Pack(imageFrame, false);
    auto mainBox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
    mainBox->Pack(leftBox);
    mainBox->Pack(divV);
    mainBox->Pack(rightBox);
    auto sfgWindow = sfg::Window::Create(sfg::Window::Style::BACKGROUND);
    sfgWindow->Add(mainBox);
    m_desktop.Add(sfgWindow);
    int m_menu_x = keyFrame->GetAllocation().width;
    m_sfwindow_size = {(float)m_imagesize.x + m_menu_x + 3* m_padding,
                       (float)m_imagesize.y + 3 * m_padding };

    m_view.reset({0, 0, m_simulation_size.x, m_simulation_size.y } );
    m_view.setViewport(
    {   imageFrame->GetAbsolutePosition().x / m_sfwindow_size.x,
        imageFrame->GetAbsolutePosition().y / m_sfwindow_size.y,
        imageFrame->GetAllocation().width   / m_sfwindow_size.x,
        imageFrame->GetAllocation().height  / m_sfwindow_size.y }); }

void Puzzle::Render()
{   m_sfWindow.create(sf::VideoMode(m_sfwindow_size.x, m_sfwindow_size.y),"ART PUZZLE");
m_sfWindow.setIcon( mondrian_ico.width,  mondrian_ico.height,  mondrian_ico.pixel_data );
    m_sfWindow.setFramerateLimit(20);
    while (m_sfWindow.isOpen())
    {   m_desktop.Update(0.101);
        m_sfWindow.clear();
        m_sfWindow.resetGLStates();
        m_sfgui.Display(m_sfWindow);
        m_sfWindow.pushGLStates();
        {   processEvents();
            if (rando) {randomTiles(); scrambleButton->SetLabel("STOP");}
            else scrambleButton->SetLabel("SCRAMBLE");
            drawTiles();
            m_sfWindow.setView(m_view); }
        m_sfWindow.popGLStates();
        key_canvas->Bind();
        key_canvas->Clear( sf::Color( 0, 0, 0, 0 ) );
        key_canvas->Draw( key_sprite );
        key_canvas->Display();
        key_canvas->Unbind();
        m_sfWindow.display();   }  }
