$autopkgFile = "package.nuspec"

# Get the ".autopkg.template" file, replace "@version" with the Appveyor version number, then save to the ".autopkg" file.
cat ($autopkgFile + ".template") | % { $_ -replace "@version", $env:appveyor_build_version } > $autopkgFile

.\nuget.exe pack package.nuspec

# Push all newly created .nupkg files as Appveyor artifacts for later deployment.
Get-ChildItem .\*.nupkg | % { Push-AppveyorArtifact $_.FullName -FileName $_.Name }
