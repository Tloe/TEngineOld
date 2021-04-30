# escape=`

# Use the latest Windows Server Core image with .NET Framework 4.8.
FROM mcr.microsoft.com/windows/servercore:ltsc2019

# Restore the default Windows shell for correct batch processing.
SHELL ["cmd", "/S", "/C"]

# Download the Build Tools bootstrapper.
ADD https://aka.ms/vs/16/release/vs_buildtools.exe C:\TEMP\vs_buildtools.exe

# Install Build Tools with the Microsoft.VisualStudio.Workload.AzureBuildTools workload, excluding workloads and components with known issues.
#RUN C:\TEMP\vs_buildtools.exe --quiet --wait --norestart --nocache `
    # --installPath C:\BuildTools `
    # --add Microsoft.VisualStudio.Workload.AzureBuildTools `
    # --remove Microsoft.VisualStudio.Component.Windows10SDK.10240 `
    # --remove Microsoft.VisualStudio.Component.Windows10SDK.10586 `
    # --remove Microsoft.VisualStudio.Component.Windows10SDK.14393 `
    # --remove Microsoft.VisualStudio.Component.Windows81SDK `
 # || IF "%ERRORLEVEL%"=="3010" EXIT 0
RUN (C:\TEMP\vs_buildtools.exe --quiet --wait --norestart --nocache `
     --installPath C:\BuildTools `
     --add Microsoft.Component.MSBuild `
     --add Microsoft.VisualStudio.Component.VC.CMake.Project `
     --add Microsoft.VisualStudio.Workload.CoreEditor || `
  IF "%ERRORLEVEL%"=="3010" EXIT 0) && `
  @"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "[System.Net.ServicePointManager]::SecurityProtocol = 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))" && `
  SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin" && `
  choco install -y visualstudio2019-workload-vctools python cmake && `
  SET "PATH=%PATH%;C:\Python39;C:\Python39\Scripts;C:\Program Files\CMake\bin" && `
  curl https://bootstrap.pypa.io/get-pip.py -o get-pip.py && `
  py get-pip.py && `
  pip install conan

# Define the entry point for the docker container.
# This entry point starts the developer command prompt and launches the PowerShell shell.
ENTRYPOINT ["C:\\BuildTools\\Common7\\Tools\\VsDevCmd.bat", "&&", "powershell.exe", "-NoLogo", "-ExecutionPolicy", "Bypass"]
