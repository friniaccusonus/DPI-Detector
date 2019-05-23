echo "*** Signing x64 AAX project... ***" >> buildResultsImplicit.log
echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> AAX x64 SIGNING >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" >> buildResultsExplicit.log
::Rename unsigned aax component
rename "C:\Users\WindowsBuilder\Documents\DPI-Detector\Builds\VisualStudio2015\x64\Debug\AAX\DPI-Detector.aaxplugin\Contents\x64\DPI-Detector.aaxplugin" "DPI-Detector.aaxplugin.unsigned"
set signSrc="C:\Users\WindowsBuilder\Documents\DPI-Detector\Builds\VisualStudio2015\x64\Debug\AAX\DPI-Detector.aaxplugin\Contents\x64\DPI-Detector.aaxplugin.unsigned"
set signDest="C:\Users\WindowsBuilder\Documents\DPI-Detector\Builds\VisualStudio2015\x64\Debug\AAX\DPI-Detector.aaxplugin\Contents\x64\DPI-Detector.aaxplugin"
rem TestPlugin GUID
set guid="BF7E6750-212C-11E8-9280-005056875CC3"
wraptool sign --verbose --account accusonus --password Kastritsi41 --wcguid %guid% --signid "Developer ID Application: Accusonus Inc." --in %signSrc% --out %signDest% --keyfile C:/AccusonusProjects/DigiCertAccusonusCertificate.p12 -P Kastritsi3,14 >> buildResultsExplicit.log 2>&1

if errorlevel 1 (
  echo "Signing x64 AAX failed.Failure Reason Given is %errorlevel%." >> buildResultsImplicit.log
  set /a totalFails+=1
  call:printTotalFails
  exit /b %errorlevel%
) else (
  echo "Signing x64 AAX succeeded." >> buildResultsImplicit.log
)

del %signSrc%