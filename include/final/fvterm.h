/***********************************************************************
* fvterm.h - Virtual terminal implementation                           *
*                                                                      *
* This file is part of the Final Cut widget toolkit                    *
*                                                                      *
* Copyright 2016-2017 Markus Gans                                      *
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

/*  Inheritance diagram
 *  ═══════════════════
 *
 *  ▕▔▔▔▔▔▔▔▔▔▏
 *  ▕  FTerm  ▏
 *  ▕▁▁▁▁▁▁▁▁▁▏
 *       ▲
 *       │
 *  ▕▔▔▔▔▔▔▔▔▔▏1         *▕▔▔▔▔▔▔▔▔▔▏
 *  ▕ FVTerm  ▏- - -┬- - -▕ FString ▏
 *  ▕▁▁▁▁▁▁▁▁▁▏     :     ▕▁▁▁▁▁▁▁▁▁▏
 *                  :
 *                  :    *▕▔▔▔▔▔▔▔▔▏
 *                  :- - -▕ FPoint ▏
 *                  :     ▕▁▁▁▁▁▁▁▁▏
 *                  :
 *                  :    *▕▔▔▔▔▔▔▔▏
 *                  └- - -▕ FRect ▏
 *                        ▕▁▁▁▁▁▁▁▏
 */

#ifndef FVTERM_H
#define FVTERM_H

#if !defined (USE_FINAL_H) && !defined (COMPILE_FINAL_CUT)
  #error "Only <final/final.h> can be included directly."
#endif

#include <sstream>  // std::stringstream

#include "final/fterm.h"

// Preprocessing handler macro
#define F_PREPROC_HANDLER(i,h) \
           static_cast<FVTerm*>((i)) \
         , reinterpret_cast<FVTerm::FPreprocessingHandler>((h))

// class forward declaration
class FWidget;

