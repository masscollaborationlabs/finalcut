// fbutton.h
// class FButton

#ifndef _FBUTTON_H
#define _FBUTTON_H

#include "fwidget.h"


//----------------------------------------------------------------------
// class FButton
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class FButton : public FWidget
{
 private:
   FString text;
   bool button_down;

 private:
   FButton (const FButton&);
   FButton& operator = (const FButton&);
   void init();
   uChar getHotkey();
   void setHotkeyAccelerator();
   void draw();
   void processClick();
   friend class FDialog;

 public:
   FButton (FWidget* parent=0);  // constructor
   FButton (const FString&, FWidget* parent=0);  // constructor
   virtual ~FButton();  // destructor

   const char* getClassName() const;

   void        hide();

   void        onKeyPress (FKeyEvent*);
   void        onMouseDown (FMouseEvent*);
   void        onMouseUp (FMouseEvent*);
   void        onMouseMove (FMouseEvent*);
   void        onAccel (FAccelEvent*);
   void        onFocusIn (FFocusEvent*);
   void        onFocusOut (FFocusEvent*);

   bool        setNoUnderline(bool);
   bool        setNoUnderline();
   bool        unsetNoUnderline();

   bool        setEnable(bool);
   bool        setEnable();
   bool        unsetEnable();
   bool        setDisable();
   bool        setFocus(bool);
   bool        setFocus();
   bool        unsetFocus();
   bool        setFlat(bool);
   bool        setFlat();
   bool        unsetFlat();
   bool        isFlat() const;
   bool        setShadow(bool);
   bool        setShadow();
   bool        unsetShadow();
   bool        hasShadow() const;
   bool        setDown(bool);
   bool        setDown();
   bool        setUp();
   bool        isDown() const;

   void        setText (const FString&);
   FString&    getText();
};
#pragma pack(pop)


// FButton inline functions
//----------------------------------------------------------------------
inline const char* FButton::getClassName() const
{ return "FButton"; }

//----------------------------------------------------------------------
inline bool FButton::setNoUnderline()
{ return setNoUnderline(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetNoUnderline()
{ return setNoUnderline(false); }

//----------------------------------------------------------------------
inline bool FButton::setEnable()
{ return setEnable(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetEnable()
{ return setEnable(false); }

//----------------------------------------------------------------------
inline bool FButton::setDisable()
{ return setEnable(false); }

//----------------------------------------------------------------------
inline bool FButton::setFocus()
{ return setFocus(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetFocus()
{ return setFocus(false); }

//----------------------------------------------------------------------
inline bool FButton::setFlat()
{ return setFlat(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetFlat()
{ return setFlat(false); }

//----------------------------------------------------------------------
inline bool FButton::isFlat() const
{ return ((flags & FLAT) != 0); }

//----------------------------------------------------------------------
inline bool FButton::setShadow()
{ return setShadow(true); }

//----------------------------------------------------------------------
inline bool FButton::unsetShadow()
{ return setShadow(false); }

//----------------------------------------------------------------------
inline bool FButton::hasShadow() const
{ return ((flags & SHADOW) != 0); }

//----------------------------------------------------------------------
inline bool FButton::setDown()
{ return setDown(true); }

//----------------------------------------------------------------------
inline bool FButton::setUp()
{ return setDown(false); }

//----------------------------------------------------------------------
inline bool FButton::isDown() const
{ return button_down; }

//----------------------------------------------------------------------
inline FString& FButton::getText()
{ return this->text; }

#endif  // _FBUTTON_H