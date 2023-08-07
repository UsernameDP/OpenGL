project "GLFW"
    kind "StaticLib"
    language "C++"
    location "Generated"
    staticruntime "on"

    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")

    files {
        "src/**.hpp",
        "src/**.cpp",
        "src/**.h",
        "src/**.c"
    }

    includedirs {
        "src",
        "include"
    }



    filter {"configurations:Debug"}
        buildoptions "/MTd" --compiler option for debug
        runtime "Debug"
        symbols "on" --generate debug symbols

    filter {"configurations:Release"}
        buildoptions "/MT"
        runtime "Release"
        optimize "on"

    --API KEYS : 
    --[[
    _GLFW_COCOA to use the Cocoa frameworks
    _GLFW_WIN32 to use the Win32 API
    _GLFW_X11 to use the X Window System
    _GLFW_WAYLAND to use the Wayland API (experimental and incomplete)
    _GLFW_OSMESA to use the OSMesa API (headless and non-interactive)
    ]]
    filter {"system:windows"}
        defines {"_GLFW_WIN32"}
        