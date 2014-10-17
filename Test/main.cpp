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
#include <iostream>
#include "Participants/player.h"
#include "Events/roundrobin.h"

using namespace std;

int main()
{
    nedges::Player team1_p1("Burair Kothari",'M',"GVTTC");

    nedges::Player team5_p2 = team1_p1;

    std::string myname(team5_p2.getName());

    nedges::Player team6_p3(team5_p2);

    std::string myname2 = team6_p3.getName();

    char mygender = team5_p2.getGender();

    char mygender2 = team6_p3.getGender();

    cout << "Hello " << myname << " " << mygender <<  "! " << endl;
    cout << "Hello " << myname2 << " " <<  mygender2 << "! " <<  endl;


    nedges::ScheduleRoundRobin(15,8);
    return 0;
}

