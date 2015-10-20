/** Brownian Motion 2015
 * \date  28.08.15
 * \file SFMLfunctions.cpp
 * \brief seperated out the exclusively SFML parts of the puzzle.
 Although this is an arbitrary dichotomy.
*/

#include "Puzzle.hpp"

void Puzzle::Grid()
{   m_image.loadFromFile(TPIC);         ///change the image name here
    m_imagesize = m_image.getSize();
    m_rows = 4;
    m_cols = 4;
    m_colsize = m_imagesize.x / m_cols;
    m_rowsize = m_imagesize.y / m_rows;
    m_blanked = m_rows * m_cols - 1;
    m_tile = m_rows * m_cols;
    m_xval = m_blanked % m_cols;
    m_yval = (m_blanked - m_blanked % m_rows)/m_rows;
    m_xpoints.resize(m_rows * m_cols );

    int xpos = 0, ypos = 0;
    for (int j = 0; j < m_cols; j++)
    {   xpos = 0;
        for (int i = 0; i < m_rows; i++)
        {   if (i > 0) xpos = xpos + m_colsize;
            m_xpoints[m_move_count].position = {(float)xpos, (float)ypos };
            m_move_count ++ ; }
        ypos = ypos  + m_rowsize; } }

void Puzzle::Setup()

{   m_blank.loadFromFile(TPIC,sf::IntRect(m_xval * m_colsize,
                                          m_yval * m_rowsize, m_colsize + 2, m_rowsize + 2));///and here

    m_blank_tile.setTexture(m_blank);
    m_blank_tile.setColor(sf::Color(220,220,220));
    m_blank_tile.setPosition(m_xpoints[m_blanked].position);
    int id = 0;
    v_sprite.resize(m_rows * m_cols);
    m_texture.resize(m_rows * m_cols);
    for (int i = 0; i < m_cols ; i ++)
    {   for (int j = 0; j < m_rows ; j ++)
        {   m_texture[id].loadFromFile(TPIC, sf::IntRect(j * m_colsize, i * m_rowsize, m_colsize, m_rowsize));
            if (id != m_blanked) v_sprite[id].setTexture(m_texture[id]);
            v_sprite[id].setPosition(m_xpoints[id].position);  id ++; } } m_move_count = 0;
    m_key.loadFromFile( TPIC );
    key_sprite.setTexture( m_key );
    key_sprite.scale(0.3,0.3); }

void Puzzle::processEvents()
{   sf::Event event;
    while(m_sfWindow.pollEvent(event))
    {   m_desktop.HandleEvent(event); /// m_desktop defined in 'widgets' - needed to activate sfg events

        switch (event.type)
        {   case sf::Event::Closed: m_sfWindow.close(); break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {   case sf::Keyboard::Escape: m_sfWindow.close(); break;
                    case sf::Keyboard::F4: settrue(replay); playBack(); break;
                    case sf::Keyboard::F5: playBack(); break;
                    case sf::Keyboard::F7: writeFile(); break;
                    case sf::Keyboard::F8: running = false; break;
                    case sf::Keyboard::F9: running = true; break;
                    default: break; }

            case sf::Event::MouseButtonPressed:
                if  (event.mouseButton.button == sf::Mouse::Left)
                {   m_mouse_position  = sf::Vector2f(event.mouseButton.x,event.mouseButton.y); break;
                default: break; } } } }


void Puzzle::moveTiles()
{   m_sprite_rect = v_sprite[m_counter].getGlobalBounds();
    m_sp = v_sprite[m_counter].getPosition();
    m_bp = m_blank_tile.getPosition();
    float z = dist(m_sp, m_bp);

    if (m_sprite_rect.contains(m_mouse_position) && z <= m_rowsize) /// z is within p
    {   m_tile = m_counter;
        if (m_sp.y < m_bp.y)
        {   m_blank_tile.move(0, -m_rowsize); ///move blank up
            v_sprite[m_counter].move(0, m_rowsize);
            success = true; } /// move sprite down
        if (m_sp.y > m_bp.y)
        {   m_blank_tile.move(0, m_rowsize); ///move blank down
            v_sprite[m_counter].move(0, -m_rowsize); /// move sprite up
            success = true; }
        if (m_sp.x < m_bp.x)
        {   m_blank_tile.move(-m_colsize, 0); ///move blank left
            v_sprite[m_counter].move(m_colsize, 0);/// move sprite right
            success = true; }
        if (m_sp.x > m_bp.x)
        {   m_blank_tile.move(m_colsize,0);///move blank right
            v_sprite[m_counter].move(-m_colsize,0); /// move sprite left
            success = true; }
        m_sp = v_sprite[m_counter].getPosition();
        m_bp = m_blank_tile.getPosition(); }
    if (success) { Write(); m_move_count ++;  } }

///*****************************************************************
int Puzzle::getSpriteNum(sf::Vector2f posn)
{   for (int i = 0 ; i <m_rows * m_cols; i++ )
    { if (v_sprite.at(i).getPosition() == posn) return i ; } ;return 0; }
///***************************************************************

