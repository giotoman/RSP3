cmake_minimum_required(VERSION 3.14)
project(RSP3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(qhull)
include_directories(qhull/Structs)

add_executable(RSP3
        qhull/Structs/Mesh.hpp
        qhull/Structs/Plane.hpp
        qhull/Structs/Pool.hpp
        qhull/Structs/Ray.hpp
        qhull/Structs/Vector3.hpp
        qhull/Structs/VertexDataSource.hpp
        qhull/ConvexHull.hpp
        qhull/HalfEdgeMesh.hpp
        qhull/MathUtils.hpp
        qhull/QuickHull.cpp
        qhull/QuickHull.hpp
        qhull/Types.hpp
        rsp3/CrossValidator.cpp
        rsp3/CrossValidator.h
        rsp3/DataHandler.cpp
        rsp3/DataHandler.h
        rsp3/Fold.cpp
        rsp3/Fold.h
        rsp3/Fullset.cpp
        rsp3/Fullset.h
        main.cpp
        rsp3/MDF.cpp
        rsp3/MDF.h
        rsp3/Point.cpp
        rsp3/Point.h
        rsp3/Reductor.cpp
        rsp3/Reductor.h
        rsp3/Subset.cpp
        rsp3/Subset.h
        rsp3/RandomIterator.cpp
        rsp3/RandomIterator.h)
