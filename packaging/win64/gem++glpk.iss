; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MainAppName "GEM++"
#define MyAppName "GEM++GLPK"
#define MyAppVersion "2015-11-04"
#define MyAppPublisher "LITIS"
#define MyAppURL "litis-ilpiso.univ-rouen.fr"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{3A6B9FF5-8F3E-49C9-BA9C-148759395F45}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MainAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
InfoBeforeFile=..\..\src\plugins\GLPK\README
LicenseFile=..\..\src\plugins\GLPK\LICENSE
OutputBaseFilename=gem++glpk_{#MyAppVersion}
Compression=lzma
SolidCompression=yes
WizardImageFile=..\..\ressources\images\installer\background.bmp
WizardSmallImageFile=..\..\ressources\images\installer\icon.bmp
SetupIconFile=..\..\ressources\images\icon.ico

[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl"
Name: "fr"; MessagesFile: "compiler:Languages\French.isl"
Name: "ge"; MessagesFile: "compiler:Languages\German.isl"
Name: "it"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "sp"; MessagesFile: "compiler:Languages\Spanish.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "..\..\build\win64\release\GEM++GLPK.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\..\src\plugins\GLPK\glpk_4_56.dll"; DestDir: "{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
;Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
;Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
;Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent