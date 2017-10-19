{
	'variables' : {
		"conditions": [
            ["OS == 'linux' ", {
               'Rose_lib': '$(ROSE)/lib/linux_x86_64_gcc_3.4_pic/lib',
               'lib_ext': '.a'
            }],
			["OS == 'mac' ", {
				'Rose_lib':'$(ROSE)/lib/macosx_all_clang/lib',
				'lib_ext':'.a'
			}],
			["OS =='win' ", {
				'Rose_lib':'$(ROSE)/lib/x64_win64_vc14_md/',
				'lib_ext':'.lib'
			}]
		]
	},
	"targets": [
        {
		"target_name": "StepNode",
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
			"./src/nodeAdaptive.h",
			"./src/nodeAdaptive.cpp",
		],
		"include_dirs": [
			"<!(node -e \"require('nan')\")",
			"$(ROSE_INCLUDE)",
			"$(ROSE_INCLUDE)/stp_aim",
			"$(ROSE_INCLUDE)/stp_arm",
			"$(ROSE_INCLUDE)/stmodule",
			"$(ROSE_INCLUDE)/stix",
			"$(ROSE_INCLUDE)/stgl",
			"$(ROSE_INCLUDE)/stixmesh",
			"$(ROSE_INCLUDE)/stixsim",
			"$(ROSE_INCLUDE)/stixctl"
		],
		"libraries": [
			'<(Rose_lib)'+"stncapt"+'<(lib_ext)',
			'<(Rose_lib)'+"stixctl"+'<(lib_ext)',
			'<(Rose_lib)'+"stp_arm"+'<(lib_ext)',
			'<(Rose_lib)'+"stmodule"+'<(lib_ext)',
			'<(Rose_lib)'+"stixsim"+'<(lib_ext)',
			'<(Rose_lib)'+"stixmesh"+'<(lib_ext)',
			'<(Rose_lib)'+"stix"+'<(lib_ext)',
			'<(Rose_lib)'+"stp_aim"+'<(lib_ext)',
			'<(Rose_lib)'+"p28e2"+'<(lib_ext)',
			'<(Rose_lib)'+"rosemath"+'<(lib_ext)',
			'<(Rose_lib)'+"rose"+'<(lib_ext)',
			'<(Rose_lib)'+"dtnurbsc"+'<(lib_ext)',
		],
		"conditions": [
			['OS=="win"', {
				"libraries": [
					'<(Rose_lib)'+"vcf2c"+'<(lib_ext)',
					"opengl32.lib",
					"glu32.lib",
					"msvcrt.lib"
				],
				'configurations':{
					'Release': {
						'msvs_settings': {
							'VCCLCompilerTool':{
								'RuntimeLibrary': '2' # /MD
							}
						}
					}
				}
			}],
		["OS==\"mac\"",
			{
					"xcode_settings": {  
					    "OTHER_CPLUSPLUSFLAGS": [  
					      "-std=c++11"
					]}}],
			['OS!="win"', {
				"libraries": ['<(Rose_lib)'+"f2c"+'<(lib_ext)'],
				"cflags":["-std=c++11"]
			}],
			['OS=="linux"', {
				"libraries": [
					"-luuid"
				]
			}]
		]
	}]
}
