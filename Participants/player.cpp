/*!************************************************************************
 *   This file is part of Nedges.                                         *
 *   A table tennis club, league and tournament management package.       *
 *                                                                        *
 *   "Wish you LOTS of nedges (Nets and Edges)."                          *
 *                                      -- Wayne Carney, Ray Mack         *
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

#include "player.h"

namespace nedges {

void Player::setName(const std::string & _name) {
    name =_name;
    return;
}

void Player::setGender(char const _gender) {
    if ((_gender == 'M') || (_gender == 'm')) {
        gender = 'M';
    } else if ((_gender == 'F') || (_gender == 'f')) {
        gender = 'F';
    } else gender ='\0';
    return;
}

char const Player::getGender() const {
    if ((gender == 'M') || (gender == 'm')) {
        return 'M';
    } else if ((gender == 'F') || (gender == 'f')) {
        return 'F';
    } else return '\0';
}

} // namespace nedges
