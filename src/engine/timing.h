/***************************************************************************
 *   fheroes2: https://github.com/ihhub/fheroes2                           *
 *   Copyright (C) 2021 - 2022                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#pragma once

#include <chrono>
#include <cstdint>

namespace fheroes2
{
    // IMPORTANT!!! According to https://en.cppreference.com/w/cpp/chrono/high_resolution_clock we should never use high_resolution_clock for time internal measurements
    // because for high_resolution_clock the time may go backwards.

    class Time
    {
    public:
        Time();

        void reset();

        // Returns time in seconds.
        double getS() const;

        // Returns rounded time in milliseconds.
        uint64_t getMs() const;

    private:
        std::chrono::time_point<std::chrono::steady_clock> _startTime;
    };

    class TimeDelay
    {
    public:
        TimeDelay() = delete;

        explicit TimeDelay( const uint64_t delayMs );

        void setDelay( const uint64_t delayMs );

        uint64_t getDelay() const
        {
            return _delayMs;
        }

        bool isPassed() const;
        bool isPassed( const uint64_t delayMs ) const;

        // Reset delay by starting the count from the current time.
        void reset();

        // Explicitly set delay to passed state. Can be used in cases when first call of isPassed() must return true.
        void pass();

    private:
        std::chrono::time_point<std::chrono::steady_clock> _prevTime;
        uint64_t _delayMs;
    };

    void delayforMs( const uint32_t delayMs );
}
