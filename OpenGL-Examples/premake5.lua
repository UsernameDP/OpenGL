project "OpenGL-Examples"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    -- location "Generated"
    staticruntime "on"

    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")


    files {
        "assets/**",
        "src/**"
    }

    includedirs {
        "../OpenGL-Core/src",
        "../OpenGL-Core/vendor/Glad/include",
        "../OpenGL-Core/vendor/GLFW/include",
        "../OpenGL-Core/vendor/glm/include",
        "../OpenGL-Core/vendor/imgui/include"
    }

    links {
        "OpenGL-Core"
    }