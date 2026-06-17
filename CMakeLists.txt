cmake_minimum_required(VERSION 3.22.1)
project(mobileapp)

set(NATIVE_APP_GLUE_DIR
    ${ANDROID_NDK}/sources/android/native_app_glue)

add_library(mobileapp SHARED
    app/src/main/cpp/main.cpp
    app/src/main/cpp/Shader/ShaderClass.cpp
    app/src/main/cpp/VAOClass/VAOClass.cpp
    app/src/main/cpp/VBOClass/VBOClass.cpp
    app/src/main/cpp/EBOClass/EBOClass.cpp
    app/src/main/cpp/SquareClass/SquareClass.cpp
    app/src/main/cpp/ScreenClass/ScreenClass.cpp
    app/src/main/cpp/ObjectClass/ObjectClass.cpp
    app/src/main/cpp/SceneClass/SceneClass.cpp
    app/src/main/cpp/HomeSceneClass/HomeSceneClass.cpp
    app/src/main/cpp/GameSceneClass/GameSceneClass.cpp
    app/src/main/cpp/ResourceManagerClass/ResourceManager.cpp
    app/src/main/cpp/MapClass/MapClass.cpp
    app/src/main/cpp/TextClass/TextClass.cpp
    app/src/main/cpp/CameraClass/CameraClass.cpp
    app/src/main/cpp/TileMapClass/TileMapClass.cpp
    app/src/main/cpp/libs/stb_image.cpp
    app/src/main/cpp/libs/stb_truetype.cpp
    ${NATIVE_APP_GLUE_DIR}/android_native_app_glue.c
)

target_include_directories(mobileapp PRIVATE
    ${NATIVE_APP_GLUE_DIR}
    app/src/main/cpp/Shader
    app/src/main/cpp/VAOClass
    app/src/main/cpp/VBOClass
    app/src/main/cpp/EBOClass
    app/src/main/cpp/libs 
)

target_link_libraries(mobileapp
    android
    log
    EGL
    GLESv3
)