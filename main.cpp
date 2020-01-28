#include "knn.hpp"

int main()
{
    //Main Function
    vector <double> predict_mode;
    predict_mode.push_back(23);
    KNN knn_mode = KNN(3, "mode");
    knn_mode.loadData("mode_data.txt");
    knn_mode.predict(predict_mode);

    vector <double> predict_mean;
    predict_mean.push_back(30); predict_mean.push_back(64.4);
    KNN knn_mean = KNN(5, "mean");
    knn_mean.loadData("mean_data.txt");
    knn_mean.predict(predict_mean);

    vector <double> predict_mode_iris;
    predict_mode_iris.push_back(4.8); predict_mode_iris.push_back(3.2); 
    predict_mode_iris.push_back(1.2); predict_mode_iris.push_back(0.3);
    KNN iris = KNN(10, "mode");
    iris.loadData("iris.data");
    iris.predict(predict_mode_iris);

}
