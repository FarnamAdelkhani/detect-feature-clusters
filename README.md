### Detecting Feature Clusters

**Problem:**

Given a panospheric image with features detected, we want to ignore outliers and detect clusters which indicate areas likely containing objects. We will receive and utilize a θ value for each feature while completely ignoring the r value.

![panospheric_sample](https://i.imgur.com/LBTv6nR.jpg)

**Inputs:** Feature locations, K, Initial Mean Values

**Process:** Detect groups of features as clusters

**Output: **The approximate center location of each cluster. Should be accurate to within 20 degrees.

------

**Dataset Analysis:** Let's see what simplifying assumptions we can make from visually inspecting our datasets. These plots were generated in GNUplot:

![](https://i.imgur.com/WkWi5CL.png)

**Assumptions:** 

- Datasets are always increasing.

- K values, indicating number of clusters, for each dataset are clearly seen.

- Clusters are tightly packed, a threshold of ~20 should be enough to detect the beginning of a new cluster as well as outliers.

- Average values for clusters can be visually confirmed to be roughly accurate.

  ------

  

**Approach:** First solution that comes to mind is utilizing k-means clustering.

K-means clustering allows us to locate groups of similar points within a dataset.

However, a faster and much less robust brute force method can also be applied. We will try using a maximum-difference threshold that will be tested for while parsing across the polar coordinate values in order to separate clusters. If two adjacent points are located within our indicated tolerance level (20-25 degrees), we can conclude that they belong to the same cluster.



**Analyzing this module's results:**

|            | Solution Provided      | Solution by this module              | Correct or Wrong?                                            |
| ---------- | ---------------------- | ------------------------------------ | ------------------------------------------------------------ |
| input0.txt | 76.2,179.4,342.6       | 78.0385,177.443,344.554              | **Correct**                                                  |
| input1.txt | 48.3,220.1,290.3       | 47.8818,213.154,291.973              | **Correct**                                                  |
| input2.txt | 61.5,189.1,286.5,359.5 | 2.95,60.8133,185.931,282.764,355.775 | There should be a cluster @ ~3 degrees. The answer provided must have missed that cluster. <br />**Correct** |
| input3.txt |                        | 6.35556,94.9846,165.473,324.875      | Appears to be **correct**                                    |
| input4.txt |                        | 109.627,188.971,251.869,322.462      | Appears to be **correct**                                    |

**Discussing Solution:**

​	My first thought when starting this problem was to use the K-means clustering method. K-means would provide a robust and precise solution. However, I realized that the problem may be seeking a more simple, naïve, and brute-force style of answer. I began by plotting all the input datasets with GnuPlot in order to have a clear means of seeing patterns that could be exploited. It was immediately clear that the upward trend, tightly packed clusters, distant outliers, clear thresholds, and predictable means could all be used to create a simple module. The script work by parsing the dataset and checking whether the next point is within a user specified threshold range. When the threshold is exceeded, if the cluster count is just 1 then it will be labeled as an outlier. If the threshold is exceeded and a new cluster begins to form, then the algorithm will begin to collect a running sum and point count once again. The function is straight forward, with ability to take in as input a .txt file with comma separated float values.

------

**Some extra questions:**

**Q:** Critique the problem statement and suggest ways it could be clarified in order to avoid surprises with the implementation. What assumptions did you make that helped you write your solution?

**A:** I don't think that the problem needs clarification since the intent was clearly stated to be a vague set of instructions which the user can play with.

**Q:** Critique this obstacle avoidance approach from a robotics perspective. What problems would you expect to find with this approach and how would you mitigate them? (Obviously this is a bit of a toy problem and a cluster of visual features doesn't necessarily mean an obstacle is there in the real world, but you may have other interesting comments here.)

**A:** Given that we are not concerning ourselves with the r value of the polar coordinates, the issue that would come up is having separate objects and the top and bottom of the field of view which would be interpreted as one large object to avoid. It may be safer to avoid the region entirely, but the robot could benefit from having greater insight into the precise location of objects.

**Q:** What is the asymptotic time complexity of your algorithm? Could another algorithm have lower time complexity?

**A:** This method of comparing points to find thresholds and cluster data is most like a bubble sort algorithm. However, given that we are not rearranging data, we are simply comparing points, this algorithm is surely learning towards a big-O notation of n. As is the best case scenario for bubble sort. I don't believe that the algorithm could have a lower time complexity in this style module since the leading points always need to be compared with the trailing value.