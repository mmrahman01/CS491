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

using namespace std;
//using std::vector;
    recon::recon(){
    }

    void recon :: read_data (){
     vector<int> temp; // get the temp data;

    for (int i =1; i <=200; i++){  // we know the number of users is 200, make robust??

        for (int j= 0; j< 1000; j++){ // we know the number of reviews are 1000,
            infile>>data;               // reads each review
            temp.push_back(data);       // make a row of reviews
        }

            user_review.push_back(temp); // holds entire review set for one user (data)
            temp.clear();
        }
    }

    void recon::print_two_data (vector < vector<float> > two_dt){

    int counter= 1;
    cout<<"User "<<counter++<<endl;
    for (int i =0; i <200; i++){
        for (int j= 0; j< 1000; j++){

            cout<<two_dt[i][j]<< "   ";
        }

           cout <<endl;
           if(counter <= 200)
           cout<<"User "<<counter++<<endl;
    }

}
    void recon::prints_two_data (vector < vector<int> > two_dt){

    int counter= 1;
    cout<<"User "<<counter++<<endl;
    for (int i =0; i <200; i++){
        for (int j= 0; j< 1000; j++){

            cout<<two_dt[i][j]<< "   ";
        }

           cout <<endl;
           if(counter <= 200)
           cout<<"User "<<counter++<<endl;
    }

}

void recon:: print_one_data (vector <float> one_dt){
    int counter = 1;

    for (int i =0; i <200; i++){
        cout<<"User "<<counter++<<" "<<one_dt[i]<<"  "<<endl;
    }
    cout<<endl;
}

void recon:: prints_one_data (vector <int> one_dt){
    int counter = 1;

    for (int i =0; i <1000; i++){
        //cout<<"User "<<counter++<<" ";
        if(one_dt[i]>0)
        {cout<<i<<"  "<<one_dt[i]<<"  "<<endl;}
    }
    cout<<endl;
}

void recon:: get_average (){
    int counter =0;
    float total = 0.0;
    float avg = 0.0;

    for(int i =0; i < 200; i ++){
        for (int j =0; j< 1000; j++){
            total = total + user_review[i][j];
            if (user_review[i][j] > 0){
                    counter++;}
        }
        avg = total/counter;
        average.push_back(avg);
        counter =0;
        total = 0.0;
        avg =0.0;
    }

}

void recon:: unbiased_data(){
    vector<float> temp;
    float dt = 0.0;
    for(int i =0; i < 200; i ++){
        for (int j =0; j< 1000; j++){
             temp.push_back(dt);
            }
            unbiased.push_back(temp);
        }

     for(int i =0; i < 200; i ++){
        for (int j =0; j< 1000; j++){
             if (user_review[i][j] > 0){
                unbiased[i][j] = user_review[i][j] - average[i];
            }
        }

    }

}

void recon:: multiply(){
    vector<float> temp;
    float multi = 0.0;

    for (int i =0; i < 200; i++){
        for (int j =0; j < 1000; j++){
             if ((i == user_number)&& (j == user_number_rank)){
            multi = 0.0;
             }
             else{
            multi = unbiased[i][j]* unbiased.at(user_number)[j];
             }
            temp.push_back(multi);
            multi = 0.0;
             }

        t1_times_t2.push_back(temp);
        temp.clear();
    }

}

void recon::squared(){

        float sq = 0.0;
        float sum = 0.0;
    for (int i =0; i < 200; i++){
        for (int j =0; j < 1000; j++){
        sum = sum+ user_review[i][j] * user_review[i][j];
        }
        sq=sqrt(sum);
        sq_root.push_back(sq);
        sum =0.0;
        sq=0.0;
    }

}

void recon::calculate(){
        vector <float> sum;
        float temp =0.0;
        for (int i =0; i< 200; i++){
            for (int j =0; j < 1000; j++){
                temp = t1_times_t2[i][j]+ temp;
            }
            sum.push_back(temp);
            temp = 0.0;
        }
        temp = 0.0;
    for (int i = 0; i < 200; i++){
          temp = sum[i] / (sq_root[i]* sq_root[user_number]);
            D.push_back(temp);
            temp =0.0;

    }
}

void recon:: sorted(){

    for (int i =0; i <200; i++){
        cosine_rank.push_back(make_pair(cos_sim[i],i));
    }
    sort(cosine_rank.begin(),cosine_rank.end());
}


void recon::recommended_rank(){

    // E = Test Avg + (( D * User1 Particular Column) +  (D another user * That user column))
    //        / (Abs D of users (summation))


    float E=0.0;
    float num = 0.0;
    float denom = 0.0;

       for (int i =0; i < 200; i++){
            num = num + D.at(i) * unbiased.at(i)[user_number_rank];
            denom = denom + abs (D.at(i));
           }
         num = num - D.at(user_number) * unbiased.at(user_number )[user_number_rank];
    E = average.at(user_number) + (num / denom );

    cout<< "Calculated Rank is: "<<round(E)<<endl;

}

