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
        "../OpenGL-Core/%{IncludeDir.GLFW}",
		"../OpenGL-Core/%{IncludeDir.glad}",
		"../OpenGL-Core/%{IncludeDir.imgui}",
		"../OpenGL-Core/%{IncludeDir.glm}",
		"../OpenGL-Core/%{IncludeDir.stb}"
    }

    links {
        "OpenGL-Core"
    }

    filter {"configurations:Debug"}
        buildoptions "/MTd" --compiler option for debug
        runtime "Debug"
        symbols "on" --generate debug symbols

    filter {"configurations:Release"}
        buildoptions "/MT"
        runtime "Release"
        optimize "on"