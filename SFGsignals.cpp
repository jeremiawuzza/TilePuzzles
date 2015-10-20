#include "artpuzzle.h"

// All signals and 'signal functions' go here

void Puzzle::Signals()
  {   scrambleButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &Puzzle:: Scramble, this ) );
      resetButton->GetSignal( sfg::Widget::OnLeftClick ).Connect( std::bind( &Puzzle:: Reset, this ) );
  }

void Puzzle::Reset()
{
settrue(replay);
playBack();
}

void Puzzle::Scramble(){toggles(rando);}