//----------------------------------------------------------------------
// class FVTerm
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class FVTerm : public FTerm
{
  public:
    // Typedefs and Enumeration
    typedef struct
    {
      uInt xmin;           // X-position with the first change
      uInt xmax;           // X-position with the last change
      uInt trans_count;    // Number of transparent characters
    } line_changes;

    typedef FOptiAttr::char_data  char_data;
    typedef void (FVTerm::*FPreprocessingHandler)();

    struct term_area;  // forward declaration

    struct vterm_preprocessing
    {
      FVTerm*               instance;
      FPreprocessingHandler handler;
    };

    typedef std::vector<vterm_preprocessing> FPreprocessing;

    enum covered_state
    {
      non_covered,
      half_covered,
      fully_covered
    };

    // Constructor
    explicit FVTerm (bool, bool = false);

    // Destructor
   ~FVTerm();

    // Overloaded operators
    template<class type> FVTerm& operator << (const type&);
    FVTerm& operator << (const std::vector<char_data>&);

    // Accessors
    virtual const char* getClassName() const;
    static short        getTermForegroundColor();
    static short        getTermBackgroundColor();
    term_area*          getVWin() const;
    FPoint              getPrintCursor();
    static char_data    getAttribute();

    // Mutators
    static void         setTermXY (register int, register int);
    static bool         hideCursor (bool);
    static bool         hideCursor();
    static bool         showCursor();
    void                setPrintCursor (const FPoint&);
    void                setPrintCursor (register int, register int);
    void                setColor (short, short);
    static void         setNormal();

    static bool         setBold (register bool);
    static bool         setBold();
    static bool         unsetBold();

    static bool         setDim (register bool);
    static bool         setDim();
    static bool         unsetDim();

    static bool         setItalic (register bool);
    static bool         setItalic();
    static bool         unsetItalic();

    static bool         setUnderline (register bool);
    static bool         setUnderline();
    static bool         unsetUnderline();

    static bool         setBlink (register bool);
    static bool         setBlink();
    static bool         unsetBlink();

    static bool         setReverse (register bool);
    static bool         setReverse();
    static bool         unsetReverse();

    static bool         setStandout (register bool);
    static bool         setStandout();
    static bool         unsetStandout();

    static bool         setInvisible (register bool);
    static bool         setInvisible();
    static bool         unsetInvisible();

    static bool         setProtected (register bool);
    static bool         setProtected();
    static bool         unsetProtected();

    static bool         setCrossedOut (register bool);
    static bool         setCrossedOut();
    static bool         unsetCrossedOut();

    static bool         setDoubleUnderline (register bool);
    static bool         setDoubleUnderline();
    static bool         unsetDoubleUnderline();

    static bool         setAltCharset (register bool);
    static bool         setAltCharset();
    static bool         unsetAltCharset();

    static bool         setPCcharset (register bool);
    static bool         setPCcharset();
    static bool         unsetPCcharset();

    static bool         setTransparent (register bool);
    static bool         setTransparent();
    static bool         unsetTransparent();

    static bool         setTransShadow (register bool);
    static bool         setTransShadow();
    static bool         unsetTransShadow();

    static bool         setInheritBackground (register bool);
    static bool         setInheritBackground();
    static bool         unsetInheritBackground();

    // Inquiries
    static bool         isCursorHidden();
    static bool         isBold();
    static bool         isDim();
    static bool         isItalic();
    static bool         isUnderline();
    static bool         isBlink();
    static bool         isReverse();
    static bool         isStandout();
    static bool         isInvisible();
    static bool         isProtected();
    static bool         isCrossedOut();
    static bool         isDoubleUnderline();
    static bool         isAltCharset();
    static bool         isPCcharset();
    static bool         isTransparent();
    static bool         isTransShadow();
    static bool         isInheritBackground();

    // Methods
    virtual void        clearArea (int = ' ');
    void                createVTerm (const FRect&);
    void                createVTerm (int, int);
    static void         resizeVTerm (const FRect&);
    static void         resizeVTerm (int, int);
    static void         putVTerm();
    static void         updateTerminal (bool);
    static void         updateTerminal();
    virtual void        addPreprocessingHandler ( FVTerm*
                                                , FPreprocessingHandler );
    virtual void        delPreprocessingHandler (FVTerm*);

    int                 printf (const wchar_t*, ...);
    int                 printf (const char*, ...)
    #if defined(__clang__)
      __attribute__((__format__ (__printf__, 2, 3)))
    #elif defined(__GNUC__)
      __attribute__ ((format (printf, 2, 3)))
    #endif
                        ;
    int                 print (const std::wstring&);
    int                 print (term_area*, const std::wstring&);
    int                 print (const wchar_t*);
    int                 print (term_area*, const wchar_t*);
    int                 print (const char*);
    int                 print (term_area*, const char*);
    int                 print (const std::string&);
    int                 print (term_area*, const std::string&);
    int                 print (const FString&);
    int                 print (term_area*, const FString&);
    int                 print (const std::vector<char_data>&);
    int                 print (term_area*, const std::vector<char_data>&);
    int                 print (int);
    int                 print (term_area*, int);
    int                 print (char_data&);
    int                 print (term_area*, char_data&);
    FVTerm&             print();

  protected:
    // Enumeration
    enum character_type
    {
      overlapped_character,
      covered_character
    };

    // Accessor
    virtual term_area*   getPrintArea();

    // Inquiries
    bool                 hasPrintArea() const;
    bool                 hasChildPrintArea() const;
    bool                 isVirtualWindow() const;

    // Mutator
    static void          setInsertCursorStyle (bool on);
    static void          setInsertCursorStyle();
    static void          unsetInsertCursorStyle();

    // Methods
    void                 createArea ( const FRect&
                                    , const FPoint&
                                    , term_area*& );

    void                 createArea ( int, int, int, int
                                    , int, int
                                    , term_area*& );

    static void          resizeArea ( const FRect&
                                    , const FPoint&
                                    , term_area* );

    static void          resizeArea ( int, int, int, int
                                    , int, int
                                    , term_area* );

    static void          removeArea (term_area*&);
    static void          restoreVTerm (const FRect&);
    static void          restoreVTerm (int, int, int, int);

    static covered_state isCovered ( const FPoint&
                                   , term_area* );

    static covered_state isCovered ( int, int
                                   , term_area* );

    static void          updateOverlappedColor ( term_area*
                                               , int, int, int, int );
    static void          updateOverlappedCharacter (term_area*, int, int);
    static void          updateShadedCharacter ( term_area*
                                               , int, int, int, int );
    static void          updateInheritBackground ( term_area*
                                                 , int, int, int, int );
    static void          updateCharacter ( term_area*
                                         , int, int, int, int );
    static bool          updateVTermCharacter ( term_area*
                                              , int, int, int, int );
    static void          callPreprocessingHandler (term_area*);
    static void          updateVTerm();
    static void          updateVTerm (term_area*);
    static bool          updateVTermCursor (term_area*);
    static bool          isInsideArea (int, int, term_area*);

    static void          setAreaCursor ( const FPoint&
                                       , bool, term_area* );

    static void          setAreaCursor ( int, int
                                       , bool, term_area*);

    static void          getArea (const FPoint&, term_area*);
    static void          getArea (int, int, term_area*);
    static void          getArea (const FRect&, term_area*);
    static void          getArea (int, int, int, int, term_area*);
    static void          putArea (const FPoint&, term_area*);
    static void          putArea (int, int, term_area*);
    static void          scrollAreaForward (term_area*);
    static void          scrollAreaReverse (term_area*);
    static void          clearArea (term_area*, int = ' ');

    static char_data     getCharacter ( character_type
                                      , const FPoint&
                                      , FVTerm* );

    static char_data     getCharacter ( character_type
                                      , int
                                      , int, FVTerm* );

    static char_data     getCoveredCharacter (const FPoint&, FVTerm*);
    static char_data     getCoveredCharacter (int, int, FVTerm*);
    static char_data     getOverlappedCharacter (const FPoint&, FVTerm*);
    static char_data     getOverlappedCharacter (int, int, FVTerm*);
    static void          processTerminalUpdate();
    static void          startTerminalUpdate();
    static void          finishTerminalUpdate();
    static void          flush_out();

    // Data Members
    static        term_area* vterm;        // virtual terminal
    static        term_area* vdesktop;     // virtual desktop
    static        term_area* active_area;  // active area
    term_area*    print_area;              // print area for this object
    term_area*    child_print_area;        // print area for children
    term_area*    vwin;                    // virtual window

  private:
    // Typedef and Enumeration
    typedef FTermcap::tcap_map termcap_map;

    enum exit_state
    {
      not_used,
      used,
      line_completely_printed
    };

    // Constants
    static const uInt TERMINAL_OUTPUT_BUFFER_SIZE = 32768;
    // Buffer size for character output on the terminal

    // Disable copy constructor
    FVTerm (const FVTerm&);

    // Disable assignment operator (=)
    FVTerm& operator = (const FVTerm&);

    // Mutators
    void                    setPrintArea (term_area*);

    // Methods
    void                    init();
    void                    finish();
    static bool             clearTerm (int = ' ');
    static bool             canClearToEOL (uInt, uInt);
    static bool             canClearLeadingWS (uInt&, uInt);
    static bool             canClearTrailingWS (uInt&, uInt);
    static bool             skipUnchangedCharacters (uInt&, uInt, uInt);
    static void             printRange (uInt, uInt, uInt, bool);
    static exit_state       eraseCharacters (uInt&, uInt, uInt, bool);
    static exit_state       repeatCharacter (uInt&, uInt, uInt);
    static void             cursorWrap();
    static void             updateTerminalLine (uInt);
    static bool             updateTerminalCursor();
    static bool             isInsideTerminal (int, int);
    static void             markAsPrinted (uInt, uInt);
    static void             markAsPrinted (uInt, uInt, uInt);
    static void             newFontChanges (char_data*&);
    static void             charsetChanges (char_data*&);
    static void             appendCharacter (char_data*&);
    static void             appendChar (char_data*&);
    static void             appendAttributes (char_data*&);
    static int              appendLowerRight (char_data*&);
    static void             appendOutputBuffer (const std::string&);
    static void             appendOutputBuffer (const char[]);

#if defined(__sun) && defined(__SVR4)
    static int              appendOutputBuffer (char);
#else
    static int              appendOutputBuffer (int);
#endif

    // Data Members
    static std::queue<int>* output_buffer;
    static char_data        term_attribute;
    static char_data        next_attribute;
    static FPoint*          term_pos;  // terminal cursor position
    static termcap_map*     tcap;
    static bool             hidden_cursor;
    static bool             terminal_update_complete;
    static bool             terminal_update_pending;
    static bool             force_terminal_update;
    static bool             stop_terminal_updates;
    static int              skipped_terminal_update;
};
#pragma pack(pop)


