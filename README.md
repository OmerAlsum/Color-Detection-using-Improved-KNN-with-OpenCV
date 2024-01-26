The goal of this project is improve the k-nearest neighbor algorithm. 

KNN is a popular classification algorithm in machine learning that classifies a new data point by considering the k-number of nearest neighbors surrounding it. However, the naive implementation of k-nearest neighbor requires computing the distance of the entire dataset to the unknown point, resulting in significant time and space consumption. To address this issue, a new implementation of k-nearest neighbor is proposed for datasets that have distinct clusters of condensed datapoints. The new implementation reduces the clusters of condensed datapoints into a single datapoint. The value k is improved from square root of n to 1; where n is the total number of points in the dataset and the 1 comes from the single closest datapoint to the unknown point. This new implementation significantly reduces the time and space complexity of the k-nearest neighbor algorithm.
To test the improved algorithm, the application of detecting color was chosen.

An implementation utilzing the Open CV library was added to the project. When an user places an object in the white box visible on the camera, the color of the is outputed.

The project was implemented in C++.
