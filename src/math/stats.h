//
// Created by Mohammed Boujemaoui on 09/10/2017.
//

#ifndef EDSP_STATS_H
#define EDSP_STATS_H

#include "config.h"
#include "math_util.h"
#include "container.h"

#include <unordered_map>
EDSP_BEGING_NAMESPACE
namespace Math {
    namespace Stat {

        template<typename T>
        constexpr T mode(const std::vector<T>& container) {
            typedef std::unordered_map<T,unsigned int> Map;
            Map counts;
            for (size_t i = 0, size = container.size(); i < size; ++i) {
                typename Map::iterator it(counts.find(container[i]));
                (it != counts.end()) ? it->second++ : counts[container[i]] = 1;
            }

            const typename Map::const_iterator pr = std::max_element(
                    counts.begin(),
                    counts.end(),
                    [] (const typename Map::value_type& p1,
                        const typename Map::value_type& p2) {
                        return  p1.second < p2.second;
                    });
            return pr->first;
        }

        template<typename T>
        constexpr T mean(const std::vector<T>& container) {
            return  Container::sum(container) / static_cast<T> (container.size());
        }

        template<typename T>
        constexpr T variance(const std::vector<T>& container) {
            return  (Container::sum_squares(container) - Util::square<T>(Container::sum(container))
                                                          / static_cast<T>(container.size()));
        }

        template<typename T>
        constexpr T standar_desviation(const std::vector<T>& container) {
            return static_cast<T>(std::sqrt(variance(container)));
        }

        template<typename T>
        constexpr T mean_error(const std::vector<T>& container) {
            return std::sqrt(variance(container) / static_cast<T>(container.size()));
        }

        template<typename T>
        constexpr T root_mean_square(const std::vector<T>& container) {
            return static_cast<T>(std::sqrt(mean(container)));
        }

        template<typename T>
        constexpr T median(const std::vector<T>& container) {
            std::vector<T> tmp(container);
            std::sort(tmp.begin(), tmp.end());
            const size_t size = tmp.size();
            return (Util::isOdd(size))  ? (tmp[uint(size/2 - 1)] + tmp[uint(size/2)]) / 2
                                  : tmp[uint(size/2)];
        }

    }
}
EDSP_END_NAMESPCE
#endif //EDSP_STATS_H
