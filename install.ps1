$GDFolder = "C:\Program Files (x86)\Steam\steamapps\common\Geometry Dash\"
$LibcurlProxyDLL = "https://github.com/Marko2155/M21ModLoader/raw/refs/heads/main/libcurl/libcurl.dll"
$CrashLoggerDLL = "https://github.com/Marko2155/M21ModLoader/raw/refs/heads/main/libcurl/m21lcrashlog.dll"
If (Test-Path -Path "$($GDFolder)GeometryDash.exe") {
	Write-Host "GD is in default folder!"
} else {
	Write-Host "GD is not in default folder!"
	Write-Host "Folder where GD is located: "
	$GDFolder = Read-Host
	if (Test-Path -Path "$($GDFolder)GeometryDash.exe") {
		Write-Host "GD is in that folder!"
  		If (Test-Path -Path "$($GDFolder)actualcurl.dll") {
			Write-Host "M21ModLoader is already installed! Updating M21ModLoader instead!"
   			Remove-Item -Path "$($GDFolder)libcurl.dll"
      			Rename-Item -Path "$($GDFolder)actualcurl.dll" -NewName "libcurl.dll"
		} else {
			Write-Host "M21ModLoader is not installed!"
  		}
		Rename-Item -Path "$($GDFolder)libcurl.dll" -NewName "actualcurl.dll"
		Invoke-WebRequest $LibcurlProxyDLL -OutFile "$($GDFolder)libcurl.dll"
  		If (Test-Path -Path "$($GDFolder)mods") {
			Write-Host "M21ModLoader mods folder exists!"
		}  else {
  			Write-Host "M21ModLoader mods folder does not exist!"
			New-Item -Path $GDFolder -Name "mods" -ItemType "Directory"
   		}
		Invoke-WebRequest $CrashLoggerDLL -OutFile "$($GDFolder)m21lcrashlog.dll"
	} else {
		Write-Host "GD is not in that folder!"
		Write-Host "Folder where GD is located: "
		$GDFolder = Read-Host
	}
}
Write-Host "M21ModLoader has been installed!"
