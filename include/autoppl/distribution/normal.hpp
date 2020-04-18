#pragma once
#include <math.h>

#include <cassert>
#include <cmath>
#include <numeric>
#include <random>

namespace ppl {

// TODO: change name to NormalDist and make class template.
// normal should be a function that creates this kind of object.

template <typename mean_type, typename var_type>
struct Normal {
    using value_t = double;
    using dist_value_t = double;

    static_assert(std::is_convertible_v<mean_type, value_t>);
    static_assert(std::is_convertible_v<var_type, value_t>);

    Normal(mean_type mean, var_type var)
        : mean_{mean}, var_{var} {
            assert(static_cast<value_t>(var_) > 0);
        };

    template <class GeneratorType>
    value_t sample(GeneratorType& gen) const {
        value_t mean, var;
        mean = static_cast<value_t>(mean_);
        var = static_cast<value_t>(var_);

        std::normal_distribution<value_t> dist(mean, var);
        return dist(gen);
    }

    dist_value_t pdf(value_t x) const {
        value_t mean, var;
        mean = static_cast<value_t>(mean_);
        var = static_cast<value_t>(var_);

        return std::exp(- 0.5 * std::pow(x - mean, 2) / var) / (std::sqrt(var * 2 * M_PI));
    }

    dist_value_t log_pdf(value_t x) const {
        value_t mean, var;
        mean = static_cast<value_t>(mean_);
        var = static_cast<value_t>(var_);

        return (-0.5 * std::pow(x - mean, 2) / var) - 0.5 * (std::log(var) + std::log(2) + std::log(M_PI));
    }

   private:
    mean_type mean_;
    var_type var_;
};

}  // namespace ppl
