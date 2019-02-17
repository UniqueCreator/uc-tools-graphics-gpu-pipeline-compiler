@rem nuget install packages.config -o packages
@rem nuget update packages.config -r packages

msbuild build.csproj /verbosity:diagnostic
