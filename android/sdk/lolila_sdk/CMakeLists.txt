# Sets the minimum version of CMake required to build the native
# library. You should either keep the default value or only pass a
# value of 3.4.0 or lower.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds it for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             # Associated headers in the same location as their source
             # file are automatically included.
             src/main/cpp/native-lib.cpp
             src/main/cpp/RenderApi.cpp
             src/main/cpp/base/geometry/Vector.cpp
             src/main/cpp/base/geometry/Line.cpp
             src/main/cpp/base/geometry/Ray.cpp
             src/main/cpp/base/geometry/LineDistance.cpp
             src/main/cpp/base/math/Matrix.cpp
             src/main/cpp/base/math/Fraction.cpp
             src/main/cpp/base/math/TMatrix.hpp
             src/main/cpp/base/math/FractionOutputAdapter.hpp
             src/main/cpp/base/math/FloatOutputAdapter.hpp
             src/main/cpp/base/utils/LogQueue.cpp
             src/main/cpp/base/utils/FloatUtils.cpp
             src/main/cpp/base/utils/GLUtils.cpp
             src/main/cpp/base/utils/esTransform.c
             src/main/cpp/base/utils/stb_image_wrap.cpp
             src/main/cpp/base/utils/Simple2DTexture.cpp
             src/main/cpp/base/utils/VBOHelper.cpp
             src/main/cpp/base/geometry/Plane.cpp
             src/main/cpp/base/geometry/PlaneIntersection.cpp
             src/main/cpp/base/geometry/ViewFrustum.cpp
             src/main/cpp/base/geometry/Projections.cpp
             src/main/cpp/base/transforms/MVPTransform.cpp
             src/main/cpp/base/transforms/Rotation.cpp
             src/main/cpp/base/transforms/Translate.cpp
             src/main/cpp/base/transforms/Camera.cpp
             src/main/cpp/base/transforms/Scaling.cpp
             src/main/cpp/shapes/AbstractShapeVertex.cpp
             src/main/cpp/shapes/ShaderProgram.cpp
             src/main/cpp/shapes/SimpleShader.cpp
             src/main/cpp/shapes/AbstractVAO.cpp
             src/main/cpp/shapes/SimpleVAO.cpp
             )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because system libraries are included in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib


              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in the
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       native-lib



                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       android
                       EGL
                       GLESv3 )
