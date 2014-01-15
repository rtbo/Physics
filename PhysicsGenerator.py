#! /usr/bin/env python

# Copyright (C) 2013-2014 Remi Thebault
# All rights reserved.
#
# This program and its source code are distributed under the
# terms of the BSD-style license, that can be found in the
# License.txt file at project root.


import sys
import os.path, time
from jinja2 import Environment, FileSystemLoader

PhysicsItems = [
	{
		'name' : 'acceleration',
		'units' : [
			{
				'name' : 'mps2',
				'wcharSeq' : R'm.s\u207B\u00B2'
			},
			{
				'name' : 'g',
				'factorToDefault' : 9.80665
			},
		],
		'defaultUnit' : 'mps2'
	},
	{
		'name' : 'area',
		'units' : [
			{
				'name' : 'm2',
				'wcharSeq' : R'm\u00B2'
			},
			{
				'name' : 'cm2',
				'wcharSeq' : R'cm\u00B2',
				'factorToDefault' : 0.0001
			},
			{
				'name' : 'mm2',
				'wcharSeq' : R'mm\u00B2',
				'factorToDefault' : 0.000001
			},
		],
		'defaultUnit' : 'm2'
	},
	{
		'name' : 'energy',
		'units' : [
			{
				'name' : 'J'
			},
			{
				'name' : 'cal',
				'factorToDefault' : 4.184
			},
			{
				'name' : 'kcal',
				'factorToDefault' : 4184.0
			},
		],
		'defaultUnit' : 'J'
	},
	{
		'name' : 'flow',
		'units' : [
			{
				'name' : 'lps',
				'wcharSeq' : R'l.s\u207B\u00B9'
			},
			{
				'name' : 'm3ps',
				'wcharSeq' : R'm\u00B3.s\u207B\u00B9',
				'factorToDefault' : 1000.0
			},
			{
				'name' : 'lpm',
				'factorToDefault' : 1/60.0
			},
			{
				'name' : 'lph',
				'factorToDefault' : 1/3600.0
			},
			{
				'name' : 'ccm',
				'factorToDefault' : 1/60000.0
			}
		],
		'defaultUnit' : 'lps'
	},
	{
		'name' : 'force',
		'units' : [
			{
				'name' : 'N',
			},
			{
				'name' : 'daN',
				'factorToDefault' : 10.0
			}
		],
		'defaultUnit' : 'N'
	},
	{
		'name' : 'length',
		'units' : [
			{
				'name' : 'm',
			},
			{
				'name' : 'cm',
				'factorToDefault' : 0.01
			},
			{
				'name' : 'mm',
				'factorToDefault' : 0.001
			},
			{
				'name' : 'km',
				'factorToDefault' : 1000.0
			}
		],
		'defaultUnit' : 'm'
	},
	{
		'name' : 'mass',
		'units' : [
			{
				'name' : 'kg'
			},
			{
				'name' : 'g',
				'litName' : 'gram',  # litName is used in Literals.hpp
				'factorToDefault' : 0.001
			},
			{
				'name' : 'ton',
				'litSeq' : 'ton',
				'factorToDefault' : 1000.0
			}
		],
		'defaultUnit' : 'kg'
	},
	{
		'name' : 'molecularMass',
		'units' : [
			{
				'name' : 'kgpmol',
				'wcharSeq' : R'kg.mol\u207B\u00B9'
			},
			{
				'name' : 'gpmol',
				'wcharSeq' : R'g.mol\u207B\u00B9',
				'factorToDefault' : 0.001
			}
		],
		'defaultUnit' : 'kgpmol'
	},
	{
		'name' : 'pressure',
		'units' : [
			{
				'name' : 'Pa'
			},
			{
				'name' : 'hPa',
				'factorToDefault' : 100.0
			},
			{
				'name' : 'kPa',
				'factorToDefault' : 1000.0
			},
			{
				'name' : 'PSI',
				'factorToDefault' : 6894.75729
			}
		],
		'defaultUnit' : 'Pa'
	},
	{
		'name' : 'quantity',
		'units' : [
			{
				'name' : 'mol'
			}
		],
		'defaultUnit' : 'mol'
	},
	{
		'name' : 'temperature',
		'units' : [
			{
				'name' : 'K'
			},
			{
				'name' : 'degC',
				'wcharSeq' : R'\u00B0C',
				'offsetToDefault' : 273.15
			},
			{
				'name' : 'degF',
				'wcharSeq' : R'\u00B0F',
				'offsetToDefault' : 459.67,
				'factorToDefault' : 5.0/9.0
			},
			{
				'name' : 'degR',
				'wcharSeq' : R'\u00B0R',
				'factorToDefault' : 5.0/9.0
			},
		],
		'defaultUnit' : 'K'
	},
	{
		'name' : 'time',
		'units' : [
			{
				'name' : 's'
			},
			{
				'name' : 'min',
				'factorToDefault' : 60.0
			},
			{
				'name' : 'hour',
				'factorToDefault' : 3600.0
			},
			{
				'name' : 'day',
				'factorToDefault' : 3600.0*24.0
			}
		],
		'defaultUnit' : 's'
	},
	{
		'name' : 'velocity',
		'units' : [
			{
				'name' : 'mps',
				'wcharSeq' : R'm.s\u207B\u00B9',
			},
			{
				'name' : 'kmph',
				'wcharSeq' : R'km/h',
				'factorToDefault' : 1000.0/3600.0
			}
		],
		'defaultUnit' : 'mps'
	},
	{
		'name' : 'volume',
		'units' : [
			{
				'name' : 'l'
			},
			{
				'name' : 'm3',
				'factorToDefault' : 1000.0
			},
			{
				'name' : 'gal',
				'factorToDefault' : 3.78541
			},
			{
				'name' : 'ml',
				'factorToDefault' : 0.001
			},
			{
				'name' : 'mm3',
				'wcharSeq' : R'mm\u00B3',
				'factorToDefault' : 0.000001
			}
		],
		'defaultUnit' : 'l'
	},
	{
		'name' : 'volumicMass',
		'units' : [
			{
				'name' : 'kgpm3',
				'wcharSeq' : R'kg.m\u207B\u00B3',
			},
			{
				'name' : 'kgpl',
				'wcharSeq' : R'kg.l\u207B\u00B9',
				'factorToDefault' : 1000.0
			}
		],
		'defaultUnit' : 'kgpm3'
	}
]



