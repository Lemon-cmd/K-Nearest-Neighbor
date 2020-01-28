# ***K Nearest Neighbor in C++*** 
    
## ***What is KNN?*** ##    
    KNN is a supervised ML algorithm used for classification and regression. It is a simple and powerful algorithm that anyone can implement!       
    
    In KNN classification, it predicts a class based on the input's nearest neighbors and the mode of a class that occurs in the cluster neighbor.  
    The mode here is the predicted class!        
    
    In KNN regression, it predicts an output based on the input's nearest neighbors and taken the mean of their outputs (Y). 
 
 ## ***Dataset Provided*** ##
    The code has three dataset that it uses. The first two datasets are simple classification and regression problems. 
    The third dataset is the Iris dataset!
  
## ***How to use the code?*** ##      
    You can simply edit the main.cpp file to use a different dataset!      
    
    When initalizing the KNN class, you can pass in K and the type of calculation (i.e., mean, or mode).   
    Mean is used for regression while Mode is used for classification problems!     
    
    Choosing the K value is entirely up to you. There are some good rules of thumb out there for choosing K.   
    You should look for them or make a guess :).
    
***Please note that it is up to you to clean your data and choose an appropriate dataset for KNN!***    

## ***How was the code implement?*** ###
    The code involves around using a min heap. 
    
    Once the distance between the target and neighbors are calculated, the distance along with the Y value of the neighbor are passed onto a structure which is stored onto the heap. 
    The heap simply arranged the smallest distance to the bottom node (left -> right; highest -> smallest).   
    
    There are two heaps being used. One heap uses double value for Y and the other string value.   
    The reason why I used these two Heaps is because I wanted to make the code more portable and modular

    C++ is not dynamic like Python but it has the performance to make up for the larger quantity of code!   
    
    Once all neighbors are calculated, the heap is pop by K times and each structure is added to a vector.   
    
    If it is a classification problem, the mode of each structure's Y is calculated and return. 
    If it is a regression problem, the Y value of each structure are calculated as mean.    
    

