/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "Wish you LOTS of nedges (Nets and Edges)!!."                        *
 *                                          -- Wayne Carney, Ray Mack     *
 *   Author: Burair Kothari, 2014                                         *
 *                Genesee Valley Table Tennis CLub                        *
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

#include <string>
#include <vector>
#include "boost/shared_ptr.hpp"
#include "boost/make_shared.hpp"

namespace nedges {
/*!
 * \brief The Player class
 */

typedef std::vector<std::pair<std::string,std::string> > player_identifiers;

class Player {
public:

    /*!
     * \brief Player
     * Constructor with parameters
     * \param _name
     * \param _place
     */

    Player (std::string _name="", char _gender='\0', std::string _place_type="", std::string _place=""):name(_name), gender(_gender) {
       identifiers.push_back(std::make_pair(_place_type,_place));
    }

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
    void addId(std::string const & _ident_type, std::string const &_ident) {
      identifiers.push_back(std::make_pair(_ident_type,_ident));
    }

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

    player_identifiers const & getIdentifiers() const {
        return identifiers;
    }

    char const getGender() const;

private:
    /*!
     * \brief name
     * Full name of Player. Last Name, First Name (optional Middle Name or initial)
     */

    std::string name;

    /*!
     * \brief identifiers
     * The identifiers associated with the player. National/International Organizations, Clubs, Locations: i.e. cities, states, countries etc
     * in pairs indicating type and value: i.e. A player with a USATT membership, ITTF rating, Ratings Central rating, a member of the clubs GVTTC and MVTTC,
     * residing in Rochester, NY USA would have:
     * org,USATT;org,ITTF;org,Ratings Central;club,GVTTC;club,MVTTC;city,Rochester;state,NY;country,USA
     */
    player_identifiers identifiers;

    /*!
     * \brief gender
     *
     * 'M' or 'm' = male; 'F' or 'f' = female;
     */

    char gender;

};

/*!
 * \brief PlayerPtr
 */
typedef boost::shared_ptr<Player> PlayerPtr;
/*!
 * \brief PlayerListType
 */
typedef std::vector<PlayerPtr> PlayerListType;
typedef boost::shared_ptr<PlayerListType> PlayerListPtrType;


} // namespace nedges
#endif // NEDGES_PLAYER_H
