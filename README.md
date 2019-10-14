# Abstract
Large volumes of training data introduce high computational cost in instance based classification. Data reduction algorithms aim to collect a small (condensing) set of representative training prototypes from the available training data. The Reduction by Space Partitioning (RSP3) algorithm is one of the most well-known prototype generation algorithms that repetitively divides the original training data into subgroups. This partitioning process searches the most distant instances in each subgroup. This is a costly process since it requires the calculation of all distances between the instances in each subgroup. We propose two new fast RSP3 variants, where the search of the most distant instances is accelerated by finding the convex hull of each subgroup. The first variant is called RSP3Q and searches the exact convex hull using Quick Hull algorithm and it is appropriate for datasets with limited dimensionality. The second variant is called RSP3A and approximates the convex hull by finding the Minimum Bounding Rectangle. It can be used for datasets of any dimensionality. The new variants are compared to each other and against RSP3 by executing experiments on sixteen datasets. The experimental study shows that the new variants involve a small computational cost to produce the condensing set without leading to less accurate classification and worse reduction rates.

# Datasets used in our experiments
Sample datasets for testing are included in the **datasets** folder. Tha table below lists all datasets 
that were included in the Thesis testing experiments. To test a dataset either include any number of
**test** sets in a directory or provide the full dataset and choose the desired number of folds to be created
with the appropriate command arguments listed in the examples below.

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

# Quick hull C++11 library

RSP3Q algorithm was implemented using **https://github.com/akuukka/quickhull**

> C++ implementation of the 3D QuickHull algorithm  
>
> by [akuukka](https://github.com/akuukka)

# Variables

`path` : *directory* or *file*  
`mdf` : max distance function to be used (**GRID**, **CONV**, **MH**, **QH**, **HH**)  
`folds` : fold count (**file only**)  

GRID: Conventional RSP3
CONV: Conventional K-NN without data reduction
MH: RSP3A (approximation of convex hull)
QH: RSP3Q (RSP3 with quick hull)
HH: HYBRID HULL (please do not use it)

# Flags

`-N` : apply normalization (0-1)  
`-IRR`: apply interquartile range ranking for attribute selection
`-NIRR`: apply both of the above  

# Attribute selection

Selection of *1, 2, ..., N* attributes of dataset (1-index based) seperated by **`,`**

# Examples

**Directory**

- Let directory `<path>/LIR` containing **5** test sets for cross validation and we desire only the **3** first attributes with *normalization* using `margin hull` as mdf.

**Command**: ./RSP3 *\<path\>*/LIR MH -Ν 1,2,3

**File**

- Let file `<path>/yeast.dat` and we desire **5** fold cross validation for all attributes with *normalization* and
*interquartile* range ranking applied using `quick hull` as mdf.

**Command**: ./RSP3 *\<path\>*/yeast.dat QH 5 -ΝIRR
