/** Brownian Motion 2015
 * \date : 030915
 * \file : Puzzle.hpp
 * \brief : all headers in here ... */

#ifndef SFML_PUZZ_HPP
#define SFML_PUZZ_HPP

//{ # include files

#include <fstream>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML/Graphics.hpp>
#include "icons.hpp"
//}

#define DP "Data/"

#define FILE0 DP "Puzzle.txt"

#define TPIC1 DP "Mondrian1.png"
#define TPIC2 DP "Caravaggio boys.png"
#define TPIC DP "Puzzle_15X480.png"
#define TPIC3 DP "radio planet.png"

using namespace std;

struct Record
{int tile = 0; int bx = 0; int by = 0; int sx = 0; int sy = 0;
Record();
Record(int p, int q, int r, int s, int t) {tile = p, bx = q, by = r, sx = s, sy = t;} };

class Puzzle
{
public:
int getSpriteNum(sf::Vector2f);
void Coords();
void drawTiles();
void Grid();
void moveTiles();
void playBack();
void processEvents();
void randomTiles();
void Render();
void Reset();
void Run();
void Scramble();
void Setup();
void SFGSetup();
void showKey();
void Signals();
void Widgets();
void Write();
void writeFile();

private:
float dist(sf::Vector2f val1, sf::Vector2f val2)
{float x,y; x = val1.x - val2.x; y = val1.y - val2.y;
return sqrt(x*x + y*y); }
void truncate() {ofstream writer( FILE0 ,ios::trunc);}
bool rando = false;
bool replay = false;
bool running = true;
bool success = false;
int m_blanked = 0;
int m_cols = 0;
int m_colsize = 0;
int m_counter = 0;
int m_move_count = 0;
int m_padding = 0;
int m_rows = 0;
int m_rowsize = 0;
int m_tile = 0;
int m_xval = 0;
int m_yval = 0;
sf::FloatRect m_sprite_rect;
sf::Font font;
sf::Image m_image;
sf::Mouse m_mouse;
sf::RenderWindow m_sfWindow;
sf::Sprite key_sprite;
sf::Sprite m_blank_tile;
sf::Text text;
sf::Texture m_blank;
sf::Texture m_key;
sf::Vector2f m_bp;
sf::Vector2f m_mouse_position;
sf::Vector2f m_sfwindow_size;
sf::Vector2f m_simulation_size;
sf::Vector2f m_sp;
sf::Vector2u m_imagesize;
sf::VertexArray m_xpoints;
sf::View m_view;
sfg::Button::Ptr scrambleButton;
sfg::Button::Ptr resetButton;
sfg::Canvas::Ptr key_canvas;
sfg::Desktop m_desktop;
sfg::Frame::Ptr imageFrame;
sfg::Frame::Ptr keyFrame;
sfg::Frame::Ptr menuFrame;
sfg::Label::Ptr Moves;
sfg::Label::Ptr Title;
sfg::SFGUI m_sfgui;
sfg::Window::Ptr keyWindow;
sfg::Window::Ptr sfgWindow;
vector <Record> v_records;
vector <sf::Sprite> v_sprite;
vector <sf::Texture> m_texture;


void setfalse(bool &var) {if (var == true) var = false;}
void settrue(bool &var) {if (var != true) var = true;}
void toggles(bool &var) {if (var == true) var = false; else var = true;}
};

#endif ///#ifndef SFML_PUZZ_HPP
