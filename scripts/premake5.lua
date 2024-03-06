PROJECT_GENERATOR_VERSION = 3

include("../garrysmod_common")
CreateWorkspace({name = "wwwwwh", abi_compatible = false, path = "../projects/"})
	CreateProject({serverside = false, source_path = "../src", manual_files = false})
		cppdialect "c++20"

		links { "d3d9", "dxgi", "d3dcompiler" }

		-- IncludeHelpersExtended()
		IncludeLuaShared()
		IncludeDetouring()
		-- IncludeScanning()
		IncludeSDKCommon()
		IncludeSDKTier0()
		IncludeSDKTier1()
		-- IncludeSDKTier2()
		-- IncludeSDKTier3()
		IncludeSDKMathlib()
		-- IncludeSDKRaytrace()
		-- IncludeSteamAPI()

		files({
			"../src/**.*"
		})
