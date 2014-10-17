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
#include "roundrobin.h"


namespace nedges {
RoundRobin::RoundRobin(std::string _name, std::string date,PlayerListPtrType _player_list)
{

}

void ScheduleRoundRobin(int num_participants, int num_venues_available) {
    int num_matches = MatchesInRoundRobin(num_participants);
    int num_venues = num_venues_available;
    if (num_venues > (num_participants/2) ) {
        num_venues = num_participants / 2;
        std::cout << "There are " << num_venues_available - num_venues << " extra tables allocated" << std::endl;
    }
    int num_rounds = ceil((double) num_matches / num_venues);
    int nbyes = num_participants - (num_venues * 2);

    RRMatchupList rr_matchups;
    PossibleMatchups(num_participants, rr_matchups);

    std::cout << "There are " << num_matches << " matches with " << num_rounds
              << " rounds, and " << num_venues << " matches per round." << std::endl;
    std::cout << "In each round there are " << nbyes << " players with a bye." << std::endl;

    std::cout << "Here are all possible matchups" << std::endl;

    for (RRMatchupListIt rr_it = rr_matchups.begin(); rr_it!=rr_matchups.end(); ++rr_it)
        std::cout << "(" <<  rr_it->first << ", " << rr_it->second << "); ";
    std::cout << std::endl;

    if(num_matches != rr_matchups.size()) {
        std::cerr << "Error! matchups not the same as num_matches" << std::endl;
    }

}

int MatchesInRoundRobin(int num_participants) {
    return (num_participants * (num_participants - 1) /2);
}

int PossibleMatchups(int num_participants , RRMatchupList & rr_matchups) {
    for (int i = 1; i!=num_participants+1;++i)
       for (int j = i+1; j!=num_participants + 1; ++j )
    rr_matchups.push_back(std::make_pair(i,j));
}

}
