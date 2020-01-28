#ifndef KNN_HPP
#define KNN_HPP
#include "dheap.hpp"
#include "sheap.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
#include <map>
#include <algorithm> //for find method
#include <stdlib.h>  //for converting string -> double
#include <vector>

class KNN
{
    /* K-Nearest Neighbor Algorithm */
    private: 
        vector < vector <string> > file;                    //file vector to hold initial values as string
        vector < vector <double> > X;                       //X vector
        vector <string> Y;                                  //Y vector
        int kn = 0;                                         //k
        vector < vector <double> > data;                    //data vector
        DHeap Dheap;                                        //Min Heap for y double values
        StrHeap Sheap;                                      //Min Heap for y string values
        int data_size;                                      //dataset size
        string type;                                        //type i.e: mean/mode

        const static double squareDiff (const double point1, const double point2)
        {
            /* Square Difference of 2 points */
            double distance = pow(point2 - point1, 2);
            return distance;
        }

        const static double labelMean(const vector<dedge*> &labels)
        {
            /* Mean of all Y's in labels */
            double sum = 0.0;
            for (auto &label : labels)
                sum += label->y;

            return sum / double(labels.size());
        }

        const static string labelMode(const vector<sedge*> &labels)
        {
            /* Mode of Y's in labels */
            map <string, int> set;
            //find all unique Y and put in map
            for (auto &label : labels)
            {
                string target = label->y;
                if (set.find(target) == set.end())
                {
                    int count = 0;
                    set[target] = count;
                }
                else
                {
                    set[target] ++;
                }
            }

            int max = 0.0;
            string mostY;

            //simple max function to find mode
            for (auto &y : set)
            {
                if (y.second > max)
                {
                    mostY = y.first;
                    max = y.second;
                }
            }
            return mostY;
        }

        void distMode(vector <double> &targets)
        {
            /* Calculate Distance between X's and targets */ 
            for (int row = 0; row < data_size; row ++)
            {
                double distance = 0.0;
                int row_size = X[row].size();

                for (int col = 0; col < row_size; col ++ )
                {
                    //find the sum of squared differences
                    distance += squareDiff(X[row][col], targets[col]);
                }
                //take the square root of the sum
                distance = sqrt(distance);    

                //create an edge and insert into the min heap                                 
                sedge* item = new sedge();
                item->distance = distance; item->y = Y[row]; 
                item->row = row;
                Sheap.insert(item);
            }
        }

        void distMean(vector <double> &targets)
        {
            /* Calculate Distance between X's and targets */ 
            
            for (int row = 0; row < data_size; row ++)
            {
                double distance = 0.0;
                int row_size = data[row].size();

                for (int col = 0; col < row_size - 1; col ++ )
                {
                    //find the sum of squared differences
                    distance += squareDiff(data[row][col], targets[col]);
                }
                //take the square root of the sum
                distance = sqrt(distance);    

                //create an edge and insert into the min heap                                 
                dedge* item = new dedge();
                item->distance = distance; item->y = data[row][row_size - 1]; 
                item->row = row;
                Dheap.insert(item);
            }
        }

        void outcomeMode()
        {
            /* Find outcome through mode */
            
            vector<sedge*> labels;
            // find # neighbors based on K value 
            for (int i = 0; i < kn; i ++)
            {
                labels.push_back(Sheap.pop());
            }

            // display neighbors
            cout << kn << " NEIGHBORS: " << endl;
            for (auto &neighbor : labels)
            {
                cout << "entry #: " << neighbor->row << " distance: " << neighbor->distance << " its value: "  << neighbor->y << endl;
            }

            //predict class based on Mode
            string mode = labelMode(labels);

            cout << "PREDICT OUTCOME BASED ON NEIGHBORS: " << mode <<  "\n" << endl;
        }

        void outcomeMean()
        {
            /* Find outcome through mean */
            vector<dedge*> labels;
            // find # neighbors based on K value 
            for (int i = 0; i < kn; i ++)
            {
                labels.push_back(Dheap.pop());
            }

            // display neighbors
            cout << "NEIGHBORS: " << endl;
            for (auto &neighbor : labels)
            {
                cout << "entry #: " << neighbor->row << " distance: " << neighbor->distance << " its value: "  << neighbor->y << endl;
            }

            //predict class based on mean
            double mean = labelMean(labels);

            cout << "PREDICT OUTCOME BASED ON NEIGHBORS: " << mean <<  "\n" << endl;
        }

        void load(const string filename, vector <vector <string> > &target)
        {
            /* Load File Method */

            // load file onto the file vector
            ifstream file(filename);    // grab file
            string line;                // a string for holding  current line

            // loop through the file
            while (getline(file, line))
            {
                //if the current line is not empty
                if (!line.empty())
                {
                    //split by comma
                    for (int c = 0; c < line.size(); c ++)
                    {
                        if (line[c] == ',') line[c] = ' ';
                    }
                    
                    vector<string> row;    
                    istringstream input(line);
                    
                    //split by space
                    for (string s; input >> s;)
                    {
                        row.push_back(s);  //append individual string onto the vector
                    }
                    //insert the row onto the data
                    target.push_back(row);
                }
            }
        }
        
        void logisticSplit()
        {
            /* Logistic Split */
            for (auto &row : file)
            {
                vector <double> x;
                for (int col = 0; col < row.size()-1; col ++)
                {
                    x.push_back(atof(row[col].c_str()));
                }
                X.push_back(x);
                Y.push_back(row[row.size()-1]);
            }
        }

        void loadData()
        {
            /* Load all values as double onto the data vector */
            for (auto &row : file)
            {
                vector <double> entry;
                for (auto &col : row)
                {
                    entry.push_back(atof(col.c_str()));
                }
                data.push_back(entry);
            }
        }
        
        public:  
            KNN(int k = 1, string knn_type = "mean")
            {
                /* set k and type */
                kn = k;
                type = knn_type;
            }

            void loadData(const string filename) 
            {
                /* Load Data */
                load(filename, file);

                if (type == "mean")
                {
                    loadData();
                    data_size = data.size();        // set data size
                }
                else
                {
                    logisticSplit();                // split data in X and Y where Y is string instead of double
                    data_size = X.size();           // set data size equal to X; aka # of entries
                }
            }

            void predict(vector <double> &targets)
            {
                /* Predict Method takes in a vector of X values for prediction*/
                for (auto &target : targets)
                {
                    cout << "TARGET: "  << target << " ";
                }
                cout << "\n";

                // return outcome based on calculation type
                if (type == "mode")
                {
                    /* if type == mode, use string for Y values */
                    Sheap = StrHeap();              //initialize heap
                    distMode(targets);              //calculate distance from target and points per entry (mode)
                    outcomeMode();                  //find mode
                }
                else
                {
                    /* if type == mean, use double for Y values */
                    Dheap = DHeap();                //initialize heap
                    distMean(targets);              //calculate distance from target and points per entry (mean)
                    outcomeMean();                  //find mean
                }   
            }
};
#endif