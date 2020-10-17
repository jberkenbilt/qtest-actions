FROM mcr.microsoft.com/windows/servercore:ltsc2019
RUN powershell iex(iwr -useb https://chocolatey.org/install.ps1)
RUN choco feature enable -n allowGlobalConfirmation
RUN choco install --no-progress msys2
RUN C:/tools/msys64/usr/bin/pacman -Sy --noconfirm make base-devel tar zip unzip