//----------------------------------------------------------------------
// struct FVTerm::term_area
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

struct FVTerm::term_area  // define virtual terminal character properties
{
  public:
   term_area()
   : offset_left (0)
   , offset_top (0)
   , width (-1)
   , height (-1)
   , right_shadow (0)
   , bottom_shadow (0)
   , cursor_x (0)
   , cursor_y (0)
   , input_cursor_x (-1)
   , input_cursor_y (-1)
   , widget()
   , preprocessing_call()
   , changes (0)
   , text (0)
   , input_cursor_visible (false)
   , has_changes (false)
   , visible (false)
   { }

  ~term_area()
   { }

   int offset_left;     // Distance from left terminal side
   int offset_top;      // Distance from top of the terminal
   int width;           // Window width
   int height;          // Window height
   int right_shadow;    // Right window shadow
   int bottom_shadow;   // Bottom window shadow
   int cursor_x;        // X-position for the next write operation
   int cursor_y;        // Y-position for the next write operation
   int input_cursor_x;  // X-position input cursor
   int input_cursor_y;  // Y-position input cursor
   FWidget* widget;     // Widget that owns this term_area
   FPreprocessing preprocessing_call;
   line_changes* changes;
   char_data* text;     // Text data for the output
   bool input_cursor_visible;
   bool has_changes;
   bool visible;

