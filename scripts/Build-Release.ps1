# This script is just a template and has to be copied and modified per project
# This script should be called from .vscode/tasks.json with
#
#   scripts/Build-Release.ps1            - for Beta builds
#   scripts/Build-Release.ps1 Release    - for Release builds
#
# {
#     "label": "Build-Release",
#     "type": "shell",
#     "command": "scripts/Build-Release.ps1 Release",
#     "args": [],
#     "problemMatcher": [],
#     "group": "test"
# },
# {
#     "label": "Build-Beta",
#     "type": "shell",
#     "command": "scripts/Build-Release.ps1 ",
#     "args": [],
#     "problemMatcher": [],
#     "group": "test"
# }

# set product names, allows mapping of (devel) name in Project to a more consistent name in release
# $settings = scripts/OpenKNX-Build-Settings.ps1

# execute generic pre-build steps
lib/OGM-Common/scripts/setup/reusable/Build-Release-Preprocess.ps1 $args[0]
if (!$?) { exit 1 }

# build firmware based on generated headerfile 
# the following build steps are project specific and must be adopted accordingly
# see comment in Build-Step.ps1 for argument description


# Example call, the following 2 lines might be there multiple times for each firmware which should be built
../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_SOM_UP firmware_SOM_UP uf2
if (!$?) { exit 1 }

if ($args[0] -eq "Dev") {
../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_DEV_BOARD firmware_DEV_BOARD uf2
if (!$?) { exit 1 }
}

# # build firmware for PiPico-BCU-Connector
# ../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_PiPico_BCU_Connector firmware_PiPico_BCU_Connector uf2
# if (!$?) { exit 1 }

# build firmware based on generated headerfile for SAMD
# ../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_SAMD_v31 firmware-v31 bin
# if (!$?) { exit 1 }

# ../OGM-Common/scripts/setup/reusable/Build-Step.ps1 release_SAMD_v30 firmware-v30 bin
# if (!$?) { exit 1 }

# execute generic post-build steps
lib/OGM-Common/scripts/setup/reusable/Build-Release-Postprocess.ps1 $args[0]
if (!$?) { exit 1 }

if (Test-Path -Path release-collection -PathType Container) {
  Copy-Item release/* release-collection/
}