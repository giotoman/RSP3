# Thesis abstract

> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;In the ever evolving scientific field of data categorization, the nearest neighbors algorithm is a stable, efficient method. However, it has several weaknesses that deem it inappropriate in some cases of data sets. Its main drawbacks are: high cost of categorizing each object due to multiple calculations, high storage requirements, and dependence of the accuracy of the results on the quality of the training data. In order to address its weaknesses, several data reduction algorithms have been implemented, aiming at minimizing the processing burden of the categorizer without affecting its accuracy. The Reduction by Space Partitioning algorithm is one of the most well-known prototype generation algorithms for accelerating instance based categorists. RSP3 is based on a repetitive separation process of the original training set. As the criterion for the most subset will be divided first, RSP3 adopts the larger diameter criterion. That is, the subset with the largest diameter defined by the two most distant objects is divided first. The process continues until the resulting subsets are homogeneous, that is, they include objects of the same class. The search for the two most remote objects of each subset is a costly process, since it requires the calculation of all the distances between the objects of each sub-set. Thus, RSP3 has a high computational pre-processing cost. In the framework of the thesis, computational geometry algorithms will be studied to find the Convex Hull of each subset. Convex Hull is composed by the objects of the data set that define its contour. The motivation for studying these algorithms stems from the following observation: If these objects that define Convex Hull are found, searching for the most remote objects in each subset will be done quickly since it will not be necessary to calculate all possible distances to the subset but only all possible distances between the objects of Convex Hull. In the experimental part of the thesis, two Convex Hull algorithms will be implemented and incorporated into RSP3. It will also be investigated whether it is possible to use Convex Hull algorithms in multi-dimensional datasets. The new variants of RSP3 will be tested in 15 sets of real data categorization data and their speed will be compared to that of the "conventional" RSP3.

# Datasets
Sample datasets are included for testing in **datasets**

| NAME | ELEMENTS | ATTRIBUTES | CLASSES |
|:----:|:--------:|:----------:|:-------:|
|  BN  |   5300   |      2     |    2    |
|  EEG |   14980  |     14     |    2    |
|  KDD |  494020  |     40     |    23   |
|  LIR |   20000  |     16     |    26   |
|  LS  |   6435   |     36     |    7    |
|  MGT |   19020  |     11     |    2    |
|  PD  |   10992  |     16     |    10   |
|  PH  |   5404   |      5     |    2    |
|  RNG |   7400   |     20     |    2    |
|  SG  |   2310   |     19     |    7    |
|  SH  |   58000  |      9     |    7    |
|  TN  |   7400   |     20     |    2    |
|  TXR |   5500   |     40     |    11   |
|  WF  |   5000   |     21     |    3    |
|  WQW |   4898   |     11     |    11   |
|  YST |   1484   |      8     |    10   |

# Variables

`path` : *directory* or *file*  
`mdf` : max distance function to be used (**GRID**, **CONV**, **MH**, **QH**, **HH**)  
`folds` : fold count (**file only**)  

# Flags

`-N` : apply normalization (0-1)  
`-IRR`: apply interquartile range ranking  
`-NIRR`: apply both of the above  

# Attribute selection

Selection of *1, 2, ..., N* attributes of dataset (1-index based) seperated by **`,`**

# Examples

**Directory**

- Let directory `<path>/LIR` containing **5** test sets for cross validation and we desire only the **3** first attributes with *normalization* using `margin hull` as mdf.

**Command**: ./RSP3 **\<path\>**/LIR MH -Ν 1,2,3

**File**

- Let file `<path>/yeast.dat` and we desire **5** fold cross validation for all attributes with *normalization* and
*interquartile* range ranking applied using `quick hull` as mdf.

**Command**: ./RSP3 **\<path\>**/yeast.dat QH 5 -ΝIRR