 private:
   // Disable copy constructor
   term_area (const term_area&);
   // Disable assignment operator (=)
   term_area& operator = (const term_area&);
};
#pragma pack(pop)


// FVTerm inline functions
//----------------------------------------------------------------------
template<class type>
inline FVTerm& FVTerm::operator << (const type& s)
{
  std::wostringstream outstream;
  outstream << s;
  print (outstream.str());
  return *this;
}

//----------------------------------------------------------------------
inline FVTerm& FVTerm::operator << (const std::vector<FVTerm::char_data>& termString)
{
  print (termString);
  return *this;
}

//----------------------------------------------------------------------
inline const char* FVTerm::getClassName() const
{ return "FVTerm"; }

//----------------------------------------------------------------------
inline short FVTerm::getTermForegroundColor()
{ return next_attribute.fg_color; }

//----------------------------------------------------------------------
inline short FVTerm::getTermBackgroundColor()
{ return next_attribute.bg_color; }

//----------------------------------------------------------------------
inline FVTerm::term_area* FVTerm::getVWin() const
{ return vwin; }

//----------------------------------------------------------------------
inline FVTerm::char_data FVTerm::getAttribute()
{ return next_attribute; }

//----------------------------------------------------------------------
inline bool FVTerm::hideCursor()
{ return hideCursor(true); }

//----------------------------------------------------------------------
inline bool FVTerm::showCursor()
{ return hideCursor(false); }

//----------------------------------------------------------------------
inline void FVTerm::setPrintCursor (const FPoint& pos)
{ setPrintCursor (pos.getX(), pos.getY()); }

//----------------------------------------------------------------------
inline void FVTerm::setColor (register short fg, register short bg)
{
  // Changes colors
  next_attribute.fg_color = fg;
  next_attribute.bg_color = bg;
}

//----------------------------------------------------------------------
inline void FVTerm::setNormal()
{
  // reset all character attributes
  next_attribute.attr.bit.bold          = \
  next_attribute.attr.bit.dim           = \
  next_attribute.attr.bit.italic        = \
  next_attribute.attr.bit.underline     = \
  next_attribute.attr.bit.blink         = \
  next_attribute.attr.bit.reverse       = \
  next_attribute.attr.bit.standout      = \
  next_attribute.attr.bit.invisible     = \
  next_attribute.attr.bit.protect       = \
  next_attribute.attr.bit.crossed_out   = \
  next_attribute.attr.bit.dbl_underline = \
  next_attribute.attr.bit.alt_charset   = \
  next_attribute.attr.bit.pc_charset    = \
  next_attribute.attr.bit.transparent   = \
  next_attribute.attr.bit.trans_shadow  = \
  next_attribute.attr.bit.inherit_bg    = \
  next_attribute.attr.bit.no_changes    = false;

  next_attribute.fg_color = fc::Default;
  next_attribute.bg_color = fc::Default;
}

