#include <random>
#include <vector>
#include <fstream>

using namespace std;


float func(float x, float y){

    return pow(x,3)+pow(y,3);
}

vector<float> up_bound {3,3};
vector<float> low_bound {-3,-3};


int dim= 2;
int NP = 10;
float cr = 0.90;  // crossover probability
float F5 = 0.50;  // Scaling factor

int Iteration_Number=20 ;


vector<vector<float>> parent_start;
vector<float> parent_val_start;


random_device rd;
default_random_engine eng(rd());


void start() {

    for (int j = 0; j < NP; j++ ){
        
        vector< float > x;

        for (int k = 0; k < dim; k++ ){

            uniform_real_distribution<> distr{low_bound[k], up_bound[k]};

            x.push_back(distr(eng));
        }
        parent_start.push_back(x);
        parent_val_start.push_back(func(x[0],x[1]));
    }
};

int find_index (int size, float target, vector<float> val_array ){

    int iterator;

    for (int q = 0 ; q < size; q++){

        if (val_array[q] == target){

            iterator = q;

            }
        }
        return iterator;
    };

int generation = 0;
vector<int> iteration;
vector<float> param1;
vector<float> param2;
vector<float> cost_func;


uniform_real_distribution<> distr_cr {0, 1};

int main(){

    start();


    for (int z = 0; z < Iteration_Number; z++){

        generation = generation+1;

                for (int i = 0; i < parent_start.size(); i++){

                    vector<float> trials;

                    int p1;
                    int p2;
                    int p_target;

                    do {

                        p1 = rand() % parent_start.size();
                        p2 = rand() % parent_start.size();
                        p_target = rand() % parent_start.size();


                    } while (p1 == i || p2 == p1 || p2 == i || p_target == i || p_target == p1 || p_target == p2);


                        for (int k = 0; k < dim; k++){

                            float rand_0_1 = distr_cr (eng);

                            if (rand_0_1 <= cr){

                                trials.push_back((parent_start[p_target])[k] + F5 * ((parent_start[p1])[k] - (parent_start[p2])[k]));
                            }

                            else {

                                trials.push_back((parent_start[i])[k]);
                            }
                        };

                        for (int s = 0; s < dim; s++){

                            if (trials[s] > up_bound[s]){

                                trials[s]=up_bound[s];
                            }

                            else if (trials[s] < low_bound[s]){

                                trials[s]=low_bound[s];
                            }

                            else if (low_bound[s] <= trials[s] <= up_bound[s]){

                                trials[s]=trials[s];
                            }
                        };

                        float child_val = func(trials[0],trials[1]);


                        if (child_val <= parent_val_start[i]){

                            parent_start[i] = trials;
                            parent_val_start[i] = child_val;
                        }
                };


                vector<float> soretd_val = parent_val_start;
                sort(soretd_val.begin(), soretd_val.end());

                int ind = find_index (parent_val_start.size(),soretd_val[0],parent_val_start);

                iteration.push_back(generation);
                param1.push_back(parent_start[ind][0]);
                param2.push_back(parent_start[ind][1]);
                cost_func.push_back(soretd_val[0]);
    }

    string filename("Results-CPP.txt");
    fstream file_out;
    file_out.open(filename, std::ios::out);

    for (int r=0 ; r < iteration.size(); r++){

        file_out << iteration[r] << "       " << param1[r]<< "       " << param2[r]<< "       " << cost_func[r]<< endl;     
 
    };

    file_out.close();

    return 0;
};