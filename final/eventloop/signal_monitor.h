/***********************************************************************
* signal_monitor.h - Signal monitoring object                          *
*                                                                      *
* This file is part of the FINAL CUT widget toolkit                    *
*                                                                      *
* Copyright 2023 Andreas Noe                                           *
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

/*  Inheritance diagram
 *  ═══════════════════
 *
 *      ▕▔▔▔▔▔▔▔▔▔▏
 *      ▕ Monitor ▏
 *      ▕▁▁▁▁▁▁▁▁▁▏
 *           ▲
 *           │
 *   ▕▔▔▔▔▔▔▔▔▔▔▔▔▔▔▔▏
 *   ▕ SignalMonitor ▏
 *   ▕▁▁▁▁▁▁▁▁▁▁▁▁▁▁▁▏
 */

#ifndef SIGNAL_MONITOR_H
#define SIGNAL_MONITOR_H

#include <array>
#include <map>
#include <memory>

#include "final/eventloop/monitor.h"
#include "final/util/fstring.h"

namespace finalcut
{

//----------------------------------------------------------------------
// class SignalMonitor
//----------------------------------------------------------------------

class SignalMonitor final : public Monitor
{
  public:
    explicit SignalMonitor(EventLoop*);

    // Disable default constructor
    SignalMonitor() = delete;

    // Disable copy constructor
    SignalMonitor(const SignalMonitor&) = delete;

    // Disable move constructor
    SignalMonitor(const SignalMonitor&&) = delete;

    // Destructor
    ~SignalMonitor() noexcept override;

    // Accessor
    auto getClassName() const -> FString;

    // Methods
    void init (int, handler_t, void*);
    void trigger (short) override;

  private:
    // class forward declaration
    class SigactionImpl;

    // Disable copy assignment operator (=)
    auto operator = (const SignalMonitor&) -> SignalMonitor& = delete;

    // Disable move assignment operator (=)
    auto operator = (SignalMonitor&&) noexcept -> SignalMonitor& = delete;

    // Methods
    static void onSignal (int);
    auto getSigactionImpl() const -> const SigactionImpl*;
    auto getSigactionImpl() -> SigactionImpl*;

    // Data members
    int signal_number{-1};
    std::array<int, 2> signal_pipe_fd{{-1, -1}};
    std::unique_ptr<SigactionImpl> impl;
};

// SignalMonitor inline functions
//----------------------------------------------------------------------
inline auto SignalMonitor::getClassName() const -> FString
{ return "SignalMonitor"; }

}  // namespace finalcut

#endif  // SIGNAL_MONITOR_H
