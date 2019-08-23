//
//  Athlete.cpp
//  RPI_Decathlon
//
//  Created by Simon Hopkins on 8/23/19.
//  Copyright © 2019 Simon Hopkins. All rights reserved.
//

#include "Athlete.hpp"
#include <vector>
#include <cmath>
#include <iostream>

// Initialize
void Athlete::initialize() {
    event_100m.event::score = 0;
    event_100m.event::points = 0;
    event_100m.event::isTrack = true;
    event_400m.event::score = 0;
    event_400m.event::points = 0;
    event_400m.event::isTrack = true;
    event_1500m.event::score = 0;
    event_1500m.event::points = 0;
    event_1500m.event::isTrack = true;
    event_110mH.event::score = 0;
    event_110mH.event::points = 0;
    event_110mH.event::isTrack = true;
    event_LJ.event::score = 0;
    event_LJ.event::points = 0;
    event_LJ.event::isTrack = false;
    event_DT.event::score = 0;
    event_DT.event::points = 0;
    event_DT.event::isTrack = false;
    event_HJ.event::score = 0;
    event_HJ.event::points = 0;
    event_HJ.event::isTrack = false;
    event_PV.event::score = 0;
    event_PV.event::points = 0;
    event_PV.event::isTrack = false;
    event_SP.event::score = 0;
    event_SP.event::points = 0;
    event_SP.event::isTrack = false;
}


// Constructors
Athlete::Athlete() {
    initialize();
}
Athlete::Athlete(vector<string> athlete_data) {
    initialize();
    name_first = athlete_data[0];
    name_last = athlete_data[1];
    country = athlete_data[2];
    set_score_for_event(athlete_data[4], athlete_data[3]);
}

// Helper methods
int Athlete::calc_points_100m() {
    if (event_100m.event::score > 0) {
        return int(25.4347 * pow((18.0 - event_100m.event::score), 1.81));
    }
    return 0;
}
int Athlete::calc_points_LJ() {
    if (event_LJ.event::score > 0) {
        return int(0.14354 * pow(((event_LJ.event::score * 100) - 220), 1.4));
    }
    return 0;
}
int Athlete::calc_points_SP() {
    if (event_SP.event::score > 0) {
        return int(51.39 * pow((event_SP.event::score - 1.5), 1.05));
    }
    return 0;
}
int Athlete::calc_points_HJ() {
    if (event_HJ.event::score > 0) {
        return int(0.8465 * pow(((event_HJ.event::score * 100) - 75), 1.42));
    }
    return 0;
}
int Athlete::calc_points_400m() {
    if (event_400m.event::score > 0) {
        return int(1.53775 * pow((82 - event_400m.event::score), 1.81));
    }
    return 0;
}
int Athlete::calc_points_110mH() {
    if (event_110mH.event::score > 0) {
        return int(5.74352 * pow((28.5 - event_110mH.event::score), 1.92));
    }
    return 0;
}
int Athlete::calc_points_DT() {
    if (event_DT.event::score > 0) {
        return int(12.91 * pow((event_DT.event::score - 4), 1.1));
    }
    return 0;
}
int Athlete::calc_points_PV() {
    if (event_PV.event::score > 0) {
        return int(0.2797 * pow(((event_PV.event::score * 100) - 100), 1.35));
    }
    return 0;
}
int Athlete::calc_points_JT() {
    if (event_JT.event::score > 0) {
        return int(10.14 * pow((event_JT.event::score - 7), 1.08));
    }
    return 0;
}
int Athlete::calc_points_1500m() {
    if (event_1500m.event::score > 0) {
        return int(0.03768 * pow((480 - event_1500m.event::score), 1.85));
    }
    return 0;
}
void Athlete::update_total() {
    total_points = 0;
    total_points += event_100m.event::points;
    total_points += event_LJ.event::points;
    total_points += event_SP.event::points;
    total_points += event_HJ.event::points;
    total_points += event_400m.event::points;
    total_points += event_110mH.event::points;
    total_points += event_DT.event::points;
    total_points += event_PV.event::points;
    total_points += event_JT.event::points;
    total_points += event_1500m.event::points;
}



// Getters
string Athlete::get_full_name() {
    return name_first + " " + name_last;
}
string Athlete::get_first_name() {
    return name_first;
}
string Athlete::get_last_name() {
    return name_last;
}
string Athlete::get_country() {
    return country;
}
int Athlete::get_total_points() {
    return total_points;
}


