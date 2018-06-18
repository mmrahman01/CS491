/*
--- Collaborative filtering----

1. M x N matrix.
2.Determine similarity between users.
(Correlation coefficient and Vector Space (Cosine Similarity)

3.R'ut + ( Total Wu, ut (Ru(o) - R'u) / (Total |Wa, Ut|
                        How to from here
4.Train Data, Each user, add non zero divide by number of non zero to get avg.
5.Subtract the avg from each ranking to get bias out.
6.Multiply User1 and Test1 (each column and total it) .. A
7.Square Columns in User1, add it and then square root (for each user)..B
8.Square Columns in Test1, add and then take square root............C
9.D = A /(B * C) (Do this for each Users)
10. E = Test Avg + (( D * User1 Particular Column) +  (D another user * That user column))
            / (Abs D of users (summation))

*/

#include "recon.h"

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <map>
#include <cmath>
#include<stdlib.h>

using namespace std;

int main()
{
    char answer = 'y';
    recon user;  // declare a class variable.
    user.infile.open("ratings.txt");// the data is coming from this file
     user.read_data(); // read the ranked data;
    //user.prints_two_data(user.user_review);

    while (answer !='q'){

    cout << "This Program Suggests movie for individual users.\n" << endl;
    cout<<"Enter User Number as a Test Case :"; // we will use a user as a test
    cin>> user.user_number;
    if ((user.user_number > 200)|| (user.user_number<1))
    {
        cout<<"Please enter a value from 1 to 200 :";
        cin>>user.user_number;
        if ((user.user_number > 200)|| (user.user_number<1))
           {
            system("cls");
            cout<<"BYE"<<endl;
            return -1;
           }
    }

    user.user_number -=1; // just for display purposes.




    for (int i=0; i<1000; i++){
        user.test_user.push_back(user.user_review.at(user.user_number)[i]);
    }

    for (int i=0; i<1000; i++){
        if (user.test_user[i]>0){
        cout<<"Movie Number :" <<i<<"  "<<user.test_user[i]<< endl ;
        }
            }
    cout<<endl;



    cout<<"Enter a movie number for testing from above list :";
    cin>>user.user_number_rank;
    cout<<endl;
  //  cout<<"User number:"<<user.user_number+1<<"   "<<"Movie Number:"<<user.user_number_rank;
   // cout<<"   Rank:"<<user.user_review[user.user_number][user.user_number_rank]<<endl;
    user.get_average();
    //user.print_one_data(user.average);
    user.unbiased_data();
    //user.print_two_data(user.unbiased);

    user.multiply();
    //user.print_two_data(user.t1_times_t2);
    user.squared();
    system("cls");
    user.calculate();

    user.calc_idf();


    user.calc_second();
    user.sorted();

/*
    //sort(user.D.begin(),user.D.end());
   //*******************************************
  for (int i =0; i < 200; i++){
        cout<<"Similarity  "<<i<<"  " <<user.cos_sim[i]<<endl;
         }

        for (int i =0; i < 200; i++){
        cout<<"Sim  "<<user.cosine_rank[i].first<<"  "<<user.cosine_rank[i].second<<" "<<endl;
        if (user.user_review[i][user.user_number_rank]!=0){
        cout<<user.user_review[i][user.user_number_rank]<<endl;
        }
         }

*/

    //cout<<user.test_user[user.user_number_rank]<<endl;
    user.recommended_rank();
   // user.modified_Rank();
    user.recommended_rank2();
   // cout<<user.D.size()<<endl;

    // clear everything to recalculate a different user and rank
    user.D.clear();
    user.idf.clear();
    user.tf_idf.clear();
    user.average.clear();
    user.unbiased.clear();
    user.t1_times_t2.clear();
    user.sq_root.clear();
    user.test_user.clear();
    cout<<"\nContinue? (Enter q to quit): ";
    cin>>answer;
    }

    user.infile.close();
    return 0;
}









