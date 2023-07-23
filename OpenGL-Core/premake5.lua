project "OpenGL-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    -- location "Generated"
    staticruntime "on"

    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")

    pchheader "glpch.hpp"
    pchsource "src/glpch.cpp"

    files {
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs {
        "src",
        "vendor/Glad/include",
        "vendor/GLFW/include",
        "vendor/glm/include",
        "vendor/imgui/include",
        "vendor/stb/include"
    }

    libdirs {
        "vendor/Glad/lib",
        "vendor/GLFW/lib",
        "vendor/imgui/lib"
    }

    links {
        "opengl32",
        "Glad",
        "imgui" -- already contains glfw3 (putting both gives lots of errors)
    }

    filter {"configurations:Debug"}
    buildoptions "/MDd" --compiler option for debug
    runtime "Debug"
    symbols "on" --generate debug symbols

    filter {"configurations:Release"}
    buildoptions "/MT"
    runtime "Release"
    optimize "on"