void Puzzle::randomTiles()
{   m_bp = m_blank_tile.getPosition();
    bool loop = true;
/// Calculate possible moves based on blank position (2, 3 or 4)
    enum blankposition {topleft = 1, topmid, topright, midleft, midmid, midright, botleft, botmid, botright };
    blankposition located;
    while (loop)
    {   if (m_bp == sf::Vector2f (0,0)) {located = topleft; break;}
        if (m_bp ==  (sf::Vector2f((m_rows-1) * m_colsize, 0)) ) {located = topright; break;}
        if (m_bp.y == 0) { located = topmid; break;}
        if (m_bp == sf::Vector2f(0, (m_cols-1) * m_rowsize)) {located = botleft; break;}
        if (m_bp == sf::Vector2f((m_rows-1) * m_colsize,(m_cols-1) * m_rowsize)) {located = botright; break;}
        if (m_bp.y == ((m_rows-1) * m_colsize)) { located = botmid; break;}
        if (m_bp.x == 0) { located = midleft; break;}
        if (m_bp.x == (m_cols-1) * m_rowsize) { located = midright; break;}
        else {located = midmid; break;} }
    enum moves {no, up, left, down, right };
    vector<moves> thismove;
    switch (located)
    {   case topleft: thismove = { down, right }; break;        /// all the moves for each of the
        case topmid: thismove = { left, down, right }; break;   /// 9 cardinal postions
        case topright: thismove = { left, down }; break;
        case midleft: thismove = { up, down, right }; break;
        case midmid: thismove = { up, left, down, right }; break;
        case midright: thismove = {  up, left, down }; break;
        case botleft: thismove = { up, right }; break;
        case botmid: thismove = { up, left, right }; break;
        case botright:thismove = { up, left }; break; }

    random_shuffle (thismove.begin(), thismove.end() ); /// this function shuffles the moves and spits one out
    moves val = thismove.at(0); /// this is the move at first posn in vector

    switch (val)
    {   case up:
        {   sf::Vector2f spriteposition(m_blank_tile.getPosition().x, m_blank_tile.getPosition().y - m_rowsize ); /// getSprite
            m_tile = getSpriteNum(spriteposition);
            m_blank_tile.move(0, - m_rowsize); ///move blank up
            v_sprite[m_tile].move(0, m_rowsize);/// move sprite do
            break; }
        case down:
        {   sf::Vector2f spriteposition(m_blank_tile.getPosition().x, m_blank_tile.getPosition().y + m_rowsize ); /// getSprite
            m_tile = getSpriteNum(spriteposition);
            m_blank_tile.move(0,  m_rowsize); ///move blank up
            v_sprite[m_tile].move(0, - m_rowsize);/// move sprite down
            break; }
        case left:
        {   sf::Vector2f spriteposition(m_blank_tile.getPosition().x - m_rowsize, m_blank_tile.getPosition().y  ); /// getSprite
            m_tile = getSpriteNum(spriteposition);
            m_blank_tile.move(-m_colsize, 0); ///move blank up
            v_sprite[m_tile].move(m_colsize, 0);/// move sprite down
            break; }
        case right:
        {   sf::Vector2f spriteposition(m_blank_tile.getPosition().x + m_rowsize, m_blank_tile.getPosition().y  ); /// getSprite
            m_tile = getSpriteNum(spriteposition);
            m_blank_tile.move(m_colsize, 0); ///move blank up
            v_sprite[m_tile].move(- m_colsize, 0);/// move sprite down
            break; }
        default: break;  }
    m_sp = v_sprite[m_tile].getPosition();
    m_bp = m_blank_tile.getPosition();
    Write();
    m_move_count ++; }

void Puzzle::drawTiles()
{   for ( m_counter = 0 ; m_counter < m_rows * m_cols; m_counter++ )
    {   m_sfWindow.draw(v_sprite[m_counter]);
        m_sfWindow.draw(m_blank_tile);
        if (! replay) moveTiles(); } }

void Puzzle::Write()
{   Moves->SetText(to_string (m_move_count));
    Record thismove( m_tile, m_bp.x, m_bp.y, m_sp.x, m_sp.y );
    v_records.emplace(v_records.begin(),thismove);
    success = false; }

void Puzzle::writeFile()
{   truncate();
    for (unsigned int i = 0 ; i < v_records.size(); i++ )
    {   int  m_tile = v_records.at(i).tile;
        m_sp.x = v_records.at(i).bx;
        m_sp.y = v_records.at(i).by;
        m_bp.x = v_records.at(i).sx;
        m_bp.y = v_records.at(i).sy;
        ofstream writer( FILE0 ,ios::app);
        writer << '\n'<<  m_tile << '\t' << m_bp.x <<'\t'<< m_bp.y << '\t' << m_sp.x <<'\t'<< m_sp.y; } }

void Puzzle::playBack()
{   for (unsigned int i = 0 ; i < v_records.size(); i++)
    {   int  p = v_records.at(i).tile;
        m_sp.x = v_records.at(i).bx;
        m_sp.y = v_records.at(i).by;
        m_bp.x = v_records.at(i).sx;
        m_bp.y = v_records.at(i).sy;
        m_blank_tile.setPosition(m_bp);
        v_sprite[p].setPosition(m_sp); }
    setfalse(replay);
    m_move_count = 1;
    Moves->SetText("count: 0");
    v_records.clear(); } ///need to build better system


