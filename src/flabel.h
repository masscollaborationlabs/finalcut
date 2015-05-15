// flabel.h
// class FLabel

#ifndef _FLABEL_H
#define _FLABEL_H

#include "fwidget.h"

#define NO_EMPHASIS  0x00000000
#define EMPHASIS     0x00000001


//----------------------------------------------------------------------
// class FLabel
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class FLabel : public FWidget
{
 private:
   FString  text;
   int      emphasis;
   int      xoffset;
   uInt     alignment;
   uChar    emphasis_color;
   uChar    ellipsis_color;
   bool     reverse_mode;
   FWidget* accel_widget;

 private:
   FLabel (const FLabel&);
   FLabel& operator = (const FLabel&);

   void  init();
   uChar getHotkey();
   void  setHotkeyAccelerator();
   void  draw();

 public:
   FLabel (FWidget* parent=0);  // constructor
   FLabel (const FString&, FWidget* parent=0);  // constructor
   virtual ~FLabel();  // destructor
   const char* getClassName() const;

   void hide();
   void onMouseDown (FMouseEvent*);
   void onAccel (FAccelEvent*);
   void cb_accel_widget_destroyed (FWidget*, void*);
   void setAccelWidget (FWidget* widget=0);
   FTerm* getAccelWidget();
   void setAlignment(uInt);
   uInt getAlignment();
   bool setEmphasis(bool);
   bool setEmphasis();
   bool unsetEmphasis();
   bool hasEmphasis();
   bool setReverseMode(bool);
   bool setReverseMode();
   bool unsetReverseMode();
   bool hasReverseMode();
   bool setEnable (bool);
   void setNumber(long);
   void setText (const FString&);
   FString& getText();
};
#pragma pack(pop)


// FLabel inline functions
//----------------------------------------------------------------------
inline const char* FLabel::getClassName() const
{ return "FLabel"; }

//----------------------------------------------------------------------
inline FTerm* FLabel::getAccelWidget ()
{ return accel_widget; }

//----------------------------------------------------------------------
inline uInt FLabel::getAlignment()
{ return alignment; }

//----------------------------------------------------------------------
inline bool FLabel::setEmphasis()
{ return setEmphasis(true); }

//----------------------------------------------------------------------
inline bool FLabel::unsetEmphasis()
{ return setEmphasis(false); }

//----------------------------------------------------------------------
inline bool FLabel::hasEmphasis()
{ return ((emphasis & EMPHASIS) != 0); }

//----------------------------------------------------------------------
inline bool FLabel::setReverseMode()
{ return setReverseMode(true); }

//----------------------------------------------------------------------
inline bool FLabel::unsetReverseMode()
{ return setReverseMode(false); }

//----------------------------------------------------------------------
inline bool FLabel::hasReverseMode()
{ return reverse_mode; }

//----------------------------------------------------------------------
inline FString& FLabel::getText()
{ return this->text; }

#endif  // _FLABEL_H