//----------------------------------------------------------------------
inline bool FVTerm::setBold (register bool on)
{ return (next_attribute.attr.bit.bold = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setBold()
{ return setBold(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetBold()
{ return setBold(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setDim (register bool on)
{ return (next_attribute.attr.bit.dim = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setDim()
{ return setDim(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetDim()
{ return setDim(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setItalic (register bool on)
{ return (next_attribute.attr.bit.italic = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setItalic()
{ return setItalic(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetItalic()
{ return setItalic(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setUnderline (register bool on)
{ return (next_attribute.attr.bit.underline = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setUnderline()
{ return setUnderline(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetUnderline()
{ return setUnderline(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setBlink (register bool on)
{ return (next_attribute.attr.bit.blink = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setBlink()
{ return setBlink(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetBlink()
{ return setBlink(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setReverse (register bool on)
{ return (next_attribute.attr.bit.reverse = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setReverse()
{ return setReverse(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetReverse()
{ return setReverse(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setStandout (register bool on)
{ return (next_attribute.attr.bit.standout = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setStandout()
{ return setStandout(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetStandout()
{ return setStandout(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setInvisible (register bool on)
{ return (next_attribute.attr.bit.invisible = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setInvisible()
{ return setInvisible(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetInvisible()
{ return setInvisible(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setProtected (register bool on)
{ return (next_attribute.attr.bit.protect = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setProtected()
{ return setProtected(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetProtected()
{ return setProtected(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setCrossedOut (register bool on)
{ return (next_attribute.attr.bit.crossed_out = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setCrossedOut()
{ return setCrossedOut(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetCrossedOut()
{ return setCrossedOut(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setDoubleUnderline (register bool on)
{ return (next_attribute.attr.bit.dbl_underline = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setDoubleUnderline()
{ return setDoubleUnderline(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetDoubleUnderline()
{ return setDoubleUnderline(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setAltCharset (register bool on)
{ return (next_attribute.attr.bit.alt_charset = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setAltCharset()
{ return setAltCharset(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetAltCharset()
{ return setAltCharset(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setPCcharset (register bool on)
{ return (next_attribute.attr.bit.pc_charset = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setPCcharset()
{ return setPCcharset(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetPCcharset()
{ return setPCcharset(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setTransparent (register bool on)
{ return (next_attribute.attr.bit.transparent = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setTransparent()
{ return setTransparent(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetTransparent()
{ return setTransparent(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setTransShadow (register bool on)
{ return (next_attribute.attr.bit.trans_shadow = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setTransShadow()
{ return setTransShadow(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetTransShadow()
{ return setTransShadow(false); }

//----------------------------------------------------------------------
inline bool FVTerm::setInheritBackground (register bool on)
{ return (next_attribute.attr.bit.inherit_bg = on); }

//----------------------------------------------------------------------
inline bool FVTerm::setInheritBackground()
{ return setInheritBackground(true); }

//----------------------------------------------------------------------
inline bool FVTerm::unsetInheritBackground()
{ return setInheritBackground(false); }

//----------------------------------------------------------------------
inline bool FVTerm::isCursorHidden()
{ return hidden_cursor; }

//----------------------------------------------------------------------
inline bool FVTerm::isBold()
{ return next_attribute.attr.bit.bold; }

//----------------------------------------------------------------------
inline bool FVTerm::isDim()
{ return next_attribute.attr.bit.dim; }

//----------------------------------------------------------------------
inline bool FVTerm::isItalic()
{ return next_attribute.attr.bit.italic; }

//----------------------------------------------------------------------
inline bool FVTerm::isUnderline()
{ return next_attribute.attr.bit.underline; }

//----------------------------------------------------------------------
inline bool FVTerm::isBlink()
{ return next_attribute.attr.bit.blink; }

//----------------------------------------------------------------------
inline bool FVTerm::isReverse()
{ return next_attribute.attr.bit.reverse; }

//----------------------------------------------------------------------
inline bool FVTerm::isStandout()
{ return next_attribute.attr.bit.standout; }

//----------------------------------------------------------------------
inline bool FVTerm::isInvisible()
{ return next_attribute.attr.bit.invisible; }

//----------------------------------------------------------------------
inline bool FVTerm::isProtected()
{ return next_attribute.attr.bit.protect; }

//----------------------------------------------------------------------
inline bool FVTerm::isCrossedOut()
{ return next_attribute.attr.bit.crossed_out; }

//----------------------------------------------------------------------
inline bool FVTerm::isDoubleUnderline()
{ return next_attribute.attr.bit.dbl_underline; }

//----------------------------------------------------------------------
inline bool FVTerm::isAltCharset()
{ return next_attribute.attr.bit.alt_charset; }

//----------------------------------------------------------------------
inline bool FVTerm::isPCcharset()
{ return next_attribute.attr.bit.pc_charset; }

//----------------------------------------------------------------------
inline bool FVTerm::isTransparent()
{ return next_attribute.attr.bit.transparent; }

//----------------------------------------------------------------------
inline bool FVTerm::isTransShadow()
{ return next_attribute.attr.bit.trans_shadow; }

//----------------------------------------------------------------------
inline bool FVTerm::isInheritBackground()
{ return next_attribute.attr.bit.inherit_bg; }

//----------------------------------------------------------------------
inline FVTerm& FVTerm::print()
{ return *this; }

//----------------------------------------------------------------------
inline bool FVTerm::hasPrintArea() const
{ return print_area; }

//----------------------------------------------------------------------
inline bool FVTerm::hasChildPrintArea() const
{ return child_print_area; }

//----------------------------------------------------------------------
inline bool FVTerm::isVirtualWindow() const
{ return vwin; }

//----------------------------------------------------------------------
inline void FVTerm::setInsertCursorStyle()
{ setInsertCursorStyle(true); }

//----------------------------------------------------------------------
inline void FVTerm::unsetInsertCursorStyle()
{ setInsertCursorStyle(false); }

//----------------------------------------------------------------------
inline void FVTerm::setPrintArea (term_area* area)
{ print_area = area; }

#endif  // FVTERM_H
