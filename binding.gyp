{
	'variables' : {
		'Rose_lib':'$(ROSE)\\lib\\x64_win64_vc14_md'
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
		"$(ROSE_INCLUDE)\\stpman",
		"$(ROSE_INCLUDE)\\stpman_arm",
		"$(ROSE_INCLUDE)\\stmodule",
		"$(ROSE_INCLUDE)\\stix",
		"$(ROSE_INCLUDE)\\stgl",
		"$(ROSE_INCLUDE)\\stixmesh",
		"$(ROSE_INCLUDE)\\stixsim",
		"$(ROSE_INCLUDE)\\stixctl"
		],
	    "conditions": [
		    ["OS == 'mac' ", {
			    "libraries": [
				    '<(Rose_lib)'+"\\libstncapt.a",
				    '<(Rose_lib)'+"\\libstixctl.a",
				    '<(Rose_lib)'+"\\libstpman_arm.a",
				    '<(Rose_lib)'+"\\libstmodule.a",
				    '<(Rose_lib)'+"\\libstpman_stixsim.a",
				    '<(Rose_lib)'+"\\libstpman_stixmesh.a",
				    '<(Rose_lib)'+"\\libstpman_stix.a",
				    '<(Rose_lib)'+"\\libstpman.a",
				    '<(Rose_lib)'+"\\libp28e2.a",
				    '<(Rose_lib)'+"\\librosemath.a",
				    '<(Rose_lib)'+"\\librose.a",
				    '<(Rose_lib)'+"\\libdtnurbsc.a",
				    '<(Rose_lib)'+"\\libvcf2c.a",
			    ]
		    }],
		    ["OS =='win' ", {
			    "libraries": [
				    '<(Rose_lib)'+"\\stgl.lib",
				    '<(Rose_lib)'+"\\stncapt.lib",
				    '<(Rose_lib)'+"\\stixctl.lib",
				    '<(Rose_lib)'+"\\stpman_arm.lib",
				    '<(Rose_lib)'+"\\stmodule.lib",
				    '<(Rose_lib)'+"\\stpman_stixsim.lib",
				    '<(Rose_lib)'+"\\stpman_stixmesh.lib",
				    '<(Rose_lib)'+"\\stpman_stix.lib",
				    '<(Rose_lib)'+"\\stpman.lib",
				    '<(Rose_lib)'+"\\p28e2.lib",
				    '<(Rose_lib)'+"\\rosemath.lib",
				    '<(Rose_lib)'+"\\rose.lib",
				    '<(Rose_lib)'+"\\dtnurbsc.lib",
				    '<(Rose_lib)'+"\\vcf2c.lib",
				    "opengl32.lib",
				    "glu32.lib",
				    "msvcrt.lib"
			    ]

		    }]
	    ]
	}]
}
