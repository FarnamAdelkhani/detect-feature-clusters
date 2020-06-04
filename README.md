#### Detecting Feature Clusters

**Problem:**

Given a panospheric image with features detected, we want to ignore outliers and detect clusters which indicate areas likely containing objects. We will receive and utilize a θ value for each feature while completely ignoring the r value.

*Note:* Ignoring the r value all-together means that we could be detecting separate objects, spread away from each-other vertically, as a single cluster.

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

