{
	'variables' : {
		'Rose_lib':'$(ROSE)/lib'
	},
	"targets": [
        {
            "target_name": "StepNC",
            "sources": [ 
		"./src/nodeStepNC.cpp",
		"./src/nodeUtils.h",
		"./src/nodeUtils.cpp",
		"./src/nodeMachineState.h",
		"./src/nodeMachineState.cpp",
		"./src/nodeFinder.h",
		"./src/nodeFinder.cpp",
		"./src/nodeAptStepMaker.h",
		"./src/nodeAptStepMaker.cpp",
		"./src/nodeTolerance.h",
		"./src/nodeTolerance.cpp",
		],
	    "include_dirs": [
		"<!(node -e \"require('nan')\")",
		"$(ROSE_INCLUDE)",
		"$(ROSE_INCLUDE)/stpman",
		"$(ROSE_INCLUDE)/stpman_arm",
		"$(ROSE_INCLUDE)/stmodule",
		"$(ROSE_INCLUDE)/stix",
		"$(ROSE_INCLUDE)/stgl",
		"$(ROSE_INCLUDE)/stixmesh",
		"$(ROSE_INCLUDE)/stixsim",
		"$(ROSE_INCLUDE)/stixctl"
		],
	    "conditions": [
		    ["OS == 'mac' ", {
			    "libraries": [
				    '<(Rose_lib)'+"/macosx_all_clang/libstncapt.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libstixctl.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libstpman_arm.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libstmodule.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libstpman_stixsim.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libstpman_stixmesh.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libstpman_stix.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libstpman.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libp28e2.a",
				    '<(Rose_lib)'+"/macosx_all_clang/librosemath.a",
				    '<(Rose_lib)'+"/macosx_all_clang/librose.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libdtnurbsc.a",
				    '<(Rose_lib)'+"/macosx_all_clang/libf2c.a",
			    ]
		    }],
		    ["OS =='win' ", {
			    "libraries": [
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\stgl.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\stncapt.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\stixctl.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\stpman_arm.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\stmodule.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\stpman_stixsim.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\stpman_stixmesh.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\stpman_stix.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\stpman.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\p28e2.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\rosemath.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\rose.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\dtnurbsc.lib",
				    '<(Rose_lib)'+"\\x65_win64_vc14_md\\vcf2c.lib",
				    "opengl32.lib",
				    "glu32.lib",
				    "msvcrt.lib"
			    ]

		    }]
	    ]
	}]
}
