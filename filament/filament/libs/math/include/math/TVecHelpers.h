#pragma once

#include <math.h>
#include <stdint.h>
#include <sys/types.h>

#include <cmath>
#include <functional>
#include <limits>
#include <iostream>

#include <math/compiler.h>


namespace math {
    namespace details {
        /**
         * No user serviceable parts here.
         * Don't use this file directly, instead include math/vec{2/3/4}.h
         */

        /**
         * TVec{Add/Product}Operators implements basic arithmetic and basic compound assigments
         * operators on a vector of type BASE<T>.
         * 
         * BASE only needs to implement operator[] and size().
         * By simply inheriting from TVec{Add|Product}Operators<BASE, T> BASE will automatically
         * get all the functionality here.
         *
         */

        template <template<typename T> class VECTOR, typename T>
        class TVecAddOperators {
            public:
            /** compound assignment from a another vector of the same size but different
             * element type.
             */
            template<typename OTHER>
            constexpr VECTOR<T>& operator +=(const VECTOR<OTHER>& v) {
                
            }

        }     
    } // details
} // math