// Setters
void Athlete::set_first_name(string name) {
    name_first = name;
}
void Athlete::set_last_name(string name) {
    name_last = name;
}
void Athlete::set_country(string name) {
    country = name;
}
void Athlete::set_score_for_event(string event, string result) {
    if (event.compare("100_METERS") == 0) {
        event_100m.event::score = stod(result);
        event_100m.event::points = calc_points_100m();
    } else if (event.compare("LONG_JUMP") == 0) {
        event_LJ.event::score = stod(result);
        event_LJ.event::points = calc_points_LJ();
    } else if (event.compare("SHOT_PUT") == 0) {
        event_SP.event::score = stod(result);
        event_SP.event::points = calc_points_SP();
    } else if (event.compare("HIGH_JUMP") == 0) {
        event_HJ.event::score = stod(result);
        event_HJ.event::points = calc_points_HJ();
    } else if (event.compare("400_METERS") == 0) {
        event_400m.event::score = stod(result);
        event_400m.event::points = calc_points_400m();
    } else if (event.compare("110_METERS_HURDLES") == 0) {
        event_110mH.event::score = stod(result);
        event_110mH.event::points = calc_points_110mH();
    } else if (event.compare("DISCUS_THROW") == 0) {
        event_DT.event::score = stod(result);
        event_DT.event::points = calc_points_DT();
    } else if (event.compare("POLE_VAULT") == 0) {
        event_PV.event::score = stod(result);
        event_PV.event::points = calc_points_PV();
    } else if (event.compare("JAVELIN_THROW") == 0) {
        event_JT.event::score = stod(result);
        event_JT.event::points = calc_points_JT();
    } else if (event.compare("1500_METERS") == 0) {
        string minutes_string = result.substr(0, result.find(":"));
        string seconds_string = result.substr(result.find(":") + 1);
        
        int minutes = stoi(minutes_string);
        double seconds = stod(seconds_string);
        
        event_1500m.event::score = (minutes * 60.0) + seconds;
        event_1500m.event::points = calc_points_1500m();
    } else {
        throw invalid_argument("Unknown event:" + event);
    }
    
    // And update total
    update_total();
}

double Athlete::get_score_for_event(string event) {
    if (event.compare("100_METERS") == 0) {
        return event_100m.event::score;
    } else if (event.compare("LONG_JUMP") == 0) {
        return event_LJ.event::score;
    } else if (event.compare("SHOT_PUT") == 0) {
        return event_SP.event::score;
    } else if (event.compare("HIGH_JUMP") == 0) {
        return event_HJ.event::score;
    } else if (event.compare("400_METERS") == 0) {
        return event_400m.event::score;
    } else if (event.compare("110_METERS_HURDLES") == 0) {
        return event_110mH.event::score;
    } else if (event.compare("DISCUS_THROW") == 0) {
        return event_DT.event::score;
    } else if (event.compare("POLE_VAULT") == 0) {
        return event_PV.event::score;
    } else if (event.compare("JAVELIN_THROW") == 0) {
        return event_JT.event::score;
    } else if (event.compare("1500_METERS") == 0) {
        return event_1500m.event::score;
    } else {
        throw invalid_argument("Unknown event:" + event);
    }
}
int Athlete::get_points_for_event(string event) {
    if (event.compare("100_METERS") == 0) {
        return event_100m.event::points;
    } else if (event.compare("LONG_JUMP") == 0) {
        return event_LJ.event::points;
    } else if (event.compare("SHOT_PUT") == 0) {
        return event_SP.event::points;
    } else if (event.compare("HIGH_JUMP") == 0) {
        return event_HJ.event::points;
    } else if (event.compare("400_METERS") == 0) {
        return event_400m.event::points;
    } else if (event.compare("110_METERS_HURDLES") == 0) {
        return event_110mH.event::points;
    } else if (event.compare("DISCUS_THROW") == 0) {
        return event_DT.event::points;
    } else if (event.compare("POLE_VAULT") == 0) {
        return event_PV.event::points;
    } else if (event.compare("JAVELIN_THROW") == 0) {
        return event_JT.event::points;
    } else if (event.compare("1500_METERS") == 0) {
        return event_1500m.event::points;
    } else {
        throw invalid_argument("Unknown event:" + event);
    }
}

int Athlete::get_avg_points_for_area(bool isTrack) {
    int area_points = 0;
    int area_events = 0;
    if (isTrack) {
        area_points += event_100m.event::points;
        area_points += event_400m.event::points;
        area_points += event_1500m.event::points;
        area_points += event_110mH.event::points;
        if (event_100m.event::points > 0) {
            area_events += 1;
        } else if (event_400m.event::points > 0) {
            area_events += 1;
        } else if (event_1500m.event::points > 0) {
            area_events += 1;
        } else if (event_110mH.event::points > 0) {
            area_events += 1;
        }
    } else {
        area_points += event_LJ.event::points;
        area_points += event_SP.event::points;
        area_points += event_HJ.event::points;
        area_points += event_DT.event::points;
        area_points += event_PV.event::points;
        area_points += event_JT.event::points;
        if (event_LJ.event::points > 0) {
            area_events += 1;
        } else if (event_SP.event::points > 0) {
            area_events += 1;
        } else if (event_HJ.event::points > 0) {
            area_events += 1;
        } else if (event_DT.event::points > 0) {
            area_events += 1;
        } else if (event_PV.event::points > 0) {
            area_events += 1;
        } else if (event_JT.event::points > 0) {
            area_events += 1;
        }
    }
    
    if (area_events > 0) {
        return area_points / area_events;
    } else {
        return 0;
    }

}


