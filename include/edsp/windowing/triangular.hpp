/*
 * eDSP, A cross-platform Digital Signal Processing library written in modern C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi, All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along width
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * File: triangular.hpp
 * Author: Mohammed Boujemaoui
 * Date: 27/7/2018
 */
#ifndef EDSP_TRIANGULAR_HPP
#define EDSP_TRIANGULAR_HPP

#include <edsp/math/numeric.hpp>
#include <edsp/meta/iterator.hpp>
#include <cmath>

namespace edsp { namespace windowing {

    /**
     * @brief Computes a triangular window of length N and stores the result in the range, beginning at d_first.
     *
     * Triangular windows are defined as:
     *
     * \f[
     *  w(n)=1-\left|{\frac {n-{\frac {N-1}{2}}}{\frac {L}{2}}}\right|
     * \f]
     *
     * @param first Input iterator defining the beginning of the output range.
     * @param last Input iterator defining the ending of the output range.
     */
    template <typename OutputIt>
    constexpr void triangular(OutputIt first, OutputIt last) {
        using value_type     = meta::value_type_t<OutputIt>;
        using size_type      = meta::diff_type_t<OutputIt>;
        const auto size      = static_cast<size_type>(std::distance(first, last));
        const value_type rem = size + std::remainder(size, 2);
        value_type initial   = -(size - 1);
        for (size_type i = 0; i < size; ++i, ++first) {
            *first = 1 - std::abs(initial / rem);
            initial += 2;
        }
    }

}} // namespace edsp::windowing

#endif // EDSP_TRIANGULAR_HPP
