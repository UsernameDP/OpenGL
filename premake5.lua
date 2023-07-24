--OpenGL-Core
workspace "OpenGL-Core"
    architecture "x64"
    startproject "OpenGL-Core"

    configurations {
        "Debug",
        "Release"
    }

    filter {"configurations:Debug"}
        buildoptions "/MDd" --compiler option for debug
        runtime "Debug"
        symbols "on" --generate debug symbols

    filter {"configurations:Release"}
        buildoptions "/MT"
        runtime "Release"
        optimize "on"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 
include "OpenGL-Core"
-------------------------------------------------------------------------------

--OpenGL-Examples
workspace "OpenGL-Examples"
    architecture "x64"
    startproject "OpenGL-Examples"
    
    configurations {
        "Debug",
        "Release"
    }

    filter {"configurations:Debug"}
        buildoptions "/MDd" --compiler option for debug
        runtime "Debug"
        symbols "on" --generate debug symbols
        warnings "Extra"
        linkoptions {"/NODEFAULTLIB:library" }

    filter {"configurations:Release"}
        buildoptions "/MT"
        runtime "Release"
        warnings "Extra"
        optimize "on"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}" 

includeexternal "OpenGL-Core"
include "OpenGL-Examples"
-------------------------------------------------------------------------------

--Clean Command
function cleanProject(projectDir)
    print("Cleaning Project : " .. projectDir)
    print("Removing binaries")
    os.rmdir(projectDir .. "/bin")

    print("Removing intermediate binaries")
    os.rmdir(projectDir .. "/bin-int")

    print("Removing project files")
    os.rmdir(projectDir .. "/.vs")
    os.rmdir(projectDir .. "/Generated")
    os.remove("**.vcxproj")
    os.remove("**.vcxproj.filters")
    os.remove("**.vcxproj.user")

end

newaction {
    trigger = "clean",
    description = "Remove all binaries and intermediate binaries, and vs files.",
    execute = function()
        cleanProject("./OpenGL-Core")
        cleanProject("./OpenGL-Examples")
        print("Removing Solution Files")
        os.remove("**.sln")
    
        print("Deleting .vs directory")
        os.rmdir(".vs")
    
        print("Done")
    end
}
-------------------------------------------------------------------------------
