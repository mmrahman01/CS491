CS491
Fall 2017
The University of Alabama

This assignment was on predictive algorithm by collaborative filtering. For the assignment we were given a dataset of 200 user with 1000 movies. The movies were ranked by the users whether users liked it or not. 1 being least liked and 5 being most liked. Our task was to get any individual user, pick any particular movie and see if the our calculation mathes with what that user ranked that particular movie. For example, if user 1 ranked movie 271 as 3. We were to use predictive analysis and see if our calculation matches with the users ranking.We used two different modeling analysis. For this project we have also used C++ (2017)

Running the program :

Use g++, add recon.cpp and recon.h with main.cpp (For the purpose of modularity a class function was used)

The program asked users to enter a user number from 1 -200 (really from 0 -199). 1 was added as a syntactic sugar). 
The program than shows the movies that particular user have ranked. It does not show the movies with ranking 0 (no decision can be made from 0 ranked movies) 

The program user than asked to enter a movie number from above list (however user may choose to ignore it and enter any number from 0 - 999 for movie number)

The program than uses two different models to predict that users ranking of the movie.


Model 1.

Model 1 of the prediction algorithm uses vector space modeling using collaborative filtering. Each users rankings are averaged, that average is subtracted from the ranked movies ( 0 ranked movies are ignored). This takes the bias of user ranking too highly or conservatively out of the equation. Using the vector space modeling a prediction for the user rank is achieved.

Model 2

Cosine similarity derived from the previous model is used. However instead of considering all the users, only users with similarity more than 0.001 is used. Just in case if the ranking is zero from these users (no one has ranked that particular movie) than users from the negative similarity are used. However the rankings of this users are reversed to calculate prediction...

Experimentation : We have done few other experiments to achieve known prediction, however all those prediction was generally contradictory. (So the theory that was taught in the class is really a dependable one). 

Result: For the most part the prediction matched the actual ranking. In few cases the ranking was off base due to rounding error. Sometimes the ranking were higher because of data used from all the users. 
These models however did make prediction for 0  ranked movies. If the user have ranked a movie 0 that means there is not enough data. However the program calculated what if the user did rank those movies. These rankings however need to be taken with a grain of salt, due to the fact there is really no data to match that prediction against.




































The first model used the vector space ranking in order to predict 