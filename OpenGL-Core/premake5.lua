project "OpenGL-Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    -- location "Generated"
    staticruntime "on"

    targetdir("bin/"..outputdir.."/%{prj.name}")
    objdir("bin-int/"..outputdir.."/%{prj.name}")

    pchheader "pch.hpp"
    pchsource "src/pch.cpp"

    files {
        "src/**.hpp",
        "src/**.cpp"
    }

    includedirs {
        "src",
        "%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb}"
    }

    links {
        "glad",
        "imgui",
        "GLFW",
        "opengl32.lib"
    }

    filter {"configurations:Debug"}
        buildoptions "/MTd" --compiler option for debug
        runtime "Debug"
        symbols "on" --generate debug symbols

    filter {"configurations:Release"}
        buildoptions "/MT"
        runtime "Release"
        optimize "on"

        defines {"VERSION_RELEASE"}