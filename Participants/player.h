/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "Wish you LOTS of nedges (Nets and Edges)!!."                        *
 *                                          -- Wayne Carney, Ray Mack     *
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
#ifndef NEDGES_PLAYER_H
#define NEDGES_PLAYER_H

#include "person.h"

namespace nedges {
/*!
 * \brief The Player class
 */

class Player: public Person {
public:

    /*!
     * \brief Player
     * Constructor with parameters
     * \param _name
     * \param _place
     */

    Player (std::string _name="", char _gender='\0', std::string _place=""):name(_name), gender(_gender), place(_place) {}

    /*!
     * Using the compiler generated copy constructor and assignment operator is fine here for
     * a class with simple data member types (std::string).
     */

    /*!
     * \brief setName
     * \param _name
     */
    void setName(std::string const &_name);

    /*!
     * \brief setPlace
     * \param _place
     */
    void setPlace(std::string const &_place);

    /*!
     * \brief setGender
     * \param _gender
     */
    void setGender(char const _gender);
    /*!
     * \brief getName
     * \return
     * Player name
     */
    std::string const & getName() const {
        return name;
    }

    /*!
     * \brief getPlace
     * \return
     * Player place
     */

    std::string const & getPlace() const {
        return place;
    }

    char const getGender() const;

private:
    /*!
     * \brief name
     * Full name of Player
     */

    std::string name;

    /*!
     * \brief place
     * The place a player is identified with e.g. club, city, state etc.
     */
    std::string place;

    /*!
     * \brief gender
     *
     * 'M' or 'm' = male; 'F' or 'f' = female;
     */

    char gender;

};

} // namespace nedges
#endif // NEDGES_PLAYER_H