def fileMustBeWritten(templateFile, outFile):
	if not os.path.exists(outFile): return True
	if os.path.getmtime(__file__) > os.path.getmtime(outFile):
		return True
	if not os.path.exists(templateFile):
		raise ValueError(templateFile+" do not exist")
	return os.path.getmtime(templateFile) > os.path.getmtime(outFile)




def titleStr(s):
	# return a copy of the string s with first character uppercased,
	# and all other characters untouched
	if len(s) == 0:
		return s;
	ts = s[0].upper()
	if len(s) > 1:
		ts = ts + s[1:]
	return ts
		
		


if __name__ == '__main__':
	
	env = Environment(trim_blocks=True, loader=FileSystemLoader('templates'))


	globTemplates = [
		{
			"input": "FwdDecl.hpp.template",
			"output": "include/physics/FwdDecl.hpp",
		},
		{
			"input": "_IncludeAll.hpp.template",
			"output": "include/physics/_IncludeAll.hpp",
		},
		{
			"input": "Literals.hpp.template",
			"output": "include/physics/Literals.hpp",
		},
		{
			"input": "QPhysics/QPhysics.hpp.template",
			"output": "QPhysics/include/QPhysics.hpp",
		},
		{
			"input": "QPhysics/QPhysics.cpp.template",
			"output": "QPhysics/QPhysics.cpp",
		},
		{
			"input": "QPhysicsUI/src.pri.template",
			"output": "QPhysicsUI/src.pri",
		},
		{
			"input": "QPhysicsDesigner/QPhysicsDesignerPlugin.hpp.template",
			"output": "QPhysicsDesigner/QPhysicsDesignerPlugin.hpp",
		},
		{
			"input": "QPhysicsDesigner/QPhysicsDesignerPlugin.cpp.template",
			"output": "QPhysicsDesigner/QPhysicsDesignerPlugin.cpp",
		}
	]
	
	itemTemplates = [
		{
			"input": "Item.hpp.template",
			"output": "include/physics/{}.hpp",
		},
		{
			"input": "QPhysicsUI/QItemSpinBox.hpp.template",
			"output": "QPhysicsUI/include/Q{}SpinBox.hpp",
		},
		{
			"input": "QPhysicsUI/QItemSpinBox.cpp.template",
			"output": "QPhysicsUI/Q{}SpinBox.cpp",
		}
	]


	# completing items
	for pi in PhysicsItems:
		pi["titleName"] = titleStr(pi["name"])
		pi["titleDefaultUnit"] = titleStr(pi["defaultUnit"])
		for u in pi["units"]:
			u["titleName"] = titleStr(u["name"])
			if not "litName" in u:
				u["litName"] = u["name"]
			if not "wcharSeq" in u:
				u["wcharSeq"] = u["name"]


	inputFiles = []
	for gt in globTemplates:
		inputFiles.append(gt["output"])
	
	for it in itemTemplates:
		for pi in PhysicsItems:
			inputFiles.append(it["output"].format(pi['titleName']))
			

	if len(sys.argv) > 1 and sys.argv[1] == 'clear':
		# clear mode

		for inF in inputFiles:
			if os.path.exists(inF):
				print ("removing " + inF)
				os.remove(inF)
				

	elif len(sys.argv) > 1 and sys.argv[1] == 'ignorefile':
		
		ignoreFName = ".gitignore"
		if len(sys.argv) > 2: ignoreFName = sys.argv[2]
		
		if os.path.exists(ignoreFName):
			with open(ignoreFName) as ignoreF:
				content = ignoreF.readlines()
		else:
			content = []
		
		
		marker = "## Lines generated by PhysicsGenerator.py ##"
		
		# removing line between the 2 markers
		with open(ignoreFName, "w") as ignoreF:
			skipping = False
			for line in content:
				if marker in line:
					skipping = not skipping
				else:
					if not skipping: ignoreF.write(line)
					
		# updating file with the updated data
		with open(ignoreFName, "a") as ignoreF:
			ignoreF.write(marker+"\n")
			for inF in inputFiles:
				ignoreF.write(inF+"\n")
			ignoreF.write(marker+"\n")
			
		
	else:

		# starting generation
		for gt in globTemplates:
			if fileMustBeWritten(os.path.join("templates", gt["input"]), gt["output"]):
				tplt = env.get_template(gt["input"])
				content = tplt.render(items=PhysicsItems)
				print("writing " + gt["output"])
				with open(gt["output"], "w") as outF:
					outF.write(content)

		for it in itemTemplates:
			tplt = None
			for pi in PhysicsItems:
				outFName = it["output"].format(pi['titleName'])
				if fileMustBeWritten(os.path.join("templates", it["input"]), outFName):
					if tplt is None: tplt = env.get_template(it["input"])
					content = tplt.render(item=pi)
					print("writing " + outFName)
					with open(outFName, "w") as outF:
						outF.write(content)
			
	sys.exit(0)

