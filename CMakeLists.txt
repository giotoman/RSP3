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
        CrossValidator.cpp
        CrossValidator.h
        DataHandler.cpp
        DataHandler.h
        Fold.cpp
        Fold.h
        Fullset.cpp
        Fullset.h
        main.cpp
        MDF.cpp
        MDF.h
        Point.cpp
        Point.h
        Reductor.cpp
        Reductor.h
        Subset.cpp
        Subset.h)
