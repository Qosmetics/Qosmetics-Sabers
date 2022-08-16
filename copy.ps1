param (
    [Parameter(Mandatory=$false)]
    [Switch]$release,
    [Parameter(Mandatory=$false)]
    [Switch]$log
)

& ./build.ps1
if (-not ($LastExitCode -eq 0)) {
    echo "build failed, not copying"
    exit
}

if ($release.IsPresent) {
    & adb push build/libqosmetics-sabers.so /sdcard/Android/data/com.beatgames.beatsaber/files/mods/libqosmetics-sabers.so
} else {
    & adb push build/debug/libqosmetics-sabers.so /sdcard/Android/data/com.beatgames.beatsaber/files/mods/libqosmetics-sabers.so
}

& adb shell am force-stop com.beatgames.beatsaber
& adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
Start-Sleep -Seconds 1.0
& adb shell am start com.beatgames.beatsaber/com.unity3d.player.UnityPlayerActivity
if ($log.IsPresent) {
    & ./log.ps1
}