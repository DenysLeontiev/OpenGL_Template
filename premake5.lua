workspace "OpenGLTemplate"
    architecture "x86"
    startproject "OpenGLTemplate"

    configurations { "Debug", "Release"}
    platforms { "Win32" }

project "OpenGLTemplate"
    location "OpenGLTemplate"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir("%{wks.location}/build/bin/%{cfg.buildcfg}-%{cfg.architecture}")
    objdir("%{wks.location}/build/bin-int/%{cfg.buildcfg}-%{cfg.architecture}")

    debugdir ("%{wks.location}/OpenGLTemplate")

    files {
        "OpenGLTemplate/src/**.cpp",
        "OpenGLTemplate/src/**.h",
        "OpenGLTemplate/src/**.hpp",
        "OpenGLTemplate/src/**.glsl",
        "OpenGLTemplate/resources/**.*",
    }

    includedirs {
        "External/Assimp/include",
        "External/GLEW/include",
        "External/GLFW/include",
        "OpenGLTemplate/src/vendor",
        "OpenGLTemplate/src/vendor/imgui",
        "OpenGLTemplate/src/vendor/stb"
    }

    libdirs {
        "External/Assimp/lib",
        "External/GLFW/lib-vc2022"
    }

    links {
        "opengl32.lib",
        "glew32s.lib",
        "glfw3.lib"
    }

    defines {
        "WIN32",
        "_CONSOLE",
        "GLEW_STATIC"
    }

    postbuildcommands {
        '{COPY} "%{wks.location}/External/Assimp/bin/*.dll" "%{cfg.targetdir}"',
        '{COPYDIR} "%{wks.location}/OpenGLTemplate/resources" "%{cfg.targetdir}/resources"'
    }

    filter "platforms:Win32"
        architecture "x86"
        libdirs { "External/GLEW/lib/Release/Win32" }
    filter {}

    filter "configurations:Debug"
        defines { "_DEBUG" }
        symbols "On"
        links { "assimp-vc143-mtd.lib" }
    filter {}

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        links { "assimp-vc143-mt.lib" }
    filter{}