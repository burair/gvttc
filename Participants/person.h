/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "May your game be full of nedges (Nets and Edges).                   *
 *                                                -- Ray Mack             *
 *   Author: Burair Kothari 2014                                          *
 *                Genesee Valley Table Tennis CLub 2014                   *
 *                http://www.gvttc.com                                    *
 *                                                                        *
 *                                                                        *
 *   Nedges is free software: you can redistribute it and/or modify       *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation, either version 3 of the License, or    *
 *   (at your option) any later version.                                  *
 *                                                                        *
 *   Nedges is distributed in the hope that it will be useful,            *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 *   GNU General Public License for more details.                         *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with Nedges.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                        *
 **************************************************************************/
#ifndef PERSON_H
#define PERSON_H

#include <string>

namespace nedges {

/*!
 * \brief The Person class
 *
 * Abstract base structure for storing information about someone affiliated with table tennis.
 *
 */

class Person {

public:

    virtual ~Person() {}

    /*!
     * \brief setName
     * set the name of the person
     *
     * \param _name
     * Full name of the person
     */
    virtual void setName(std::string const &_name)=0;

    /*!
     * \brief setPlace
     * set the place the person comes from or belongs to (club, locality, organization etc.)
     *
     * \param _place
     */
    virtual void setPlace(std::string const &_place)=0;
};


}

#endif // PERSON_H
