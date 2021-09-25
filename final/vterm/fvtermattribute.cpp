/***********************************************************************
* fvtermattribute.cpp - [brief description]                                 *
*                                                                      *
* This file is part of the FINAL CUT widget toolkit                    *
*                                                                      *
* Copyright [year] [Maintainer]                                        *
*                                                                      *
* FINAL CUT is free software; you can redistribute it and/or modify    *
* it under the terms of the GNU Lesser General Public License as       *
* published by the Free Software Foundation; either version 3 of       *
* the License, or (at your option) any later version.                  *
*                                                                      *
* FINAL CUT is distributed in the hope that it will be useful, but     *
* WITHOUT ANY WARRANTY; without even the implied warranty of           *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
* GNU Lesser General Public License for more details.                  *
*                                                                      *
* You should have received a copy of the GNU Lesser General Public     *
* License along with this program.  If not, see                        *
* <http://www.gnu.org/licenses/>.                                      *
***********************************************************************/

#include "final/vterm/fvtermattribute.h"

namespace finalcut
{

// static class attributes
FChar FVTermAttribute::next_attribute{};

//----------------------------------------------------------------------
// class FVTermAttribute
//----------------------------------------------------------------------

// constructors and destructor
//----------------------------------------------------------------------
FVTermAttribute::FVTermAttribute() = default;  // constructor

//----------------------------------------------------------------------
FVTermAttribute::~FVTermAttribute() noexcept = default;  // destructor


// public methods of FVTermAttribute
//----------------------------------------------------------------------
void FVTermAttribute::initAttribute()
{
  // next_attribute contains the state of the next printed character
  next_attribute.ch           = {{ L'\0' }};
  next_attribute.fg_color     = FColor::Default;
  next_attribute.bg_color     = FColor::Default;
  next_attribute.attr.byte[0] = 0;
  next_attribute.attr.byte[1] = 0;
  next_attribute.attr.byte[2] = 0;
  next_attribute.attr.byte[3] = 0;
}

}  // namespace finalcut