void recon::modified_Rank(){
    float sim =0.0;
    float diff =0.0;
    float result =0.0;
    int count_sim=0, count_diff =0, sim_a =0, sim_b =0, rev1=0, rev2=0;
    int temp =0;


    for (int i =0; i < 200; i++){
    if(D[i]> 0){
            sim = sim + unbiased.at(i)[user_number_rank];
            sim_a = sim_a + user_review[i][user_number_rank];
            if (user_review[i][user_number_rank]> 0){rev1++;}

            if (unbiased.at(i)[user_number_rank]> 0){count_sim++;}
           }
         else
         {
             diff = diff+ unbiased.at(i)[user_number_rank];
             if (unbiased.at(i)[user_number_rank]!= 0){count_diff++;}

             temp = user_review[i][user_number_rank];
             switch (temp){
             case 1: temp =5; break;
             case 2: temp =4;break;
             case 3: temp =3;break;
             case 4: temp =2;break;
             case 5: temp =1;break;
             default: temp =0;break;
             }
             sim_b = sim_b+temp;
             if (user_review[i][user_number_rank]!= 0){rev2++;}

         }

    }

        sim = sim / count_sim;
        diff = diff / count_diff;
        if (diff <=1.0) {diff = 5.0;}
        else if  ((diff > 1.0)&& (diff <= 2.0)) {diff = 4.0;}
        else if  ((diff > 2.0)&& (diff <= 3.0)) {diff = 3.0;}
        else if  ((diff > 3.0)&& (diff <= 4.0)) {diff = diff + 2.0;}
        else if  ((diff > 4.0)&& (diff <= 5.0)) {diff = diff + 1.0;}
        else  {diff =0.0;}


    result = (sim + diff) / 2.0;

    cout<<"Modified Rank1: "<<round(sim)<<endl;
    cout<<"Modified Rank2: "<<round(result)<<endl;

     sim =0.0;
     count_sim =0;
     if(rev1 ==0) rev1 =1;
     if (rev2 ==0)rev2= 1;
     sim = ((sim_a / rev1) + (sim_b / rev2)) / 2;
     cout<<"Modified Rank3: "<<round(sim)<<endl;



}



void recon::recommended_rank2(){

    // E = Test Avg + (( D * User1 Particular Column) +  (D another user * That user column))
    //        / (Abs D of users (summation))


    float F=0.0;
    float num = 0.0;
    float denom = 0.0;

    for (int i =0; i < 200; i++){
            if (cos_sim[i]>0.0001){
            num = num + cos_sim[i] * unbiased[i][user_number_rank];
            denom = denom + abs (cos_sim[i]);
         }
    }
     num = num - cos_sim.at(user_number) * unbiased.at(user_number )[user_number_rank];
    F = average.at(user_number) + (num / denom );

    cout<< "Modified Rank: "<<round(F)<<endl;
    //cout<< "Ca : "<<D.at(1)<< "  "<<unbiased.at(1)[user_number_rank]<<endl;

}


void recon::calc_idf(){
int count1=0;
float x =200.00;
float temp =0.0;
vector<float>temp1;
vector <float>temp2;

    for (int j =0; j< 1000; j++){
        for (int i=0; i<200; i++){
            if (user_review[i][j]>0){
                count1++;
            }
        }
        if (count1==0){temp = 0.0;}
        else { temp = log2(x/count1);}
        temp1.push_back(temp);
        count1 =0;
        temp = 0.0;
    }

    for (int i = 0; i <200; i++){
        for (int j =0; j<1000; j++){
            if(user_review[i][j]> 0){temp = temp1[j];}
            else {temp =0.0;}
            temp2.push_back(temp);
        }
        idf.push_back(temp2);
        temp2.clear();
        temp =0.0;

    }
    for (int i =0; i < 200; i++){
        for (int j =0; j< 1000; j++){
            if (unbiased[i][j] !=0){
                temp= (unbiased[i][j]/1000) * temp1[j];
                }
             else {(temp =0.0);}
            temp2.push_back(temp);
    }
        tf_idf.push_back(temp2);
        temp2.clear();
        temp=0.0;
    }

    for (int i=0; i <200; i++){
        for (int j=0; j<1000; j++){
            temp = tf_idf[i][j]*tf_idf[i][j]+ temp;
        }

        temp = sqrt(temp);
        length.push_back(temp);
        temp=0.0;
    }


}


void recon::calc_second(){

    float temp=0.0;
    vector<float>temp1;

    for(int i =0; i<200; i++){
        for (int j=0; j<1000; j++){
            temp = tf_idf[i][j]*tf_idf[user_number][user_number_rank]+temp;;

        }
       temp1.push_back(temp);
       temp =0.0;
    }

    for (int i=0; i< 200; i++){
        temp = temp1[i] / length[i]* length[user_number];
        cos_sim.push_back(temp);
        temp =0.0;

    }

}









