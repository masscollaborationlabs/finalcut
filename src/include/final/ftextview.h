/***********************************************************************
* ftextview.h - Widget FTextView (a multiline text viewer)             *
*                                                                      *
* This file is part of the Final Cut widget toolkit                    *
*                                                                      *
* Copyright 2014-2019 Markus Gans                                      *
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
 * ▕▔▔▔▔▔▔▔▔▔▏
 * ▕  FTerm  ▏
 * ▕▁▁▁▁▁▁▁▁▁▏
 *      ▲
 *      │
 * ▕▔▔▔▔▔▔▔▔▔▏ ▕▔▔▔▔▔▔▔▔▔▏
 * ▕ FVTerm  ▏ ▕ FObject ▏
 * ▕▁▁▁▁▁▁▁▁▁▏ ▕▁▁▁▁▁▁▁▁▁▏
 *      ▲           ▲
 *      │           │
 *      └─────┬─────┘
 *            │
 *       ▕▔▔▔▔▔▔▔▔▔▏
 *       ▕ FWidget ▏
 *       ▕▁▁▁▁▁▁▁▁▁▏
 *            ▲
 *            │
 *      ▕▔▔▔▔▔▔▔▔▔▔▔▏
 *      ▕ FTextView ▏
 *      ▕▁▁▁▁▁▁▁▁▁▁▁▏
 */

#ifndef FTEXTVIEW_H
#define FTEXTVIEW_H

#if !defined (USE_FINAL_H) && !defined (COMPILE_FINAL_CUT)
  #error "Only <final/final.h> can be included directly."
#endif

#include <memory>
#include <vector>

#include "final/fapplication.h"
#include "final/fscrollbar.h"
#include "final/fstatusbar.h"
#include "final/fstring.h"
#include "final/fwidget.h"

namespace finalcut
{

//----------------------------------------------------------------------
// class FTextView
//----------------------------------------------------------------------

#pragma pack(push)
#pragma pack(1)

class FTextView : public FWidget
{
  public:
    // Using-declarations
    using FWidget::setGeometry;

    // Constructor
    explicit FTextView (FWidget* = nullptr);

    // Disable copy constructor
    FTextView (const FTextView&) = delete;

    // Destructor
    virtual ~FTextView();

    // Disable assignment operator (=)
    FTextView& operator = (const FTextView&) = delete;

    // Accessors
    virtual const char* getClassName() const override;
    std::size_t         getColumns() const;
    std::size_t         getRows() const;
    const FString       getText() const;
    const FStringList&  getLines() const;

    // Mutators
    virtual void        setGeometry ( const FPoint&, const FSize&
                                    , bool = true ) override;
    void                setText (const FString&);
    void                scrollToX (int);
    void                scrollToY (int);
    void                scrollTo (const FPoint&);
    void                scrollTo (int, int);
    void                scrollBy (int, int);

    // Methods
    virtual void        hide() override;
    template<typename T>
    void                append (const std::initializer_list<T>&);
    void                append (const FString&);
    template<typename T>
    void                insert (const std::initializer_list<T>&, int);
    void                insert (const FString&, int);
    void                replaceRange (const FString&, int, int);
    void                deleteRange (int, int);
    void                deleteLine (int);
    void                clear();

    // Event handlers
    virtual void        onKeyPress (FKeyEvent*) override;
    virtual void        onMouseDown (FMouseEvent*) override;
    virtual void        onMouseUp (FMouseEvent*) override;
    virtual void        onMouseMove (FMouseEvent*) override;
    virtual void        onWheel (FWheelEvent*) override;
    virtual void        onFocusIn (FFocusEvent*) override;
    virtual void        onFocusOut (FFocusEvent*) override;

  protected:
    // Method
    virtual void        adjustSize() override;

  private:
    // Typedef
    typedef std::shared_ptr<FScrollbar> FScrollbarPtr;
    typedef void (FTextView::*FTextViewCallback)(FWidget*, FDataPtr);

    // Accessors
    std::size_t         getTextHeight();
    std::size_t         getTextWidth();

    // Inquiry
    bool                isHorizontallyScrollable();
    bool                isVerticallyScrollable();

    // Methods
    void                init();
    void                initScrollbar ( FScrollbarPtr&
                                      , fc::orientation
                                      , FTextViewCallback );
    virtual void        draw() override;
    void                drawText();
    void                processChanged();

    // Callback methods
    void                cb_VBarChange (FWidget*, FDataPtr);
    void                cb_HBarChange (FWidget*, FDataPtr);

    // Data Members
    FStringList        data{};
    FScrollbarPtr      vbar{nullptr};
    FScrollbarPtr      hbar{nullptr};
    bool               update_scrollbar{true};
    int                xoffset{0};
    int                yoffset{0};
    int                nf_offset{0};
    std::size_t        maxLineWidth{0};
};
#pragma pack(pop)


// FListBox inline functions
//----------------------------------------------------------------------
inline const char* FTextView::getClassName() const
{ return "FTextView"; }

//----------------------------------------------------------------------
inline std::size_t FTextView::getColumns() const
{ return maxLineWidth; }

//----------------------------------------------------------------------
inline std::size_t FTextView::getRows() const
{ return std::size_t(data.size()); }

//----------------------------------------------------------------------
inline const FStringList& FTextView::getLines() const
{ return data; }

//----------------------------------------------------------------------
inline void FTextView::scrollTo (const FPoint& pos)
{ scrollTo(pos.getX(), pos.getY()); }

//----------------------------------------------------------------------
template<typename T>
void FTextView::append (const std::initializer_list<T>& list)
{
  for (auto& str : list)
    insert(str, -1);
}

//----------------------------------------------------------------------
template<typename T>
void FTextView::insert (const std::initializer_list<T>& list, int pos)
{
  for (auto& str : list)
  {
    insert(str, pos);
    pos++;
  }
}

//----------------------------------------------------------------------
inline void FTextView::deleteRange (int from, int to)
{ replaceRange (FString(), from, to); }

//----------------------------------------------------------------------
inline void FTextView::deleteLine (int pos)
{ deleteRange (pos, pos); }

//----------------------------------------------------------------------
inline bool FTextView::isHorizontallyScrollable()
{ return bool( maxLineWidth > getTextWidth() ); }

//----------------------------------------------------------------------
inline bool FTextView::isVerticallyScrollable()
{ return bool( getRows() > getTextHeight() ); }

}  // namespace finalcut

#endif  // FTEXTVIEW_H
