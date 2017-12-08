/***********************************************************************
* scrollview.cpp - Shows client widgets in a scroll area               *
*                                                                      *
* This file is part of the Final Cut widget toolkit                    *
*                                                                      *
* Copyright 2017 Markus Gans                                           *
*                                                                      *
* The Final Cut is free software; you can redistribute it and/or       *
* modify it under the terms of the GNU Lesser General Public License   *
* as published by the Free Software Foundation; either version 3 of    *
* the License, or (at your option) any later version.                  *
*                                                                      *
* The Final Cut is distributed in the hope that it will be useful,     *
* but WITHOUT ANY WARRANTY; without even the implied warranty of       *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU Lesser General Public License for more details.                  *
*                                                                      *
* You should have received a copy of the GNU Lesser General Public     *
* License along with this program.  If not, see                        *
* <http://www.gnu.org/licenses/>.                                      *
***********************************************************************/

#include <final/final.h>


//----------------------------------------------------------------------
// class Scrollview
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class Scrollview : public FScrollView
{
  public:
    // Constructor
    explicit Scrollview (FWidget* = 0);

    // Destructor
    ~Scrollview  ();

    // Mutator
    void setScrollSize (int, int);

  private:
    // Disable copy constructor
    Scrollview (const Scrollview&);
    // Disable assignment operator (=)
    Scrollview& operator = (const Scrollview&);

    // Method
    void draw();

    // Callback methods
    void cb_go_east (FWidget*, data_ptr);
    void cb_go_south (FWidget*, data_ptr);
    void cb_go_west (FWidget*, data_ptr);
    void cb_go_north (FWidget*, data_ptr);

    // Data Members
    FButton* go_east;
    FButton* go_south;
    FButton* go_west;
    FButton* go_north;
};
#pragma pack(pop)

//----------------------------------------------------------------------
Scrollview::Scrollview (FWidget* parent)
  : FScrollView(parent)
  , go_east()
  , go_south()
  , go_west()
  , go_north()
{
  // Create the four navigation buttons
  go_east = new FButton(wchar_t(fc::BlackRightPointingPointer) , this);
  go_east->setGeometry (1, 1, 5, 1);

  go_south = new FButton(wchar_t(fc::BlackDownPointingTriangle) , this);
  go_south->setGeometry (getScrollWidth() - 5, 1, 5, 1);

  go_west = new FButton(wchar_t(fc::BlackLeftPointingPointer) , this);
  go_west->setGeometry (getScrollWidth() - 5, getScrollHeight() - 2, 5, 1);

  go_north = new FButton(wchar_t(fc::BlackUpPointingTriangle) , this);
  go_north->setGeometry (1, getScrollHeight() - 2, 5, 1);

  // Add scroll function callbacks to the buttons
  go_east->addCallback
  (
    "clicked",
    F_METHOD_CALLBACK (this, &Scrollview::cb_go_east)
  );

  go_south->addCallback
  (
    "clicked",
    F_METHOD_CALLBACK (this, &Scrollview::cb_go_south)
  );

  go_west->addCallback
  (
    "clicked",
    F_METHOD_CALLBACK (this, &Scrollview::cb_go_west)
  );

  go_north->addCallback
  (
    "clicked",
    F_METHOD_CALLBACK (this, &Scrollview::cb_go_north)
  );
}

//----------------------------------------------------------------------
Scrollview::~Scrollview()
{ }

//----------------------------------------------------------------------
void Scrollview::setScrollSize (int width, int height)
{
  FScrollView::setScrollSize (width, height);
  go_south->setPos (width - 5, 1);
  go_west->setPos (width - 5, height - 1);
  go_north->setPos (1, height - 1);
}

//----------------------------------------------------------------------
void Scrollview::draw()
{
  if ( isMonochron() )
    setReverse(true);

  setColor (wc.label_inactive_fg, wc.dialog_bg);
  clearArea();

  for (int y = 0; y < getScrollHeight(); y++)
  {
    setPrintPos (1, 1 + y);

    for (int x = 0; x < getScrollWidth(); x++)
      print (32 + ((x + y) % 0x5f));
  }

  if ( isMonochron() )
    setReverse(false);

  FScrollView::draw();
}

//----------------------------------------------------------------------
void Scrollview::cb_go_east (FWidget*, data_ptr)
{
  scrollToX (getScrollWidth() - getViewportWidth() + 1);
  go_south->setFocus();
  go_east->redraw();
  go_south->redraw();
}

//----------------------------------------------------------------------
void Scrollview::cb_go_south (FWidget*, data_ptr)
{
  scrollToY (getScrollHeight() - getViewportHeight() + 1);
  go_west->setFocus();
  go_south->redraw();
  go_west->redraw();
}

//----------------------------------------------------------------------
void Scrollview::cb_go_west (FWidget*, data_ptr)
{
  scrollToX (1);
  go_north->setFocus();
  go_west->redraw();
  go_north->redraw();
}

//----------------------------------------------------------------------
void Scrollview::cb_go_north (FWidget*, data_ptr)
{
  scrollToY (1);
  go_east->setFocus();
  go_north->redraw();
  go_east->redraw();
}


//----------------------------------------------------------------------
// class Scrollviewdemo
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class Scrollviewdemo : public FDialog
{
  public:
    // Constructor
    explicit Scrollviewdemo (FWidget* = 0);

    // Destructor
    ~Scrollviewdemo  ();

    // Event handler
    void onClose (FCloseEvent*);

    // Callback method
    void cb_quit (FWidget* = 0, data_ptr = 0);
};
#pragma pack(pop)


//----------------------------------------------------------------------
Scrollviewdemo::Scrollviewdemo (FWidget* parent)
  : FDialog(parent)
{
  setGeometry (16, 3, 50, 19);
  setText ("Scrolling viewport example");

  // The scrolling viewport widget
  Scrollview* sview = new Scrollview (this);
  sview->setGeometry(3, 2, 44, 12);
  sview->setScrollSize(188, 124);

  // Quit button
  FButton* button = new FButton("&Quit", this);
  button->setGeometry(37, 15, 10, 1);

  // Add function callback
  button->addCallback
  (
    "clicked",
    F_METHOD_CALLBACK (this, &Scrollviewdemo::cb_quit)
  );

  // Text label
  FLabel* label = new FLabel (this);
  label->setGeometry(2, 1, 46, 1);
  label->setEmphasis();
  *label << L"Use scrollbars to change the viewport position";
}

//----------------------------------------------------------------------
Scrollviewdemo::~Scrollviewdemo()
{ }

//----------------------------------------------------------------------
void Scrollviewdemo::cb_quit (FWidget*, data_ptr)
{
  close();
}

//----------------------------------------------------------------------
void Scrollviewdemo::onClose (FCloseEvent* ev)
{
  FApplication::closeConfirmationDialog (this, ev);
}


//----------------------------------------------------------------------
//                               main part
//----------------------------------------------------------------------
int main (int argc, char* argv[])
{
  // Create the application object
  FApplication app(argc, argv);

  // Create a simple dialog box
  Scrollviewdemo svdemo(&app);

  // Set dialog main_dlg as main widget
  app.setMainWidget(&svdemo);

  // Show and start the application
  svdemo.show();
  return app.exec();
}