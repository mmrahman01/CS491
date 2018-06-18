#ifndef RECON_H
#define RECON_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <cmath>

using std::vector;

class recon
{
    public:
    recon();
    std::  vector < vector<int> > user_review; // will hold the user rank for movies
    std:: vector <float> average; // holds average of each users rank
    std:: vector < vector<float> >unbiased;// subtract average from each rank, unbiased
    std:: vector < vector<float> >t1_times_t2; // t1 = training, t2 = testing data;...A
    std:: vector <float> sq_root; // summation of unbiased square then take root....B, C here
    std:: vector <float> D; //D = A /(B * C)
    //std:: vector <float> E; //E = Test Avg + (( D * User1 Particular Column) +
                            //(D another user * That user column)) / (Abs D of users (summation))
    std:: vector< vector< float> >idf;
    std:: vector< vector<float> >tf_idf;
    std:: vector<float>length;
    vector<int> test_user;
    vector<std::pair <float,int> >cosine_rank;
    std:: vector<float>cos_sim;

    std::ifstream infile; // the datafile
    int data;               // actual data
    float A=0.0;
    int user_number=0;
    int user_number_rank =0;

//reads the data and holds it in a global variable
    void read_data ();
// next four functions to print data on screen, to see progress and calculations
    void print_two_data (vector < vector<float> > two_dt);
    void prints_two_data (vector < vector<int> > two_dt);
    void print_one_data (vector <float> one_dt);
    void prints_one_data (vector <int> one_dt);
// calculated idf, tf* idf
    void calc_idf();
// average each users rank
    void get_average ();
// subtract average and gets unbiased data / rank from users
    void unbiased_data();
//  next three functions implements the vector space model and recommends data
    void multiply();
    void squared();
    void calculate();
    void recommended_rank();
// recommend rank2 uses a different approach, it takes only the user > 0.001 in cosine similarity
    void recommended_rank2();
    void sorted ();
// few other ways we experimented, the function results are not displayed to the professor
//just to show what else we have tried
    void modified_Rank();
    void calc_second();
    protected:

    private:
};

#endif // RECON_H










