//
//  Athlete.hpp
//  RPI_Decathlon
//
//  Created by Simon Hopkins on 8/23/19.
//  Copyright © 2019 Simon Hopkins. All rights reserved.
//

#ifndef Athlete_hpp
#define Athlete_hpp

#include <stdio.h>
#include <string>
using namespace std;

class Athlete
{
    struct event {
        bool isTrack;
        double score;
        int points;
    };
    
private:
    string name_first;
    string name_last;
    string country;
    int total_points;
    event event_100m;
    event event_LJ;
    event event_SP;
    event event_HJ;
    event event_400m;
    event event_110mH;
    event event_DT;
    event event_PV;
    event event_JT;
    event event_1500m;
    int calc_points_100m();
    int calc_points_LJ();
    int calc_points_SP();
    int calc_points_HJ();
    int calc_points_400m();
    int calc_points_110mH();
    int calc_points_DT();
    int calc_points_PV();
    int calc_points_JT();
    int calc_points_1500m();
    void update_total();
    void initialize();
public:
    Athlete();
    Athlete(vector<string> athlete_data);
    string get_full_name();
    string get_first_name();
    string get_last_name();
    string get_country();
    int get_total_points();
    void set_first_name(string name);
    void set_last_name(string name);
    void set_country(string name);
    void set_score_for_event(string event, string result);
    double get_score_for_event(string event);
    int get_points_for_event(string event);
    int get_avg_points_for_area(bool isTrack);
    
    
};
#endif /* Athlete_hpp */
