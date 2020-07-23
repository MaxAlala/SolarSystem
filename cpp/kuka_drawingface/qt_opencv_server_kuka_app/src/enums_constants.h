#ifndef ENUMS_CONSTANTS_H
#define ENUMS_CONSTANTS_H

/*!

    \brief the purpose of this enum is to clarify the names of two regimes
    \author Mx
    \version 1.0
    \date February 5, 2020
*/
enum CurrentRegime{
    TWO_ELEM_REGIME, ///< regime that has a set of straight lines at the output. A straight line can be described by two points.

    ALL_ELEM_REGIME ///< regime that has a set of curve lines at the output. A curve line can be described by many points and some equation.
};
#endif // ENUMS_CONSTANTS_H
